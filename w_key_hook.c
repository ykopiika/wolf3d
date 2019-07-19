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

	left = (t_point){.y = cos(FRAME.rotSpeed),.x =  sin(FRAME.rotSpeed)};
	right =  (t_point){.y = cos(-FRAME.rotSpeed),.x =  sin(-FRAME.rotSpeed)};
	if (FLAGS.keydown_d == 1)
		alpha = left;
	if (FLAGS.keydown_a == 1)
		alpha = right;
	old_p = (t_point){.x = LBRNT.dirX, .y = LBRNT.dirY};
	old_pl = (t_point){.x = LBRNT.planeX, .y = LBRNT.planeY};
	LBRNT.dirX = old_p.x * alpha.y - old_p.y * alpha.x;
	LBRNT.dirY = (old_p.x * alpha.x) + (old_p.y * alpha.y);
	LBRNT.planeX = old_pl.x * alpha.y - old_pl.y * alpha.x;
	LBRNT.planeY = old_pl.x * alpha.x + old_pl.y * alpha.y;
}

static void moov_in_map(t_wolf *wolf)
{
//	double mv_x = 0.03 * LBRNT.dirX;
//	double mv_y = 0.03 * LBRNT.dirY;

	double mv_x = FRAME.moveSpeed * LBRNT.dirX;
	double mv_y = FRAME.moveSpeed * LBRNT.dirY;
	double a = 1.5;

	if (FLAGS.keydown_down == 1)
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX - (mv_x* a))] == S_FREE)
			LBRNT.posX -= mv_x;
		if (LBRNT.map[(int)(LBRNT.posY - (mv_y* a))][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY -= mv_y;
	}
	if (FLAGS.keydown_up == 1)
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX + (mv_x * a))] == S_FREE)
			LBRNT.posX += mv_x;
		if (LBRNT.map[(int)(LBRNT.posY + (mv_y * a))][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY += mv_y;
	}
	if (FLAGS.keydown_right == 1)
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX - (mv_y* a))] == S_FREE)
			LBRNT.posX -= mv_y;
		if (LBRNT.map[(int)(LBRNT.posY + (mv_x* a))][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY += mv_x;
	}
	if (FLAGS.keydown_left == 1)
	{
		if (LBRNT.map[(int)LBRNT.posY][(int)(LBRNT.posX + (mv_y * a))] == S_FREE)
			LBRNT.posX += mv_y;
		if (LBRNT.map[(int)(LBRNT.posY - (mv_x * a))][(int)LBRNT.posX] == S_FREE)
			LBRNT.posY -= mv_x;
	}
//	if (FLAGS.keydown_down || FLAGS.keydown_up
//		|| FLAGS.keydown_left || FLAGS.keydown_right)
//		printf(T_RED"%.2fx   %.2fy\n\n"R,LBRNT.posX, LBRNT.posY);

}

void w_key_hook(t_wolf *wolf)
{
	moov_in_map(wolf);
	if (FLAGS.keydown_a == 1 || FLAGS.keydown_d == 1)
		turn_left_right(wolf);
}

