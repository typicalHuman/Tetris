void RotateLeft();
void UpdateRotationState(int value);
int getXIndex(int x);
int getYIndex(int y);
void UpdateFieldIndexes();
void UpdateRotationState(int value);


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




void RotateLine()
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


void RotateLeftLR()
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

void RotateLeftL()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(-1, 25, -25, 25, 0, 25, 25, -25, 0);
	}
	else if(state == 3)
	{
		Rotate(-1, -25, 25, 0, 0, 25, -25, 0, -50);
	}
	else if(state == 2)
	{
		Rotate(-1, 25, 25, 0, 0, -50, 0, -25, -25);
	}
	else if(state == 1)
	{
		Rotate(-1, 0, 50, 25, 25, 0, 0, -25, -25);
	}
}

void RotateZ()
{
	if(sh->CurrentRotationState == 0)
	{
		Rotate(-1, 0, 50, 0, 0, 0,0, -50, 0);
	}
	else if(sh->CurrentRotationState == 1)
	{
		Rotate(-1, 50, 0, 0, -50, 0, 0, 0, 0);
	}
}

void RotateS()
{
	if(sh->CurrentRotationState == 0)
	{
		Rotate(-1, 0, -50, 0, 0, 0,0, -50, 0);
	}
	else if(sh->CurrentRotationState == 1)
	{
		Rotate(-1, 0, 50, 50, 0, 0, 0, 0, 0);
	}
}

void RotateLeft()
{
	switch(sh->Type)
	{
		case Line:
		RotateLine();
		break;
		case T:
		RotateLeftT();
		break;
		case L:
		RotateLeftL();
		break;
		case LR:
		RotateLeftLR();
		break;
		case Z:
		RotateZ();
		break;
		case S:
		RotateS();
		break;
		default:
		break;
	}
}


void RotateRightT()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(1, 0, 0, 0, -25, 0, -25, -25, 25);
	}
	else if(state == 3)
	{
		Rotate(1, -25, 25, 0, 0, 0, 0, -0, 0);
	}
	else if(state == 2)
	{
		Rotate(1, 25, 25, 0, 0, -0, 0, 0, 0);
	}
	else if(state == 1)
	{
		Rotate(1, 0, 0, 0, 0, 0, 0, 25,-25);
	}
}

void RotateRightLR()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(1, 0, 25, 0, -25, -25, 0, -25, 0);
	}
	else if(state == 3)
	{
		Rotate(1, 25, 25, 0, 0, -25, -25, 0, 50);
	}
	else if(state == 2)
	{
		Rotate(1, 25, -25, 25, -25, 0, 0, 0, -50);
	}
	else if(state == 1)
	{
		Rotate(1, 0, -25, -25, 0, 0, 0, 25, -25);
	}
}

void RotateRightL()
{
	int state = sh->CurrentRotationState;
	if (state == 0)
	{
		Rotate(1, 25, -25, 0, -50, 0, 0, -25, 25);
	}
	else if(state == 3)
	{
		Rotate(1, -25, 25, 0, 0, -25, 0, 0, -25);
	}
	else if(state == 2)
	{
		Rotate(1, 25, 25, 0, 0, -25, 0, 0, 25);
	}
	else if(state == 1)
	{
		Rotate(1, 50, 0, 25, 25, 0, 0, -25, -25);
	}
}

void RotateRight()
{
	switch(sh->Type)
	{
		case Line:
		RotateLine();
		break;
		case T:
		RotateRightT();
		break;
		case L:
		RotateRightL();
		break;
		case LR:
		RotateRightLR();
		break;
		case Z:
		RotateZ();
		break;
		case S:
		RotateS();
		break;
		default:
		break;
	}
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