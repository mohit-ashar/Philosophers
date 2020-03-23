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
    while (ts[i])
        buffer = ft_stradd(buffer, ts[i++]);
    i = 0; 
    while (sp[i])
        buffer = ft_stradd(buffer, sp[i++]);
    i = 0;
    while (index[i])
        buffer = ft_stradd(buffer, index[i++]);
    i = 0;
    while (action[i])
        buffer = ft_stradd(buffer, action[i++]);
    return (buffer);
}

void    print_line(char *str, t_global *gl)
{
    pthread_mutex_lock(&gl->print);
    ft_putstr(str);
    pthread_mutex_unlock(&gl->print);
    ft_free(&str);
}

void    print_status(t_global *gl, t_philo *p, t_status status)
{
    char *timestamp;
    char *space;
    char *p_num;
    char *action;
    unsigned long time;

    time = get_current_time();
    timestamp = ft_itoa(time);
    space = ft_strdup(" ");
    p_num = ft_itoa(p->p_no + 1);
    if (status == THINKING)
        action = ft_strdup(" is thinking\n");
    if (status == EATING)
        action = ft_strdup(" is eating\n");
    if (status == SLEEPING)
        action = ft_strdup(" is sleeping\n");
    if (status == FORK_TAKEN)
        action = ft_strdup(" has taken a fork\n");
    if (status == DIED)
        action = ft_strdup(" died\n");
    print_line(construct_line(timestamp, space, p_num, action), gl);
}