/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:23:26 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/21 19:36:30 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	load_image(t_wolf *wolf)
{
	int i;

	i = -1;
	BMP[0] = IMG_Load("./img/bricks.bmp");
	BMP[1] = IMG_Load("./img/lavaf4.bmp");
	BMP[2] = IMG_Load("./img/leavesop.bmp");
	BMP[3] = IMG_Load("./img/walkstone.bmp");
	BMP[4] = IMG_Load("./img/bluestone.bmp");
	BMP[5] = IMG_Load("./img/redbrick.bmp");
	BMP[6] = IMG_Load("./img/wood.bmp");
	BMP[7] = IMG_Load("./img/eagle.bmp");
	while (++i < 8)
	{
		if (!(BMP[i]))
			w_error(ERR_SDL);
	}
}

static void	init_wolf(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		w_error(ERR_SDL);
	WIN = SDL_CreateWindow("Hello SDL World",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WDTH, HGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!WIN)
		w_error(ERR_SDL);
	SURF_WIN = SDL_GetWindowSurface(WIN);
	if (!SURF_WIN)
		w_error(ERR_SDL);
	BMP = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 8);
	if (!BMP)
		w_error(ERR_MALLOC);
	load_image(wolf);
}

static void	init_param(t_wolf *wolf)
{
	S_FREE = ' ';
	S_WALL = '*';
	S_PLYR = '+';
	FLAGS.free_sp = 0;
	FLAGS.player = 0;
	LBRNT.rays = WDTH;
	FLAGS.textur = 0;
	FLAGS.speed = 1;
	FLAGS.zoom = 1.0;
	LBRNT.ply_drct_x = -1;
	LBRNT.ply_drct_y = 0;
	LBRNT.prjct_x = 0;
	LBRNT.prjct_y = 0.60;
	VALUE = LBRNT;
}

static void valid_name(char *name)
{
	int len;

	len = ft_strlen(name);
	if (len < 5)
		w_error(ERR_ARGV);
	if (ft_strcmp(".map", &name[len-4]) != 0)
		w_error(ERR_ARGV);
}

int			main(int ac, char **av)
{
	t_wolf	*wolf;
	int		fd;

	if (ac != 2)
		w_error(ERR_USAGE);
	wolf = (t_wolf *)malloc(sizeof(t_wolf));
	if (!wolf)
		w_error(ERR_MALLOC);
	init_param(wolf);

	valid_name(av[1]);

	fd = open(av[1], O_RDONLY);
	w_valid_map(wolf, fd);
	close(fd);
	init_wolf(wolf);
	w_raycasting(wolf);
	w_event(wolf);
	system("leaks -q wolf3d");//
	return (0);
}
