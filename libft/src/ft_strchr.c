/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:23:05 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:32:34 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				n;
	unsigned char	v;
	char			*str;

	str = (char *)s;
	v = c;
	n = 0;
	while (str[n])
	{
		if ((unsigned char)str[n] == v)
			return (&str[n]);
		n++;
	}
	if ((unsigned char)str[n] == v)
		return (&str[n]);
	return (NULL);
}
