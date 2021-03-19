extern App app;

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

void RotateLeft();

void cleanKeys()
{
	app.right = 0;
	app.left = 0;
	app.down = 0;
}


void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			app.down = 0;
		else if (event->keysym.scancode == SDL_SCANCODE_LEFT)
			app.left = 0;
		else if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
			app.right = 0;
		 if(event->keysym.scancode == SDL_SCANCODE_A)
		     RotateLeft();
	}
}

void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
	    if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			cleanKeys();
			app.down = 1;
		}
		
		else if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			cleanKeys();
			app.left = 1;
		}
		
		else if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			cleanKeys();
			app.right = 1;
		}
	}
}

void doInput(void)
{
	SDL_Event event;
	const uint8_t* keystate = SDL_GetKeyboardState(NULL);
	bool b = keystate[SDL_SCANCODE_LEFT] + keystate[SDL_SCANCODE_RIGHT] + keystate[SDL_SCANCODE_DOWN];
    //continuous-response keys
    if(b)
    {
    	int msec = 0, trigger = 110; 
		clock_t before = clock();
		if(keystate[SDL_SCANCODE_DOWN])
		   trigger = 60;

		do {
	    clock_t difference = clock() - before;
	    msec = difference * 1000 / CLOCKS_PER_SEC;
	    } while ( msec < trigger );
	}

	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
				
			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;
				
			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
}