#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>//Time Heading

//Password Cracking using multi thread (Password is NB50)

pthread_t thread_a, thread_b;

struct crypt_data *crypt_data_a, *crypt_data_b;

int count = 0;

void substring(char *dest, char *src, int start, int length)
{
    memcpy(dest, src + start, length);
    *(dest + length) = '\0';
}

void *kernel_function_1(char *salt_and_encrypted)
{
    int x, y, z;
    char salt[7];
    char plain[7];
    char *enc;

    substring(salt, salt_and_encrypted, 0, 6);

    for (x = 'A'; x <= 'M'; x++)
    {
        for (y = 'A'; y <= 'Z'; y++)
        {
            for (z = 0; z <= 99; z++)
            {
                sprintf(plain, "%c%c%02d", x, y, z);
                enc = (char *)crypt_r(plain, salt, crypt_data_a);

                count++;
                if (strcmp(salt_and_encrypted, enc) == 0)
                {
                    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
                    printf("#%-8d%s %s\n", count, plain, enc);

                    pthread_cancel(thread_a);
                    pthread_cancel(thread_b);
                    pthread_exit(NULL);
                    return 0;
                }
                else
                {
                    sleep(0);
                }
            }
        }
    }
}

void *kernel_function_2(char *salt_and_encrypted)
{
    int x, y, z;
    char salt[7];
    char plain[7];
    char *enc;
    substring(salt, salt_and_encrypted, 0, 6);

    for (x = 'N'; x <= 'Z'; x++)
    {
        for (y = 'A'; y <= 'Z'; y++)
        {
            for (z = 0; z <= 99; z++)
            {
                sprintf(plain, "%c%c%02d", x, y, z);
                enc = (char *)crypt_r(plain, salt, crypt_data_b);
                count++;

                if (strcmp(salt_and_encrypted, enc) == 0)
                {

                    printf("#%-8d%s %s\n", count, plain, enc);
                    pthread_cancel(thread_a);
                    pthread_cancel(thread_b);
                    pthread_exit(NULL);
                    return 0;
                }
                else
                {
                    sleep(0);
                }
            }
        }
    }
}

int time_count(struct timespec *start, struct timespec *end,
                   long long int *diff)
{
    long long int in_sec = end->tv_sec - start->tv_sec;
    long long int in_nano = end->tv_nsec - start->tv_nsec;
    if (in_nano < 0)
    {
        in_sec--;
        in_nano += 1000000000;
    }
    *diff = in_sec * 1000000000 + in_nano;
    return !(*diff > 0);
}

int main(int argc, char *argv[])
{
    int i;

    crypt_data_a = (struct crypt_data *)malloc(sizeof(struct crypt_data));
    crypt_data_a->initialized = 0;

    crypt_data_b = (struct crypt_data *)malloc(sizeof(struct crypt_data));
    crypt_data_b->initialized = 0;

    struct timespec start, end;
    long long int time_used;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    pthread_create(&thread_a, NULL, (void *)kernel_function_1, "$6$AS$CzyhYqlIEPjrA8mqSJS92xvh3GKglj4tO89Simi2aej43pi0rXoSU3RAk5ierxRTHey9O22.zI1SZI9VoR5UC/");

    pthread_create(&thread_b, NULL, (void *)kernel_function_2, "$6$AS$CzyhYqlIEPjrA8mqSJS92xvh3GKglj4tO89Simi2aej43pi0rXoSU3RAk5ierxRTHey9O22.zI1SZI9VoR5UC/");

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    time_count(&start, &end, &time_used);

    printf("Time taked: %f Seconds OR %lld Nano Seconds\n", (time_used / 1.0e9), (time_used));
    return 0;
}
