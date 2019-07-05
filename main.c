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
}

 static void w_event(t_wolf *wolf)
 {
	 int running = 1;
	 SDL_Event event;

	 while (running)
		 while(SDL_PollEvent(&event))
			 if((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type
			 		&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				 running = 0;
	 SDL_DestroyWindow(WIN);
	 SDL_Quit();
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

 	fd = open(av[1], O_RDONLY);
 	w_valid_map(wolf, fd);
 	close(fd);

 	init_wolf(wolf);

 	w_event(wolf);
 	system ("leaks -q wolf3d");
 	return (0);
 }
