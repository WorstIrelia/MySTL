#ifndef _FC_MEMPOLL_ALLOCATOR_
#define _FC_MEMPOLL_ALLOCATOR_


#include <cstdio>
#include "_default_allocator.hpp"

namespace fc{

enum{
    THRESHOLD = 128
};

class _mempoll_allocator{
private:
    static void* list_head[THRESHOLD / 8];
    static char *start_free;
    static size_t leave_size;
    static size_t heap_size;
public:
    static void * allocate(size_t n){
        // printf("im in allocate %ld\n", n);
        int index = n / 8 - 1;
        // printf("%p\n",list_head[index]);
        if(list_head[index] == NULL){
            list_head[index] = create_list(n, 20);
        }
        void *ret = list_head[index];
        list_head[index] = (void*)*(long**)list_head[index];
        return ret;
    }
    static void deallocate(void *ptr, size_t tot_size){
        // printf("im in deallocate\n");
        int index = tot_size / 8 - 1;
        long *p = (long*)(ptr);
        // printf("ok\n");
        // printf("%p\n", ptr);
        *p = (long)list_head[index]; 
        list_head[index] = ptr;
        // printf("ok\n");
    }
    static void* create_list(size_t bytes, size_t n){
        // printf("im in create_list\n");
        int objs = n;
        void * res = get_pool(bytes, objs);
        // printf("%p\n", res);
        for(int i = 0; i < objs; i++){
            long **p = (long **)((char*)res + i * bytes);
            if(i + 1 != objs){
                *p = &*(long *)((char*)res + (i + 1) * bytes);
            }
            else{
                *p = 0;
            }
        }
        return res;

    }
    static inline void* add_pool(size_t n){
        // printf("im in add_pool %ld\n", n);
        
        return _default_allocator::_allocate(n);
    }
    static void* get_pool(size_t bytes, int &n){
        // printf("im in get_pool %ld %d\n",bytes, n);
        size_t tot_size = bytes * n;
        // printf("%ld %ld\n",leave_size, tot_size);
        if(leave_size >= tot_size){
            leave_size -= tot_size;
            void *ret = (void *)start_free;
            start_free += tot_size;
            if(!leave_size) start_free = 0;
            return ret;
        }
        else if(leave_size >= bytes){
            n = leave_size / bytes;
            leave_size -= n * bytes;
            void *ret = (void*)start_free;
            start_free += n * bytes;
            if(!leave_size) start_free = 0; 
            return ret;
        }
        else{
            
            if(start_free){
                // printf("%p %ld\n",start_free, leave_size);
                int index = leave_size / 8 - 1;
                long *p = (long*)start_free;
                
                *p = (long)list_head[index];
                // printf("ok\n");
                list_head[index] = start_free;
                
                start_free = 0;
                leave_size = 0;

            }
            // printf("im here\n");
            // printf("im in done\n");
            int index = bytes / 8 - 1;
            for(int i = index; i < THRESHOLD / 8; i++){
                if(list_head[i]){
                    start_free = (char*)list_head[i];
                    leave_size =  (index + 1) * 8;
                    list_head[i] = (void*)*(long**)list_head[i];
                    return get_pool(bytes, n);
                }
            }
            size_t req_tot = 2 * tot_size + heap_size;
            // printf("%ld\n", req_tot);
            req_tot = (req_tot + 7) / 8 * 8; 
            start_free = (char*) add_pool(req_tot);
            leave_size = req_tot;
            heap_size = 128 + heap_size;
            return get_pool(bytes, n);

        }
    }
    
protected:

};

char* _mempoll_allocator::start_free = 0;
size_t _mempoll_allocator::leave_size = 0;
size_t _mempoll_allocator::heap_size = 0;
void* _mempoll_allocator::list_head[THRESHOLD / 8] = {0};



}

#endif