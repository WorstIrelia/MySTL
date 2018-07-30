#ifndef _FC_RBT_NODE_
#define _FC_RBT_NODE_

#include "fc_tree_node_base.hpp"
namespace fc{

template<typename T>
struct _rbt_node:public _tree_node{
    T value;
    int color;
};



}











#endif