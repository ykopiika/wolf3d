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
	t_point	alpha;
	t_point	old_p;
	t_point	old_pl;

	right = (t_point){.y =  0.9945,.x =  -0.1045 };
	left =  (t_point){.y = 0.9945,.x = 0.1045};
	old_p = (t_point){.x = VALUE.dirX, .y = VALUE.dirY};
	old_pl = (t_point){.x = VALUE.planeX, .y = VALUE.planeY};


	if (LBRNT.turn == 15 || LBRNT.turn == -15)
	{
		if(LBRNT.turn < 0)
		{
			LBRNT.dirX = 0;
			LBRNT.dirY = 1;
			LBRNT.planeX = 0.60;
			LBRNT.planeY = 0;
		}
		else
		{
			LBRNT.dirX = 0;
			LBRNT.dirY = -1;
			LBRNT.planeX = -0.60;
			LBRNT.planeY = 0;
		}
	}
	if (LBRNT.turn == 60 || LBRNT.turn == -60)
	{
			LBRNT.dirX = -1;
			LBRNT.dirY = 0;
			LBRNT.planeX = 0;
			LBRNT.planeY = 0.60;
			LBRNT.turn = 0;
	}
	if (SDL_KEYDOWN == EVENT.type
		&& SDL_SCANCODE_D == EVENT.key.keysym.scancode)
	{
		alpha = left;
		LBRNT.turn++;
	}
	if (SDL_KEYDOWN == EVENT.type
		&& SDL_SCANCODE_A == EVENT.key.keysym.scancode)
	{
		alpha = right;
		LBRNT.turn--;
	}
	old_p = (t_point){.x = LBRNT.dirX, .y = LBRNT.dirY};
	old_pl = (t_point){.x = LBRNT.planeX, .y = LBRNT.planeY};
	LBRNT.dirX = old_p.x * alpha.y - old_p.y * alpha.x;
	LBRNT.dirY = (old_p.x * alpha.x) + (old_p.y * alpha.y);
	LBRNT.planeX = old_pl.x * alpha.y - old_pl.y * alpha.x;
	LBRNT.planeY = old_pl.x * alpha.x + old_pl.y * alpha.y;

	w_experyment(wolf);
	if (LBRNT.turn == 0
		|| abs(LBRNT.turn) == 15
		|| abs(LBRNT.turn) == 60
		|| abs(LBRNT.turn) == 45
		|| abs(LBRNT.turn) == 30)
	{
		printf(T_YEL"\n%d"R" - turn\n", LBRNT.turn);
		printf("%f\t %f\t - dirX dirY\n", LBRNT.dirX, LBRNT.dirY);
		printf("%f\t %f\t - pl_X pl_Y\n", LBRNT.planeX, LBRNT.planeY);
	}
}

void w_key_hook(t_wolf *wolf, int *running)
{
	if((SDL_QUIT == EVENT.type) || (SDL_KEYDOWN == EVENT.type
									&& SDL_SCANCODE_ESCAPE == EVENT.key.keysym.scancode))
		*running = 0;
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_DOWN == EVENT.key.keysym.scancode))
	{
		printf("DOWN\n");
		LBRNT.posX -= 0.1 * LBRNT.dirX;
		LBRNT.posY -= 0.1 * LBRNT.dirY;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_UP == EVENT.key.keysym.scancode))
	{
		printf("UP\n");
		LBRNT.posX += 0.1 * LBRNT.dirX;
		LBRNT.posY += 0.1 * LBRNT.dirY;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_RIGHT == EVENT.key.keysym.scancode))
	{
		printf("RIGHT\n");
		LBRNT.posX -= 0.1 * LBRNT.dirY;
		LBRNT.posY += 0.1 * LBRNT.dirX;
		w_experyment(wolf);
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_LEFT == EVENT.key.keysym.scancode))
	{
		printf("LEFT\n");
		LBRNT.posX += 0.1 * LBRNT.dirY;
		LBRNT.posY -= 0.1 * LBRNT.dirX;
		w_experyment(wolf);
	}
	if (SDL_KEYDOWN == EVENT.type &&
			((SDL_SCANCODE_D == EVENT.key.keysym.scancode)
			|| (SDL_SCANCODE_A == EVENT.key.keysym.scancode)))
	{
		turn_left_right(wolf);

	}

}

