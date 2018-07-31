#ifndef _FC_RBT_
#define _FC_RBT_

#include "allocator.hpp"
#include "fc_rbt_iterator.hpp"
#include "fc_rbt_node.hpp"


namespace fc{

enum{
    BLACK,
    RED
};


template< typename Key, typename Value, typename KeyofValue, typename Compare, typename Alloc = allocator<Value> >

class rb_tree{
public:
    typedef Value                                                           value_type;
    typedef Value*                                                          pointer;
    typedef Value&                                                          reference;
    typedef _rbt_iterator<value_type, reference, pointer>                   iterator;
    typedef _rbt_node<value_type>*                                          rbt_node_ptr;
    typedef _tree_node*                                                     tree_node_ptr;
    typedef typename Alloc::template rebind<_rbt_node<value_type>>::other   alloc;


private:
    rbt_node_ptr head;
    rbt_node_ptr _min;
    rbt_node_ptr _max;
public:
    rb_tree(){
        head = alloc::allocate();
        head->lson = head->rson = 0;
        head->father = head;
        head->size = 0;
    }
    ~rb_tree(){
        alloc::deallocate(head);
    }
    rbt_node_ptr get_node(reference value){//opt
        rbt_node_ptr ret = alloc::allocate();
        construct(&(ret->value), value);
        ret->lson = 0;
        ret->rson = 0;
        ret->size = 1;
        return ret;
    }
    static rbt_node_ptr& lson(rbt_node_ptr& now){
        return (rbt_node_ptr&)(now->lson);
    }
    static rbt_node_ptr& rson(rbt_node_ptr& now){
        return (rbt_node_ptr&)(now->rson);
    }
    static rbt_node_ptr& father(rbt_node_ptr& now){
        return (rbt_node_ptr&)(now->father);
    } 
    inline void get_size(rbt_node_ptr now){
        printf("im in get_size\n");
        now->size = std::max((lson(now) ? lson(now)->size : 0), (rson(now) ? rson(now)->size : 0)) + 1;
    }
    inline void AVL_r_rotate(rbt_node_ptr now){
        printf("im in r rotate\n");
        now->_do_r_rotate((tree_node_ptr)now);
        get_size(now);
        get_size(father(now));
        printf("im down\n");
    }
    inline void AVL_l_rotate(rbt_node_ptr now){
        now->_do_l_rotate((tree_node_ptr)now);
        // printf("%d %d %d\n",now->value, father(now)->value, rson(father(now))->value);
        get_size(now);
        get_size(father(now));
        printf("im ok\n");
    }
    inline void AVL_lr_rotate(rbt_node_ptr now){
        printf("im in lr\n");
        AVL_l_rotate(lson(now));
        AVL_r_rotate(now);
    }
    inline void AVL_rl_rotate(rbt_node_ptr now){
        printf("im in rl\n");
        AVL_r_rotate(rson(now));
        AVL_l_rotate(now);
    }

    iterator begin(){
        rbt_node_ptr tmp = head;
        while(lson(tmp)) tmp = lson(tmp);
        return tmp;
    }
    iterator end(){
        return head;
    }
    bool _maintate(rbt_node_ptr now){
        
        int lsize = lson(now)? lson(now)->size : 0;
        int rsize = rson(now)? rson(now)->size : 0;
        printf("%d %d\n",lsize, rsize);
        if(lsize - rsize > 1){
            rbt_node_ptr tmp = lson(now);
            int llsize = lson(tmp)? lson(tmp)->size : 0;
            int rrsize = rson(tmp)? rson(tmp)->size : 0;
            if(llsize > rrsize) {
                AVL_r_rotate(now);
            }
            else AVL_lr_rotate(now);
        }
        else if(rsize - lsize > 1){
            rbt_node_ptr tmp = rson(now);
            int llsize = lson(tmp)? lson(tmp)->size : 0;
            int rrsize = rson(tmp)? rson(tmp)->size : 0;
            if(rrsize > llsize) {
                AVL_l_rotate(now);
            }
            else AVL_rl_rotate(now);
        }
       
    }
    void _insert(rbt_node_ptr& now, reference value){
        // printf("im in _insert\n");
        if(now == 0){
            now = get_node(value);
            return ;
        }
        if(now->value < value){//for test
            bool flag = rson(now) == 0;
            _insert(rson(now), value);
            if(flag) father(rson(now)) = now;//不应该由调用者调整 设计的有问题
        }
        else if(value < now->value){
            bool flag = lson(now) == 0;
            _insert(lson(now), value);
            if(flag) father(lson(now)) = now;
        }
        get_size(now);
        _maintate(now);
    }
    void insert(reference value){
        // printf("im in insert\n");
        if(lson(head) == 0){
            rbt_node_ptr tmp = get_node(value);
            lson(head) = rson(head) = tmp;
            father(tmp) = head;
        }
        else{
            _insert(lson(head), value);
        }
        if(lson(head) != rson(head)) rson(head) = lson(head);
        head->size = lson(head)->size;
    }
    int dfs(rbt_node_ptr root){
        if(root == 0) return 0;
        printf("... %d\n", root->value);
        return std::max(dfs(rson(root)), dfs(lson(root))) + 1;
    }
    void pri(){
        printf("%d\n", dfs(lson(head)));
    }

};

























}












#endif