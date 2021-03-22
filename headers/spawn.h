
int GetXIndex(struct Entity ent);
int GetYIndex(struct Entity ent);

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
	int sh_index = rand() % 1;
	switch (sh_index){
		case 0:
		SpawnZShape(); 
			break;
		case 1:
		SpawnTShape();
			break;
		case 2:
		SpawnSquareShape();
			break;
		case 3:
		SpawnLShape();
			break;
		case 4:
		SpawnLRShape();
			break;
		case 5:
		
		SpawnLineShape(); 
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