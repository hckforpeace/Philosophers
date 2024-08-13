/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/08/13 13:49:32 by pierre           ###   ########.fr       */
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
	if (!data->forks || !data->write_lock || !data->dead_lock
		|| !data->checkeat_lock || !data->checklstmeal_lock
		|| !data->thread || !data->monitor || !data->philos)
	{

		free_exit(data, 1);
	}
}
void	free_exit(t_data *data, int code)
{
	free(data->forks);
	free(data->write_lock);
	free(data->dead_lock);
	free(data->checkeat_lock);
	free(data->checklstmeal_lock);
	free(data->thread);
	free(data->monitor);
	free(data->philos);
	exit(code);
}
void	destroy_mutexs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->write_lock);
	pthread_mutex_destroy(data->dead_lock);
	pthread_mutex_destroy(data->checklstmeal_lock);
	pthread_mutex_destroy(data->checkeat_lock);
}

int	display(t_philo *philo, char state)
{
	if (is_dead(philo))
		return (0);
	long long time;
	pthread_mutex_lock(philo->write_lock);
	time = get_timestamp() - philo->first_timestamp;
	if (state == 'l')
		printf("%09lld %d has taken left fork\n", time, philo->id);
	else if (state == 'r')
		printf("%09lld %d has taken right fork\n", time, philo->id);
	else if (state == 'e')
		printf("%09lld %d is eating\n", time, philo->id);
	else if (state == 's')
		printf("%09lld %d is sleeping\n", time, philo->id);
	else if (state == 't')
		printf("%09lld %d is thinking\n", time, philo->id);
	else if (state == 'd')
		printf("%09lld %d died\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (1);
}
