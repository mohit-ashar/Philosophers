#include "philosophers.h"

int     str_error(char *err_msg, int ret)
{
    t_global *gl;

    gl = get_global();
    sem_wait(gl->print_error);
    ft_putstr_fd(err_msg, 2);
    sem_post(gl->print_error);
    return (ret);
}