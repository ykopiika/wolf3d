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

//	REN = SDL_CreateRenderer( WIN, -1, SDL_RENDERER_ACCELERATED );
//	SDL_RenderSetLogicalSize( REN, WDTH, HGHT );
//	SDL_RenderClear (REN);
//	SDL_SetRenderDrawColor( REN, 255, 0, 0, 255 );
//	SDL_RenderDrawLine(REN,0,0,20,20);
//	SDL_RenderPresent (REN);

//	SDL_Delay(50);
//		t_point	left;
//		t_point	right;
//		left = (t_point){.x = -0.049, .y = 0.998};
//		right = (t_point){.x = 0.049, .y = 0.998};


}

void w_event(t_wolf *wolf)
 {
	 int running = 1;

	 while (running)
	 {
		 FRAME.oldTime = FRAME.time;
		 FRAME.time = SDL_GetTicks();
		 FRAME.frameTime = (FRAME.time - FRAME.oldTime) / 1000.0;
		 FRAME.moveSpeed = FRAME.frameTime * 5.0;
		 FRAME.rotSpeed = FRAME.frameTime * 3.0;
		 while(SDL_PollEvent(&EVENT))
		 {
		 	w_key_hook(wolf, &running);
		 }
	 }

//	 SDL_DestroyRenderer(REN);

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
	 LBRNT.rays = 1200;
	 LBRNT.turn = 0;

	 LBRNT.posX = 24.5;
	 LBRNT.posY = 2.5;
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

 	w_experyment(wolf);
// 	w_lodev(wolf);

 	w_event(wolf);
 	system ("leaks -q wolf3d");
 	return (0);
 }
