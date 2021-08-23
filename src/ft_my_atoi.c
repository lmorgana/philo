#include "../header.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

static int	mk_num(const char *str, int *num_res, int si)
{
	size_t			i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + str[i] - 48;
		if (num > 2147483647)
		{
			if (num == 2147483648 && si < 0)
			{
				num = num * si;
				break ;
			}
			return (0);
		}
		i++;
	}
	*num_res = num * si;
	return (1);
}

int	ft_my_atoi(const char *str, int *numb)
{
	size_t		i;
	char		ch;
	int			si;

	i = 0;
	si = 1;
	while (i < ft_strlen(str))
	{
		ch = str[i];
		if (ft_isdigit(ch))
			return (mk_num(&str[i], numb, si));
		else if (ch == '-' || ch == '+')
		{
			if (ch == '-')
				return (0);
			if (ft_isdigit(str[i + 1]))
				return (si * mk_num(&str[i + 1], numb, si));
			return (0);
		}
		else if ((ch < 9 || ch > 13) && ch != 32)
			return (0);
		i++;
	}
	return (0);
}
