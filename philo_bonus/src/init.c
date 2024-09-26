/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:20:25 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/26 14:21:19 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* inits the t_data struct and checks for possible logic 
errors and inits mutexs */
int	init(int argc, char **argv, t_data *data)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (argc == 5)
		data->max_meals = -1;
	else
		data->max_meals = ft_atoi(argv[5]);
	if (data->nbr_philo == 0 || data->max_meals == 0)
		return (1);
	if (init_sems(data))
		return (1);
	return (0);
}

int	init_sems(t_data *data)
{
	int	i;

	i = 0;
	data->forks = sem_open("forks", O_CREAT, O_CREAT, data->nbr_philo);
	if (errno == SEM_FAILED)
		return (1);
	data->write = sem_open("forks", O_CREAT, O_CREAT, 1);
	if (errno == SEM_FAILED)
		return (1);
	return (0);
}

int	get_mealtimes(t_data *data, t_philo *philo)
{
	int	val;

	sem_wait(&data->incr_eat);
	val = philo->meals_eaten;
	sem_post(&data->incr_eat);
	return (val);
}
