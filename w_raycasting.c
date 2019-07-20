/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:20:38 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/17 18:20:41 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void print_textured_line(t_text	t, int ray, t_raycast *v)
{
	while (++t.y < v->drawStart)
		t.data[(t.y * WDTH) + ray] = SKY_COLOR;
	t.y = v->drawStart;
	while (t.y < v->drawEnd)
	{
		t.d = t.y * 256 - HGHT * 128 + v->lineHeight * 128;
		t.texY = ((t.d * t.texHeight) / v->lineHeight) / 256;
		t.color = t.dat_bmp[t.texHeight * t.texY + t.texX];
		t.data[t.y * WDTH + ray] = t.color;
		t.y++;
	}
	t.y--;
	while (++t.y < HGHT)
		t.data[(t.y * WDTH) + ray] = FLOOR_COLOR;
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

static void print_wall(t_wolf *wolf, t_raycast *v, int ray)
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
	t.y = -1;

	t.texX = (int)(t.wallX * (double)t.texWidth);

	if(v->side == 0 && v->rayDirX > 0)
		t.texX = t.texWidth - t.texX - 1;
	if(v->side == 1 && v->rayDirY < 0)
		t.texX = t.texWidth - t.texX - 1;
	choose_right_texture(&t, wolf, v);
	print_textured_line(t, ray, v);
}

static void count_side_dist(t_raycast *v)
{
	v->mapX = (int)v->posX;
	v->mapY = (int)v->posY;
	if (v->rayDirX < 0)
	{
		v->stepX = -1;
		v->sideDistX = (v->posX - v->mapX) * v->deltaDistX;
	}
	else
	{
		v->stepX = 1;
		v->sideDistX = (v->mapX + 1.0 - v->posX) * v->deltaDistX;
	}
	if (v->rayDirY < 0)
	{
		v->stepY = -1;
		v->sideDistY = (v->posY - v->mapY) * v->deltaDistY;
	}
	else
	{
		v->stepY = 1;
		v->sideDistY = (v->mapY + 1.0 - v->posY) * v->deltaDistY;
	}
}

static void count_len_ray(t_wolf *wolf, t_raycast *v)
{
	int hit = 0;
	while (hit == 0)
	{
		if (v->sideDistX < v->sideDistY)
		{
			v->sideDistX += v->deltaDistX;
			v->mapX += v->stepX;
			v->side = 0;
		}
		else
		{
			v->sideDistY += v->deltaDistY;
			v->mapY += v->stepY;
			v->side = 1;
		}
		if (LBRNT.map[v->mapY][v->mapX] == S_WALL)
			hit = 1;
	}
}

static void count_hight_wall(t_raycast *v)
{
	if (!v->side)
		v->perpWallDist =
			(v->mapX - v->posX + (1.0f - v->stepX) / 2)	/ v->rayDirX;
	else
		v->perpWallDist =
			(v->mapY - v->posY + (1.0f - v->stepY) / 2)	/ v->rayDirY;
	v->lineHeight = (int)(HGHT / v->perpWallDist);
	v->drawStart = -v->lineHeight / 2 + HGHT / 2;

	if(v->drawStart < 0)
		v->drawStart = 0;
	v->drawEnd = v->lineHeight / 2 + HGHT / 2;
	if(v->drawEnd >= HGHT)
		v->drawEnd = HGHT - 1;
}

void w_raycasting(t_wolf *wolf)
{
	t_raycast v;

	v.ray = 0;
	v.posX = LBRNT.posX;
	v.posY = LBRNT.posY;
	v.dirX = LBRNT.dirX;
	v.dirY = LBRNT.dirY;
	v.planeX = LBRNT.planeX;
	v.planeY = LBRNT.planeY;
	while (v.ray < LBRNT.rays)
	{
		v.cameraX = 1 - (2.0 * (double)v.ray / LBRNT.rays);
		v.rayDirX = v.dirX + v.planeX * v.cameraX;
		v.rayDirY = v.dirY + v.planeY * v.cameraX;
		v.deltaDistX = fabs(1 / v.rayDirX);
		v.deltaDistY = fabs(1 / v.rayDirY);

		count_side_dist(&v);
		count_len_ray(wolf, &v);
		count_hight_wall(&v);
		print_wall(wolf, &v, v.ray);
		v.ray++;
	}
	SDL_UpdateWindowSurface(WIN);
}
