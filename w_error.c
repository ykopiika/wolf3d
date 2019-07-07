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
	printf(T_RED);
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
	else if (err_nb == ERR_LENGTH)
	{
		ft_putendl("Length of your labyrinth not equal to size");
		exit(err_nb);
	}
	else if (err_nb == ERR_HEIGHT)
	{
		ft_putendl("Height of your labyrinth not equal to size");
		exit(err_nb);
	}
	else if (err_nb == ERR_SIZE)
	{
		ft_putendl("labyrinth_size is invalid");
		exit(err_nb);
	}
	else if (err_nb == ERR_WALL)
	{
		ft_putendl("Detected free space in the labyrinth perimeter");
		exit(err_nb);
	}
	else if (err_nb == ERR_FREE)
	{
		ft_putendl("There is no free place for a player in your labyrinth");
		exit(err_nb);
	}
}