#include <bits/stdc++.h>
#include "allocator.hpp"
using namespace std;

void test(){
    cout << "bad" <<endl;
}


struct aa{
    int x[3];

};

int main(){
    // fc::allocator<int4>::set_handler(test);
    for(int i = 1; i <= 6265; i++){
        int *ptr = fc::allocator<int>::allocate(i%32+1);
        // printf("%p ...\n", ptr);
        for(int j = 0; j < i; j++){
            *(ptr + j) = i * 10 + j;
        }
        fc::allocator<int>::deallocate(ptr, i%32+1);
    }
    // int *ptr = fc::allocator<int>::allocate(156);
    // printf("%p ...\n", ptr);        
    // fc::allocator<int>::deallocate(ptr, 156);
    //我有一个4字节的对象，分配了三个，考虑8字节对其，应该申请16字节的空间，如果没有之前信息来记录，可能会直接释放4个这样的元素，导致错误，所以new[] 需要多记录空间。


    return 0;

}
