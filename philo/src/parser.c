/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:05:41 by pierre            #+#    #+#             */
/*   Updated: 2024/08/23 13:03:00 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_integer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (*str == '-' || (str[0] == '0' && str[1] != '\0'))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parser(char **argv)
{
	while (*argv)
	{
		if (is_integer(*argv) && !is_overflow(*argv))
			argv++;
		else
			return (0);
	}
	return (1);
}

int	is_overflow(char *str)
{
	double	vald;
	int		vali;

	vald = ft_atof(str);
	vali = ft_atoi(str);
	if (*str == '-' && ft_strlen(str) > 11)
		return (1);
	else if (*str != '-' && ft_strlen(str) > 10)
		return (1);
	if (vald != vali)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
		write(fd, str, len);
}
