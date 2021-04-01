#define SDL_MAIN_HANDLED
#include "headers/main.h"
#include "headers/game.h"
#include <stdint.h>
#include "SDL2/SDL.h"

uint32_t callback(uint32_t interval, void* param)
{
	MoveShapeDown();
	SDL_AddTimer(MOVING_DOWN_INTERVAL, callback, NULL);
    return 0;
}

int main(int argc, char* argv[])
{
	initSDL();
	TTF_Init();
	atexit(CloseSDLWindow);
	blockTexture = loadTexture("C:/users/hp/desktop/tetris/resources/s.bmp");
	DrawField();
	SDL_AddTimer(MOVING_DOWN_INTERVAL, callback, NULL);
	SpawnRndShape();
    font = TTF_OpenFont("C:/users/hp/desktop/tetris/resources/font.ttf", 16); //this opens a font style and sets a size
	UpdateScore();
	UpdateNextMessage();

	while (1)
	{
		prepareScene();
		doInput();
		UpdateField();
		if(!isGameOver)
		{
			MoveShape();
			RenderNextShape();
		}
		for(int i = 0; i < FIELD_WIDTH; i++)
		{
			for(int k = 0; k <FIELD_HEIGHT; k++)
			{
			    blit(field_blocks[i][k].texture, field_blocks[i][k].x, field_blocks[i][k].y);
			}
		}
		RenderAllMessages();
		presentScene();
	}
    return 0;
}

