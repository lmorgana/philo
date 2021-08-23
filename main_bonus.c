#include "src_bonus/header_bonus.h"

static int	ft_ch_pr_philo(int index, t_conf *conf)
{
	struct timeval	time_last_eat;
	int				stat;
	int				i;

	time_last_eat = conf->time_start;
	stat = 1;
	i = 0;
	while (stat != 0)
	{
		if (ft_eat(index, &time_last_eat, conf))
		{
			i++;
			if (conf->num_of_eating != -1 && index == conf->number - 1 \
			&& i >= conf->num_of_eating)
				return (1);
			stat = ft_sleep_think(index, &time_last_eat, conf);
		}
		else
			stat = 0;
	}
	return (1);
}

static	int	ft_process(int index, t_conf *conf)
{
	if (conf->number == 1)
	{
		ft_for_one_philo_bonus(conf);
		return (1);
	}
	if (index < conf->number)
	{
		conf->pids[index] = fork();
		if (conf->pids[index] < 0)
		{
			ft_close_pids(conf);
			return (0);
		}
		else if (conf->pids[index] == 0)
			return (ft_ch_pr_philo(index, conf));
		return (ft_process(index + 1, conf));
	}
	wait(0);
	ft_close_pids(conf);
	return (1);
}

int	main(int argc, char **argv)
{
	t_conf	*conf;

	if (argc != 5 && argc != 6)
		return (ft_err_msg("Args error\n"));
	conf = ft_get_conf(argc, argv);
	if (conf)
		conf = ft_get_pids(conf);
	if (conf)
	{
		if (ft_get_time(&(conf->time_start)) == 0 || \
		 ft_process(0, conf) == 0)
		{
			ft_clear_conf_bonus(conf);
			return (0);
		}
		ft_clear_conf_bonus(conf);
		return (1);
	}
	return (ft_err_msg("Args error \n"));
}
