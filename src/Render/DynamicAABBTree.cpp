#include "DynamicAABBTree.h"

#include <algorithm>

DynamicAABBTree

	DynamicAABBTree();
	~DynamicAABBTree();
	
	unsigned CreateProxy(const AABB& aabb, void* userdata);
	unsigned DestroyProxy(const AABB& aabb, void* userdata);
	
	bool MoveProxy(int proxyId, const AABB& aabb, const Vector2& displacement);
	
unsigned DynamicAABBTree::NodePool::AllocateNode()
{
	if(freeList = null_node)
	{
		Expand();
	}
	
	int node = freeList;
	freeList = nodes[node].next;
	nodes[node].parent = null_node;
	nodes[node].left = null_node;
	nodes[node].right = null_node;
	nodes[node].height = 0;
	nodes[node]userData = nullptr;
	
	++nodeCount;
	return node;
}

inline unsigned DynamicAABBTree::NodePool::Expand()
{
	Node* newNodes = new Node[nodeCapacity * 2];
	for(unsigned i = 0; i < nodeCapacity; ++i)
	{
		newNode[i] = nodes[i];
	}
	
	delete nodes;
	nodes = newNodes;
	nodeCapacity *= 2;
	
	for(unsigned i = nodeCount; i < NodeCapacity - 1; ++i)
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
	if(root = null_node)
	{
		root = leaf;
		nodes[root].parent = null_node;
		return;
	}
	int sibling = FindBestSibling(leaf);
	
	int oldParent = nodes[sibling].parent;
	int newParent = nodes.AllocateNode();
	nodes[newParent].parent = oldParent;
	nodes[newParent].userdata = nullptr;
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
	
	FixTree(index);
}

inline void DynamicAABBTree::Fixtree(int index)
{
	// Walk back up the tree fixing heights and AABBs
	index = nodes[leaf].parent;
	while (index != null_node)
	{
		index = Balance(index);

		int left = nodes[index].left;
		int right = nodes[index].right;

		nodes[index].height = 1 + std::max(m_nodes[child1].height, m_nodes[child2].height);
		nodes[index].aabb.Combine(nodes[child1].aabb, nodes[child2].aabb);

		index = nodes[index].parent;
	}
}

inline unsigned DynamicAABBTree::FindBestSibling(const int leaf) const
{
	AABB leafAABB = nodes[leaf].aabb;
	int index = root;
	while(!nodes[index].isLeaf())
	{
		int left = nodes[index].left;
		int right = nodes[index].right;
		
		double area = nodes[index].GetPerimeter();
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

inline double DynamicAABBTree::ComputeCost(const int node, const double inheritanceCost, const& AABB leafAABB) const
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
		b2AABB aabb;
		aabb.Combine(leafAABB, nodes[node].aabb);
		double oldArea = nodes[node].aabb.GetPerimeter();
		double newArea = aabb.GetPerimeter();
		cost = (newArea - oldArea) + inheritanceCost;
	}
	return cost;
}

void DynamicAABBTree::RemoveLeaf(int node);

int DynamicAABBTree::Balance(int index);