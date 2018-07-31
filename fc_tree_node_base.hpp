#ifndef _FC_TREE_NODE_BASE_
#define _FC_TREE_NODE_BASE_

#include "fc_tree_iterator_base.hpp"

namespace fc{


class _tree_node{
public:

    typedef _tree_node*  node_pointer;

public:

    node_pointer            lson;
    node_pointer            rson;
    node_pointer            father;

public:
    node_pointer get_min(node_pointer ptr){
        while(ptr->lson) ptr = ptr->lson;
        return ptr;
    }
    node_pointer get_max(node_pointer ptr){
        while(ptr->rson) ptr = ptr->rson;
        return ptr;
    }
    inline void _do_r_rotate(node_pointer root){
        if(root->father->lson == root){
            root->father->lson = root->lson;
        }
        else root->father->rson = root->lson;    
        root->lson->father = root->father;
        root->father = root->lson;
        if(root->lson->rson){
            root->lson->rson->father = root;
            node_pointer tmp = root->lson->rson;
            root->lson->rson = root;
            root->lson = tmp;
        }
        else{
            root->lson->rson = root;
            root->lson = 0;
        }
    }
    inline void _do_l_rotate(node_pointer root){
        printf("im do l rotate\n");
        if(root->father->lson == root){
            root->father->lson = root->rson;
        }
        else root->father->rson = root->rson;
        
        root->rson->father = root->father;
        root->father = root->rson;
        if(root->rson->lson){
            root->rson->lson->father = root;
            node_pointer tmp = root->rson->lson;
            root->rson->lson = root;
            root->rson = tmp;
        }
        else{
            root->rson->lson = root;
            root->rson = 0;
        }
        printf("im done \n");
    }
    inline void _do_lr_rotate(node_pointer root){
        _do_l_rotate(root->lson);
        _do_r_rotate(root);
    }
    inline void _do_rl_rotate(node_pointer root){
        _do_r_rotate(root->rson);
        _do_l_rotate(root);
    }

};



}










// keyofvalue





#endif