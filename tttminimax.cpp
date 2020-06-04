#include <iostream>
using namespace std;

struct point
{
    int x,y;
};

bool isMovesLeft(char board[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]==' ') 
                return true; 
    return false; 
}

int evaluate(char b[3][3]) 
{ 
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]=='X') 
                return +10; 
            else if (b[row][0]=='O') 
                return -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]=='X') 
                return +10; 
  
            else if (b[0][col]=='O') 
                return -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]=='X') 
            return +10; 
        else if (b[0][0]=='O') 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]=='X') 
            return +10; 
        else if (b[0][2]=='O') 
            return -10; 
    } 
    return 0; 
} 

void printboard(char b[3][3])
{
	cout<<"\n\n";
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          cout<<b[i][j]<<" ";
        }
    cout<<"\n";
    }
    cout<<"\n\n";
}

int minimax(char board[3][3],bool ismax)
{
    int score=evaluate(board);
    //printboard(board);
    
    if(score)
        return score;
    if(isMovesLeft(board)==false)
        return 0;
    
    if(ismax)
    {
       int besteval=-1000;
       for(int i=0;i<3;i++)
       {
            for (int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='X';
                    //printboard(board);
                besteval=max(minimax(board,!ismax),besteval);
                board[i][j]=' ';
                
                }
            }
       }
        return besteval;
            
    }
    
    else
    {
       int besteval=1000;
       for(int i=0;i<3;i++)
       {
            for (int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='O';
                besteval=min(minimax(board,!ismax),besteval);
                board[i][j]=' ';
                
                }
            }
       }
        return besteval;
            
    }


}

point bestmove(char board[3][3])
{
    point best;
    int eval=-100;int c=0;
    for(int i=0;i<3;i++)
    {
	
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
              
           {
           	  board[i][j]='X';;
           	  int m=minimax(board,false);
			  board[i][j]=' ';
            	if(eval<m)
                {
                    best.x=i;
                    best.y=j;
                    eval=m;
                    c++;
                }
			}
            
        }	
    }
    return best;
}

int main() {
	 char board[3][3] = 
    { 
        { ' ', ' ', ' ' }, 
        { ' ', ' ', ' ' }, 
        { ' ', ' ', ' ' } 
    }; 
    
   while(isMovesLeft(board))
    {
    int c1,c2;
   p1: cout<<"Enter coordinates\n";
    cin>>c1;
    cin>>c2;
    if(board[c1][c2]!=' ')
    {
    	cout<<"Invalid move\n";
    	printboard(board);
    	goto p1;
	}
    board[c1][c2]='O';
	//cout<<minimax(board,true)<<"minimax after O\n";
    point a=bestmove(board);
    board[a.x][a.y]='X';
    //cout<<minimax(board,false)<<":minimax after X\n";
    printboard(board);
    if(evaluate(board)==10)
        cout<<"X wins";
    else if(evaluate(board)==-10)
        cout<<"O wins";
    else if(evaluate(board)==0 && isMovesLeft(board)==false)
        cout<<"draw";
    }
    
   
    return 0;
}

