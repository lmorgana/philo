#include "../header.h"

int	ft_make_is_dead(t_conf *conf)
{
	pthread_mutex_lock(conf->mut_for_dead);
	conf->is_dead = 1;
	pthread_mutex_unlock(conf->mut_for_dead);
	return (0);
}

int	ft_is_dead(t_conf *conf)
{
	int	result;

	result = 0;
	pthread_mutex_lock(conf->mut_for_dead);
	if (conf->is_dead == 1)
		result = 1;
	pthread_mutex_unlock(conf->mut_for_dead);
	return (result);
}
