#pragma once
class CustomVector
{
	int size = 0;
	int capacity = 0;
	int* values = nullptr;

public:
	~CustomVector();
	int Length();
	void Add(int value);
	void Remove();
	int At(int index);
};

