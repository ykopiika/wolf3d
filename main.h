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
# include "color.h"///
////////////////////////

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2_image/SDL_image.h"
# include "SDL2_ttf/SDL_ttf.h"

# define WIN		wolf->sdl_data.win
# define REN		wolf->sdl_data.ren
# define EVENT		wolf->sdl_data.event
# define SURF_WIN	wolf->sdl_data.surf_win
# define READ		wolf->read
# define FLAGS		wolf->flags
# define LBRNT		wolf->lbrnt
# define VALUE		wolf->value
# define FRAME		wolf->frame

# define S_PLYR		wolf->smbl.plyr
# define S_WALL		wolf->smbl.wall
# define S_FREE		wolf->smbl.free

# define RGB_Red		0xff00b7
# define RGB_Green		0x6cd100
# define RGB_Blue		0x0081d1
# define RGB_White		0xffffff
# define RGB_Yellow		0xffd000

# define ERR_USAGE			0
# define ERR_MALLOC			1
# define ERR_SDL			2
# define ERR_ARGV			3
# define ERR_LENGTH			4
# define ERR_HEIGHT			5
# define ERR_SIZE			6
# define ERR_WALL			7
# define ERR_FREE			8
# define ERR_WRONG_SYMBOL	9

# define WDTH 1200
# define HGHT 800

typedef struct			s_labyrinth
{
	int 				size;
	char 				**map;
	int 				rays;
	int 				turn;

	double 				posX;
	double 				posY;
	double 				dirX;
	double 				dirY;
	double 				planeX;
	double 				planeY;

}						t_labyrinth;

typedef struct			s_sdl_ptr
{
	SDL_Window 			*win;
	SDL_Surface 		*surf_win;

	SDL_Renderer 		*ren;
	SDL_Event 			event;
}						t_sdl_ptr;

typedef struct			s_read
{
	char				*line;
	int					row;
	int					len;

	struct s_read		*next;
	struct s_read		*prev;
}						t_read;

typedef struct			s_flags
{
	int 				free_sp;
	int 				player;

	int 				keydown_a;
	int 				keydown_d;
	int 				keydown_up;
	int 				keydown_down;
	int 				keydown_right;
	int 				keydown_left;
}						t_flags;

typedef struct			s_point
{
	double 				x;
	double 				y;
}						t_point;

typedef struct			s_symb_lab
{
	char 				plyr;
	char 				free;
	char 				wall;
}						t_symb_lab;

typedef struct			s_frame
{
	double				time;
	double				oldTime;
	double				frameTime;
	double				moveSpeed;
	double				rotSpeed;
}						t_frame;

typedef struct			s_wolf
{
	t_labyrinth			lbrnt;
	t_labyrinth			value;
	t_symb_lab			smbl;
	t_sdl_ptr			sdl_data;
	t_read				*read;
	t_flags				flags;
//	t_frame				frame;

	SDL_Surface 		**bmp;
	SDL_Surface 		*bmp_b;
}						t_wolf;

void	w_error(int err_nb);
void	w_valid_map(t_wolf *wolf, int fd);
void	w_lodev(t_wolf *wolf);
void	w_event(t_wolf *wolf);
void	w_raycasting(t_wolf *wolf);
void	w_key_hook(t_wolf *wolf);

#endif
