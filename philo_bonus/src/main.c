/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:34:05 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 23:34:33 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (parser(&argv[1]))
			simulation(&argv[0], argc);
		else
			display_error(0);
	}
	else
		display_error(0);
	return (0);
}

/* Init, launch simulation and checks errors */
void	simulation(char **argv, int argc)
{
	t_data	data;

	if (init(argc, argv, &data))
	{
		display_error(1);
		return ;
	}
	if (launch_children(&data))
	{
		display_error(2);
		return ;
	}
}

/* eat routine */
void	eat(t_data *data)
{
	sem_wait(data->forks);
	display(data, 'f');
	sem_wait(data->forks);
	display(data, 'f');
	display(data, 'e');
	data->last_meal = get_timestamp();
	data->meals_eaten++;
	ft_sleep(data, data->tte);
	sem_post(data->forks);
	sem_post(data->forks);
}
