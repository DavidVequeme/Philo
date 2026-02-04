
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philosophers.h"

void *thread_tester()
{
    printf("hello\n");
    sleep(3);
    printf("ADEUS\n");
}

int main(int ac, char **av)
{

    t_info *inf;
    pthread_t t1;
    pthread_t t2;
    int count;

    pthread_create(&t1, NULL, &thread_tester, NULL);
    pthread_create(&t2, NULL, &thread_tester, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    count = 8;
    inf->i = 0;
    inf->str = malloc(sizeof (char) * count);
}



