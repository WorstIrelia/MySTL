#ifndef _FC_LIST_ITERATOR_
#define _FC_LIST_ITERATOR_



namespace fc{
template<typename T>
struct _list_node{
    T value;
    _list_node<T>* next;
    _list_node<T>* prev;
};


template<typename T, typename Ref, typename Pointer>
class _list_iterator{
private:
    

public:
    typedef _list_iterator<T, T&, T*>           iterator;
    typedef _list_iterator<T, Ref, Pointer>     self;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;


public:
    _list_node<T>* ptr;  
    _list_iterator(){}
    _list_iterator(_list_node<T>* rsh){
        ptr = rsh;
    }
    bool operator==(const self& rsh){
        return ptr == rsh.ptr;
    }
    bool operator!=(const self& rsh){
        return ptr != rsh.ptr;
    }
    reference operator*(){
        return ptr->value;
    }
    pointer operator->(){
        return &operator*();
    }
    self& operator++(){
        ptr = ptr -> next;
        return *this;
    }
    self operator++(int){
        self ret = *this;
        ++(*this);
        return ret;
    }
    self& operator--(){
        ptr = ptr -> prev;
        return *this;
    }
    self operator--(int){
        self ret = *this;
        --(*this);
        return ret;
    }
};


}

#endif