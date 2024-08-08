/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/08/01 20:56:16 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->numb_philo);
	if (!threads)
		return (NULL);
	i = 0;
	while (i < data->numb_philo)
	{
		if (pthread_create(&threads[i], NULL, &routine, &data->philos[i]) != 0)
		{
			write(2, "Error in thread creation !\n", 27);
			break ;
		}
		i++;
	}
}

void	routine(t_philo *philo)
{
	while (!*philo->dead)
	{
		eat(philo);
		sleep(philo->time_to_sleep);
		think();
	}
}