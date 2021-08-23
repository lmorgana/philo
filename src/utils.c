#include "../header.h"

int	ft_write_msg(char *msg, t_philo_pthr *ph, int is_dead_msg)
{
	struct timeval	time_now;
	long			t_time;

	pthread_mutex_lock(ph->conf->mut_msg);
	ft_get_time(&time_now);
	t_time = ft_get_mlsec(&(ph->conf->time_start), &time_now);
	if (t_time < __INT_MAX__ && t_time >= 0 && msg)
		printf(msg, t_time, ph->name + 1);
	if (is_dead_msg == 0 && ph->conf->mut_msg)
		pthread_mutex_unlock(ph->conf->mut_msg);
	return (1);
}

pthread_mutex_t	*ft_forks(int len)
{
	int				i;
	pthread_mutex_t	*arr_muts;

	arr_muts = malloc(sizeof(pthread_mutex_t) * len);
	if (arr_muts)
	{
		i = 0;
		while (i < len)
		{
			if (pthread_mutex_init(&arr_muts[i], NULL) != 0)
			{
				free(arr_muts);
				return (0);
			}
			i++;
		}
		return (arr_muts);
	}
	return (NULL);
}

void	*ft_for_one_philo(void *one_ph)
{
	t_philo_pthr	*ph;

	ph = (t_philo_pthr *) one_ph;
	ft_write_msg("%ld %d has taken a fork\n", ph, 0);
	ft_my_usleep(ph->conf->t_die, ph);
	ft_write_msg("%ld %d died\n", ph, 0);
	ph->conf->is_dead = 1;
	return (0);
}

int	ft_my_usleep(long t, t_philo_pthr *ph)
{
	struct timeval	t_start;
	struct timeval	t_now;

	ft_get_time(&t_start);
	ft_get_time(&t_now);
	while (ft_get_mlsec(&t_start, &t_now) < t)
	{
		usleep(50);
		ft_get_time(&t_now);
		if (ft_get_mlsec(&(ph->time), &t_now) > ph->conf->t_die)
		{
			ft_make_is_dead(ph->conf);
			ft_write_msg("%ld %d died\n", ph, 1);
			return (0);
		}
	}
	return (1);
}
