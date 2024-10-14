#include <windows.h>
#include <stdio.h>
 
#define MAX_THREADS 100 
 
struct threadinfo {
    int index;       
    HANDLE h;         
    DWORD tid;        
};
 
DWORD WINAPI thread_func(void* p);
 
int main() {
    int n;
    printf("Enter number of threads (n): ");
    scanf_s("%d", &n);
 
    struct threadinfo* thread_arr = (struct threadinfo*)malloc(n * sizeof(struct threadinfo));
    if (thread_arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
 
    for (int i = 0; i < n; i++) {
        thread_arr[i].index = i;
        thread_arr[i].h = CreateThread(NULL, 0, thread_func, &thread_arr[i], CREATE_SUSPENDED, &thread_arr[i].tid);
    }
 
    for (int i = 0; i < n; i++) {
        ResumeThread(thread_arr[i].h);
    }
 
    printf("main thread terminated\n");
 
    ExitThread(0);
}
 
DWORD WINAPI thread_func(void* p) {
    struct threadinfo* p1 = (struct threadinfo*)p;
 
    printf("thread %d started\n", p1->index);
 
    for (int i = 0; i < 100000; i++);
 
    printf("thread %d terminated\n", p1->index);
 
    return 0;
}
