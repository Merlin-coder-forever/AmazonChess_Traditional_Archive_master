#include "stdafx.h"
#include "MoveGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MoveGenerator::MoveGenerator()
{

}

MoveGenerator::~MoveGenerator()
{

}

int MoveGenerator::CreatePossibleMove(BYTE position[][12],int side,int nply)
{
	moveCount=0;
	BYTE i,j;
	BYTE k,l;
for(int ii=0;  ii<2500; ii++)
	{
		moveLine[nply][ii].x=0;
		moveLine[nply][ii].y=0;
		moveLine[nply][ii].priviousX=0;
		moveLine[nply][ii].priviousY=0;
		moveLine[nply][ii].barX=0;
		moveLine[nply][ii].barY=0;
moveLine[nply][ii].score=0;
	}

	for(i=0;i<12;i++)
	{
		for(j=0;j<12;j++)
		{
			if(position[i][j]==2&&side==0)
			{
				k=i;l=j;
				while(position[k-1][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l-1,i,j,nply);k--;l--;}

				k=i;l=j;
				while(position[k-1][l]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l,i,j,nply);k--;}

				k=i;l=j;
				while(position[k-1][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l+1,i,j,nply);k--;l++;}

				k=i;l=j;
				while(position[k][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k,l-1,i,j,nply);l--;}

				k=i;l=j;
				while(position[k][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k,l+1,i,j,nply);l++;}

				k=i;l=j;
				while(position[k+1][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l-1,i,j,nply);k++;l--;}

				k=i;l=j;
				while(position[k+1][l]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l,i,j,nply);k++;}

				k=i;l=j;
				while(position[k+1][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l+1,i,j,nply);k++;l++;}

			}

			if(position[i][j]==3&&side==1)
			{
				k=i;l=j;
				while(position[k-1][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l-1,i,j,nply);k--;l--;}

				k=i;l=j;
				while(position[k-1][l]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l,i,j,nply);k--;}

				k=i;l=j;
				while(position[k-1][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k-1,l+1,i,j,nply);k--;l++;}

				k=i;l=j;
				while(position[k][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k,l-1,i,j,nply);l--;}

				k=i;l=j;
				while(position[k][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k,l+1,i,j,nply);l++;}

				k=i;l=j;
				while(position[k+1][l-1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l-1,i,j,nply);k++;l--;}

				k=i;l=j;
				while(position[k+1][l]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l,i,j,nply);k++;}

				k=i;l=j;
				while(position[k+1][l+1]==0)
				{moveCount=moveCount+CreatePossibleBar(position,k+1,l+1,i,j,nply);k++;l++;}

			}


		}
	}

	return moveCount;

}

int MoveGenerator::CreatePossibleBar(BYTE position[][12],int x,int y,int lx,int ly,int nply)
{
	BYTE curposition[12][12];
	int n=0;
	int i,j;
	int k,l;
	for(i=0;i<12;i++)
	{
		for(j=0;j<12;j++)
		{
			curposition[i][j]=position[i][j];
		}
	}

	curposition[x][y]=curposition[lx][ly];
	curposition[lx][ly]=0;
    i=x;j=y;

//			
			
                k=i;l=j;
				while(curposition[k-1][l-1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k-1;moveLine[nply][n+moveCount].barY=l-1;
			        moveLine[nply][n+moveCount].score=0;
					k--;l--;n++;
				}

                k=i;l=j;
				while(curposition[k-1][l]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k-1;moveLine[nply][n+moveCount].barY=l;
			        moveLine[nply][n+moveCount].score=0;
					k--;n++;
				}

				k=i;l=j;
				while(curposition[k-1][l+1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k-1;moveLine[nply][n+moveCount].barY=l+1;
			        moveLine[nply][n+moveCount].score=0;
					k--;l++;n++;
				}

				k=i;l=j;
				while(curposition[k][l-1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k;moveLine[nply][n+moveCount].barY=l-1;
			moveLine[nply][n+moveCount].score=0;
					l--;n++;
				}

				k=i;l=j;
				while(curposition[k][l+1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k;moveLine[nply][n+moveCount].barY=l+1;
			   moveLine[nply][n+moveCount].score=0;
					l++;n++;
				}

				k=i;l=j;
				while(curposition[k+1][l-1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k+1;moveLine[nply][n+moveCount].barY=l-1;
			moveLine[nply][n+moveCount].score=0;
					k++;l--;n++;
				}

				k=i;l=j;
				while(curposition[k+1][l]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k+1;moveLine[nply][n+moveCount].barY=l;
			moveLine[nply][n+moveCount].score=0;
					k++;n++;
				}

				k=i;l=j;
				while(curposition[k+1][l+1]==0)
				{
					moveLine[nply][n+moveCount].x=x;moveLine[nply][n+moveCount].y=y;moveLine[nply][n+moveCount].priviousX=lx;moveLine[nply][n+moveCount].priviousY=ly;moveLine[nply][n+moveCount].barX=k+1;moveLine[nply][n+moveCount].barY=l+1;
				moveLine[nply][n+moveCount].score=0;
					k++;l++;n++;
				}
			
			return n;
		
	


}

