/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_key_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:41:42 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/12 17:41:45 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void turn_left_right(t_wolf *wolf)
{
	t_point	right;
	t_point	left;
	t_point	old_p;
	t_point	old_pl;

//	right = (t_point){.y =  0.998,.x =  -0.049 };
//	left =  (t_point){.y = 0.998,.x = 0.049};

	right = (t_point){.y =  0.9945,.x =  -0.1045 };
	left =  (t_point){.y = 0.9945,.x = 0.1045};
	old_p = (t_point){.x = LBRNT.dirX, .y = LBRNT.dirY};
	old_pl = (t_point){.x = LBRNT.planeX, .y = LBRNT.planeY};

	if (SDL_KEYDOWN == EVENT.type
		&& SDL_SCANCODE_D == EVENT.key.keysym.scancode)
	{
		LBRNT.dirX = old_p.x * right.y - old_p.y * right.x;
		LBRNT.dirY = old_p.x * right.x + old_p.y * right.y;
		LBRNT.planeX = old_pl.x * right.y - old_pl.y * right.x;
		LBRNT.planeY = old_pl.x * right.x + old_pl.y * right.y;
	}
	if (SDL_KEYDOWN == EVENT.type
		&& SDL_SCANCODE_A == EVENT.key.keysym.scancode)
	{
		LBRNT.dirX = (old_p.x * left.y) - (old_p.y * left.x);
		LBRNT.dirY = old_p.x * left.x + old_p.y * left.y;
		LBRNT.planeX = old_pl.x * left.y - old_pl.y * left.x;
		LBRNT.planeY = old_pl.x * left.x + old_pl.y * left.y;
	}
	w_experyment(wolf);
}

void w_key_hook(t_wolf *wolf, int *running)
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
	if (SDL_KEYDOWN == EVENT.type &&
			((SDL_SCANCODE_D == EVENT.key.keysym.scancode)
			|| (SDL_SCANCODE_A == EVENT.key.keysym.scancode)))
	{
		turn_left_right(wolf);

	}
	if (SDL_KEYDOWN == EVENT.type
		&& ((EVENT.key.keysym.scancode == SDL_SCANCODE_A)
			|| (EVENT.key.keysym.scancode == SDL_SCANCODE_D)))
	{
		printf("%.1f %.1f - dirX dirY\n", LBRNT.dirX, LBRNT.dirY);
		printf("%.1f %.1f - pl_X pl_Y\n\n", LBRNT.planeX, LBRNT.planeY);
	}
}

