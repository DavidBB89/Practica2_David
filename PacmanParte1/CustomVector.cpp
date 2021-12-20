#include "CustomVector.h"

CustomVector::~CustomVector()
{
    delete[] values;
}

int CustomVector::Length()
{
    return size;
}

void CustomVector::Add(int value)
{
    if (values == nullptr) {
        capacity = 5;
        values = new int[capacity];
        values[0] = value;
        size = 1;
    }
    else {
        if (size <= capacity) {
            values[size] = value;
            size++;
        }
        else {
            int* lastValues = values;
            capacity += capacity/2;
            values = new int[capacity];
            for (size_t i = 0; i < size; i++)
            {
                values[i] = lastValues[i];
            }
            values[size] = value;
            size++;
            delete[] lastValues;
        }
    }
}

void CustomVector::Remove()
{
    size--;
}

int CustomVector::At(int index)
{
    if(index >= size)
        return 0;
    return values[index];
}
