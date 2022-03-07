 #include "stdafx.h"
#include "AmazonsView.h"
#include "SearchEngine.h"
#include "math.h"
#include "AmazonsAI.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Move killMoveTable[9][2];
MoveGenerator *mg;//走法产生指针
 static int nDistance;
 int Player;
BYTE currentPosition[12][12];
Move nullMove;

struct RS{ 
Move curhashmove ,killer1,killer2;
int nPhase, curcount,nCount;
 
void Init(Move mv)
{
    curhashmove=mv;
    killer1=killMoveTable[nDistance][0];
    killer2=killMoveTable[nDistance][1];
    nPhase= PHASE_HASH;
}
 Move Next(int depth);
};


SearchEngine::SearchEngine()
{
 

}

SearchEngine::~SearchEngine()
{
 //delete mg;
//delete ef;
if (m_HistoryTable)
	 delete(m_HistoryTable); 
 delete(m_p_TT);
}

bool Valid(Move  move )
{
	if( currentPosition[move.priviousX][move.priviousY]!=(Player+2)  || currentPosition[move.x][move.y]!=0 )
	   
		return false;
 	
	else if ( rules(move.priviousX,move.priviousY,move.x,move.y) )   
	{
	
	 
		BYTE ASD;
	    ASD=currentPosition[move.priviousX][move.priviousY];
        currentPosition[move.priviousX][move.priviousY]=0;
        currentPosition[move.x][move.y]=ASD;
		  if(currentPosition[move.barX][move.barY]==0)
		  {
		       if(rules(move.x, move.y, move.barX, move.barY)  )
			   {
         	   currentPosition[move.priviousX][move.priviousY]=ASD;
	           currentPosition[move.x][move.y]=0;
	           return true;
			   } 
	           else
			   {
		       currentPosition[move.priviousX][move.priviousY]=ASD;
	           currentPosition[move.x][move.y]=0;
	           return false;
		   
			 }

		  }
	  else 
	  {
	           currentPosition[move.priviousX][move.priviousY]=ASD;
	           currentPosition[move.x][move.y]=0;
	           return false;
	  
	  }
	
	
	}
	      
}


bool rules(int x,int y,int xx, int yy )
{
   
if(x==xx||y==yy||(y-x)==(yy-xx)||(x+y)==(xx+yy))
{  
	if( x==xx && y==yy )
		return false;
	
	if(x==xx)
		{
			if(yy>y)
			{
				for(int i=y+1;i<yy;i++)
					if(currentPosition[x][i]!=0)////==1||curposition[x][i]==2||curposition[x][i]==3)
						return 0;
			}
			else 
			{
				for(int i=yy+1;i<y;i++)
					if(currentPosition[x][i]!=0)//==1||curposition[x][i]==2||curposition[x][i]==3)
						return 0;
			}
			return 1;
		}
	
	else if(yy==y)
		{
			if(xx>x)
			{
				for(int i=x+1;i<xx;i++)
					if(currentPosition[i][y]!=0)//==1||curposition[i][y]==2||curposition[i][y]==3)
						return 0;
			}
			else
			{
				for(int i=xx+1;i<x;i++)
					if(currentPosition[i][y]!=0)//==1||curposition[i][y]==2||curposition[i][y]==3)
						return 0;
			}
			return 1;
		}
	
	else if((yy-xx)==(y-x))
		{
			int k=y-x;
		 
		   if(yy>y)
			{
				for(int i=y+1;i<yy;i++)
					if(currentPosition[i-k][i]!=0)//==1||curposition[i-k][i]==2||curposition[i-k][i]==3)
						return 0;
			}
			else
			{
				for(int i=yy+1;i<y;i++)
					if(currentPosition[i-k][i]!=0)//==1||curposition[i-k][i]==2||curposition[i-k][i]==3)
						return 0;
			}
			return 1;
		}
	
	else if((yy+xx)==(y+x))
		{
			int k=y+x;
			if(yy>y)
			{
				for(int i=y+1;i<yy;i++)
					if(currentPosition[k-i][i]!=0)//==1||curposition[k-i][i]==2||curposition[k-i][i]==3)
						return 0;
			}
			else
			{
				for(int i=yy+1;i<y;i++)
					if(currentPosition[k-i][i]!=0)//==1||curposition[k-i][i]==2||curposition[k-i][i]==3)
						return 0;
			}
			return 1;
		}
} 
	return 0;
}

