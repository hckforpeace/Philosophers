/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 14:54:26 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <error.h>
# define LEFT 0
# define RIGHT 1

typedef struct s_data
{
	int					nbr_philo;
	int					ttd;
	int					tte;
	int					tts;
	int					max_meals;
	int					meals_eaten;
	int					id;
	long long			last_meal;
	sem_t				*forks;
	sem_t				*write;
}	t_data;

// main.c
int			main(int argc, char **argv);
void		simulation(char **argv, int argc);
int			is_dead(t_data *data);
void		eat(t_data *data, t_philo *philo);

// init.c
int			init(int argc, char **argv, t_data *data);
void		init_philos(t_data *data);
int			init_sems(t_data *data);
int			get_mealtimes(t_data *data, t_philo *philo);

// parcer.c
int			parser(char **argv);
int			is_overflow(char *str);
void		ft_putstr_fd(char *str, int fd);

// threads.c
int			launch_children(t_data *data);
void		*routine(t_data *data, int num);
// void		monitor(t_data *data, t_philo *philos);
int			all_ate(t_data *data);

// utils.c
int			ft_atoi(const char *nptr);
long long	get_timestamp(void);
void		thread_sleep(t_data *data, long long time);
void		set_dead(t_data *data, t_philo *philo);

// libft_utils.c
double		ft_atof(const char *string);
int			numb_len(long num, int base);
int			ft_pow(int i, int pow);
int			ft_strlen(char *str);

// display.c
void		display(t_data *data, t_philo *philo, char state);
void		display_error(int type);

#endif