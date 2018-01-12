#include "DynamicAABBTree.h"

#include <algorithm>

DynamicAABBTree::DynamicAABBTree() :
	root(null_node),
	nodes(16)
{		
}
	
int DynamicAABBTree::CreateProxy(const AABB& aabb, void* userData)
{
	int proxyId = nodes.AllocateNode();

	// Fatten the aabb.
	Vector2 r(50, 50);
	nodes[proxyId].aabb.lowerBound = aabb.lowerBound - r;
	nodes[proxyId].aabb.upperBound = aabb.upperBound + r;
	nodes[proxyId].userData = userData;
	nodes[proxyId].height = 0;

	InsertLeaf(proxyId);

	return proxyId;
}
	
void DynamicAABBTree::DestroyProxy(int proxyId)
{
	RemoveLeaf(proxyId);
	nodes.FreeNode(proxyId);
}
	
bool DynamicAABBTree::MoveProxy(int proxyId, const AABB& aabb, const Vector2& displacement)
{
	if (nodes[proxyId].aabb.Contains(aabb))
	{
		return false;
	}

	RemoveLeaf(proxyId);

	// Extend AABB.
	AABB b = aabb;
	Vector2 r(50, 50);
	b.lowerBound = b.lowerBound - r;
	b.upperBound = b.upperBound + r;

	// Predict AABB displacement.
	Vector2 d = 10 * displacement;

	if (d.x < 0.0d)
	{
		b.lowerBound.x += d.x;
	}
	else
	{
		b.upperBound.x += d.x;
	}

	if (d.y < 0.0d)
	{
		b.lowerBound.y += d.y;
	}
	else
	{
		b.upperBound.y += d.y;
	}

	nodes[proxyId].aabb = b;

	InsertLeaf(proxyId);
	
	return true;
}
	
int DynamicAABBTree::NodePool::AllocateNode()
{
	if(freeList == null_node)
	{
		Expand();
	}
	
	int node = freeList;
	freeList = nodes[node].next;
	nodes[node].parent = null_node;
	nodes[node].left = null_node;
	nodes[node].right = null_node;
	nodes[node].height = 0;
	nodes[node].userData = nullptr;
	
	++nodeCount;
	return node;
}

inline void DynamicAABBTree::NodePool::Expand()
{
	Node* newNodes = new Node[nodeCapacity * 2];
	for(unsigned i = 0; i < nodeCount; ++i)
	{
		newNodes[i] = nodes[i];
	}
	
	delete nodes;
	nodes = newNodes;
	nodeCapacity *= 2;
	
	for(unsigned i = nodeCount; i < nodeCapacity - 1; ++i)
	{
		nodes[i].next = i + 1;
		nodes[i].height = -1;
	}
	nodes[nodeCapacity - 1].next = null_node;
	freeList = nodeCount;
}

void DynamicAABBTree::NodePool::FreeNode(const unsigned node)
{
	nodes[node].next = freeList;
	nodes[node].height = -1;
	freeList = node;
	--nodeCount;
}
	
void DynamicAABBTree::InsertLeaf(const int leaf)
{
	if(root == null_node)
	{
		root = leaf;
		nodes[root].parent = null_node;
		return;
	}
	int sibling = FindBestSibling(leaf);
	AABB leafAABB = nodes[leaf].aabb;
	
	int oldParent = nodes[sibling].parent;
	int newParent = nodes.AllocateNode();
	nodes[newParent].parent = oldParent;
	nodes[newParent].userData = nullptr;
	nodes[newParent].aabb.Combine(leafAABB, nodes[sibling].aabb);
	nodes[newParent].height = nodes[sibling].height + 1;
	
	if (oldParent != null_node)
	{
		// The sibling was not the root.
		if (nodes[oldParent].left == sibling)
		{
			nodes[oldParent].left = newParent;
		}
		else
		{
			nodes[oldParent].right = newParent;
		}

		nodes[newParent].left = sibling;
		nodes[newParent].right = leaf;
		nodes[sibling].parent = newParent;
		nodes[leaf].parent = newParent;
	}
	else
	{
		// The sibling was the root.
		nodes[newParent].left = sibling;
		nodes[newParent].right = leaf;
		nodes[sibling].parent = newParent;
		nodes[leaf].parent = newParent;
		root = newParent;
	}
	
	FixTree(nodes[leaf].parent);
}

inline void DynamicAABBTree::FixTree(int index)
{
	// Walk back up the tree fixing heights and AABBs
	while (index != null_node)
	{
		index = Balance(index);

		int left = nodes[index].left;
		int right = nodes[index].right;

		nodes[index].height = 1 + std::max(nodes[left].height, nodes[right].height);
		nodes[index].aabb.Combine(nodes[left].aabb, nodes[right].aabb);

		index = nodes[index].parent;
	}
}

