#ifndef _FC_ALLOC_
#define _FC_ALLOC_

#include "_default_allocator.hpp"
#include "_mempoll_allocator.hpp"
#define THRESHOLD 128

namespace fc{


enum{
    _ALIGN = 8
};

template<typename T1, typename T2>//construct 的时候不需要迭代器
inline void construct(T1* ptr, T2& value){
    // printf("im in construct %p\n", ptr);
    new (ptr) T1(value);
    // printf("im out construct\n");
}

template<typename T>
inline void destroy(T* ptr){
    ptr->~T();
}

template<typename Iter>
void destroy(Iter first, Iter last){
    for(Iter it = first; it != last; it++){
        destroy(&*it);
    }
}

template<typename Iter>
void copy(Iter dest, Iter src, size_t num){
    while(num--){
        construct(&*dest, *src);
        src++;
        dest++;
    }
}



template<typename T>
class allocator{
private:
    inline static size_t ALIGN(size_t size){
        return (size + _ALIGN - 1)& ~(_ALIGN - 1);
    }

public:
    typedef T* pointer;
    typedef T& reference;
    typedef T  type;
    static pointer allocate(size_t n){
        size_t tot_size = ALIGN(n * sizeof(type));
        if(tot_size > THRESHOLD){
            return static_cast<pointer>(_default_allocator::_allocate(tot_size));
        }
        return static_cast<pointer>(_mempoll_allocator::allocate(tot_size));
    }
    static inline pointer allocate(){
        return allocate(1);
    }
    static void deallocate(pointer ptr, size_t n){
        size_t tot_size = ALIGN(n * sizeof(type));
        if(tot_size > THRESHOLD){
            _default_allocator::_deallocate(ptr);
        }
        else _mempoll_allocator::deallocate(ptr, tot_size);
    }
    static inline void deallocate(pointer ptr){
        deallocate(ptr, 1);
    }
    static _default_allocator::func set_handler(_default_allocator::func ptr){
        return _default_allocator::set_handler(ptr);
    }
protected:

};







}



#endif