/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:39:00 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 23:26:59 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	val;
	int	isneg;

	isneg = 1;
	val = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		isneg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		val = (10 * val) + *nptr - '0';
		nptr++;
	}
	return (val * isneg);
}

/* retreives time_stamp in milliseconds */
long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		time_stamp;
	long long		seconds;
	long long		microseconds;

	if (gettimeofday(&tv, NULL) != 0)
	{
		ft_putstr_fd("Error has occured in gettimeofday!\n", 2);
		exit(1);
	}
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	time_stamp = seconds + microseconds;
	return (time_stamp);
}

void	ft_sleep(t_data *data, long long time)
{
	long long	start;

	start = get_timestamp();
	while (!is_dead(data))
	{
		if (get_timestamp() - start >= time)
			break ;
		usleep(50);
	}
}

int	is_dead(t_data *data)
{
	if (get_timestamp() - data->last_meal > data->ttd)
		return (1);
	return (0);
}
