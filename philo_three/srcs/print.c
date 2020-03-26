#include "philosophers.h"

int				ft_free(char **str)
{
	if (!str || !*str)
		return (1);
	free(*str);
	*str = 0;
	return (1);
}

char			*ft_stradd(char *str, char ch)
{
	char		*res;
	int			len;
	int			i;

	res = NULL;
	len = str ? ft_strlen(str) : 0;
	len = len + 2;
	res = (char*)malloc(sizeof(char) * (len));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str && str[++i])
		res[i] = str[i];
	res[len - 2] = ch;
	res[len - 1] = 0;
	ft_free(&str);
	return (res);
}

char    *construct_line(char *ts, char *sp, char *index, char *action)
{
    int i;
    char *buffer;

    buffer = 0;
    i = 0;
    while (ts[i] != '\0')
        buffer = ft_stradd(buffer, ts[i++]);
    i = 0; 
    while (sp[i] != '\0') 
        buffer = ft_stradd(buffer, sp[i++]);
    i = 0;
    while (index[i] != '\0')
        buffer = ft_stradd(buffer, index[i++]);
    i = 0;
    while (action[i] != '\0')
        buffer = ft_stradd(buffer, action[i++]);
    ft_free(&ts);
    ft_free(&sp);
    ft_free(&index);
    ft_free(&action);
    return (buffer);
}

void    print_line(char *str, t_global *gl, t_status status, int is_exit)
{
    if ((sem_wait(gl->print) == -1))
	    str_error("error: sem_wait\n", 1);
	ft_putstr_fd(str, 1);
	if (!is_exit)
    {
		if ((sem_post(gl->print) == -1))
            str_error("error: sem_post\n", 1);
    }
    ft_free(&str);
}

void    print_status(t_global *gl, t_philo *p, t_status status, int is_exit)
{
    char *timestamp;
    char *space;
    char *p_num;
    char *action;
    unsigned long time;

    time = get_current_time() - p->start_time;
    timestamp = ft_itoa(time);
    space = ft_strdup(" ");
    p_num = ft_itoa(p->p_no + 1);
    if (status == THINKING)
        action = ft_strdup(" is thinking\n");
    else if (status == EATING)
        action = ft_strdup(" is eating\n");
    else if (status == SLEEPING)
        action = ft_strdup(" is sleeping\n");
    else if (status == TAKEN_FORK)
        action = ft_strdup(" has taken a fork\n");
    else if (status == DIED)
        action = ft_strdup(" died\n");
    print_line(construct_line(timestamp, space, p_num, action), gl, status, is_exit);
}