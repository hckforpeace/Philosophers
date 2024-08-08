/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:28:57 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 17:53:24 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*get_next_line(int fd)
{
	t_list		*lst;
	int			ret;
	char		*str;
	static char	buffer[BUFFER_SIZE];

	lst = NULL;
	ret = 1;
	if (fd < 0)
		return (NULL);
	if (*buffer)
		add_node(&lst, ft_setter(buffer), buffer);
	while (!contains_nextline(buffer) && ret > 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0 && !add_node(&lst, ret, buffer))
			return (NULL);
		if (ret < 0)
			return (ft_lstclear(&lst, free), NULL);
	}
	str = get_string(lst);
	ft_lstclear(&lst, free);
	if (!*str)
		return (free(str), NULL);
	return (str);
}

int	add_node(t_list **lst, int len, char *buffer)
{
	char	*str;
	t_list	*new;
	int		n;

	n = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (ft_lstclear(lst, free), 0);
	while (buffer[n])
	{
		str[n] = buffer[n];
		n++;
	}
	str[n] = '\0';
	new = ft_lstnew(str, len);
	if (!new)
		return (ft_lstclear(lst, free), 0);
	ft_lstadd_back(lst, new);
	return (1);
}

int	contains_nextline(char *s)
{
	int	n;

	n = 0;
	while (s[n])
	{
		if (s[n] == '\n')
			return (1);
		n++;
	}
	return (0);
}

int	ft_setter(char *buffer)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (buffer[n] != '\n')
	{
		buffer[n] = '\0';
		n++;
	}
	buffer[n] = '\0';
	n++;
	while (buffer[n])
	{
		buffer[i] = buffer[n];
		buffer[n] = '\0';
		i++;
		n++;
	}
	return (i);
}
/* #define FILE_NAME "fchier.txt"
#include <fcntl.h>

int	main()
{
	int fd = open(FILE_NAME, O_RDONLY);
	char *str;
	do{
		str = get_next_line(fd);
	}while (str != NULL);

	return (0);
} */