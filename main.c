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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		w_error(ERR_SDL);
	WIN = SDL_CreateWindow("Hello SDL World",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WDTH, HGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	if (!WIN)
		w_error(ERR_SDL);

	SURF_WIN = SDL_GetWindowSurface(WIN);
	wolf->bmp_b = SDL_LoadBMP("../img/sur.bmp");
	wolf->bmp = SDL_LoadBMP("../img/hello.bmp");
	SDL_BlitSurface( wolf->bmp, NULL, SURF_WIN, NULL);
	SDL_BlitSurface( wolf->bmp_b, NULL, SURF_WIN, NULL );
	SDL_UpdateWindowSurface(WIN);
//	SDL_Delay(50);
//		t_point	left;
//		t_point	right;
//		left = (t_point){.x = -0.049, .y = 0.998};
//		right = (t_point){.x = 0.049, .y = 0.998};
}

static void w_key_hook(t_wolf *wolf, int *running)
{
	if((SDL_QUIT == EVENT.type) || (SDL_KEYDOWN == EVENT.type
		&& SDL_SCANCODE_ESCAPE == EVENT.key.keysym.scancode))
		*running = 0;
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_DOWN == EVENT.key.keysym.scancode))
	{
		printf("DOWN\n");
		if (LBRNT.posY < LBRNT.size - 1)
			LBRNT.posY += 1;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_UP == EVENT.key.keysym.scancode))
	{
		printf("UP\n");
		if (LBRNT.posY >= 1)
			LBRNT.posY -= 1;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_RIGHT == EVENT.key.keysym.scancode))
	{
		printf("RIGHT\n");
		if (LBRNT.posX < LBRNT.size - 1)
			LBRNT.posX += 1;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_LEFT == EVENT.key.keysym.scancode))
	{
		printf("LEFT\n");
		if (LBRNT.posX >= 1)
			LBRNT.posX -= 1;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_D == EVENT.key.keysym.scancode))
	{
		printf("TURN_RIGHT\n");
		t_point	right;
		t_point	old_p;
		t_point	old_pl;

		right = (t_point){.y = 0.049, .x = 0.998};
		old_p = (t_point){.x = LBRNT.dirX, .y = LBRNT.dirY};
		old_pl = (t_point){.x = LBRNT.planeX, .y = LBRNT.planeY};

		LBRNT.dirX = old_p.x * right.y - old_p.y * right.x;
		LBRNT.dirY = old_p.x * right.x - old_p.y * right.y;
		LBRNT.planeX = old_pl.x * right.y - old_pl.y * right.x;
		LBRNT.planeY = old_pl.x * right.x - old_pl.y * right.y;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_A == EVENT.key.keysym.scancode))
	{
		printf("TURN_LEFT\n");
		t_point	left;
		t_point	old_p;
		t_point	old_pl;

		left = (t_point){.y = -0.049, .x = -0.998};
		old_p = (t_point){.x = LBRNT.dirX, .y = LBRNT.dirY};
		old_pl = (t_point){.x = LBRNT.planeX, .y = LBRNT.planeY};

		LBRNT.dirX = (old_p.x * left.y) - (old_p.y * left.x);
		LBRNT.dirY = old_p.x * left.x - old_p.y * left.y;
		LBRNT.planeX = old_pl.x * left.y - old_pl.y * left.x;
		LBRNT.planeY = old_pl.x * left.x - old_pl.y * left.y;
		w_experyment(wolf);
	}
	if (SDL_KEYDOWN == EVENT.type
		&& ((EVENT.key.keysym.scancode == SDL_SCANCODE_A)
		|| (EVENT.key.keysym.scancode == SDL_SCANCODE_D)))
	{
		printf("%.1f %.1f - dirX dirY\n", LBRNT.dirX, LBRNT.dirY);
		printf("%.1f %.1f - pl_X pl_Y\n\n", LBRNT.planeX, LBRNT.planeY);
	}
}

void w_event(t_wolf *wolf)
 {
	 int running = 1;

	 while (running)
		 while(SDL_PollEvent(&EVENT))
		 	w_key_hook(wolf, &running);

//	 SDL_DestroyRenderer(REN);

	 SDL_DestroyWindow(WIN);
	 SDL_Quit();
 }

 static void init_param(t_wolf	*wolf)
 {
	 S_FREE = ' ';
	 S_WALL = '*';
	 S_PLYR = '+';
	 FLAGS.free_sp = 0;
	 FLAGS.player = 0;
	 LBRNT.rays = 100;

	 LBRNT.posX = 12.5;
	 LBRNT.posY = 12.5;
	 LBRNT.dirX = -1;
	 LBRNT.dirY = 0;
	 LBRNT.planeX = 0;
	 LBRNT.planeY = 0.60;
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

 	w_experyment(wolf);
// 	w_lodev(wolf);

 	w_event(wolf);
 	system ("leaks -q wolf3d");
 	return (0);
 }
