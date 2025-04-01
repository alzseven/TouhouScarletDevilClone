// ObjectPool.h
#pragma once
#include "config.h"

template<typename T>
class ObjectPool {
    std::vector<T> pool;
    std::vector<T*> active;
    std::vector<T*> free;

public:
    void Init(int preAlloc = 1000);

    T* Allocate();

    void Release(T* obj);

    // void ReleaseMarked();
    
    void Clear();

    vector<T*> GetActive() { return active; }
};

template <typename T>
void ObjectPool<T>::Init(int preAlloc)
{
    pool.resize(preAlloc);
    free.reserve(preAlloc);
    for(int i=0; i<preAlloc; ++i) {
        free.push_back(&pool[i]);
    }
}

template <typename T>
T* ObjectPool<T>::Allocate() {
    if(free.empty()) {
        size_t oldSize = pool.size();
        pool.resize(oldSize * 2);
        for(size_t i=oldSize; i<pool.size(); ++i) {
            free.push_back(&pool[i]);
        }
    }
        
    T* obj = free.back();
    free.pop_back();
    active.push_back(obj);
    return obj;
}

template <typename T>
void ObjectPool<T>::Release(T* obj) {
    auto it = std::find(active.begin(), active.end(), obj);
    if(it != active.end()) {
        std::iter_swap(it, active.end()-1);
        active.pop_back();
        free.push_back(obj);
    }
}
//
// template <typename T>
// void ObjectPool<T>::ReleaseMarked()
// {
//     auto newEnd = std::remove_if(active.begin(), active.end(),
//         //TODO:
//         [](T* obj){ return obj->IsPendeingRelease(); });
//     
//     for(auto it = newEnd; it != active.end(); ++it) {
//         (*it)->Reset();
//         free.push(*it);
//     }
//     
//     active.erase(newEnd, active.end());
// }

template <typename T>
void ObjectPool<T>::Clear()
{
    free.clear();
    active.clear();
    pool.clear();
}