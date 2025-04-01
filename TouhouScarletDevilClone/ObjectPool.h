// ObjectPool.h
#pragma once
#include <stack>
#include <unordered_set>

#include "config.h"

template<typename T>
class ObjectPool {
    std::vector<T> pool;
    stack<int> freeList;
    
public:
    ObjectPool() = default;
    ~ObjectPool() = default;

    void Init(int preAlloc = 1000);
    
    T* Allocate();

    void Release(T* obj);

    void Clear();


    vector<T*> GetActiveObjects();
};

template <typename T>
void ObjectPool<T>::Init(int preAlloc)
{
    pool.resize(preAlloc);
    for(int i=0; i<preAlloc; ++i) {
        // pool[i].isActive = false;
        freeList.push(i);
    }
}


template <typename T>
T* ObjectPool<T>::Allocate()
{
    if(freeList.empty()) {
        size_t newSize = pool.size() * 2;
        pool.resize(newSize);
        for(size_t i=pool.size()/2; i<newSize; ++i)
            freeList.push(i);
    }
        
    int index = freeList.top();
    freeList.pop();
    // pool[index].isActive = true;
    return &pool[index];
}

template <typename T>
void ObjectPool<T>::Release(T* obj)
{
    // obj->Reset();
    // obj->isActive = false;
    freeList.push(obj - &pool[0]);
}

template <typename T>
void ObjectPool<T>::Clear()
{
    pool.clear();
    while(!freeList.empty())
    {
        freeList.pop();
    }
}

template <typename T>
vector<T*> ObjectPool<T>::GetActiveObjects()
{
    std::vector<T*> result;
    unordered_set<int> freeSet;
    
    // Create temporary copy to preserve original freeList
    std::stack<int> tmpFree = freeList;
    
    // Convert stack to set for O(1) lookups
    while (!tmpFree.empty()) {
        freeSet.insert(tmpFree.top());
        tmpFree.pop();
    }
    
    // Check all pool indices
    for (int i = 0; i < pool.size(); ++i) {
        if (freeSet.find(i) == freeSet.end()) {
            result.push_back(&pool[i]);
        }
    }
    
    return result;
}