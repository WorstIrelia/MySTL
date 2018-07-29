#ifndef _FC_ALLOC_
#define _FC_ALLOC_

#include "_default_allocator.hpp"
#include "_mempoll_allocator.hpp"
#define THRESHOLD 128

namespace fc{


enum{
    _ALIGN = 8
};

template<typename T>
class allocator{
private:
    // static _default_allocator default_allocator;

    inline static size_t ALIGN(size_t size){
        return (size + _ALIGN - 1)& ~(_ALIGN - 1);
    }

public:
    typedef T* pointer;
    typedef T& reference;
    typedef T  type;
    static pointer allocate(size_t n){
        size_t tot_size = ALIGN(n * sizeof(type));
        //printf("%ld\n",tot_size);
        if(tot_size > THRESHOLD){
            return static_cast<pointer>(_default_allocator::_allocate(tot_size));
        }
        return static_cast<pointer>(_mempoll_allocator::allocate(tot_size));
    }
    static pointer allocate(){
        size_t tot_size = ALIGN(1 * sizeof(type));
        if(tot_size > THRESHOLD){
            return static_cast<pointer>(_default_allocator::_allocate(tot_size));
        }
        return static_cast<pointer>(_mempoll_allocator::allocate(tot_size));
    }
    static void deallocate(pointer ptr,size_t n){
        size_t tot_size = ALIGN(n * sizeof(type));
        if(tot_size > THRESHOLD){
            _default_allocator::_deallocate(ptr);
        }
        else _mempoll_allocator::deallocate(ptr, tot_size);
    }

    
    static _default_allocator::func set_handler(_default_allocator::func ptr){
        return _default_allocator::set_handler(ptr);
    }
    static void construct(){

    }
    static void deconstruct(){

    }
protected:

};







}



#endif