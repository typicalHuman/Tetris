#define SDL_MAIN_HANDLED
#include "headers/main.h"
#include "headers/game.h"
#include <stdint.h>
#include "SDL2/SDL.h"
/*void f();
void CreateTimer(int ms)
{
	MSG msg;
  SetTimer(NULL, 0, ms, (TIMERPROC)&f);
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}


void CALLBACK f()
{

}
*/

uint32_t callback(uint32_t interval, void* param)
{
	MoveShapeDown();
	SDL_AddTimer(UPDATE_INTERVAL, callback, NULL);
    return 0;
}

int main(int argc, char* argv[])
{

	initSDL();
	atexit(CloseSDLWindow);
	blockTexture = loadTexture("C:/users/hp/desktop/tetris/resources/s.bmp");
	DrawField();
	SDL_AddTimer(UPDATE_INTERVAL, callback, NULL);
	SpawnRndShape();
	while (1)
	{
		prepareScene();
		doInput();
		UpdateField();
		MoveShape();
		for(int i = 0; i < FIELD_WIDTH; i++)
		{
			for(int k = 0; k <FIELD_HEIGHT; k++)
			{
			    blit(field_blocks[i][k].texture, field_blocks[i][k].x, field_blocks[i][k].y);
			}
		}
		presentScene();
	}
    return 0;
}

