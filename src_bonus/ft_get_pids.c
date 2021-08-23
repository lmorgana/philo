#include "header_bonus.h"

int	ft_close_pids(t_conf *conf)
{
	int	i;

	i = 0;
	while (i < conf->number)
	{
		if (conf->pids[i])
			kill(conf->pids[i], SIGKILL);
		i++;
	}
	sem_close(conf->num_of_forks);
	sem_close(conf->sem_for_msg);
	sem_close(conf->sem_for_sum);
	return (1);
}

t_conf	*ft_get_pids(t_conf *conf)
{
	int	*pids;

	pids = malloc(sizeof(int) * conf->number);
	if (pids)
	{
		sem_unlink("sema");
		sem_unlink("sem_msg");
		sem_unlink("sem_sum");
		conf->num_of_forks = sem_open("sema", O_CREAT, \
		S_IRWXU, conf->number);
		conf->sem_for_msg = sem_open("sem_msg", O_CREAT, S_IRWXU, 1);
		conf->sem_for_sum = sem_open("sem_sum", O_CREAT, S_IRWXU, 1);
		if (conf->num_of_forks && conf->sem_for_msg && conf->sem_for_sum)
		{
			pids = (int *) memset(pids, '\0', sizeof(int) * conf->number);
			conf->pids = pids;
			return (conf);
		}
		sem_close(conf->num_of_forks);
		sem_close(conf->sem_for_msg);
		sem_close(conf->sem_for_sum);
		free(pids);
	}
	ft_clear_conf_bonus(conf);
	return (0);
}

int	ft_my_usleep_bonus(int t, struct timeval *time_last_eat, t_conf *conf)
{
	struct timeval	t_start;
	struct timeval	t_now;

	ft_get_time(&t_start);
	ft_get_time(&t_now);
	while (ft_get_mlsec(&t_start, &t_now) < t)
	{
		usleep(50);
		ft_get_time(&t_now);
		if (ft_is_dead(time_last_eat, conf))
			return (0);
	}
	return (1);
}
