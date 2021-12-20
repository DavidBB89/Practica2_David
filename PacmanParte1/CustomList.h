#pragma once
class CustomList
{
	struct Node {
		Node* prev = nullptr;
		int value = 0;
		Node* next = nullptr;
	};
	Node* first;
	Node* last;
	int count;
public:
	CustomList();
	~CustomList();
	
	int Length();
	void Add(int value);
	void Remove(int index);
	int At(int index);
};

