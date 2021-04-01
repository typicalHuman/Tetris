#include "rotation.h"
#include "spawn.h"

///
///Prototypes
///
int CanMove(int left, int right, int down);
int FieldBorderCheck(int left, int right, int down);
int BlocksBorderCheck(int left, int right, int down);
int GetXIndex(struct Entity _ent);
int GetYIndex(struct Entity _ent);
int getXIndex(int x);
int getYIndex(int y);
void UpdateFieldIndexes();
void SetFieldFromTemp(struct Entity temp_field[FIELD_WIDTH][FIELD_HEIGHT]);
int IsShapesBlock(int x, int y);
int CheckBlockMove(int left, int right, int down, int i);
void SpawnRndShape();
void UpdateScore();
void UpdateBurningStatus(char* burningStatus);
void SetRestartInstructionMessage();
void SetGameOverMessage();
///
///BG field methods
///
void DrawField()
{
	struct Entity ent;
	ent.texture = loadTexture("C:/users/hp/desktop/tetris/resources/field.bmp");	
	for(int i = 0; i < FIELD_WIDTH; i++)
	{
		for(int k = 0; k < FIELD_HEIGHT; k++)
		{
			ent.x = 200 + BLOCK_SIZE*i;
			ent.y = 100 + BLOCK_SIZE*k;
			field[i][k] = ent;
		}
	}
}
void UpdateField()
{
	for(int i = 0; i < FIELD_WIDTH; i++)
	{
		for(int k = 0; k < FIELD_HEIGHT; k++)
		{
			blit(field[i][k].texture, field[i][k].x, field[i][k].y);
		}
	}
}

void CheckForBurnings()
{
	int burningsCount = 0;
	int lastY = 0;
	for(int i = 0; i < FIELD_HEIGHT; i++)
	{
		int isBurn = 1;
		for(int k = 0; k < FIELD_WIDTH; k++)
		{
			if(field_blocks[k][i].texture == NULL)
			{
				isBurn = 0;
				break;
			}
		}
		if(isBurn)
		{
			burningsCount++;
			lastY = i;
			for(int j = 0; j < FIELD_WIDTH; j++)
				field_blocks[j][i].texture = NULL;
		}
	}
	if(burningsCount > 0)
	{
		for(int i = lastY-1; i >= 0; i--)
		{
			for(int k = FIELD_WIDTH -1; k >= 0 ;k--)
			{
				if(field_blocks[k][i].texture != NULL)
					field_blocks[k][i].y += BLOCK_SIZE * burningsCount;
			}
		}
		char* burningStatus = TETRIS;
		if(burningsCount == 1)
		{
			Score+=40;
			burningStatus = SINGLE;
		}
		else if(burningsCount == 2)
		{
			Score+= 100;
			burningStatus = DOUBLE;
		}
		else if(burningsCount == 3)
		{
			Score+= 300;
			burningStatus = TRIPLE;
		}
		else
			Score += 1200;
		UpdateScore();
		UpdateBurningStatus(burningStatus);
	}
	UpdateFieldIndexes();
}








///
///Move shape methods
///
void MoveShape()
{
	int can = CanMove(app.left, app.right, app.down);
	for(int i = 0; i < BLOCKS_COUNT; i++)
	{
		if(can)
		{
			if (app.down)
				sh->Blocks[i]->y += BLOCK_SIZE;
			else if (app.left)
				sh->Blocks[i]->x -= BLOCK_SIZE;
			else if (app.right)
				sh->Blocks[i]->x += BLOCK_SIZE;
		}
	}
	if(can)
		UpdateFieldIndexes();
	else if(!can && app.down)
	{
		CheckForBurnings();
		SpawnRndShape();
	}
}
int CanMove(int left, int right, int down)
{
	return FieldBorderCheck(left, right, down) && BlocksBorderCheck(left, right, down);
}
void MoveShapeDown()
{
	int can = CanMove(0, 0, 1);
	if(can)
	{
	   for(int i = 0; i < BLOCKS_COUNT; i++)
	   	sh->Blocks[i]->y += BLOCK_SIZE;
	UpdateFieldIndexes();
	}
	else
	{
		CheckForBurnings();
	 	SpawnRndShape();
	}
}






///
///Check methods
///
int FieldBorderCheck(int left, int right, int down)
{
	
	if(!left && !right && !down)
		return 0;
	for(int i = 0; i < BLOCKS_COUNT; i++)
	{
		if(sh->Blocks[i])
		{
			if(right && sh->Blocks[i]->x >= RIGHT_FIELD_BORDER)
				return 0;
			if(down && sh->Blocks[i]->y >= BOTTOM_FIELD_BORDER)
				return 0;
			if(left && sh->Blocks[i]->x <= LEFT_FIELD_BORDER)
				return 0;
		}
	}
	return 1;
}
int BlocksBorderCheck(int left, int right, int down)
{
	if(!left && !right && !down)
		return 0;
	for(int i = 0; i < BLOCKS_COUNT; i++)
	{
		if(sh->Blocks[i])
		{
			if(!CheckBlockMove(left, right, down, i))
				return 0;
		}
	}
	return 1;
}
int IsShapesBlock(int x, int y)
{
	for(int i = 0; i < BLOCKS_COUNT; i++)
	    if(sh->Blocks[i]->x == x && sh->Blocks[i]->y == y)
		return 1;
	return 0;
}