inline unsigned DynamicAABBTree::FindBestSibling(const int leaf) const
{
	AABB leafAABB = nodes[leaf].aabb;
	int index = root;
	while(!nodes[index].IsLeaf())
	{
		int left = nodes[index].left;
		int right = nodes[index].right;
		
		double area = nodes[index].aabb.GetPerimeter();
		AABB combinedAABB;
		combinedAABB.Combine(nodes[index].aabb, leafAABB);
		double combinedArea = combinedAABB.GetPerimeter();
		
		double cost = 2.0d * combinedArea;
		double inheritanceCost = 2.0d * (combinedArea - area);
		
		double cost1 = ComputeCost(left, inheritanceCost, leafAABB);
		double cost2 = ComputeCost(right, inheritanceCost, leafAABB);
		
		if(cost < cost1 && cost < cost2)
		{
			break;
		}
		
		if(cost1 < cost2)
		{
			index = left;
		}
		else
		{
			index = right;
		}
	}
	return index;
} 

inline double DynamicAABBTree::ComputeCost(const int node, const double inheritanceCost, const AABB& leafAABB) const
{
	double cost;
	if (nodes[node].IsLeaf())
	{
		AABB aabb;
		aabb.Combine(leafAABB, nodes[node].aabb);
		cost = aabb.GetPerimeter() + inheritanceCost;
	}
	else
	{
		AABB aabb;
		aabb.Combine(leafAABB, nodes[node].aabb);
		double oldArea = nodes[node].aabb.GetPerimeter();
		double newArea = aabb.GetPerimeter();
		cost = (newArea - oldArea) + inheritanceCost;
	}
	return cost;
}

void DynamicAABBTree::RemoveLeaf(int leaf)
{
	if (leaf == root)
	{
		root = null_node;
		return;
	}

	int parent = nodes[leaf].parent;
	int grandParent = nodes[parent].parent;
	int sibling;
	if (nodes[parent].left == leaf)
	{
		sibling = nodes[parent].right;
	}
	else
	{
		sibling = nodes[parent].left;
	}

	if (grandParent != null_node)
	{
		// Destroy parent and connect sibling to grandParent.
		if (nodes[grandParent].left == parent)
		{
			nodes[grandParent].left = sibling;
		}
		else
		{
			nodes[grandParent].right = sibling;
		}
		nodes[sibling].parent = grandParent;
		nodes.FreeNode(parent);

		// Adjust ancestor bounds.
		FixTree(grandParent);
	}
	else
	{
		root = sibling;
		nodes[sibling].parent = null_node;
		nodes.FreeNode(parent);
	}
}

//If this is confusing its just AVL tree rotations in a single function
int DynamicAABBTree::Balance(int iA)
{
	Node& A = nodes[iA];
	if (A.IsLeaf() || A.height < 2)
	{
		return iA;
	}

	int iB = A.left;
	int iC = A.right;

	Node& B = nodes[iB];
	Node& C = nodes[iC];

	int balance = C.height - B.height;

	// Rotate C up
	if (balance > 1)
	{
		int iF = C.left;
		int iG = C.right;
		Node& F = nodes[iF];
		Node& G = nodes[iG];

		// Swap A and C
		C.left = iA;
		C.parent = A.parent;
		A.parent = iC;

		// A's old parent should point to C
		if (C.parent != null_node)
		{
			if (nodes[C.parent].left == iA)
			{
				nodes[C.parent].left = iC;
			}
			else
			{
				nodes[C.parent].right = iC;
			}
		}
		else
		{
			root = iC;
		}

		// Rotate
		if (F.height > G.height)
		{
			C.right = iF;
			A.right = iG;
			G.parent = iA;
			A.aabb.Combine(B.aabb, G.aabb);
			C.aabb.Combine(A.aabb, F.aabb);

			A.height = 1 + std::max(B.height, G.height);
			C.height = 1 + std::max(A.height, F.height);
		}
		else
		{
			C.right = iG;
			A.right = iF;
			F.parent = iA;
			A.aabb.Combine(B.aabb, F.aabb);
			C.aabb.Combine(A.aabb, G.aabb);

			A.height = 1 + std::max(B.height, F.height);
			C.height = 1 + std::max(A.height, G.height);
		}

		return iC;
	}
	
	// Rotate B up
	if (balance < -1)
	{
		int iD = B.left;
		int iE = B.right;
		Node& D = nodes[iD];
		Node& E = nodes[iE];

		// Swap A and B
		B.left = iA;
		B.parent = A.parent;
		A.parent = iB;

		// A's old parent should point to B
		if (B.parent != null_node)
		{
			if (nodes[B.parent].left == iA)
			{
				nodes[B.parent].left = iB;
			}
			else
			{
				nodes[B.parent].right = iB;
			}
		}
		else
		{
			root = iB;
		}

		// Rotate
		if (D.height > E.height)
		{
			B.right = iD;
			A.left = iE;
			E.parent = iA;
			A.aabb.Combine(C.aabb, E.aabb);
			B.aabb.Combine(A.aabb, D.aabb);

			A.height = 1 + std::max(C.height, E.height);
			B.height = 1 + std::max(A.height, D.height);
		}
		else
		{
			B.right = iE;
			A.left = iD;
			D.parent = iA;
			A.aabb.Combine(C.aabb, D.aabb);
			B.aabb.Combine(A.aabb, E.aabb);

			A.height = 1 + std::max(C.height, D.height);
			B.height = 1 + std::max(A.height, E.height);
		}

		return iB;
	}

	//If we get here A is balanced so we just return it
	return iA;
}