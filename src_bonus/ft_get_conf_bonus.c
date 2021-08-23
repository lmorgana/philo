#include "header_bonus.h"

int	ft_clear_conf_bonus(t_conf *conf)
{
	if (conf)
	{
		if (conf->pids)
			free(conf->pids);
		free(conf);
		return (1);
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

t_conf	*ft_get_conf(int argc, char **argv)
{
	t_conf	*conf;

	conf = malloc(sizeof(t_conf));
	if (conf)
	{
		conf->number = -1;
		conf->t_die = -1;
		conf->t_eat = -1;
		conf->t_sleep = -1;
		conf->num_of_eating = -1;
		conf->num_finish_eat = 0;
		conf->is_dead = -1;
		if (ft_take_args(argc, argv, conf))
		{
			if (!(conf->number < 1 || conf->num_of_eating == 0 || \
			conf->number >= 200 || \
			conf->t_die < 10 || conf->t_eat < 10 || conf->t_sleep < 10))
				return (conf);
		}
		free(conf);
	}
	return (NULL);
}
