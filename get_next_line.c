/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevgusma <kevgusma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 15:05:27 by kevgusma          #+#    #+#             */
/*   Updated: 2015/05/01 22:38:16 by kevgusma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

static int		delete_mailon(t_list **list, int fd, char *str)
{
	t_list	*p_list;
	size_t	count;

	p_list = (*list);
	count = 0;
	while (p_list != NULL)
	{
		count++;
		if (p_list->fd == fd)
			break ;
		p_list = p_list->next;
	}
	if (count == 1)
		*p_list = (t_list){0, ft_strnew(1), NULL};
	else if (p_list->next->next == NULL)
		*p_list = (t_list){p_list->next->fd, ft_strdup(p_list->str), NULL};
	free(p_list->next);
	free(str);
	str = NULL;
	return (0);
}

static t_list	*create_mailon(int fd, t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if ((tmp = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	*tmp = (t_list){fd, ft_strnew(1), (*list)};
	(*list) = tmp;
	return (tmp);
}

static int		get_next_line_ret(char **line, char **str)
{
	size_t		lenght;
	char		*tmp;

	if (ft_strchr(*str, '\n') != NULL)
	{
		tmp = *str;
		lenght = ft_strchr(*str, '\n') - *str;
		if (ft_strint(*str, '\n') == 0)
		{
			*line = NULL;
			*str = ft_strsub(*str, 1, ft_strlen(*str));
		}
		else
		{
			*line = ft_strsub(*str, 0, lenght);
			*str = ft_strsub(*str, lenght + 1, ft_strlen(*str));
		}
		ft_free(tmp);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_free(*str);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*p_list;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	if (fd == -1 || BUFF_SIZE <= 0 || line == NULL
		|| (p_list = create_mailon(fd, &list)) == NULL)
		return (-1);
	while (ft_strchr(p_list->str, '\n') == NULL
			&& (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = p_list->str;
		p_list->str = ft_strjoin(p_list->str, buf);
		free(tmp);
		tmp = NULL;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && ft_strlen(p_list->str) == 0)
		return (delete_mailon(&list, fd, p_list->str));
	get_next_line_ret(line, &p_list->str);
	return (1);
}
