#ifndef HEADER_BONUS_H
# define HEADER_BONUS_H

# include <stdio.h>

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

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
	sem_t			*num_of_forks;
	sem_t			*sem_for_msg;
	sem_t			*sem_for_sum;
	int				*pids;
}					t_conf;

t_conf	*ft_get_conf(int argc, char **argv);
int		ft_clear_conf_bonus(t_conf *conf);
int		ft_my_atoi(const char *str, int *numb);

t_conf	*ft_get_pids(t_conf *conf);
int		ft_close_pids(t_conf *conf);

int		ft_err_msg(char *str);
int		ft_write_msg(char *msg, int index, t_conf *conf, int is_dead);
int		ft_is_dead(struct timeval *time_last_eat, t_conf *conf);

int		ft_get_time(struct timeval *t_time);
long	ft_get_mlsec(struct timeval *t_prev, struct timeval *t_now);

int		ft_eat(int index, struct timeval *time_last_eat, t_conf *conf);
int		ft_sleep_think(int index, struct timeval *time_last_eat, t_conf *conf);

int		ft_for_one_philo_bonus(t_conf *conf);
int		ft_my_usleep_bonus(int t, struct timeval *time_last_eat, t_conf *conf);

#endif
