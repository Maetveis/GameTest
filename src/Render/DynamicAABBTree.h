#ifndef DYNAMIC_AABB_TREEE_H
#define DYNAMIC_AABB_TREEE_H

#include "AABB.h"

#define null_node -1
#define aabb_extension 0.1d
#define aabb_multiplier 2.0d

template<typename T>
class DynamicAABBTree
{
public:
	using ValueType = T;

	DynamicAABBTree();
	~DynamicAABBTree();
	
	int CreateProxy(const AABB& aabb, T* userData);
	void DestroyProxy(int ProxyId);
	bool MoveProxy(int proxyId, const AABB& aabb, const Vector2& displacement);
	
	T* GetUserData(unsigned proxyId) const;
	
	const AABB& GetFatAABB(unsigned proxyId) const;
	
	template <class K>
	void Query(K* callback, const AABB& aabb) const;
protected:
private:
	struct Node
	{
		AABB aabb;
		
		int left;
		int right;
		int height;
		
		T* userData;
		
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
	
	void Expand();
	int AllocateNode();
	void FreeNode(const unsigned node);
	
	void InsertLeaf(int leaf);
	void FixTree(int index);
	unsigned FindBestSibling(int leaf) const;
	double ComputeCost(const int node, const double inheritanceCost, const AABB& leafAABB) const;
	void RemoveLeaf(int node);

	int Balance(int index);
	
	int freeList;
	Node* nodes;
	unsigned nodeCount;
	unsigned nodeCapacity;
	
	int root;
};

//Implementation
#include "DynamicAABBTree.tpp"

#endif //DYNAMIC_AABB_TREEE_H