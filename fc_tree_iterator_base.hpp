#ifndef _FC_TREE_ITERATOR_BASE_
#define _FC_TREE_ITERATOR_BASE_
#include "fc_tree_iterator_base.hpp"
#include "fc_tree_node_base.hpp"

namespace fc{
struct _tree_iterator{
    typedef _tree_node* pointer;
    pointer base_ptr;
    _tree_iterator(){}
    _tree_iterator(pointer ptr):base_ptr(ptr){}
    ~_tree_iterator(){}
    void get_min(){
        while(base_ptr->lson) base_ptr = base_ptr->lson;
    }
    void get_max(){
        while(base_ptr->rson) base_ptr = base_ptr->rson;
    }
    void increcement(){
        if(base_ptr->rson){
            base_ptr = base_ptr->rson;
            while(base_ptr->lson) base_ptr = base_ptr->lson;
        }
        else{
            while(base_ptr->father && base_ptr->father->rson == base_ptr) base_ptr = base_ptr->father;
            base_ptr = base_ptr->father;

        }
    }
    void decrecement(){
        if(base_ptr->lson){
            base_ptr = base_ptr->lson;
            while(base_ptr->rson) base_ptr = base_ptr->rson;
        }
        else{
            while(base_ptr->father && base_ptr->father->lson == base_ptr) base_ptr = base_ptr->father;
            base_ptr = base_ptr->father;
        }
    }


};


}








#endif