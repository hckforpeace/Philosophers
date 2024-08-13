/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:05:41 by pierre            #+#    #+#             */
/*   Updated: 2024/08/08 19:41:25 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_integer(char *str)
{
	int	i;

	i = 0;
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