#include "SDL.h"
#include "input.h"
#include <sys/time.h>


App app;
struct Entity field[10][20];
Shape* sh;
struct Entity field_blocks[10][20];
SDL_Texture* blockTexture;