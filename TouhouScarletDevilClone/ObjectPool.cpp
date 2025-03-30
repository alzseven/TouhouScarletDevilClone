#include "ObjectPool.h"

template <typename T>
void ObjectPool<T>::Init(size_t preAlloc)
{
    pool.reserve(preAlloc);
    for(size_t i=0; i<preAlloc; ++i) {
        pool[i].isActive = false;
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
    pool[index].isActive = true;
    return &pool[index];
}

template <typename T>
void ObjectPool<T>::Release(T* obj)
{
    obj->Reset();
    obj->isActive = false;
    freeList.push(obj - &pool[0]);
}
