#include "../header.h"

pthread_mutex_t	*ft_get_mut_msg(void)
{
	pthread_mutex_t	*muts;

	muts = malloc(sizeof(pthread_mutex_t));
	if (muts)
	{
		if (pthread_mutex_init(muts, NULL) != 0)
		{
			free(muts);
			return (NULL);
		}
		return (muts);
	}
	return (NULL);
}

t_philo_pthr	*ft_new_philo(int name, t_conf *conf)
{
	t_philo_pthr	*ph;

	ph = malloc(sizeof(t_philo_pthr));
	if (ph)
	{
		if (ft_get_time(&(ph->time)) != 1)
			return (0);
		ph->name = name;
		ph->conf = conf;
		return (ph);
	}
	return (NULL);
}

int	ft_sleep_think(t_philo_pthr *ph)
{
	ft_write_msg("%ld %d is sleeping\n", ph, 0);
	ft_my_usleep(ph->conf->t_sleep, ph);
	ft_write_msg("%ld %d is thinking\n", ph, 0);
	return (1);
}

pthread_t	*ft_get_ts(int len)
{
	int			i;
	pthread_t	*ts;

	ts = malloc(sizeof(pthread_t) * (len));
	if (ts)
	{
		i = 0;
		while (i < len)
			ts[i++] = 0;
		return (ts);
	}
	return (NULL);
}

int	ft_free_phs(t_philo_pthr **phs, int len)
{
	int	i;

	if (phs)
	{
		i = 0;
		while (i < len)
		{
			if (phs[i])
				free(phs[i]);
			i++;
		}
		free(phs);
		return (1);
	}
	return (0);
}
