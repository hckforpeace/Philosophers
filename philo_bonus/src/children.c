/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:24:04 by pierre            #+#    #+#             */
/*   Updated: 2024/09/27 00:02:24 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Launches philo's thread, monitors with the main thread */
int	launch_children(t_data *data)
{
	int			i;
	int			pid;
	i = 0;
	while (i < data->nbr_philo)
	{
		data->id = i;
		pid = fork();
		if (pid == 0)
			routine(data);
		i++;
	}
	monitor(data);
	return (0);
}

/* destroy threads and mutexs */
void	clear_sems(t_data *data)
{
	if (sem_close(data->forks) < 0)
		ft_putstr_fd("sem_close error\n", 2);
	if (sem_close(data->write) < 0)
		ft_putstr_fd("sem_close error\n", 2);		
}

/* philo's routine */
void	routine(t_data *data)
{
	data->first_timestamp = get_timestamp();
	if (data->nbr_philo == 1)
	{
		sem_wait(data->forks);
		display(data, 'f');
		sem_post(data->forks);
		ft_sleep(data, data->ttd + 1);
		display(data, 'd');
		clear_sems(data);
		exit(EXIT_SUCCESS);
	}
	if (data->id % 2)
		usleep(15000);
	while (!is_dead(data))
	{
		eat(data);
		if (data->max_meals > 0 && data->meals_eaten > data->max_meals)
		{
			clear_sems(data);
			exit(EXIT_FAILURE);
		}
		display(data, 's');
		ft_sleep(data, data->tts);
		display(data, 't');
	}
	display(data, 'd');
	clear_sems(data);
	kill(-2, 15);
	exit(EXIT_SUCCESS);
}

/* checks if a philo is dead or if all the philo's are full */
void	monitor(t_data *data)
{
	int	status;

	while (errno != ECHILD)
		waitpid(0, &status, 0);
	clear_sems(data);
	sem_unlink("forks");
	sem_unlink("write");
}
