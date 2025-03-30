// ObjectPool.h
#pragma once
#include <stack>

#include "config.h"

template<typename T>
class ObjectPool {
    std::vector<T> pool;
    stack<size_t> freeList;
    
public:
    ObjectPool() = default;
    ~ObjectPool() = default;

    void Init(size_t preAlloc = 1000);
    
    T* Allocate();

    void Release(T* obj);

    void Clear();
    // auto GetActiveObjects() {
    //     return pool | std::views::filter([](const T& o){ return o.isActive; });
    // }
};

template <typename T>
void ObjectPool<T>::Init(size_t preAlloc)
{
    pool.resize(preAlloc);
    for(size_t i=0; i<preAlloc; ++i) {
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
        
    size_t index = freeList.top();
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
