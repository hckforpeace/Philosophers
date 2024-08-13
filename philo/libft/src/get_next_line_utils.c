/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:28:34 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 17:52:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*  void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
} */

/* t_list	*ft_lstnewgnl(void *content, int len)
{
	t_list	*liste;

	liste = (t_list *)malloc(sizeof(t_list));
	if (liste == NULL)
		return (NULL);
	liste->content = content;
	liste->len = len;
	liste->next = NULL;
	return (liste);
} */

/* void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*temp1;

	temp = *lst;
	while (temp != NULL)
	{
		temp1 = temp->next;
		free(temp->content);
		free(temp);
		temp = temp1;
	}
	*lst = NULL;
} */

char	*get_string(t_list *lst)
{
	char	*str;
	int		n;
	int		i;

	n = 0;
	str = (char *)malloc(sizeof(char) * (get_total_length(lst) + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	i = 0;
	while (lst != NULL)
	{
		while (n < lst->len)
		{
			str[i] = *(((char *)(lst->content)) + n);
			i++;
			if (*(((char *)(lst->content)) + n) == '\n')
				break ;
			n++;
		}
		n = 0;
		lst = lst->next;
	}
	str[i] = '\0';
	return (str);
}

int	get_total_length(t_list *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		len += lst->len;
		lst = lst->next;
	}
	return (len);
}
