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
		SpawnRndShape();
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
	else if(!can)
	  SpawnRndShape();
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
	else if(left)
	{
		_x = getXIndex(sh->Blocks[i]->x - BLOCK_SIZE);
		_y = getYIndex(sh->Blocks[i]->y);
	}
	else if(down)
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
   if(res < 0)
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