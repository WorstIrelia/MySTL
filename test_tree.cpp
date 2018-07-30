#include <bits/stdc++.h>

#include "test_tree.hpp"

using namespace std;

int main(){
    fc::test_tree<int> a;
    for(int i = 0; i < 8; i++){
        int tmp = i;
        a.insert(tmp);
    }
    for(auto it = a.begin(); it != a.end(); it++){
        cout<< *it << endl;
    }

}