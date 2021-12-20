#include "CustomList.h"

CustomList::CustomList()
{
	count = 0;
	first = nullptr;
	last = nullptr;
}

CustomList::~CustomList()
{
	Node* element = last;
	for (int i = count - 1; i >= 0; i--)
	{
		Node* eliminate = element;
		element = element->prev;
		delete eliminate;
	}
}

int CustomList::Length()
{
	return count;
}

void CustomList::Add(int value)
{
	Node* node = new Node();
	node->value = value;
	if (first == nullptr) 
	{
		first = node;
		last = node;
	}
	else 
	{
		node->prev = last;
		node->prev->next = node;
		last = node;
	}
	count++;
}

void CustomList::Remove(int index)
{
	if (index >= count)
		return;
	Node* currentNode = first;
	for (size_t i = 0; i < index; i++) 
		currentNode = currentNode->next;
	if (index > 0) 
		currentNode->prev->next = currentNode->next;
	else 
		first = currentNode->next;
	if (index < count -1)
		currentNode->next->prev = currentNode->prev;
	else 
		last = currentNode->prev;
	
	delete currentNode;
}

int CustomList::At(int index)
{
	if (index >= count) return 0;
	Node* currentNode = first;
	if (index > count / 2) 
	{
		currentNode = last;
		for (int i = count - 1; i > index; i--)
		{
			currentNode = currentNode->prev;
		}
	}
	else 
	{
		for (size_t i = 0; i < index; i++)
		{
			currentNode = currentNode->next;
		}
	}
	return currentNode->value;
}
