#ifndef _FC_RBT_ITERATOR_
#define _FC_RBT_ITERATOR_

#include "fc_tree_iterator_base.hpp"
#include "fc_tree_node_base.hpp"
#include "fc_rbt_node.hpp"
namespace fc{

template<typename T, typename Ref, typename Pointer>
class _rbt_iterator:public _tree_iterator{
public:
    typedef _rbt_iterator<T, T&, T*>                    iterator;
    typedef _rbt_iterator<T, Ref, Pointer>              self;
    typedef T&                                          reference;
    typedef T*                                          pointer;
    typedef T                                           value_type;
    typedef _rbt_node<T>*                               rbt_node_ptr;
    typedef _tree_node*                                 tree_node_ptr;
public:    
    _rbt_iterator(){}
    _rbt_iterator(rbt_node_ptr ptr):_tree_iterator((tree_node_ptr)ptr){}
    _rbt_iterator(tree_node_ptr ptr):_tree_iterator(ptr){}
    ~_rbt_iterator(){}
    bool operator==(const iterator& rsh){
        return base_ptr == rsh.base_ptr;
    }
    bool operator!=(const iterator& rsh){
        return base_ptr != rsh.base_ptr;
    }
    reference operator*() const{
        return rbt_node_ptr(base_ptr)->value;
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
    self operator--(int){
        self ret = *this;
        --(*this);
        return ret;
    }
};
























}











#endif