#ifndef _FC_DEFAULT_ALLOCATOR_
#define _FC_DEFAULT_ALLOCATOR_

#include <malloc.h>
#include <cstdio>
#include <cstdlib>


namespace fc{


class _default_allocator{
private:
    static void (*oom_handler)();
    static void* oom_malloc(size_t n);
    static int tot;
public:
    typedef void (*func)();
    static void* _allocate(size_t n){
        printf("%ld\n", n);
        tot += n;
        printf("tot = %d\n", tot);
        void *ret = malloc(n);
        printf("%p allo\n", ret);
        // free(ret);
        // printf("im ok\n");
        // assert(n == 624 || n == 40);
        if(ret == 0){
            ret = oom_malloc(n);
        }
        
        return ret;
    }
    static void _deallocate(void *ptr){
        printf("im in _deallocate %p\n", ptr);
        free(ptr);
        printf("free ok\n");
    }
    static func set_handler(func ptr){
        func old = oom_handler;
        oom_handler = ptr;
        return old;
    }


protected:


};



int _default_allocator::tot = 0;
void* _default_allocator::oom_malloc(size_t n){
    void *ret;
    for(;;){
        if(oom_handler == 0 ){
            printf("bad_alloc\n");
            exit(-1);
        }
        (oom_handler)();
        ret = malloc(n);
        if(ret) return ret;
    } 
}

void (* _default_allocator::oom_handler)() = static_cast<void(*)()>(0);

}


#endif