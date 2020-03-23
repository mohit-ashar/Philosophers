#include "philosophers.h"

int     str_err(char *err_msg, int ret)
{
    ft_putstr_fd(err_msg, 2);
    return (ret);
}