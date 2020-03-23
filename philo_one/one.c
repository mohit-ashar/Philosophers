#include "philosophers.h"
#include <stdio.h>
int main()
{
    unsigned long time;
    char *buffer;
    int i = 10;
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    buffer = ft_itoa(i);
    ft_putstr_fd(buffer, 1);
    ft_putstr("\n");
    printf("time->%ld\n", time);
}
