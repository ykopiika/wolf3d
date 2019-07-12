#include "main.h"

void print_position(t_wolf *wolf, int posX, int posY)
{
	int i = 0;

	printf(T_YEL"\n\n%d %d - posX posY\n\n"R, posX, posY);
	while (i < LBRNT.size)
	{
		int j = -1;
		while (++j < LBRNT.size)
		{
			if (i == posY && j == posX)
				printf(T_GRN"%c"R, '@');
			else
				printf(T_RED"%c"R, LBRNT.map[i][j]);
		}
		printf("\n");
		i++;
	}
}


static void print_ray(t_wolf *wolf, int drawStart, int drawEnd, int color, int ray)
{
	int step = WDTH/LBRNT.rays;
	int *data;
	int y = -1;

	data = SURF_WIN->pixels;
	while (++y < drawStart)
	{
		int x = (ray * step) - 1;
		while (++x < (ray * step) + step)
			data[(y * WDTH) + x] = 0x96efff;
	}
	y = drawStart -1;
	while (++y <= drawEnd)
	{
		int x = (ray * step) - 1;
		while (++x < (ray * step) + step)
			data[(y * WDTH) + x] = color;
	}
	y--;
	while (++y < HGHT)
	{
		int x = (ray * step) - 1;
		while (++x < (ray * step) + step)
			data[(y * WDTH) + x] = 0x252626;
	}
}

void w_experyment(t_wolf *wolf)
{
//	print_img_data(wolf);
	int ray = 0;

	double posX = LBRNT.posX;
	double posY = LBRNT.posY;
//	print_position(wolf, posX, posY);
	double dirX = LBRNT.dirX;
	double dirY = LBRNT.dirY;
	double planeX = LBRNT.planeX;
	double planeY = LBRNT.planeY;

	printf("pos: %f, %f\n", LBRNT.posX, LBRNT.posY);
	while (ray < LBRNT.rays)
	{
		double cameraX = 1 - (2.0 * (double)ray / LBRNT.rays);
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

//		printf("ray %d dir = %f,%f; cam = %f\n", ray, rayDirX, rayDirY, cameraX);

		int mapX = posX;
		int mapY = posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);

		int stepX;
		int stepY;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (LBRNT.map[mapY][mapX] == S_WALL) hit = 1;
		}

		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HGHT / 2;
		if(drawEnd >= HGHT)
			drawEnd = HGHT - 1;

		int color;
		color = 255;	///left
		if (dirX >= 0)
			color = RGB_Blue;	///right

		if ((rayDirX < 0 && rayDirY < 0) || (rayDirX >= 0 && rayDirY < 0))
		{
			if (side == 1)
				color = RGB_Green;	///up
		}
		if ((rayDirX < 0 && rayDirY >= 0) || (rayDirX >= 0 && rayDirY >= 0))
		{
			if (side == 1)
				color = RGB_Red;	///down
		}

		print_ray(wolf, drawStart, drawEnd, color, ray);
		if ((ray == 0) || (ray == (LBRNT.rays - 2)))
			printf("%d - h\n", (drawEnd - drawStart));
		ray++;
	}
//	printf("%d / %d - rays/LB ray\n",);
	SDL_UpdateWindowSurface(WIN);

	return ;
}
