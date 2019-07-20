/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:23:26 by ykopiika          #+#    #+#             */
/*   Updated: 2019/05/14 13:23:29 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_wolf(t_wolf *wolf)
{
	int i;

	i = -1;
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
	wolf->bmp = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 8);
	if (!wolf->bmp)
		w_error(ERR_MALLOC);
	wolf->bmp[0] = IMG_Load("./img/bricks.bmp");
	wolf->bmp[1] = IMG_Load("./img/lavaf4.bmp");
	wolf->bmp[2] = IMG_Load("./img/leavesop.bmp");
	wolf->bmp[3] = IMG_Load("./img/walkstone.bmp");
	wolf->bmp[4] = IMG_Load("./img/bluestone.bmp");
	wolf->bmp[5] = IMG_Load("./img/redbrick.bmp");
	wolf->bmp[6] = IMG_Load("./img/wood.bmp");
	wolf->bmp[7] = IMG_Load("./img/eagle.bmp");
	SDL_SetColorKey(SURF_WIN, SDL_TRUE, SDL_MapRGB(SURF_WIN->format,0,0,0));

	while (++i < 8)
	{
		if (!(wolf->bmp[i]))
			w_error(ERR_SDL);
	}
}

static void w_event(t_wolf *wolf)
 {
	 int running = 1;
	 int key;

	 while (running)
	 {
		FRAME.oldTime = FRAME.time;
		FRAME.time = SDL_GetTicks();
		FRAME.frameTime = (FRAME.time - FRAME.oldTime) / 1000.0;
		FRAME.moveSpeed = FRAME.frameTime * 5.0;
		FRAME.rotSpeed = FRAME.frameTime * 3.0;
		 while(SDL_PollEvent(&EVENT))
		 {
		 	key = EVENT.key.keysym.sym;
		 	if(EVENT.type == SDL_QUIT
				|| (EVENT.type == SDL_KEYDOWN
				&& key == SDLK_ESCAPE))
				 running = 0;
		 	if (EVENT.type == SDL_KEYDOWN && key == SDLK_a)
			 	FLAGS.keydown_a = 1;
		 	if (EVENT.type == SDL_KEYUP && key == SDLK_a)
				FLAGS.keydown_a = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_d)
				 FLAGS.keydown_d = 1;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_d)
				 FLAGS.keydown_d = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_UP)
				 FLAGS.keydown_up = 1;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_UP)
				 FLAGS.keydown_up = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_DOWN)
				 FLAGS.keydown_down = 1;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_DOWN)
				 FLAGS.keydown_down = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_LEFT)
				 FLAGS.keydown_left = 1;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_LEFT)
				 FLAGS.keydown_left = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_RIGHT)
				 FLAGS.keydown_right = 1;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_RIGHT)
				 FLAGS.keydown_right = 0;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_LSHIFT)
				 FLAGS.speed = 2;
			 if (EVENT.type == SDL_KEYUP && key == SDLK_LSHIFT)
				 FLAGS.speed = 1;

			 if (EVENT.type == SDL_KEYDOWN && key == SDLK_t)
				 FLAGS.textur = (FLAGS.textur == 0) ? 4 : 0;

		 }
		 w_key_hook(wolf);
		 w_raycasting(wolf);
	 }

	 SDL_DestroyWindow(WIN);
	 SDL_Quit();
 	system ("leaks -q wolf3d");
 }

 static void init_param(t_wolf	*wolf)
 {
	 S_FREE = ' ';
	 S_WALL = '*';
	 S_PLYR = '+';
	 FLAGS.free_sp = 0;
	 FLAGS.player = 0;
	 LBRNT.rays = WDTH;
	 FLAGS.textur = 0;
	 FLAGS.speed = 1;

	 LBRNT.posX = 16.5;
	 LBRNT.posY = 12.5;

	 LBRNT.dirX = -1;
	 LBRNT.dirY = 0;
	 LBRNT.planeX = 0;
	 LBRNT.planeY = 0.60;
	 VALUE = LBRNT;
 }

 int main(int ac, char **av)
 {
 	t_wolf	*wolf;
 	int 	fd;

 	if (ac != 2)
 		w_error(ERR_USAGE);
 	wolf = (t_wolf *)malloc(sizeof(t_wolf));
 	if (!wolf)
 		w_error(ERR_MALLOC);

	init_param(wolf);

 	fd = open(av[1], O_RDONLY);
 	w_valid_map(wolf, fd);
 	close(fd);

 	init_wolf(wolf);

	 w_raycasting(wolf);

 	w_event(wolf);
 	system ("leaks -q wolf3d");
 	return (0);
 }
