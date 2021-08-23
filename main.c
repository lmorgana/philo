#include "header.h"

void	*philo(void *ph)
{
	t_philo_pthr	*one_ph;
	int				i;

	one_ph = (t_philo_pthr *) ph;
	i = 0;
	while ((one_ph) && !ft_is_dead(one_ph->conf))
	{
		if (ft_eat(one_ph))
		{
			i++;
			if (one_ph->conf->num_of_eating > 0 && \
				i >= one_ph->conf->num_of_eating)
				one_ph->conf->num_finish_eat++;
			if (one_ph->conf->num_finish_eat >= one_ph->conf->number)
			{
				ft_make_is_dead(one_ph->conf);
				ft_write_msg(NULL, one_ph, 1);
				return (0);
			}
			ft_sleep_think(one_ph);
		}
	}
	return (0);
}

int	ft_mk_ph_pthr(int i, t_conf *conf, t_philo_pthr **phs)
{
	phs[i] = ft_new_philo(i, conf);
	if (conf->number == 1)
	{
		if (pthread_create(&(conf->ts[i]), NULL, \
		&ft_for_one_philo, phs[i]) != 0)
		{
			conf->is_dead = 1;
			return (0);
		}
		return (1);
	}
	if (phs[i])
	{
		if (pthread_create(&(conf->ts[i]), NULL, &philo, phs[i]) != 0)
		{
			conf->is_dead = 1;
			return (0);
		}
		return (1);
	}
	return (0);
}

static	int	ft_process(int len_arg, t_conf *conf)
{
	int				i;
	t_philo_pthr	**phs;

	i = 0;
	phs = malloc(sizeof(t_philo_pthr *) * conf->number);
	if (phs)
	{
		while (i < conf->number)
		{
			if (ft_mk_ph_pthr(i, conf, phs) == 0)
			{
				ft_close_all(len_arg, conf);
				ft_free_phs(phs, conf->number);
				return (0);
			}
			i++;
		}
		while (conf->is_dead != 1)
			usleep(2000);
	}
	usleep(400000);
	ft_close_all(conf->number, conf);
	ft_free_phs(phs, conf->number);
	return (1);
}

int	main(int argc, char **argv)
{
	t_conf	c;
	t_conf	*conf;

	if (argc != 5 && argc != 6)
		return (printf("Args error\n") * 0);
	conf = &c;
	conf = ft_get_conf(argc, argv, conf);
	if (conf)
		conf = ft_get_muts_forks(argc - 1, conf);
	if (conf)
	{
		if (ft_get_time(&(conf->time_start)) == 0 || \
		 ft_process(argc - 1, conf) == 0)
		{
			ft_clear_conf(conf);
			printf("Some error\n");
			return (0);
		}
		ft_clear_conf(conf);
		return (0);
	}
	return (printf("Args error \n") * 0);
}
