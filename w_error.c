/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:17:33 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/05 15:17:37 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	w_error(int err_nb)
{
	system ("leaks -q wolf3d");
	if (err_nb == ERR_USAGE)
	{
		ft_putendl("Usage : ./wolf3d <the labyrinth>");
		exit(err_nb);
	}
	else if (err_nb == ERR_MALLOC)
	{
		ft_putendl("Malloc failed");
		exit(err_nb);
	}
	else if (err_nb == ERR_SDL)
	{
		ft_putendl("Get pointer from SDL_function failed");
		exit(err_nb);
	}
	else if (err_nb == ERR_ARGV)
	{
		ft_putendl("No file or empty map");
		exit(err_nb);
	}
}