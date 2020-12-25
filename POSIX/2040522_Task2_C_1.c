#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>//Time Heading

//2 Character 2 digit password Cracking: GENERIC METHOD
int count = 0;

void substr(char *dest, char *src, int start, int length)
{
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crack(char *salt_and_encrypted)
{
  int x, y, z;
  char salt[7];
  char plain[7];
  char *enc;

  substr(salt, salt_and_encrypted, 0, 6);

  for (x = 'A'; x <= 'Z'; x++)
  {
    for (y = 'A'; y <= 'Z'; y++)
    {
      for (z = 0; z <= 99; z++)
      {
        sprintf(plain, "%c%c%02d", x, y, z);
        enc = (char *)crypt(plain, salt);
        count++;
        if (strcmp(salt_and_encrypted, enc) == 0)
        {
          printf("#%-8d%s %s\n", count, plain, enc);
          return;
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
  struct timespec start, end;
  long long int time_used;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  crack("$6$AS$CzyhYqlIEPjrA8mqSJS92xvh3GKglj4tO89Simi2aej43pi0rXoSU3RAk5ierxRTHey9O22.zI1SZI9VoR5UC/");

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  printf("%d solutions explored\n", count);

  time_count(&start, &end, &time_used);

  printf("Time taked: %f Seconds OR %lld Nano Seconds\n", (time_used / 1.0e9), (time_used));
  return 0;
}
