#include "main.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
		{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

void	verLine(t_wolf *wolf, int x, int drawStart, int drawEnd, int color)
{
//	SDL_SetRenderDrawColor(REN, 0, 0, 0, 0);
//	SDL_RenderClear(REN);
	int y = 0;
//	SURF_WIN


	SDL_SetRenderDrawColor(REN, 0, 0, 0, 255);
	while (y < drawStart)
	{
		SDL_RenderDrawPoint(REN, x - 1, y);
		y++;
	}
	if (color == RGB_Red)
		SDL_SetRenderDrawColor(REN, 255, 0, 183, 255);
	if (color == RGB_Green)
		SDL_SetRenderDrawColor(REN, 108, 209, 0, 255);
	if (color == RGB_Blue)
		SDL_SetRenderDrawColor(REN, 0, 129, 209, 255);
	if (color == RGB_White)
		SDL_SetRenderDrawColor(REN, 255, 255, 255, 255);
	if (color == RGB_Yellow)
		SDL_SetRenderDrawColor(REN, 255, 208, 0, 255);
	y = drawStart;
	while (y <= drawEnd)
	{
		SDL_RenderDrawPoint(REN, x - 1, y);
		y++;
	}
	SDL_SetRenderDrawColor(REN, 0, 0, 0, 255);
	y = drawEnd;
	while (y < HGHT)
	{
		SDL_RenderDrawPoint(REN, x - 1, y);
		y++;
	}
	SDL_RenderPresent(REN);

	y = 0;


	SDL_SetRenderDrawColor(REN, 0, 0, 0, 255);
	while (y < drawStart)
	{
		SDL_RenderDrawPoint(REN, x, y);
		y++;
	}
	if (color == RGB_Red)
		SDL_SetRenderDrawColor(REN, 255, 0, 183, 255);
	if (color == RGB_Green)
		SDL_SetRenderDrawColor(REN, 108, 209, 0, 255);
	if (color == RGB_Blue)
		SDL_SetRenderDrawColor(REN, 0, 129, 209, 255);
	if (color == RGB_White)
		SDL_SetRenderDrawColor(REN, 255, 255, 255, 255);
	if (color == RGB_Yellow)
		SDL_SetRenderDrawColor(REN, 255, 208, 0, 255);
	y = drawStart;
	while (y <= drawEnd)
	{
		SDL_RenderDrawPoint(REN, x, y);
		y++;
	}
	SDL_SetRenderDrawColor(REN, 0, 0, 0, 255);
	y = drawEnd;
	while (y < HGHT)
	{
		SDL_RenderDrawPoint(REN, x, y);
		y++;
	}
	SDL_RenderPresent(REN);
}

void	w_lodev(t_wolf *wolf)
{
	(void)wolf;
	double posX = 13, posY = 20;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

//	double time = 0; //time of current frame
//	double oldTime = 0; //time of previous frame

	SDL_CreateWindowAndRenderer(WDTH, HGHT, 0, &WIN, &REN);
	SDL_SetRenderDrawColor(REN, 0, 0, 0, 0);
	SDL_RenderClear(REN);

//	screen(512, 384, 0, "Raycaster");
//	while(!done())
//	{
		int x = 0;
		while(x < WDTH)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / WDTH - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = posX;
			int mapY = posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
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
			//perform DDA
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
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(HGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + HGHT / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + HGHT / 2;
			if(drawEnd >= HGHT)drawEnd = HGHT - 1;

			//choose wall color
			int color;
			switch(worldMap[mapX][mapY])
			{
				case 1:  color = RGB_Red;  break; //red
				case 2:  color = RGB_Green;  break; //green
				case 3:  color = RGB_Blue;   break; //blue
				case 4:  color = RGB_White;  break; //white
				default: color = RGB_Yellow; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line

			verLine(wolf, x, drawStart, drawEnd, color);
			x++;
		}
//		//timing for input and FPS counter
//		oldTime = time;
//		time = getTicks();
//		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//		print(1.0 / frameTime); //FPS counter
//		redraw();
//		cls();
//
//		//speed modifiers
//		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
//		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
//		readKeys();
//		//move forward if no wall in front of you
//		if (keyDown(SDLK_UP))
//		{
//			if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//			if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//		}
//		//move backwards if no wall behind you
//		if (keyDown(SDLK_DOWN))
//		{
//			if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//			if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//		}
//		//rotate to the right
//		if (keyDown(SDLK_RIGHT))
//		{
//			//both camera direction and camera plane must be rotated
//			double oldDirX = dirX;
//			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//			double oldPlaneX = planeX;
//			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//		}
//		//rotate to the left
//		if (keyDown(SDLK_LEFT))
//		{
//			//both camera direction and camera plane must be rotated
//			double oldDirX = dirX;
//			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//			double oldPlaneX = planeX;
//			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//		}
//	}
//	return ;
}