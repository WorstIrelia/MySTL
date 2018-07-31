#include <bits/stdc++.h>
#include "fc_vector.hpp"
#include "fc_list.hpp"

using namespace std;


enum{
    x = 123,
    y = 234

};

template<int N>
struct fib{
    enum{ret = N * fib<N - 1>::ret };

};
template<>
struct fib<0>{
    enum{ret = 1};
};

// 编译期可以计算的enum, const static unsigend int 
// 
template<int N>
struct prime{

};

template<typename T>
struct test{
    T x;
    template<typename U>
    struct rebind{
        typedef test<U> other;
    };
};



int main(){
    test<int>a;
    cout << sizeof(a.x) <<endl;
    test<int>::rebind<double>::other b;
    cout<< sizeof(b.x) << endl;




    cout << fib<10>::ret << endl;
    fc::list<int>l;
    for(int i = 0; i < 5; i++){
        l.push_back(i);
    }
    for(auto elem: l){
        cout << elem << endl;
    }
    for(int i = 0; i < 5; i++){
        l.push_front(i);
    }
    for(auto elem: l){
        cout << elem << endl;
    }
    auto it = l.begin();
    int cnt = 5;
    while(cnt--){
        ++it;
    }
    *it = 99999;
    // *ptr = 123445;
    cout << &it << endl;
    for(auto elem: l){
        cout << elem << endl;
    }
    l.erase(it);



    for(auto elem: l){
        cout << elem << endl;
    }
    
    l.front() = 123;
    cout << l.front() << endl;
    cout << l.back() << endl;
    // map<int,int>::iterator::
    
    
    // printf("%d\n", x);

}