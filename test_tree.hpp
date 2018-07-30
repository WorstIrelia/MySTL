#ifndef _TEST_TREE_
#define _TEST_TREE_

#include "fc_rbt_iterator.hpp"
#include "fc_rbt_node.hpp"
#include "allocator.hpp"

namespace fc{


template<typename T, typename Alloc = allocator<T>>
struct test_tree{
//public:


    typedef _rbt_iterator<T, T&, T*>                            iterator;
    typedef _rbt_node<T>                                        node_value;
    typedef typename Alloc::template rebind<node_value>::other  alloc;
    typedef T                                                   value_type;
    typedef T*                                                  pointer;
    typedef T&                                                  reference;
    typedef _tree_node*                                         node_ptr;

    node_ptr head;
    test_tree(){
        head = alloc::allocate();
        head->father = head;
        head->lson = 0;
        head->rson = 0;
    }
    ~test_tree(){
        

    }
    const iterator begin(){
        iterator tmp = head;
        tmp.get_min();
        return tmp;
    }
    const iterator end(){
        return head;
    }
    void _insert(node_ptr& now, value_type &value){
        if(now == 0){
            node_ptr tmp = alloc::allocate();
            
            construct(&(((node_value*)tmp)->value), value);
            now = tmp;
            tmp->lson = 0;
            tmp->rson = 0;
        }
        if(((node_value*)now)->value > value){
            _insert(now->lson, value);
            now->lson->father = now;
            
        }
        else if(((node_value*)now)->value < value){
            _insert(now->rson, value);
            now->rson->father = now;
        }
        return ;
    }
    void insert(value_type& value){
        // printf("%d\n",value);
        if(head->lson == 0){
            node_ptr tmp = alloc::allocate();
            construct(&(((node_value*)tmp)->value), value);
            head->lson = tmp;
            head->rson = tmp;
            tmp->father = head;            
            tmp->lson  = 0;
            tmp->rson  = 0;
        }
        else _insert(head->lson, value);
    }







};



}






#endif