#include "../header.h"

static int	ft_take_fork(int index, int numb, t_philo_pthr *ph)
{
	pthread_mutex_t	*muts;

	muts = ph->conf->forks;
	if (index < numb - 1)
	{
		pthread_mutex_lock(&muts[index]);
		pthread_mutex_lock(&muts[index + 1]);
	}
	else
	{
		pthread_mutex_lock(&muts[0]);
		pthread_mutex_lock(&muts[index]);
	}
	ft_write_msg("%ld %d has taken a fork\n", ph, 0);
	ft_write_msg("%ld %d has taken a fork\n", ph, 0);
	ft_write_msg("%ld %d is eating\n", ph, 0);
	return (1);
}

static	int	ft_put_fork(int index, t_philo_pthr *ph)
{
	pthread_mutex_t	*muts;

	muts = ph->conf->forks;
	if (index < ph->conf->number - 1)
	{
		if (&muts[index])
			pthread_mutex_unlock(&muts[index]);
		if (&muts[index + 1])
			pthread_mutex_unlock(&muts[index + 1]);
	}
	else
	{
		if (&muts[0])
			pthread_mutex_unlock(&muts[0]);
		if (&muts[index])
			pthread_mutex_unlock(&muts[index]);
	}
	return (1);
}

int	ft_eat(t_philo_pthr *ph)
{
	struct timeval	time_now;

	if (ph)
	{
		ft_take_fork(ph->name, ph->conf->number, ph);
		ft_get_time(&time_now);
		if (ft_get_mlsec(&(ph->time), &time_now) > ph->conf->t_die)
		{
			ft_make_is_dead(ph->conf);
			ft_write_msg("%ld %d died\n", ph, 1);
			return (0);
		}
		ft_get_time(&(ph->time));
		ft_my_usleep(ph->conf->t_eat, ph);
		ft_put_fork(ph->name, ph);
	}
	return (1);
}
