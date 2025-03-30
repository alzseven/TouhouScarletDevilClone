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

    // auto GetActiveObjects() {
    //     return pool | std::views::filter([](const T& o){ return o.isActive; });
    // }
};

