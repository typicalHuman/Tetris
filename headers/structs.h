typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int down;
	int left;
	int right;
} App;

struct Entity{
	int x;
	int y;
	int isMoving;
	SDL_Texture *texture;
};

enum ShapeType {Line = 1, T, Square, L, LR, Z, S};

typedef struct
{
   struct Entity* Blocks[4];
   enum ShapeType Type;
   int RotationsCount;
   int CurrentRotationState;
}Shape;