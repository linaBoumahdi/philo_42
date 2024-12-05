#include <stdio.h>
#include <pthread.h>

void *count_to_100(void *arg)
{
 (void)arg;

 for(int i = 0; i < 100; i++);
 printf("The count has finished\n");
 return (NULL);
}

void *print_hello(void *arg)
{
 (void)arg;

 for(int i = 0; i < 100; i++)
  printf("Hello, world!\n");
 return (NULL);
}

int main()
{
 pthread_t thread_1;
 pthread_t thread_2;

pthread_create(&thread_1, NULL, count_to_100, NULL);
 pthread_create(&thread_2, NULL, print_hello, NULL);
  pthread_join(thread_1, NULL);
 pthread_join(thread_2, NULL);
}