bool xor(Move move1, Move move2)
{
	if(move1.barX==move2.barX && move1.barY==move2.barY && move1.priviousX==move2.priviousX 
		&& move1.priviousY==move2.priviousY && move1.x==move2.x && move1.y==move2.y)
        return false;
	else 
		return true;
}
void SearchEngine::SetBestMove(Move MV ,int depth)
{
Move *kv;
      
    EnterHistoryScore(&MV,depth);
      
		 kv=killMoveTable[nDistance];
  if( xor(MV , kv[0] ) )
     {
	        kv[1]=kv[0];
	        kv[0]=MV; 
	 
  }   

}

BYTE SearchEngine::makeMove(Move *MOVE)
{   

   Hash_MakeMove( MOVE , currentPosition);  
	Player=1-Player;
	nDistance++;
	BYTE ID;
	
	ID=currentPosition[MOVE->priviousX][MOVE->priviousY];
    currentPosition[MOVE->x][MOVE->y]=ID;
	currentPosition[MOVE->priviousX][MOVE->priviousY]=0;
	currentPosition[MOVE->barX][MOVE->barY]=1;
	return ID;
}


void SearchEngine::unMakeMove(Move *MOVE,BYTE ID)
{   	 
    Hash_UnMakeMove( MOVE , currentPosition );
	Player=1-Player;
      nDistance--;
	currentPosition[MOVE->barX][MOVE->barY]=0;
	currentPosition[MOVE->priviousX][MOVE->priviousY]=ID;
	currentPosition[MOVE->x][MOVE->y]=0;
}

int times;  
 int testc ;
 int md=0;
 int node;
 int Verteilung;
