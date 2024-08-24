/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:18:23 by pierre            #+#    #+#             */
/*   Updated: 2024/08/23 11:04:24 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# define LEFT 0
# define RIGHT 1

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					meals_eaten;
	long long			last_meal;
	struct s_data		*data;
	pthread_t			thread;
}	t_philo;

typedef struct s_data
{
	int					numb_philo;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					max_eat;
	int					dead;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		write;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		incr_eat;
	t_philo				philosophers[250];
}	t_data;

// main.c
int			main(int argc, char **argv);
void		simulation(char **argv, int argc);
int			is_dead(t_data *data);
void		eat(t_data *data, t_philo *philo);

// init.c
int			init(int argc, char **argv, t_data *data);
void		init_philos(t_data *data);
int			init_mutexs(t_data *data);
int			get_mealtimes(t_data *data, t_philo *philo);

// parcer.c
int			parser(char **argv);
int			is_overflow(char *str);
void		ft_putstr_fd(char *str, int fd);

// threads.c
int			launch_threads(t_data *data);
void		clear_mutthre(t_data *data, t_philo *philo);
void		*routine(void *arg);
void		monitor(t_data *data, t_philo *philos);
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