#include "header_bonus.h"

int	ft_is_dead(struct timeval *time_last_eat, t_conf *conf)
{
	struct timeval	time_now;

	ft_get_time(&time_now);
	return (ft_get_mlsec((time_last_eat), &time_now) > conf->t_die);
}

int	ft_write_msg(char *msg, int index, t_conf *conf, int is_dead)
{
	struct timeval	time_now;
	long			t_time;

	sem_wait(conf->sem_for_msg);
	ft_get_time(&time_now);
	t_time = ft_get_mlsec(&(conf->time_start), &time_now);
	printf(msg, t_time, index + 1);
	if (is_dead == 0)
		sem_post(conf->sem_for_msg);
	return (0);
}

int	ft_for_one_philo_bonus(t_conf *conf)
{
	ft_write_msg("%ld %d has taken a fork\n", 0, conf, 0);
	usleep(conf->t_die * 1000);
	ft_write_msg("%ld %d died\n", 0, conf, 0);
	conf->is_dead = 1;
	return (1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write(fd, &s[i], fd);
			i++;
		}
	}
}

int	ft_err_msg(char *str)
{
	if (str)
		ft_putstr_fd(str, 1);
	return (0);
}
