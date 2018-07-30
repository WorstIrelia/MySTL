#ifndef _FC_LIST_
#define _FC_LIST_
#include "fc_list_iterator.hpp"
#include "allocator.hpp"
namespace fc{



template<typename T, typename Alloc = allocator<_list_node<T>> >
class list{



public:
    typedef _list_iterator<T, T&, T*>           iterator;   
    typedef _list_node<T>*                      node;    
    typedef Alloc                               alloc;
    typedef T&                                  reference;
    typedef T*                                  pointer;
    typedef T                                   value_type;
private:
    iterator mark;
public:
    list(){
        mark.ptr = alloc::allocate();
        mark.ptr->next = mark.ptr;
        mark.ptr->prev = mark.ptr;
    }
    ~list(){
        destroy(begin(), end());
        node it = mark.ptr;
        do{
            node tmp = it->next;
            alloc::deallocate(tmp);
            it = tmp;
        }while(it != mark.ptr);
    }
    iterator begin(){
        return iterator(mark.ptr->next);
    }
    iterator end(){
        return mark;
    }
    void insert(iterator pos, T& value){
        iterator tmp;
        tmp.ptr = alloc::allocate();
        construct(&*tmp, value);
        tmp.ptr->next = pos.ptr;
        tmp.ptr->prev = pos.ptr->prev;
        pos.ptr->prev->next = tmp.ptr;
        pos.ptr->prev = tmp.ptr;
    }
    void erase(iterator pos){
        pos.ptr->prev->next = pos.ptr->next;
        pos.ptr->next->prev = pos.ptr->prev;
        destroy(&*pos);
        alloc::deallocate(pos.ptr);
    }  
    void push_back(T& value){
        insert(end(), value);
    }
    void pop_back(){
        erase(--end());
    }
    void push_front(T& value){
        insert(begin(), value);
    }
    void pop_front(){
        erase(begin());
    }
    reference front(){
        return *begin();
    }
    reference back(){
        return *(--end());
    }
    bool empty(){
        return mark.ptr->next == mark.ptr;
    }


};







}













#endif