Move SearchEngine::searchMove(BYTE position[][12], bool side, int & md_, int & score_, int & node_)
{
  
	int i,j;
	nullMove.barX=nullMove.barY=nullMove.priviousX=nullMove.priviousY=nullMove.score=nullMove.x=nullMove.y=0;
    int punkt=0;
 	for(i=1;i<11;i++)
		for(j=1;j<11;j++)
		{
			if(position[i][j]==1)
				punkt++;
  }
   
   srand(time(0));
   int selekt=rand()%8;;   //可以定义为开局的随机数目 所有开局均为一步评价排位靠前的 0-1为对称棋局以此类推 目前8种开局
  	                   //其中 6，7为电脑搜索4层时 认为最好开局
    if(punkt==0)   ////注意！ 这里可以修改开局表  
	{
		m_HistoryTable = new int[1];
		m_p_TT = new HashItem[1];
		if (side) {//player1
			if (selekt == 0)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 3;
				bestMove.barX = 2;
				bestMove.barY = 5;

				return bestMove;
			}
			else if (selekt == 1)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 3;
				bestMove.barX = 9;
				bestMove.barY = 5;

				return bestMove;
			}

			//////////////////////////////////////////////////////////////
			else if (selekt == 2)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 4;
				bestMove.barX = 7;
				bestMove.barY = 4;

				return bestMove;
			}
			else if (selekt == 3)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 4;
				bestMove.barX = 4;
				bestMove.barY = 4;

				return bestMove;
			}
			//////////////////////////////////////////
			else if (selekt == 4)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 2;
				bestMove.barX = 5;
				bestMove.barY = 2;

				return bestMove;
			}
			else if (selekt == 5)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 2;
				bestMove.barX = 6;
				bestMove.barY = 2;

				return bestMove;
			}
			////////////////////////////////////////// 
			else if (selekt == 6)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 2;
				bestMove.barX = 4;
				bestMove.barY = 2;

				return bestMove;
			}
			else if (selekt == 7)
			{

				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 2;
				bestMove.barX = 7;
				bestMove.barY = 2;

				return bestMove;

			}
		}
		else {
			if (selekt == 0)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 3;
				bestMove.barX = 2;
				bestMove.barY = 5;

				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			else if (selekt == 1)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 3;
				bestMove.barX = 9;
				bestMove.barY = 5;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}

			//////////////////////////////////////////////////////////////
			else if (selekt == 2)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 4;
				bestMove.barX = 7;
				bestMove.barY = 4;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			else if (selekt == 3)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 4;
				bestMove.barX = 4;
				bestMove.barY = 4;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			//////////////////////////////////////////
			else if (selekt == 4)
			{
				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 2;
				bestMove.barX = 5;
				bestMove.barY = 2;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			else if (selekt == 5)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 2;
				bestMove.barX = 6;
				bestMove.barY = 2;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			////////////////////////////////////////// 
			else if (selekt == 6)
			{
				bestMove.priviousX = 7;
				bestMove.priviousY = 10;
				bestMove.x = 7;
				bestMove.y = 2;
				bestMove.barX = 4;
				bestMove.barY = 2;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;
			}
			else if (selekt == 7)
			{

				bestMove.priviousX = 4;
				bestMove.priviousY = 10;
				bestMove.x = 4;
				bestMove.y = 2;
				bestMove.barX = 7;
				bestMove.barY = 2;
				bestMove.priviousY = 11 - bestMove.priviousY;
				bestMove.y = 11 - bestMove.y;
				bestMove.barY = 11 - bestMove.barY;
				bestMove.x = 11 - bestMove.x;
				bestMove.priviousX = 11 - bestMove.priviousX;
				bestMove.barX = 11 - bestMove.barX;
				return bestMove;

			}
		}


	}
  
	MoveGenerator As;
  	EvaluationFunction Bs;
 
	mg=&As;
	p_evaluation=&Bs;
    testc=0;
	node=0;
 
	m_HistoryTable = new int[1000000];
    memset(m_HistoryTable,0,1000000*4);
    memset( killMoveTable,0,18*sizeof(Move));
  
    
 	Bs.Evaluation(position,side);
	int ws=0;
	ws=Bs.w;

	if (ws >= 40)
	{
		//	AfxMessageBox("4");
		Verteilung = 120000;
		md = 3;
	}
	if (ws < 40 && ws >= 28)
	{
		//   AfxMessageBox("5");
		Verteilung = 150000;
		md = 4;

	}
   if(ws<28)
	 {
//	   AfxMessageBox("6");
	   Verteilung=180000;
		 md=5;
	 } 

    Player=!side;
    nDistance=0;
	InitializeHashKey(); 
    memcpy(currentPosition ,position , 144);
 	CalculateInitHashKey(position);
	times=GetTickCount();
 
    bestMove=nullMove;
 
	for(maxDepth=1;maxDepth<=md;maxDepth++)
    { 
	    
		if( GetTickCount()-times >90000)
		 {	
           //AfxMessageBox("break-w");
		 	break;
		 } 
		sR(maxDepth,0, side);
 
   }

	md_ = md;
	node_ = node;
	score_ = bestMove.score;
	return bestMove;
 
 
 	
}
bool testMove(int depth ,int count,Move mv)
{  
      
   for(int i=0;i<count;i++)
   {
      if (mg->moveLine[depth][i].barX==mv.barX 
		  &&mg->moveLine[depth][i].barY==mv.barY 
		  && mg->moveLine[depth][i].priviousY==mv.priviousY
		  && mg->moveLine[depth][i].priviousX==mv.priviousX
	      &&mg->moveLine[depth][i].x==mv.x 
		  && mg->moveLine[depth][i].y==mv.y)
	  {	return true;}
   
   }
	
	return false;



}
Move RS::Next(int depth)
{
  Move moves;
 
  moves=nullMove;
  switch(nPhase){
  case PHASE_HASH:
           nPhase=PHASE_KILLER1;
          if(xor(curhashmove,moves))
		  { 
			  return curhashmove;
		  }
  case PHASE_KILLER1:
	  nPhase=PHASE_KILLER2;
  
	  if(  Valid(killer1)   && xor(curhashmove ,killer1)    )        
	  {      
		 
			 return   killer1;}

  case PHASE_KILLER2:
	   nPhase=PHASE_CreatePM;
	   curcount=0; 
	   
	   
	   if(  Valid(killer2) && xor(curhashmove ,killer2) )
	   {
		   return  killer2;
	   }   
	    
	    
  case PHASE_CreatePM:
	      while(curcount<nCount)
		  { 
		 
		    moves=mg->moveLine[depth][curcount]; 
			curcount++;
			if(xor(moves ,killer1) && xor(moves,killer2)  && xor(curhashmove ,moves)  )
			{  return moves; }
				 
		  }
 
  
 default:
		      return  nullMove;
  }
}
 

  double SearchEngine::sR( int depth, int node_type, bool side)
  {
      double score ,best;
      Move mv; 
	  BYTE ID;
	  int  i ;
     
      RS Rs;
    best=-20000;

     
     
	 
 	 Rs.nCount=mg->CreatePossibleMove(currentPosition,Player,depth);

/////////////////////F P///////////////////////////////////////////////
  if( depth==maxDepth)
	 { 

   for(i=0;i<Rs.nCount;i++)
   {   	   ID=makeMove(&mg->moveLine[maxDepth][i]);	   
	       double s=p_evaluation->Evaluation(currentPosition,!Player);//0
           mg->moveLine[maxDepth][i].score=s;	 
	       unMakeMove(&mg->moveLine[maxDepth][i],ID);
   }
      
      int g=sortMove(maxDepth,Rs.nCount,1,20);
    
    	  if(Rs.nCount>210) 
		  {
		     if(  g>100  )   
		          Rs.nCount=100;
	          else
				  Rs.nCount=210;
		  }
 
	}
////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////
  
 Rs.Init(bestMove);
 
  while(xor(mv=Rs.Next(depth),nullMove) )
  {      
      
	   if(maxDepth==md)
	   {
	      node++;
	   }
	   
   
	  if( GetTickCount()-times >180000)
	  {
       //  AfxMessageBox("break-n");
		  break;
	  } 
        ID=makeMove(&mv);
 		
		if( best==-20000)
		{	score=-moveScore(   -20000,   20000 ,depth-1 ,-node_type);  }    ////first blood  here nodetype must be 0     
    	else
		{
	   score=-moveScore(   -best-.0001,  -best , depth-1 , (node_type==CUT_NODE ?ALL_NODE:CUT_NODE)  );  ////fresh meat  here nodetype must be 1     
	      if(score>best){
    	score=-moveScore(   -20000,  -best ,depth-1 ,node_type);    // must be 0
		  }
		}
		unMakeMove(&mv,ID); 
	  
       if( abs((long long)score)!=1234567 )
       {
		if(score>best){

			   best=score;
		       bestMove=mv;
		 
		    bestMove.score=best;
		}
	  }
  }
        
  
 	 EnterHashTable(exact, best, depth ,bestMove);
     SetBestMove(bestMove,depth);
	
  return best;
  }

  double SearchEngine::moveScore(double alpha, double beta , int depth , int node_type)
  {
    double score ,best;
      Move mv,bestmv  ,hashmv; 
	  int  i ;
      RS Rs;
      ENTRY_TYPE hashflag;
      BYTE ID;
   
   if(maxDepth==md && (GetTickCount()-times)>180000 && node>=1 )
   {
       return 1234567;
   }  
    
       score= LookUpHashTable(alpha,beta,depth ,hashmv);
            if(score!=66666)
			{  
			   return score;
			}   
	   
            
		if(depth<=0)
		{  
         testc++;
     	 score =p_evaluation->Evaluation(currentPosition,Player);
         EnterHashTable(exact,score,depth ,hashmv);
		 return score;  
		}
	
 

 


 best=-20000;
 hashflag=upper_bound;
  bestmv.barX=bestmv.barY=bestmv.priviousX=bestmv.priviousY=bestmv.x=bestmv.y=0;
 
 Rs.Init(hashmv);
 

	 Rs.nCount=mg->CreatePossibleMove(currentPosition,Player,depth);
 
 
 
 
  for (i=0;i<Rs.nCount;i++) 
	   {
		mg->moveLine[depth][i].score = 
 			           0.8*GetHistoryScore(&mg->moveLine[depth][i]);
  }   
  
   qrs(depth,0,Rs.nCount-1);  
 //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////muti-cut/////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////
/*   if(node_type==CUT_NODE && depth>2 )
{


  int cc=0,mm=0;
     while(xor(mv=Rs.Next(depth),zero) && mm< (Rs.nCount<M ? Rs.nCount : M) )
	 {     ID=makemove(&mv);
           score=-ms(-beta,-alpha,depth-1-R,-node_type);
	       unmakemove(&mv,ID); 
		      if(score>=beta)
			  {
		        cc++;
			    if(cc> (Rs.nCount<C ? Rs.nCount :C ) )
				  return beta;
			  }
                 mm++;
      
	 }
   }     */

 ////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////
  while(xor(mv=Rs.Next(depth),nullMove) )//testmv(depth,Rs.nCount, mv=Rs.Next(depth) ) )
	{      
 
        ID=makeMove(&mv);
      

		if(best==-20000){
		score=-moveScore( -beta, -alpha ,depth-1 ,-node_type);  
		}
		else
		{
			score=-moveScore( -alpha-.0001, -alpha ,depth-1 ,(node_type==CUT_NODE ?ALL_NODE:CUT_NODE)  );   
			if(score>best){
            score=-moveScore( -beta, -alpha ,depth-1 ,node_type);  
			}
		}
		
		
		
		
		
		unMakeMove(&mv,ID); 
		
		if(score>best)	   
		{
		   best=score;
		   if(score>=beta)
		   {    hashflag=lower_bound;
			    bestmv=mv;
				break;
		   }  
		   if(score>alpha)
		   {    hashflag=exact;
				alpha=score;
			    bestmv=mv;
		       
		   }
 
	    
		}
           
			   
	 }

if(best==-20000)
{  return (nDistance-20000);}


  EnterHashTable(hashflag, best, depth, bestmv);


   if( xor(bestmv,nullMove) )  //testmv(depth,Rs.nCount,bestmv) )
   {
   SetBestMove(bestmv,depth);
	   
   }


   return best;	

  }
 
 





 
