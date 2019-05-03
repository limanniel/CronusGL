#include "LinkedList.h"



LinkedList::LinkedList()
{
	_nodeHead = CreateNode(nullptr); // Dummy head with no data
}


LinkedList::~LinkedList()
{
	DeleteList(_nodeHead);
}

LinkedList::Node* LinkedList::CreateNode(SceneObject* object)
{
	Node* newNode = new Node();
	newNode->object = object;
	newNode->next = nullptr;
	return newNode;
}

LinkedList::Node* LinkedList::GetNode(Node* node, int position)
{
	int count = 0;
	while (node != nullptr)
	{
		if (count == position)
		{
			return node;
		}
	count++;
	node = node->next;
	}
	// Node not found
	return nullptr;
}

LinkedList::Node* LinkedList::FindNode(Node* node, SceneObject* object)
{
	if (node->object == object)
	{
		return node;
	}

	node = node->next;

	if (node->next != nullptr)
	{
		FindNode(node, object);
	}

	// Node not found
	return nullptr;
}

LinkedList::Node* LinkedList::InsertNodeFirst(Node* node, Node* newNode)
{
	newNode->next = node;
	_ListSize++;
	return newNode;
}

void LinkedList::InsertNodeAfter(Node* node, Node* newNode)
{
	newNode->next = node->next;
	node->next = newNode;
	_ListSize++;
}

void LinkedList::DeleteNodeAfter(Node* node)
{
	Node* tempNode;
	if (node != nullptr && node->next != nullptr)
	{
		tempNode = node->next;
		node->next = tempNode->next;
		_ListSize--;
		delete tempNode;
	}
}


void LinkedList::DeleteList(Node* node)
{
	Node* tempNode;

	tempNode = node;
	node = node->next;
	delete tempNode;

	if (node->next != nullptr)
	{
		DeleteList(node);
	}
}
