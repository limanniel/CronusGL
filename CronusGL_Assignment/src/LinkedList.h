#pragma once
#include "SceneObject.h"

class LinkedList
{
private:
	struct Node 
	{
		SceneObject* object;
		Node* next;
	};
	Node* _nodeHead{ nullptr };
	unsigned int _ListSize{ 0 };

public:
	LinkedList();
	~LinkedList();

	Node* CreateNode(SceneObject* object);
	Node* GetNode(Node* node, int position);
	Node* FindNode(Node* node, SceneObject* object);
	Node* InsertNodeFirst(Node* node, Node* newNode);
	void InsertNodeAfter(Node* node, Node* newNode);
	void DeleteNodeAfter(Node* node);
	void DeleteList(Node* node);

	inline Node* GetNodeHead() const { return _nodeHead; }
	inline int GetListSize() const { return _ListSize; }
};

