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

void	w_valid_map(t_wolf *wolf, int fd)
{
	(void)wolf;

	int		gnl;
	char	*string;

	wolf->read = NULL;
	string = NULL;
	gnl = 0;

	while ((gnl = get_next_line(fd, &string)) == 1)
	{
		fill_str(string);
		wolf->l = malloc_lst(wolf->l, string);
		f_read_coord(wolf->l);
		ft_strdel(&string);
	}
	if (wolf->l == NULL || gnl == -1)
		f_error("No file or empty map");


	while (wolf->l->prev)
	{
		if (wolf->l->col != wolf->l->prev->col)
			f_error("Found wrong line length. Exiting.");
		wolf->l->prev->row = wolf->l->row;
		wolf->l = wolf->l->prev;
	}
}

//			**************************
//			*                        *
//			*   ***                  *
//			*   ***        +         *
//			*   ***                  *
//			*                        *
//			**************************