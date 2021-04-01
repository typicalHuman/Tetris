
int GetXIndex(struct Entity ent);
int GetYIndex(struct Entity ent);
enum ShapeType GetRandomShapeType(void);
void SetRotationsCount();
void SetGameOverMessage();
int CanMove(int left, int right, int down);
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

void SpawnLRShape()
{
	SpawnTShape();
	sh->Blocks[2]->x += BLOCK_SIZE;
	for(int i = 0; i <BLOCKS_COUNT; i++)
		sh->Blocks[i]->y -= BLOCK_SIZE;
	sh->Type  = LR;	
	UpdateFieldIndexes();
}
void SpawnLShape()
{
	SpawnTShape();
	sh->Blocks[2]->x -= BLOCK_SIZE;
	for(int i = 0; i <BLOCKS_COUNT; i++)
		sh->Blocks[i]->y -= BLOCK_SIZE;
	sh->Type  = L;
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
	sh->Blocks[0]->y += BLOCK_SIZE;
	sh->Type  = S;
	UpdateFieldIndexes();
}


void SpawnZShape()
{	
	SpawnTShape();
	sh->Blocks[3]->y += BLOCK_SIZE;
	sh->Type  = Z;
	UpdateFieldIndexes();
}



void SpawnRndShape()
{
	if(!isGameOver)
	{
		if(!NextShapeType)
			NextShapeType = GetRandomShapeType();
		enum ShapeType currentShapeType = NextShapeType;
		NextShapeType = GetRandomShapeType();
		switch (currentShapeType){
			case Line:
			SpawnLineShape(); 
				break;
			case T:
			SpawnTShape();
				break;
			case Square:
			SpawnSquareShape();
				break;
			case L:
			SpawnLShape();	
				break;
			case LR:
			SpawnLRShape();
				break;
			case Z:
			SpawnZShape(); 
				break;
			default:
			SpawnSShape(); 
				break;

		}
		if(!CanMove(1, 1, 1))
		{
			SetGameOverMessage();
			isGameOver = 1;
		}
		SetRotationsCount();
	}
}

void SetRotationsCount()
{
		if(sh->Type == Line || sh->Type == S || sh->Type == Z )
			sh->RotationsCount = 2;
		else if(sh->Type == Square)
			sh->RotationsCount = 0;
		else
			sh->RotationsCount = 4;
		sh->CurrentRotationState = 0;
}

enum ShapeType GetRandomShapeType(void)
{
	int sh_index = rand() % 7;
	switch(sh_index)
	{
		case 0:
		return Line;
		case 1:
		return T;
		case 2:
		return Square;
		case 3:
		return L;
		case 4:
		return LR;
		case 5:
		return Z;
		default:
		return S;
	}
}
