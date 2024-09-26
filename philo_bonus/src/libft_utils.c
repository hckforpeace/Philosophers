/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:50:27 by pierre            #+#    #+#             */
/*   Updated: 2024/09/26 21:51:07 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	numb_len(long num, int base)
{
	int	n;

	n = 0;
	if (num < 0)
		n++;
	while (num / base != 0)
	{
		num = num / base;
		n++;
	}
	n++;
	return (n);
}

int	ft_pow(int i, int pow)
{
	if (pow == 0)
		return (1);
	else
		return (i * ft_pow(i, pow - 1));
}

static double	get_decimal(const char *num)
{
	double	decimal;
	int		zero;

	decimal = 0.0;
	zero = 0;
	if (!*num)
		return (0.0);
	if (*num == '.')
		num++;
	while (*num == '0')
	{
		zero++;
		num++;
	}
	decimal += ft_atoi(num);
	decimal /= ft_pow(10, numb_len(decimal, 10) + zero);
	return (decimal);
}

double	ft_atof(const char *string)
{
	double	result;
	double	decimal;

	result = ft_atoi(string);
	decimal = get_decimal(&string[numb_len(result, 10)]);
	result += decimal;
	return (result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
