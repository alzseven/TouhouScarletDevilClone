#pragma once
#include <deque>  // vector 대신 deque 사용
#include <vector>

template<typename T>
class ObjectPool {
    std::deque<T> pool;
    std::vector<T*> active;
    std::vector<T*> free;
    std::vector<T*> updatedActive;

public:
    void Init(int preAlloc = 1000);
    T* Allocate();
    void Release(T* obj);
    void UpdateActive() { updatedActive = active; }
    void Clear();
    
    std::vector<T*>& GetActive() { return updatedActive; }
};

template <typename T>
void ObjectPool<T>::Init(int preAlloc) {
    pool.resize(preAlloc);
    free.reserve(preAlloc);
    for(auto& obj : pool) {
        free.push_back(&obj);
    }
}

template <typename T>
T* ObjectPool<T>::Allocate() {
    if(free.empty()) {
        const size_t newSize = pool.size() * 2;
        pool.resize(newSize);  // deque 사용으로 포인터 유지
        for(size_t i = pool.size() - newSize/2; i < newSize; ++i) {
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
template <typename T>
void ObjectPool<T>::Clear()
{
    free.clear();
    active.clear();
    pool.clear();
}