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

void	w_valid_map(t_wolf *wolf, int fd)
{
	int		gnl;
	char	*string;

	gnl = 0;
	wolf->read = NULL;
	string = NULL;
	while ((gnl = get_next_line(fd, &string)) == 1)
	{
		wolf->read = malloc_lst(wolf->read, string);
		ft_strdel(&string);
	}
	if ((wolf->read == NULL) || gnl == -1)
		w_error(ERR_ARGV);
//	while (wolf->l->prev)
//	{
//		if (wolf->l->col != wolf->l->prev->col)
//			f_error("Found wrong line length. Exiting.");
//		wolf->l->prev->row = wolf->l->row;
//		wolf->l = wolf->l->prev;
//	}
}