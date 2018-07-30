#ifndef _FC_RBT_ITERATOR_
#define _FC_RBT_ITERATOR_

#include "fc_tree_iterator_base.hpp"
#include "fc_rbt_node.hpp"
namespace fc{

template<typename T, typename Ref, typename Pointer>
struct _rbt_iterator:public _tree_iterator{
    typedef _rbt_iterator<T, T&, T*>                    iterator;
    typedef _rbt_iterator<T, Ref, Pointer>              self;
    typedef T&                                          reference;
    typedef T*                                          pointer;
    typedef T                                           value_type;
    typedef _rbt_node<T>*                               node;
    _rbt_iterator(){}
    _rbt_iterator(node ptr):_tree_iterator((_tree_node*)ptr){}
    _rbt_iterator(_tree_node* ptr):_tree_iterator(ptr){}
    bool operator==(const iterator& rsh){
        return base_ptr == rsh.base_ptr;
    }
    bool operator!=(const iterator& rsh){
        return base_ptr != rsh.base_ptr;
    }
    reference operator*() const{
        return ((node)base_ptr)->value;
    }
    pointer operator->() const{
        return &(operator*());
    }
    self& operator++(){
        increcement();
        return *this;
    }
    self operator++(int){
        self ret = *this;
        ++(*this);
        return ret;
    }
    self& operator--(){
        decrecement();
        return *this;
    }
    self operator--(int ){
        self ret = *this;
        --(*this);
        return ret;
    }
};
























}











#endif