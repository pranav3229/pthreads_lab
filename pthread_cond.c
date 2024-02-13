// /*

// A program where the producer produces some output and the consumer waits for it.

// */
// #include <pthread.h>
// #include <stdio.h>

// pthread_mutex_t mutex;
// pthread_cond_t cond;

// int buffer[100];

// int loopCount = 5;
// int length = 0;

// void* producer(void* arg) {
//     int i;
//     for (i = 0; i < loopCount; i++) {
//         // pthread_mutex_lock(&mutex);
//         buffer[length++] = i;
//         printf("Producer length %d\n", length);
//         pthread_cond_signal(&cond);
//         // pthread_mutex_unlock(&mutex);
//     }
// }

// void* consumer(void* arg) {
//     int i;
//     for (i = 0; i < loopCount; i++) {
//         // pthread_mutex_lock(&mutex);
//         while (length == 0) {
//             printf("Consumer waiting...\n");
//             pthread_cond_wait(&cond, &mutex);
//         }
//         int item = buffer[--length];
//         printf("Consumer %d\n", item);
//         // pthread_mutex_unlock(&mutex);
//     }
// }

// int main(int argc, char* argv[]) {

//     pthread_mutex_init(&mutex, 0);
//     pthread_cond_init(&cond, 0);

//     pthread_t pThread, cThread;
//     pthread_create(&pThread, 0, producer, 0);
//     pthread_create(&cThread, 0, consumer, 0);
//     pthread_join(pThread, NULL);
//     pthread_join(cThread, NULL);

//     pthread_mutex_destroy(&mutex);
//     pthread_cond_destroy(&cond);
//     return 0;
// }


#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int buffer[100];

int loopCount = 5;
int length = 0;

void* producer(void* arg) {
    int i;
    for (i = 0; i < loopCount; i++) {
        pthread_mutex_lock(&mutex);
        buffer[length++] = i;
        printf("Producer length %d\n", length);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg) {
    int i;
    for (i = 0; i < loopCount; i++) {
        pthread_mutex_lock(&mutex);
        while (length == 0) {
            printf("Consumer waiting...\n");
            pthread_cond_wait(&cond, &mutex);
        }
        int item = buffer[--length];
        printf("Consumer %d\n", item);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t pThread1,pThread2, cThread1, cThread2;
    pthread_create(&pThread1, NULL, producer, NULL);
    pthread_create(&pThread2, NULL, producer, NULL);
    pthread_create(&cThread1, NULL, consumer, NULL);
    pthread_create(&cThread2, NULL, consumer, NULL);

    pthread_join(pThread1, NULL);
    pthread_join(pThread2, NULL);
    pthread_join(cThread1, NULL);
    pthread_join(cThread2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
