// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h> 

// int i;

// void* thread_func() {
//     //  int i = 0;
//     while (1) {
//         printf("child thread: %d\n", i++);
//         sleep(1);
//     }
// }
// int main() {
//     pthread_t t1;
//     pthread_t t2;
//     pthread_t t3;
//     pthread_create(&t1, NULL, thread_func, NULL);
//     pthread_create(&t2, NULL, thread_func, NULL);
//     pthread_create(&t3, NULL, thread_func, NULL);
//     //int i = 0;
//     while (1) {
//         printf("main thread: %d\n", i++);
//         sleep(1);
//     }
// }

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

int i;
pthread_mutex_t mutex_i = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    pthread_t tid = pthread_self(); // Get thread ID
    while (1) {
        pthread_mutex_lock(&mutex_i); // Lock mutex before accessing i
        printf("child thread %lu: %d\n", tid, i++);
        pthread_mutex_unlock(&mutex_i); // Unlock mutex after modifying i
        sleep(1);
    }
}

int main() {
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);
    pthread_create(&t3, NULL, thread_func, NULL);

    pthread_t main_tid = pthread_self(); // Get main thread ID

    while (1) {
        pthread_mutex_lock(&mutex_i); // Lock mutex before accessing i
        printf("main thread %lu: %d\n", main_tid, i++);
        pthread_mutex_unlock(&mutex_i); // Unlock mutex after modifying i
        sleep(1);
    }

    pthread_mutex_destroy(&mutex_i); // Destroy mutex when done
    return 0;
}
