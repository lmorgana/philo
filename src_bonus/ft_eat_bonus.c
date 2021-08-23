#include "header_bonus.h"

int	ft_eat(int index, struct timeval *time_last_eat, t_conf *conf)
{
	if (ft_is_dead(time_last_eat, conf))
	{
		ft_write_msg("%ld %d died\n", index, conf, 1);
		return (0);
	}
	sem_wait(conf->num_of_forks);
	sem_wait(conf->num_of_forks);
	ft_write_msg("%ld %d has taken a fork\n", index, conf, 0);
	ft_write_msg("%ld %d has taken a fork\n", index, conf, 0);
	ft_write_msg("%ld %d is eating\n", index, conf, 0);
	if (ft_my_usleep_bonus(conf->t_eat, time_last_eat, conf) == 0)
	{
		ft_write_msg("%ld %d died\n", index, conf, 1);
		return (0);
	}
	ft_get_time(time_last_eat);
	sem_post(conf->num_of_forks);
	sem_post(conf->num_of_forks);
	return (1);
}

int	ft_sleep_think(int index, struct timeval *time_last_eat, t_conf *conf)
{
	ft_write_msg("%ld %d is sleeping\n", index, conf, 0);
	if (ft_my_usleep_bonus(conf->t_sleep, time_last_eat, conf) == 0)
	{
		ft_write_msg("%ld %d died\n", index, conf, 1);
		return (0);
	}
	ft_write_msg("%ld %d is thinking\n", index, conf, 0);
	return (1);
}
