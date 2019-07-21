/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_print_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 21:44:13 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/21 21:44:15 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void print_textured_line(t_text	t, int ray, t_raycast *v)
{
	int y;

	y = -1;
	while (++y < v->drawStart)
		t.data[(y * WDTH) + ray] = SKY_COLOR;
	y = v->drawStart;
	while (y < v->drawEnd)
	{
		t.c = y * 256 - HGHT * 128 + v->lineHeight * 128;
		t.y_text = ((t.c * t.texHeight) / v->lineHeight) / 256;
		t.color_text = t.dat_bmp[t.texHeight * t.y_text + t.x_text];
		t.data[y * WDTH + ray] = t.color_text;
		y++;
	}
	y--;
	while (++y < HGHT)
		t.data[(y * WDTH) + ray] = FLOOR_COLOR;
}

static void choose_right_texture(t_text	*t, t_wolf *wolf, t_raycast *v)
{
	t->dat_bmp = wolf->bmp[0 + FLAGS.textur]->pixels;

	if ((v->rayDirX < 0 && v->rayDirY < 0)
		|| (v->rayDirX >= 0 && v->rayDirY < 0))
	{
		if (v->side == 1)
			t->dat_bmp = wolf->bmp[1 + FLAGS.textur]->pixels;
	}
	if ((v->rayDirX < 0 && v->rayDirY >= 0)
		|| (v->rayDirX >= 0 && v->rayDirY >= 0))
	{
		if (v->side == 1)
			t->dat_bmp = wolf->bmp[2 + FLAGS.textur]->pixels;
	}
	if ((v->rayDirX >= 0 && v->rayDirY < 0)
		|| (v->rayDirX >= 0 && v->rayDirY >= 0))
	{
		if (v->side == 0)
			t->dat_bmp = wolf->bmp[3 + FLAGS.textur]->pixels;
	}
}

void w_print_wall(t_wolf *wolf, t_raycast *v, int ray)
{
	t_text	t;

	t.texWidth = 64;
	t.texHeight = 64;
	if (!v->side)
		t.wallX = LBRNT.posY + v->perpWallDist * v->rayDirY;
	else
		t.wallX = LBRNT.posX + v->perpWallDist * v->rayDirX;
	t.wallX -= (int)(t.wallX);
	t.data = SURF_WIN->pixels;

	t.x_text = (int)(t.wallX * (double)t.texWidth);

	if(v->side == 0 && v->rayDirX > 0)
		t.x_text = t.texWidth - t.x_text - 1;
	if(v->side == 1 && v->rayDirY < 0)
		t.x_text = t.texWidth - t.x_text - 1;
	choose_right_texture(&t, wolf, v);
	print_textured_line(t, ray, v);
}
