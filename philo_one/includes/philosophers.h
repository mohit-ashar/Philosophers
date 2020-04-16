/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 12:17:21 by user42            #+#    #+#             */
/*   Updated: 2020/04/15 13:06:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_philo
{
	int					p_no;
	pthread_t			thread;
	pthread_t			m_thread;
	int					num_eat;
	unsigned long		start_time;
	unsigned long		last_eat_time;
}					t_philo;

typedef struct		s_global
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	int					num_alive;
	int					flag_died;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*eats;
	pthread_mutex_t		pickup;
	pthread_mutex_t		putdown;
	pthread_mutex_t		alive;
	pthread_mutex_t		print;
	pthread_mutex_t		someone_died;
}					t_global;

typedef enum		e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK_TAKEN,
	DIED
}					t_status;

int					ft_isdigit(int c);
int					ft_atoi(const char *s1);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *str);
int					ft_strlen(const char *s);
int					ft_strlcat(char *dst, const char *src, int dst_size);
unsigned long		get_current_time();
int					create_philo(t_global *gl);
int					free_all(int ret);
t_global			*get_global();
int					str_err(char *err_msg, int ret);
void				*monitoring(void *vp);
char				*ft_itoa(unsigned long nbr);
char				*ft_strdup(const char *s1);
void				print_status(t_global *gl, t_philo *p, t_status status);
int					init_mutexes(t_global *gl);
void				ft_usleep(unsigned long time);
#endif