int CheckBlockMove(int left, int right, int down, int i)
{
	int _x, _y;
	if(right)
	{
		_x = getXIndex(sh->Blocks[i]->x + BLOCK_SIZE);
		_y = getYIndex(sh->Blocks[i]->y);
	}
	if(left)
	{
		_x = getXIndex(sh->Blocks[i]->x - BLOCK_SIZE);
		_y = getYIndex(sh->Blocks[i]->y);
	}
	if(down)
	{
		_x = getXIndex(sh->Blocks[i]->x);
		_y = getYIndex(sh->Blocks[i]->y + BLOCK_SIZE);
	}
	return field_blocks[_x][_y].isMoving || field_blocks[_x][_y].texture == NULL;
}





///
///Get index methods
///
int GetXIndex(struct Entity _ent)
{
	return getXIndex(_ent.x);
}
int getXIndex(int x)
{
	int res = ((x - LEFT_FIELD_BORDER) / BLOCK_SIZE);
	if(res < 0 || x > RIGHT_FIELD_BORDER)
   	 	return -1;
	return res;
}
int GetYIndex(struct Entity _ent)
{
	return getYIndex(_ent.y);
}
int getYIndex(int y)
{
int res = (((y - TOP_FIELD_BORDER) / BLOCK_SIZE) - 2);
   if(res < 0 || y > BOTTOM_FIELD_BORDER)
   	 return -1;
	return res;
}


///
///Update methods
///
void UpdateFieldIndexes()
{
	struct Entity temp_field[FIELD_WIDTH][FIELD_HEIGHT] = {0};
	for(int x = 0; x < FIELD_WIDTH; x++)
	{
		for(int y = 0; y < FIELD_HEIGHT; y++)
		{
			if(field_blocks[x][y].texture)
			{
				int _x = GetXIndex(field_blocks[x][y]);
				int _y = GetYIndex(field_blocks[x][y]);
				temp_field[_x][_y] = field_blocks[x][y];
			}
		}
	}
	SetFieldFromTemp(temp_field);

}

void SetFieldFromTemp(struct Entity temp_field[FIELD_WIDTH][FIELD_HEIGHT])
{
	int counter = 0;//blocks in shape counter (moving blocks always 4)
	for(int i = 0 ; i < FIELD_WIDTH; i++)
	{
		for(int k = 0; k < FIELD_HEIGHT;k++)
		{
			field_blocks[i][k] = temp_field[i][k];
			if(field_blocks[i][k].isMoving)//for checking does block belong to the moving shape
			{
				sh->Blocks[counter] = &field_blocks[i][k];
				counter++;
			}
		}
	}
}
void UpdateScore()
{
	char s[100];
   memcpy(s, SCORE_STRING,100);
	char s2[100];
    strcat(s,itoa(Score,s2,10));
	 Message = GetMessageTexture(s);

	Message_rect.x = 20;  
	Message_rect.y = 20; 
	Message_rect.w = 150; 
	Message_rect.h = 50; 
}

void UpdateBurningStatus(char* status)
{
	B_Message = GetMessageTexture(status);
	B_Message_rect.x = 400;  
	B_Message_rect.y = 20;
	B_Message_rect.w = 150; 
	B_Message_rect.h = 50; 
}

void UpdateNextMessage()
{
	C_Message = GetMessageTexture("NEXT");
	C_Message_rect.x = 475;  
	C_Message_rect.y = 260; 
	C_Message_rect.w = 80; 
	C_Message_rect.h = 50; 
}

void SetGameOverMessage()
{
	D_Message = GetMessageTexture("GAME OVER");

	D_Message_rect.x = 235;  
	D_Message_rect.y = 260; 
	D_Message_rect.w = 180; 
	D_Message_rect.h = 80; 
}

void RenderAllMessages()
{
		SDL_RenderCopy(app.renderer, Message, NULL, &Message_rect); 
		SDL_RenderCopy(app.renderer, B_Message, NULL, &B_Message_rect); 
		SDL_RenderCopy(app.renderer, C_Message, NULL, &C_Message_rect);
		if(isGameOver)
			SDL_RenderCopy(app.renderer, D_Message, NULL, &D_Message_rect);  
}

void DrawLine()
{
	for(int i = 0; i < BLOCKS_COUNT; i++)
	{
		struct Entity* ent = (struct Entity*)malloc(sizeof(struct Entity));
		ent->texture = blockTexture;
		ent->x = 500;
		ent->y = BLOCK_SIZE*i + 300;
		NextShape[i] = *ent;
	}
}
void DrawT()
{
	DrawLine();
	NextShape[0].y += BLOCK_SIZE*2;
	NextShape[2].x += BLOCK_SIZE;
	NextShape[2].y -= BLOCK_SIZE;
	NextShape[3].x -= BLOCK_SIZE;
	NextShape[3].y -= BLOCK_SIZE * 2;
}

void DrawL()
{
	DrawT();
	NextShape[0].x -= BLOCK_SIZE;
}
void DrawLR()
{
	DrawT();
	NextShape[0].x += BLOCK_SIZE;
}

void DrawSquare()
{
	DrawLine();
	NextShape[0].y += BLOCK_SIZE;
	NextShape[1].x += BLOCK_SIZE;
	NextShape[3].y -= BLOCK_SIZE;
	NextShape[3].x += BLOCK_SIZE;
}

void DrawS()
{
	DrawT();
	NextShape[3].y += 25;
}


void DrawZ()
{	
	DrawT();
	NextShape[2].y += BLOCK_SIZE;
}
void RenderNextShape()
{
	switch(NextShapeType)
	{
			case Line:
		DrawLine(); 
			break;
		case T:
		DrawT();
			break;
		case Square:
		DrawSquare();
			break;
		case L:
		DrawL();
			break;
		case LR:
		DrawLR();
			break;
		case Z:
		DrawZ();
			break;
	    default:
		DrawS();
			break;
	}
	for(int i = 0; i < BLOCK_SIZE; i++)
	 blit(NextShape[i].texture, NextShape[i].x,  NextShape[i].y);
}