int SearchEngine::sortMove(int depth, int count ,bool flag, double score)
{

       
  int i,j;
  Move m;
  if( flag=0){
  for(j=1;j<=count-1;j++)
	  for(i=0;i<count-j;i++ )
		  if(mg->moveLine[depth][i].score<mg->moveLine[depth][i+1].score)
		  {//////////////////////////////////////////////////
		   m=mg->moveLine[depth][i];
		   mg->moveLine[depth][i]=mg->moveLine[depth][i+1];
		   mg->moveLine[depth][i+1]=m;
		  }
  return count;
  }
       else
	   {
	         for(j=1;j<=count-1;j++)
	               for(i=0;i<count-j;i++ )
		             if(mg->moveLine[depth][i].score<mg->moveLine[depth][i+1].score)
					 {//////////////////////////////////////////////////
		              m=mg->moveLine[depth][i];
		              mg->moveLine[depth][i]=mg->moveLine[depth][i+1];
		              mg->moveLine[depth][i+1]=m;
					 }
	   
	        for(int i=0;i<count;i++)
				if(mg->moveLine[depth][i].score<score)
					return i;
	   }
return 0;

}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////////Transposition Table////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
LONGLONG rand64(void)
{

    return rand() ^ ((LONGLONG)rand() << 15) ^ ((LONGLONG)rand() << 30) ^

        ((LONGLONG)rand() << 45) ^ ((LONGLONG)rand() << 60);

}
LONG rand32(void)
{

    return rand() ^ ((LONG)rand() << 15) ^ ((LONG)rand() << 30);

}
 
