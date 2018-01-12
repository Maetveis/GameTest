#ifndef DYNAMIC_AABB_TREEE_H
#define DYNAMIC_AABB_TREEE_H

#include "AABB.h"

#include <stack>
#include <iostream>

#define null_node -1
#define aabb_extension 0.1d
#define aabb_multiplier 2.0d

class DynamicAABBTree
{
public:
	DynamicAABBTree();
	~DynamicAABBTree() = default;
	
	int CreateProxy(const AABB& aabb, void* userdata);
	void DestroyProxy(int ProxyId);
	bool MoveProxy(int proxyId, const AABB& aabb, const Vector2& displacement);
	
	void* GetUserData(unsigned proxyId) const;
	
	const AABB& GetFatAABB(unsigned proxyId) const;
	
	template <typename T>
	void Query(T callback, const AABB& aabb) const;
protected:
private:
	struct Node
	{
		AABB aabb;
		
		int left;
		int right;
		int height;
		
		void* userData;
		
		bool IsLeaf() const
		{
			return left == null_node;
		}
		
		union
		{
			int next;
			int parent;
		};
	};
	
	class NodePool
	{
	public:
		NodePool(const unsigned capacity) :
			freeList(0),
			nodeCapacity(capacity)
		{
			nodes = new Node[capacity];
			for(unsigned i = 0; i < nodeCapacity - 1; ++i)
			{
				nodes[i].next = i + 1;
				nodes[i].height = -1;
			}
			nodes[nodeCapacity - 1].next = null_node;
		}
	
		int AllocateNode();
		void FreeNode(const unsigned node);
		
		inline Node& operator[](const unsigned index)
		{
			return nodes[index];
		}
		
		inline const Node& operator[](const unsigned index) const
		{
			return nodes[index];
		}
		
		inline unsigned Count() const
		{
			return nodeCount;
		}
		
		inline unsigned Capacity() const
		{
			return nodeCapacity;
		}
	protected:
	private:
		void Expand();
	
		int freeList;
		Node* nodes;
		unsigned nodeCount;
		unsigned nodeCapacity;
	};
	
	void InsertLeaf(int leaf);
	void FixTree(int index);
	unsigned FindBestSibling(int leaf) const;
	double ComputeCost(const int node, const double inheritanceCost, const AABB& leafAABB) const;
	void RemoveLeaf(int node);

	int Balance(int index);
	
	int root;
	NodePool nodes;
};

template <typename T>
inline void DynamicAABBTree::Query(T callback, const AABB& aabb) const
{
	std::stack<int> stack;
	stack.push(root);

	while(!stack.empty())
	{
		int nodeId = stack.top();
		stack.pop();
		
		if (nodeId == null_node)
		{
			continue;
		}

		const Node& node = nodes[nodeId];

		if (node.aabb.Overlaps(aabb))
		{
			if (node.IsLeaf())
			{
				bool proceed = callback(nodeId);
				if (!proceed)
				{
					return;
				}
			}
			else
			{
				stack.push(node.left);
				stack.push(node.right);
			}
		}
	}
}

inline void* DynamicAABBTree::GetUserData(unsigned proxyId) const
{
	return nodes[proxyId].userData;
}

inline const AABB& DynamicAABBTree::GetFatAABB(unsigned proxyId) const
{
	return nodes[proxyId].aabb;
}

#endif //DYNAMIC_AABB_TREEE_H