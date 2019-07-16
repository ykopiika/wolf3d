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

static void moov_in_map(t_wolf *wolf, int key)
{
	double mv_x = 0.1 * LBRNT.dirX;
	double mv_y = 0.1 * LBRNT.dirY;

	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_DOWN == key))
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX - mv_x)] == S_FREE)
			LBRNT.posX -= mv_x;
		if (LBRNT.map[(int)(LBRNT.posY - mv_y)][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY -= mv_y;
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_UP == key))
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX + mv_x)] == S_FREE)
			LBRNT.posX += mv_x;
		if (LBRNT.map[(int)(LBRNT.posY + mv_y)][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY += mv_y;
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_RIGHT == key))
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX - mv_y)] == S_FREE)
			LBRNT.posX -= mv_y;
		if (LBRNT.map[(int)(LBRNT.posY + mv_x)][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY += mv_x;
	}
	if ((SDL_KEYDOWN == EVENT.type && SDL_SCANCODE_LEFT == key))
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX + mv_y)] == S_FREE)
			LBRNT.posX += mv_y;
		if (LBRNT.map[(int)(LBRNT.posY - mv_x)][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY -= mv_x;
	}
	w_experyment(wolf);
//	if (SDL_KEYDOWN == EVENT.type
//		&& (key == SDL_SCANCODE_DOWN
//			|| key == SDL_SCANCODE_UP))
//		moov_in_map(wolf,key);
//	if ((SDL_KEYDOWN == EVENT.type && key == SDL_SCANCODE_UP))
//		moov_in_map(wolf,key);
//	if ((SDL_KEYDOWN == EVENT.type && key == SDL_SCANCODE_RIGHT))
//		moov_in_map(wolf,key);
//	if ((SDL_KEYDOWN == EVENT.type && key == SDL_SCANCODE_LEFT))
//		moov_in_map(wolf,key);
}

void w_key_hook(t_wolf *wolf, int *running)
{
	int key;

	key = EVENT.key.keysym.scancode;
	if(EVENT.type == SDL_QUIT
		|| (EVENT.type == SDL_KEYDOWN && key == SDL_SCANCODE_ESCAPE))
		*running = 0;

	if (EVENT.type == SDL_KEYDOWN
		&& (key == SDL_SCANCODE_DOWN || key == SDL_SCANCODE_UP
		|| key == SDL_SCANCODE_RIGHT || key == SDL_SCANCODE_LEFT))
		moov_in_map(wolf,key);

	if (EVENT.type == SDL_KEYDOWN && (key == SDL_SCANCODE_D
			|| key == SDL_SCANCODE_A))
		turn_left_right(wolf);

	if (EVENT.type == SDL_KEYDOWN)
	{
		printf(T_GRN"%.2f %.2f"R" - x y\n", LBRNT.posX, LBRNT.posY);
	}

}

