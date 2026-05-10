#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Storage
{
private:
    T data[100];
    int count;

public:
    Storage() { count = 0; }

    bool add(const T& item);
    bool removeID(int id);
    T* findID(int id);

    T* getData() { return data; }
    int size() const { return count; }
};

template <typename T>
bool Storage<T>::add(const T& item) 
{
    if (count >= 100) 
        return false;
    
    data[count++] = item;
    return true;
}

template <typename T>
bool Storage<T>::removeID(int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (data[i].getID() == id) 
        {
            for (int j = i; j < count - 1; j++)
            {
                data[j] = data[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

template <typename T>
T* Storage<T>::findID(int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (data[i].getID() == id)
            return &data[i];
    }
    return nullptr;
}
