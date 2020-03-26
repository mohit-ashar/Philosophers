#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <wait.h>
# define EXIT 1
# define NO_EXIT 0
# define PHILO_ATE_ENOUGH 0
# define PHILO_DIED 1

typedef struct      s_philo
{
    int             p_no;
    int             no_eaten;
    pthread_t       thread;
    pid_t           pid;
    unsigned long   last_eat_time;
    unsigned long   start_time;
}                   t_philo;

typedef struct      s_global
{
    int             n_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_must_eat;
    int             num_alive;
    int             died_flag;
    sem_t           *fork;
    sem_t           *eat;
    sem_t           *pickup;
    sem_t           *putdown;
    sem_t           *print;
    sem_t           *alive;
    sem_t           *died;
    sem_t           *print_error;
    t_philo         *philo;
}                   t_global;

typedef enum        e_status
{
    THINKING,
    EATING,
    SLEEPING,
    TAKEN_FORK,
    DIED,
}                   t_status;

int             ft_isdigit(int c);
char			*ft_itoa(unsigned long nbr);
int             ft_atoi(const char *s1);
void	        ft_putstr_fd(char *s, int fd);
int             ft_strlen(const char *s);
void			ft_putnbr_fd(int n, int fd);
t_global        *get_global();
int             init_global();
void            philosophing(void *vp);
void            *monitoring(void *vp);
void            print_status(t_global *gl, t_philo *p, t_status status, int is_exit);
unsigned long   get_current_time();
int             create_philo1(t_global *gl);
int             str_error(char *err_msg, int ret);
int             free_and_unlink(t_global *gl, int ret);
char            *ft_strdup(const char *s1);
int             ft_unlink(int ret);
# endif