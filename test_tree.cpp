#include <bits/stdc++.h>

// #include "test_tree.hpp"
#include "fc_tree_iterator_base.hpp"
#include "fc_rbt_iterator.hpp"
#include "fc_rbt.hpp"

using namespace std;
// template<typename T>
// struct Base{
//     T x;
// };

// template<typename T>
// struct Derive:public Base<T>{
//     void pri(){
//         cout << Base<T>::x << endl;
//     }
// };



int main(){
    
    fc::rb_tree<int, int, int, int> rb_tree;
    for(int i = 0; i< 32; i++){
        cout << i << endl;
        int tmp = rand()%1000;
        rb_tree.insert(tmp);
    }
    for(auto it = rb_tree.begin(); it != rb_tree.end(); it++){
        cout << *it << endl;
    }
    rb_tree.pri();
    // fc::_rbt_iterator<int, int&, int* >it;
    

}