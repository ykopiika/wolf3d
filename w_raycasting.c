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

void print_txt(t_wolf *wolf, int drawStart, int drawEnd,
				int ray, int side, int lineHeight, double perpWallDist,
			   double rayDirX, double rayDirY)
{
	t_text	t;


	t.texWidth = 64;
	t.texHeight = 64;
	if (side == 0)
		t.wallX = LBRNT.posY + perpWallDist * rayDirY;
	else
		t.wallX = LBRNT.posX + perpWallDist * rayDirX;
	t.wallX -= (int)(t.wallX);

	t.step = WDTH/LBRNT.rays;
	t.y = -1;

	t.data = SURF_WIN->pixels;
	while (++t.y < drawStart)
	{
		t.x = (ray * t.step) - 1;
		while (++t.x < (ray * t.step) + t.step)
			t.data[(t.y * WDTH) + t.x] = 0x96efff;
	}


	t.texX = (int)(t.wallX * (double)(t.texWidth));

	if(side == 0 && rayDirX > 0)
		t.texX = t.texWidth - t.texX - 1;
	if(side == 1 && rayDirY < 0)
		t.texX = t.texWidth - t.texX - 1;
		t.dat_bmp = wolf->bmp[0 + FLAGS.textur]->pixels;

		if ((rayDirX < 0 && rayDirY < 0) || (rayDirX >= 0 && rayDirY < 0))
		{
			if (side == 1)
				t.dat_bmp = wolf->bmp[1 + FLAGS.textur]->pixels;
		}
		if ((rayDirX < 0 && rayDirY >= 0) || (rayDirX >= 0 && rayDirY >= 0))
		{
			if (side == 1)
				t.dat_bmp = wolf->bmp[2 + FLAGS.textur]->pixels;
		}
		if ((rayDirX >= 0 && rayDirY < 0) || (rayDirX >= 0 && rayDirY >= 0))
		{
			if (side == 0)
				t.dat_bmp = wolf->bmp[3 + FLAGS.textur]->pixels;
		}
	t.y = drawStart;
	while (t.y < drawEnd)
	{
		t.d = t.y * 256 - HGHT * 128 + lineHeight * 128;
		t.texY = ((t.d * t.texHeight) / lineHeight) / 256;



		t.color = t.dat_bmp[t.texHeight * t.texY + t.texX];
		t.data[t.y * WDTH + ray] = t.color;
		t.y++;
	}
	t.y--;
	while (++t.y < HGHT)
	{
		t.x = (ray * t.step) - 1;
		while (++t.x < (ray * t.step) + t.step)
			t.data[(t.y * WDTH) + t.x] = 0x252626;
	}
}

void w_raycasting(t_wolf *wolf)
{
	int ray = 0;
	t_raycast v;

	v.posX = LBRNT.posX;
	v.posY = LBRNT.posY;
	v.dirX = LBRNT.dirX;
	v.dirY = LBRNT.dirY;
	v.planeX = LBRNT.planeX;
	v.planeY = LBRNT.planeY;

	while (ray < LBRNT.rays)
	{
		v.cameraX = 1 - (2.0 * (double)ray / LBRNT.rays);
		v.rayDirX = v.dirX + v.planeX * v.cameraX;
		v.rayDirY = v.dirY + v.planeY * v.cameraX;

		v.mapX = v.posX;
		v.mapY = v.posY;


		v.deltaDistX = fabs(1 / v.rayDirX);
		v.deltaDistY = fabs(1 / v.rayDirY);

		if (v.rayDirX < 0)
		{
			v.stepX = -1;
			v.sideDistX = (v.posX - v.mapX) * v.deltaDistX;
		}
		else
		{
			v.stepX = 1;
			v.sideDistX = (v.mapX + 1.0 - v.posX) * v.deltaDistX;
		}

		if (v.rayDirY < 0)
		{
			v.stepY = -1;
			v.sideDistY = (v.posY - v.mapY) * v.deltaDistY;
		}
		else
		{
			v.stepY = 1;
			v.sideDistY = (v.mapY + 1.0 - v.posY) * v.deltaDistY;
		}

		v.hit = 0;
		while (v.hit == 0)
		{
			if (v.sideDistX < v.sideDistY)
			{
				v.sideDistX += v.deltaDistX;
				v.mapX += v.stepX;
				v.side = 0;
			}
			else
			{
				v.sideDistY += v.deltaDistY;
				v.mapY += v.stepY;
				v.side = 1;
			}
			if (LBRNT.map[v.mapY][v.mapX] == S_WALL)
				v.hit = 1;
		}

		if (!v.side)
			v.perpWallDist = (v.mapX - v.posX + (1 - v.stepX) / 2) / v.rayDirX;
		else
			v.perpWallDist = (v.mapY - v.posY + (1 - v.stepY) / 2) / v.rayDirY;

		v.lineHeight = (int)(HGHT / v.perpWallDist);
		v.drawStart = -v.lineHeight / 2 + HGHT / 2;

		if(v.drawStart < 0)
			v.drawStart = 0;
		v.drawEnd = v.lineHeight / 2 + HGHT / 2;
		if(v.drawEnd >= HGHT)
			v.drawEnd = HGHT - 1;
		print_txt(wolf, v.drawStart, v.drawEnd, ray, v.side, v.lineHeight,
				  v.perpWallDist, v.rayDirX, v.rayDirY);
		ray++;
	}
	SDL_UpdateWindowSurface(WIN);

	return ;
}
