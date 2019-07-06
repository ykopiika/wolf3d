/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:47:20 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/03 12:47:23 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

////////////////////////
# include <stdio.h>/////
# include <stdbool.h>///
////////////////////////

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "SDL2/SDL.h"

#define WIN			wolf->sdl_data.win
#define SURF_WIN	wolf->sdl_data.surf_win

# define ERR_USAGE	0
# define ERR_MALLOC	1
# define ERR_SDL	2
# define ERR_ARGV	3

# define S_SIZE	15
# define M_SIZE	25
# define L_SIZE	35

# define WDTH 1200
# define HGHT 800

typedef struct			s_sdl_ptr
{
	SDL_Window 			*win;
	SDL_Surface 		*surf_win;
}						t_sdl_ptr;

typedef struct			s_read
{
	char				*line;
	int					row;
	int					len;

	struct s_read		*next;
	struct s_read		*prev;
}						t_read;

typedef struct			s_wolf
{
	t_sdl_ptr			sdl_data;
	t_read				*read;

	SDL_Surface 		*bmp;
	SDL_Surface 		*bmp_b;
}						t_wolf;

void	w_error(int err_nb);
void	w_valid_map(t_wolf *wolf, int fd);

#endif