void SearchEngine::InitializeHashKey()
{
	int i,j,k;
	
	srand( (unsigned)time( NULL ));
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 10; j++)
			for (k = 0; k < 10; k++)
			{
				m_nHashKey32[i][j][k] = rand32();
				m_ulHashKey64[i][j][k] = rand64();
			}
    m_p_TT= new HashItem[2048*2048];
  
}
void SearchEngine::CalculateInitHashKey(BYTE position[][12])
{
	int i,j;
	BYTE nStoneType;
	m_HashKey32 = 0;
	m_HashKey64 = 0;
	for (i = 1; i < 11; i++)
		for (j = 1; j < 11; j++)
		{
			nStoneType = position[i][j];
		  
			if (nStoneType != 0)    //0=NO_CHESS  
			{                        
				m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nStoneType][i-1][j-1]; 
				m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nStoneType][i-1][j-1]; 
	 
			}
		}

 

}
void SearchEngine::Hash_MakeMove(Move *MOVE, BYTE position[][12])
{  BYTE FromID;
      FromID=position[MOVE->priviousX][MOVE->priviousY];
	  ////////////////////起子
   	m_HashKey32 = m_HashKey32^m_nHashKey32[FromID][MOVE->priviousX-1][MOVE->priviousY-1]; 
	m_HashKey64 = m_HashKey64 ^m_ulHashKey64[FromID][MOVE->priviousX-1][MOVE->priviousY-1]; 
  ////////////////////////落子/////////////////////////////////////////
   m_HashKey32 = m_HashKey32^m_nHashKey32[FromID][MOVE->x-1][MOVE->y-1]; 
   m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[FromID][MOVE->x-1][MOVE->y-1]; 
/////////////////////////////放置障碍/////////////////// 障碍=1？
   m_HashKey32 = m_HashKey32^m_nHashKey32[1][MOVE->barX-1][MOVE->barY-1]; 
   m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[1][MOVE->barX-1][MOVE->barY-1]; 
}
void SearchEngine::Hash_UnMakeMove(Move *MOVE , BYTE position[][12])
{
     BYTE ToID;
	 ToID=position[MOVE->x][MOVE->y];
	 /////////////////////复原障碍//////////////////////
        m_HashKey32 = m_HashKey32^m_nHashKey32[1][MOVE->barX-1][MOVE->barY-1]; 
        m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[1][MOVE->barX-1][MOVE->barY-1]; 
	////////////////复原落子点///////////////////////
        m_HashKey32 = m_HashKey32^m_nHashKey32[ToID][MOVE->x-1][MOVE->y-1]; 
        m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[ToID][MOVE->x-1][MOVE->y-1]; 
//////////////////////////////复员起子点///////////////////////
        m_HashKey32 = m_HashKey32^m_nHashKey32[ToID][MOVE->priviousX-1][MOVE->priviousY-1]; 
     	m_HashKey64 = m_HashKey64 ^m_ulHashKey64[ToID][MOVE->priviousX-1][MOVE->priviousY-1];
}
double SearchEngine::LookUpHashTable(double alpha, double beta, int depth ,Move  &mv )
{

		int x;
	HashItem * pht;

	x = m_HashKey32 & 0x3FFFFF;
	pht = &m_p_TT[x];
       
    if( pht->checksum != m_HashKey64 )
	{  
		mv.barX=mv.barY=mv.priviousX=mv.priviousY=mv.x=mv.y=0;
	return 66666;  }
	
   mv=pht->hashMove;
	
	if (pht->depth >=  depth )
	{
		switch (pht->entry_type) 
		{
		case exact: 
			return pht->eval;
		case lower_bound:
			if (pht->eval >= beta)
				return (pht->eval);
			else 
				break;
		case upper_bound:
			if (pht->eval <= alpha)
				return (pht->eval);
			else 
				break;
        }
	}

	return 66666;


}
void SearchEngine::EnterHashTable(ENTRY_TYPE entry_type, double eval, short depth ,Move mv)
{
	int x;
	HashItem * pht;

	x = m_HashKey32 & 0x3FFFFF;//二十位哈希地址
	pht = &m_p_TT[x];
  if(pht->depth>depth)
	 { 
	  return ;
  }
    pht->checksum = m_HashKey64;
	pht->entry_type = entry_type;
    pht->hashMove=mv;
	pht->eval = eval;
	pht->depth = depth;

}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////////////History Heuristic////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BYTE SearchEngine::GetHistoryScore(Move *MOVE)
{  int number;
        number=(MOVE->priviousX-1)+(MOVE->priviousY-1)*10+(MOVE->x-1)*100+(MOVE->priviousY-1)*1000+(MOVE->barX-1)*10000+(MOVE->barY-1)*100000; 
    return m_HistoryTable[number];
}
void SearchEngine::EnterHistoryScore(Move *MOVE ,int depth)
{
    int number;
    number=(MOVE->priviousX-1)+(MOVE->priviousY-1)*10+(MOVE->x-1)*100+(MOVE->priviousY-1)*1000+(MOVE->barX-1)*10000+(MOVE->barY-1)*100000; 
    m_HistoryTable[number]+=2^depth;
}
void SearchEngine::qrs(int depth ,int left, int right)
{
  int i,j;
  double middle;
  Move temp;
  Move *a=& ( *mg->moveLine[depth]);
i = left; 
j = right;
   middle = a[(left+right)/2].score; 
 
   do{ 
   while((a[i].score > middle) && (i<right))//从左扫描大于中值的数 
    i++;      
   while((a[j].score <middle) && (j>left))//从右扫描大于中值的数 
    j--; 
   if(i<=j)//找到了一对值 
   { 
    //交换 
    temp =a[i]; 
    a[i]= a[j]; 
    a[j] = temp; 
    i++; 
    j--; 
   } 
}while(i<=j); 

 if(left<j) 
   qrs(depth,left,j); 
if(right>i) 
   qrs(depth,i,right); 


}
