/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:15:43 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/05 18:15:46 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_read	*malloc_lst(t_read *read, char *str)
{
	if (!read)
	{
		if (!(read = (t_read *)malloc(sizeof(t_read))))
			w_error(ERR_MALLOC);
		read->line = ft_strdup(str);
		read->row = 0;
		read->len = ft_strlen(str);
		read->next = NULL;
		read->prev = NULL;
		return (read);
	}
	else
	{
		read->next = (t_read *)malloc(sizeof(t_read));
		if (!read->next)
			w_error(ERR_MALLOC);
		read->next->line = ft_strdup(str);
		read->next->row = read->row + 1;
		read->next->len = ft_strlen(str);
		read->next->next = NULL;
		read->next->prev = read;
		return (read->next);
	}
}

static void first_line(t_wolf *wolf)
{
	if (ft_strcmp(READ->line, "labyrinth_size: 15") == 0)
		LBRNT.size = 15;
	else if (ft_strcmp(READ->line, "labyrinth_size: 25") == 0)
		LBRNT.size = 25;
	else if (ft_strcmp(READ->line, "labyrinth_size: 35") == 0)
		LBRNT.size = 35;
	else
		w_error(ERR_SIZE);
}

static void w_valid_read(t_wolf *wolf)
{
	int i;
	int j;

	i = 0;
	first_line(wolf);
	while(READ->next)
	{
		READ = READ->next;
		if (READ->len != LBRNT.size)
			w_error(ERR_LENGTH);
		if (i == 0 || i == (LBRNT.size - 1))
		{
			j = -1;
			while (++j < READ->len)
				if (READ->line[j] != S_WALL)
					w_error(ERR_WALL);
		}
		if ((READ->line[0] != S_WALL) || (READ->line[READ->len - 1] != S_WALL))
			w_error(ERR_WALL);
		i++;
	}
	if (i != LBRNT.size)
		w_error(ERR_HEIGHT);
}

void	w_valid_map(t_wolf *wolf, int fd)
{
	int		gnl;
	char	*string;

	gnl = 0;
	string = NULL;
	READ = NULL;
	while ((gnl = get_next_line(fd, &string)) == 1)
	{
		READ = malloc_lst(READ, string);
		ft_strdel(&string);
		printf("%d \t %d %s$\n", wolf->read->row,
				wolf->read->len, wolf->read->line);
	}
	if ((READ == NULL) || gnl == -1)
		w_error(ERR_ARGV);
	while (READ->prev != NULL)
		READ = READ->prev;
	w_valid_read(wolf);
}