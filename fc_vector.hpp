#ifndef _FC_VECTOR_
#define _FC_VECTOR_

#include "allocator.hpp"

namespace fc{
template<typename T, typename ALLOC = allocator<T> >
class vector{
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef T&          reference;
    typedef ALLOC       alloc;
    typedef pointer     iterator;
private:
    pointer start;
    pointer current_ptr;
    size_t leave_size;
    size_t now;
public:
    vector(){
        leave_size = 0;
        start = 0;
        current_ptr = 0;
        now = 0;
    }
    vector(size_t n){
        current_ptr = start = alloc::allocate(n);
        leave_size = n;
        now = n;
    }
    ~vector(){
        destroy(start, current_ptr);
        alloc::deallocate(start, current_ptr - start);
    }
    iterator begin(){
        return start;
    }
    iterator end(){
        return current_ptr ;
    }
    void push_back(T& value){
        // printf("push_back %d\n", value);
        if(!leave_size){
            expand();
        }
        // printf("im here\n");
        construct(current_ptr++, value);
        leave_size--;
        
    }
    void pop_back(){
        assert(current_ptr != start);
        current_ptr --;
        leave_size ++;
        destroy(current_ptr);
    }
    bool empty(){
        return current_ptr == start;
    }
    size_t size(){
        return current_ptr - start;
    }
    
private:
    void expand(){
        // printf("im in expand\n");
        size_t old = now;
        if(!now) now++;
        now <<= 1;
        pointer new_ptr = alloc::allocate(now);
        // printf("%p %p %p\n",new_ptr, start, current_ptr);
        size_t size = current_ptr - start;
        // printf("%ld\n", size);
        if(old){
            copy(new_ptr, start, size);
            destroy(start, current_ptr);
            alloc::deallocate(start, size);
        }
        start = new_ptr;
        leave_size = now - size;
        current_ptr = start + size;
        // printf("im ok\n");
    }






};



}
#endif