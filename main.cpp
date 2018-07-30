#include <bits/stdc++.h>
#include "allocator.hpp"
using namespace std;

void test(){
    cout << "bad" <<endl;
}


struct aa{
    int x[3];
    ~aa(){
        printf("deconstructor\n");
    }
};

template<typename T>
T foo(T* x){
    x->~T();
}




int main(){
    // fc::allocator<int4>::set_handler(test);

    int* ptr = new int();
    foo(ptr);
    // int *ptr = new int();



    
    // srand(time(0));
    // vector<int*>vec;
    // int cnt = 0;
    // int num = 2;
    // while(num--){
    // for(int i = 0; i <= 40; i++){
    //     // printf("%d %d\n", i, i % 100 + 33);
    //     int *ptr = fc::allocator<int>::allocate(1);
    //     // printf("%p ...\n", ptr);
    //     *ptr = cnt++;
    //     vec.push_back(ptr);
    //     // for(int j = 0; j < size; j++){
    //     //     *(ptr + j) = i * 10 + j;
    //     // }
    //     // printf("%p \n", ptr);
    //     // fc::allocator<int>::deallocate(ptr, 1);
    // }
    // for(auto elem:vec){
    //     printf("%d\n", *elem);
    //     fc::allocator<int>::deallocate(elem, 1);
    // }
    // vec.clear();
    // }




    //for()
    // int *ptr = fc::allocator<int>::allocate(156);
    // printf("%p ...\n", ptr);        
    // fc::allocator<int>::deallocate(ptr, 156);
    
    
    //我有一个4字节的对象，分配了三个，考虑8字节对其，应该申请16字节的空间，如果没有之前信息来记录，可能会直接释放4个这样的元素，导致错误，所以new[] 需要多记录空间。
    //函数重载和模板推导都不能依赖返回值
    //foo() 调用，返回值和参数都不能推导出来。
    //为什么需要traits编程技巧
    // 1. 模板编程的情况下， 不能通过迭代器的类型识别出所指物的类型
    // 2. 可以通过参数类型推导
    // 3. 但是模板推导不依赖返回值
    // 4. 通过一个Iterator的类型来推导出所指向的类型
    // 5. 但是迭代器是指针 类型是不是Iterator<int> 是 int *,怎么办
    // 6. 偏特化
    // 7. 所以我们现在通过迭代器的类型就可推导出迭代器所指向的东西的类型,更一般的，迭代器中所包含的属性都可以推导。

    return 0;

}

// template<typename T>
// struct Iterator{

//     typedef T value_type;
    
// };

// template<typename T>
// struct Iterator<T *>{
//     typedef T value_type;
// };

// template<typename Iter>
// struct traits{
//     typedef Iter::value_type value_type;
// };


// template<typename T>
// typename traits<T>::value_type
// foo(T Iter){
//     return *T;
// }

