/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevgusma <kevgusma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 15:13:01 by kevgusma          #+#    #+#             */
/*   Updated: 2015/03/21 18:05:55 by kevgusma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128

typedef struct		s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);

#endif
