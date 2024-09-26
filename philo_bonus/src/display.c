/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:47:43 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 23:54:47 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* displays state with time_stamp first checks if philo is not 
dead and then locks write mutex before writing */
void	display(t_data *data, char state)
{
	long long	time;

	time = get_timestamp() - data->first_timestamp;
	sem_wait(data->write);
	if (state == 'f')
		printf("%09lld %d has taken a fork\n", time, data->id + 1);
	else if (state == 'e')
		printf("%09lld %d is eating\n", time, data->id + 1);
	else if (state == 's')
		printf("%09lld %d is sleeping\n", time, data->id + 1);
	else if (state == 't')
		printf("%09lld %d is thinking\n", time, data->id + 1);
	else if (state == 'd')
		printf("%09lld %d has died\n", time, data->id + 1);
	sem_post(data->write);
}

void	display_error(int type)
{
	if (type == 0)
	{
		ft_putstr_fd("error(s) in arguments format:\n\n", 2);
		ft_putstr_fd("./philo nbr_philo ttd tte tts", 2);
		ft_putstr_fd("[max eat for each philo] OPTIONAL\n", 2);
		ft_putstr_fd("numbers must be positive and in", 2);
		ft_putstr_fd("fit in a type int\n", 2);
	}
	else if (type == 1)
		ft_putstr_fd("An error of logic has occured check your args\n", 2);
	else if (type == 2)
		ft_putstr_fd("An error has occured while initialisation\n", 2);
}
