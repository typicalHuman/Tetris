#include "SDL.h"
#include "input.h"
#include <sys/time.h>


App app;
struct Entity field[FIELD_WIDTH][FIELD_HEIGHT];
Shape* sh;
struct Entity field_blocks[FIELD_WIDTH][FIELD_HEIGHT];
SDL_Texture* blockTexture;

int Score = 0;
char SCORE_STRING[100] = "score   ";

int isGameOver = 0;

struct Entity NextShape[BLOCKS_COUNT];
enum ShapeType NextShapeType = 0;

SDL_Texture* Message;
SDL_Rect Message_rect;

SDL_Texture* B_Message;
SDL_Rect B_Message_rect;

SDL_Texture* C_Message;
SDL_Rect C_Message_rect;

SDL_Texture* D_Message;
SDL_Rect D_Message_rect;
