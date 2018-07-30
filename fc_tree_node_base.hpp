#ifndef _FC_TREE_NODE_BASE_
#define _FC_TREE_NODE_BASE_

namespace fc{

struct _tree_node{
    typedef _tree_node* node_pointer;
    node_pointer lson;
    node_pointer rson;
    node_pointer father;

};

}
















#endif