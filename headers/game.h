
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
void RotateLeft();
void UpdateRotationState(int value);

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
///Spawn methods
///

void SpawnLineShape()
{
	if(sh)
	{
		for(int i = 0; i < BLOCKS_COUNT; i++)
			sh->Blocks[i]->isMoving = 0;
	}
	sh = NULL;
	sh = (Shape*)(malloc(sizeof(Shape)));
	int _x, _y;
	for(int i = 0; i < BLOCKS_COUNT; i++)
	{
		struct Entity *ent = (struct Entity*)malloc(sizeof(struct Entity));
		ent->texture = blockTexture;
		ent->x = 300;
		ent->y = BLOCK_SIZE*i + 100;
		_x = GetXIndex(*ent);
		_y = GetYIndex(*ent);
		field_blocks[_x][_y] = *ent; 
		field_blocks[_x][_y].isMoving = true;
		sh->Blocks[i] = &field_blocks[_x][_y];
	}
	sh->Type  = Line;
	UpdateFieldIndexes();
}
void SpawnTShape()
{
	SpawnLineShape();
	sh->Blocks[0]->y += BLOCK_SIZE*2;
	sh->Blocks[2]->x += BLOCK_SIZE;
	sh->Blocks[2]->y -= BLOCK_SIZE;
	sh->Blocks[3]->x -= BLOCK_SIZE;
	sh->Blocks[3]->y -= BLOCK_SIZE * 2;
	sh->Type  = T;
	UpdateFieldIndexes();
}

void SpawnLShape()
{
	SpawnTShape();
	sh->Blocks[2]->x += BLOCK_SIZE;
	for(int i = 0; i <BLOCKS_COUNT; i++)
		sh->Blocks[i]->y -= BLOCK_SIZE;
	sh->Type  = L;	
	UpdateFieldIndexes();
}
void SpawnLRShape()
{
	SpawnTShape();
	sh->Blocks[2]->x -= BLOCK_SIZE;
	for(int i = 0; i <BLOCKS_COUNT; i++)
		sh->Blocks[i]->y -= BLOCK_SIZE;
	sh->Type  = LR;
	UpdateFieldIndexes();
}

void SpawnSquareShape()
{
	SpawnLineShape();
	sh->Blocks[1]->x += BLOCK_SIZE;
	sh->Blocks[1]->y -= BLOCK_SIZE;
	sh->Blocks[2]->y -= BLOCK_SIZE;
	sh->Blocks[3]->y -= BLOCK_SIZE* 2;
	sh->Blocks[3]->x += BLOCK_SIZE;
	sh->Type  = Square;
	UpdateFieldIndexes();
}

void SpawnSShape()
{
	SpawnTShape();
	sh->Blocks[3]->y += BLOCK_SIZE;
	sh->Type  = S;
	UpdateFieldIndexes();
}


void SpawnZShape()
{
	SpawnTShape();
	sh->Blocks[2]->y += BLOCK_SIZE;
	sh->Type  = Z;
	UpdateFieldIndexes();
}

void SpawnRndShape()
{
	int sh_index = rand() % 1;
	switch (sh_index){
		case 0:
		SpawnLShape(); 
			break;
		case 1:
		SpawnTShape();
		
			break;
		case 2:
		SpawnSquareShape();
			break;
		case 3:
		SpawnLineShape(); 
	
			break;
		case 4:
		SpawnLRShape(); 
			break;
		case 5:
		SpawnZShape(); 
			break;
	    default:
		SpawnSShape(); 
			break;

	}
	if(sh->Type == Line || sh->Type == S || sh->Type == Z )
		sh->RotationsCount = 2;
	else if(sh->Type == Square)
		sh->RotationsCount = 0;
	else
		sh->RotationsCount = 4;
	sh->CurrentRotationState = 0;
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
///Rotation methods
///
int CheckBlockRotate(struct Entity ent)
{
	return !ent.texture || ent.isMoving;
}

int CanRotate(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int _x1 =  getXIndex(sh->Blocks[0]->x + x1);
	int _y1 =  getYIndex(sh->Blocks[0]->y + y1);
	int _x2 = getXIndex(sh->Blocks[1]->x + x2);
	int _y2 =  getYIndex(sh->Blocks[1]->y + y2);
	int _x3 = getXIndex(sh->Blocks[2]->x + x3);
	int _y3 = getYIndex(sh->Blocks[2]->y + y3);
	int _x4 = getXIndex(sh->Blocks[3]->x + x4);
	int _y4 = getYIndex(sh->Blocks[3]->y + y4);
	if(_x1 < 0 || _x2 < 0 || _x3 < 0 || _x4 < 0)
		return 0;
	return CheckBlockRotate(field_blocks[_x1][_y1]) && CheckBlockRotate(field_blocks[_x2][_y2])
	&& CheckBlockRotate(field_blocks[_x3][_y3]) && CheckBlockRotate(field_blocks[_x4][_y4]);
}

void Rotate(int rotValue, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int canRotate = CanRotate(x1, y1, x2,y2,x3,y3,x4,y4);
	if(canRotate)
	{
	    sh->Blocks[0]->x += x1;
		sh->Blocks[0]->y += y1;
		sh->Blocks[1]->x += x2;
		sh->Blocks[1]->y += y2;
		sh->Blocks[2]->x += x3;
		sh->Blocks[2]->y += y3;
		sh->Blocks[3]->x += x4;
		sh->Blocks[3]->y += y4;
		UpdateFieldIndexes();
		UpdateRotationState(rotValue);
	}
}




void RotateLeftLine()
{
	if(sh->CurrentRotationState == 0)
	{
		Rotate(-1, -25, 25, 0, 0, 25, -25, 50, -50);
	}
	else if(sh->CurrentRotationState == 1)
	{
		Rotate(-1, 25, -25, 0, 0, -25, +25, -50, +50);
	}
}
void RotateLeftT()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(-1, 25, 25, 0, 0, 25, -25, -25, -25);
	}
	else if(state == 3)
	{
		Rotate(-1, 0, -0, 0, 0, -25, -25, -0, 0);
	}
	else if(state == 2)
	{
		Rotate(-1, 0, 0, 0, 0, 0, 0, -25,25);
	}
	else if(state == 1)
	{
		Rotate(-1, 0, 0, 0, 25, 0, 25, 25,-25);
	}
}

void RotateLeftL()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(-1, 25, -25, 0, 0, 0, -25, -25, 0);
	}
	else if(state == 3)
	{
		Rotate(-1, -25, 25, 0, 0, 25, -25, -50, 0);
	}
	else if(state == 2)
	{
		Rotate(-1, 0, 50, 25, 25, 0, 0, -25, -25);
	}
	else if(state == 1)
	{
		Rotate(-1, 0, -25, 0, 25, 25, 0, 25, 0);
	}
}

void RotateLeft()
{
	switch(sh->Type)
	{
		case Line:
		RotateLeftLine();
		break;
		case T:
		RotateLeftT();
		break;
		case L:
		RotateLeftL();
		break;
		case LR:
		break;
		case Z:
		break;
		case S:
		break;
		default:
		break;
	}
}
void RotateRight()
{

}

void UpdateRotationState(int value)
{
	int sum = sh->CurrentRotationState + value;
	if(sum < sh->RotationsCount && 
	sum > -1)
	    sh->CurrentRotationState += value;
	else if(sum < 0)
		sh->CurrentRotationState = sh->RotationsCount - 1;
	else 
	    sh->CurrentRotationState = 0;
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