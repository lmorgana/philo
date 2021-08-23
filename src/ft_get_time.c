#include "../header.h"

long	ft_get_mlsec(struct timeval *t_prev, struct timeval *t_now)
{
	long	t_time;

	if (t_prev && t_now)
	{
		t_time = (t_now->tv_sec - t_prev->tv_sec) * 1000;
		t_time += (t_now->tv_usec - t_prev->tv_usec) / 1000;
		return (t_time);
	}
	return (0);
}

int	ft_get_time(struct timeval *t_time)
{
	struct timezone	t_tz;

	if (gettimeofday(t_time, &t_tz) == 0)
		return (1);
	return (0);
}
