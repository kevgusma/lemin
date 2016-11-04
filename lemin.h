#ifndef LEMIN_H
# define LEMIN_H
# include "get_next_line.h"
# include "libft/libft.a"

typedef struct		s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}					t_list;
#endif
