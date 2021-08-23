#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_conf
{
	int				number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_of_eating;
	int				num_finish_eat;
	struct timeval	time_start;
	int				is_dead;
	pthread_t		*ts;
	pthread_mutex_t	*mut_msg;
	pthread_mutex_t	*mut_for_dead;
	pthread_mutex_t	*forks;
}					t_conf;

typedef struct s_philo_pthr
{
	int				name;
	t_conf			*conf;
	struct timeval	time;
}					t_philo_pthr;

pthread_mutex_t	*ft_forks(int len);

t_conf			*ft_get_conf(int argc, char **argv, t_conf *conf);
t_conf			*ft_get_muts_forks(int len_arg, t_conf *conf);
pthread_t		*ft_get_ts(int len);
int				ft_clear_conf(t_conf *conf);
int				ft_close_all(int len, t_conf *conf);
int				ft_my_atoi(const char *str, int *numb);

int				ft_write_msg(char *msg, t_philo_pthr *ph, int is_dead_msg);

t_philo_pthr	*ft_new_philo(int name, t_conf *conf);
pthread_mutex_t	*ft_get_mut_msg(void);
int				ft_eat(t_philo_pthr *ph);
int				ft_sleep_think(t_philo_pthr *ph);

int				ft_get_time(struct timeval *t_time);
long			ft_get_mlsec(struct timeval *t_prev, struct timeval *t_now);

int				ft_free_phs(t_philo_pthr **phs, int len);
void			*ft_for_one_philo(void *one_ph);

int				ft_my_usleep(long t, t_philo_pthr *ph);

int				ft_make_is_dead(t_conf *conf);
int				ft_is_dead(t_conf *conf);
#endif