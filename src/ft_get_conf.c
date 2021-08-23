#include "../header.h"

int	ft_close_all(int len, t_conf *conf)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_detach(conf->ts[i]);
		i++;
	}
	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&(conf->forks[i]));
		i++;
	}
	pthread_mutex_destroy(conf->mut_for_dead);
	pthread_mutex_destroy((conf->mut_msg));
	return (1);
}

int	ft_clear_conf(t_conf *conf)
{
	if (conf)
	{
		if (conf->mut_msg)
			free(conf->mut_msg);
		if (conf->mut_for_dead)
			free(conf->mut_for_dead);
		if (conf->forks)
			free(conf->forks);
		if (conf->ts)
			free(conf->ts);
		return (1);
	}
	return (0);
}

t_conf	*ft_get_muts_forks(int len_arg, t_conf *conf)
{
	pthread_mutex_t	*mut_msg;
	pthread_mutex_t	*arr_forks;
	pthread_t		*ts;

	if (conf)
	{
		(void) len_arg;
		mut_msg = ft_get_mut_msg();
		arr_forks = ft_forks(conf->number);
		ts = ft_get_ts(conf->number);
		conf->mut_msg = mut_msg;
		conf->forks = arr_forks;
		conf->mut_for_dead = ft_get_mut_msg();
		conf->ts = ts;
		if (mut_msg && arr_forks && ts && conf->mut_for_dead)
			return (conf);
		ft_clear_conf(conf);
	}
	return (0);
}

static	int	ft_take_args(int argc, char **argv, t_conf *conf)
{
	if (ft_my_atoi(argv[1], &conf->number) == 0)
		return (0);
	if (ft_my_atoi(argv[2], &conf->t_die) == 0)
		return (0);
	if (ft_my_atoi(argv[3], &conf->t_eat) == 0)
		return (0);
	if (ft_my_atoi(argv[4], &conf->t_sleep) == 0)
		return (0);
	if (argc == 6)
	{
		if (ft_my_atoi(argv[5], &conf->num_of_eating) == 0)
			return (0);
	}
	return (1);
}

t_conf	*ft_get_conf(int argc, char **argv, t_conf *conf)
{
	if (conf)
	{
		conf->number = 0;
		conf->t_die = -1;
		conf->t_eat = -1;
		conf->t_sleep = -1;
		conf->num_of_eating = -1;
		conf->num_finish_eat = 0;
		conf->is_dead = 0;
		if (ft_take_args(argc, argv, conf))
		{
			if (!(conf->number < 1 || conf->num_of_eating == 0 || \
			conf->number >= 200 || \
			conf->t_die < 10 || conf->t_eat < 10 || conf->t_sleep < 10))
				return (conf);
		}
	}
	return (NULL);
}
