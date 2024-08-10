/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/08/09 13:36:05 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void alloc_dataparams(t_data *data)
{
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->numb_philo);
	data->write_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->checkeat_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->checklstmeal_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->thread = (pthread_t *)malloc(sizeof(pthread_t) * data->numb_philo);
	data->monitor = (pthread_t *)malloc(sizeof(pthread_t));
	data->philos = (struct s_philo *)malloc(sizeof(struct s_philo) * data->numb_philo);
	data->dead = (int *)malloc(sizeof(int));
	if (!data->forks || !data->write_lock || !data->dead_lock
		|| !data->checkeat_lock || !data->checklstmeal_lock
		|| !data->thread || !data->monitor || !data->philos || !data->dead)
	{

		free_exit(data);
	}
}
void	free_exit(t_data *data)
{
	fprintf(stderr, "nerve\n");
	free(data->forks);
	free(data->write_lock);
	free(data->dead_lock);
	free(data->checkeat_lock);
	free(data->checklstmeal_lock);
	free(data->thread);
	free(data->monitor);
	free(data->philos);
	free(data->dead);
	exit(1);
}
