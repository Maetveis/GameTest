#ifndef DYNAMIC_AABB_TREEE_H
#define DYNAMIC_AABB_TREEE_H

#define null_node -1

class DynamicAABBTree
{
public:
	DynamicAABBTree();
	~DynamicAABBTree();
	
	unsigned CreateProxy(const AABB& aabb, void* userdata);
	unsigned DestroyProxy(const AABB& aabb, void* userdata);
	bool MoveProxy(int proxyId, const AABB& aabb, const Vector2& displacement);
	
	void* GetUserData(unsigned proxyId);
	
	const AABB& GetFatAABB(unsigned proxyId);
	
	template <typename T>
	void Query(T* callback, const b2AABB& aabb) const;
protected:
private:
	struct Node
	{
		AABB aabb;
		
		int left;
		int right;
		int height;
		
		bool IsLeaf() const
		{
			return left == null_node;
		}
		
		union
		{
			int next;
			int parent;
		}
	};
	
	class NodePool
	{
	public:
		NodePool(const unsigned capacity) :
			nodeCapacity(capacity)
		{
			nodes = new Node[nodeCapacity];
			freeList = 0;
		}
	
		unsigned AllocateNode();
		void FreeNode(const unsigned node);
		
		inline Node& operator[](const unsigned index)
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
	void Fixtree(int index);
	unsigned FindBestSibling(int leaf) const;
	double ComputeCost(const int node, const double inheritanceCost, const& AABB leafAABB) const;
	void RemoveLeaf(int node);

	int Balance(int index);
	
	int root;
	unsigned path;
	NodePool nodes;
};

template <typename T>
void Query(T* callback, const b2AABB& aabb) const;

void* GetUserData(unsigned proxyId);

const AABB& GetFatAABB(unsigned proxyId);

#endif //DYNAMIC_AABB_TREEE_H