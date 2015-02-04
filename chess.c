#include <stdio.h>
#include <stdlib.h>

#define current board[currv][currh]
#define newpos board[newv][newh]
#define currentm arr[currv][currh]
#define newposm arr[newv][newh]

struct node
{
    char copybrd[8][8];
    struct node *child;
};

int capital();
int small();
float minimax(struct node *,int,int);
int eyesight(int,int);
int ceyesight(int,int);
int eyesight_min(int,int,char [][8]);
int ceyesight_min(int,int,char [][8]);
void copy_array(int,int,int,int,char [][8],char [][8]);
int mate(char [][8]);
int cmate(char [][8]);
int makemove(int,int,int,int);
int printbrd();
void promote(int,int);
void cpromote(int,int);
int pawn(int,int,int,int);
int cpawn(int,int,int,int);
int rook(int,int,int,int);
int crook(int,int,int,int);
int bishop(int,int,int,int);
int cbishop(int,int,int,int);
int knight(int,int,int,int);
int cknight(int,int,int,int);
int queen(int,int,int,int);
int cqueen(int,int,int,int);
int king(int,int,int,int);
int cking(int,int,int,int);
int valid_move(int,int,int,int);
void promote_min(int,int,char [][8]);
void cpromote_min(int,int,char [][8]);
int pawn_min(int,int,int,int,char [][8]);
int cpawn_min(int,int,int,int,char [][8]);
int rook_min(int,int,int,int,char [][8]);
int crook_min(int,int,int,int,char [][8]);
int bishop_min(int,int,int,int,char[][8]);
int cbishop_min(int,int,int,int,char [][8]);
int knight_min(int,int,int,int,char [][8]);
int cknight_min(int,int,int,int,char [][8]);
int queen_min(int,int,int,int,char [][8]);
int cqueen_min(int,int,int,int,char[][8]);
int king_min(int,int,int,int,char[][8]);
int cking_min(int,int,int,int,char[][8]);
int valid_move_min(int,int,int,int,char[][8]);
int value_board(char[][8]);
int val_pawn(int,int,int*,char[][8]);
int val_cpawn(int,int,int*,char[][8]);
int val_rook(int,int,int*,char[][8]);
int val_crook(int,int,int*,char[][8]);
int val_bishop(int,int,int*,char[][8]);
int val_cbishop(int,int,int*,char[][8]);
int val_knight(int,int,int*,char[][8]);
int val_cknight(int,int,int*,char[][8]);
int val_queen(int,int,int*,char[][8]);
int val_cqueen(int,int,int*,char[][8]);
int val_king(int,int,int*,char[][8]);
int val_cking(int,int,int*,char[][8]);
int isolated(char[][8]);
int cisolated(char[][8]);
int doubled(char[][8]);
int cdoubled(char[][8]);
int blocked(char[][8]);

char board[8][8]={'r','n','b','q','k','b','n','r',
			 	  'p','p','p','p','p','p','p','p',
				  ' ',' ',' ',' ',' ',' ',' ',' ',
				  ' ',' ',' ',' ',' ',' ',' ',' ',
			  	  ' ',' ',' ',' ',' ',' ',' ',' ',
			 	  ' ',' ',' ',' ',' ',' ',' ',' ',
			 	  'P','P','P','P','P','P','P','P',
			 	  'R','N','B','Q','K','B','N','R'
				 };

int rightrook_moved=0,leftrook_moved=0,king_moved=0,cking_moved=0,rightcrook_moved=0,leftcrook_moved=0;

int rightrook_moved_min=0,leftrook_moved_min=0,king_moved_min=0,cking_moved_min=0,rightcrook_moved_min=0,leftcrook_moved_min=0;
int depth=4;


int cnewv=0,cnewh=0,ccurrv=0,ccurrh=0;

//Tree for evaluating best board



int isolated(char arr[][8])
{
    int iso=0,k,i,j;
    for (i=0;i<7;i++)
    {
        k=0;
        for (j=0;j<8;j++)
            if (arr[j][i]=='P')
                k=1;
        if(k==1)
            for(j=0;j<8;j++)
                if(arr[j][i+1]=='P')
                    k=0;
        if(k==1)
            iso++;
    }
    return iso;
}

int cisolated(char arr[][8])
{
    int ciso=0,k,i,j;
    for(i=0;i<7;i++)
    {
        k=0;
        for(j=0;j<8;j++)
            if(arr[j][i]=='p')
                k=1;
        if (k==1)
            for(j=0;j<8;j++)
                if(arr[j][i+1]=='p')
                    k=0;
        if (k==1)
            ciso++;
    }
    return ciso;
}

int doubled(char arr[][8])
{
    int dou=0,k=0,i,j;
    for(i=0;i<8;i++)
    {
        k=0;
        for(j=0;j<8;j++)
        {
            if(arr[j][i]=='P')
                k++;
        }
        if(k>1)
            dou++;
    }
    return dou;
}

int cdoubled(char arr[][8])
{
    int cdou=0,k=0,i,j;
    for(i=0;i<8;i++)
    {
        k=0;
        for(j=0;j<8;j++)
        {
            if(arr[j][i]=='p')
                k++;
        }
        if (k>1)
            cdou++;
    }
    return cdou;
}

int blocked(char arr[][8])
{
    int blo=0,i,j;
    for(i=0;i<8;i++)
        for(j=0;j<7;j++)
            if(arr[j][i]=='p'&&arr[j+1][i]=='P')
                blo++;
    return blo;
}

int val_pawn(int currv,int currh,int *pawn,char arr[][8])
{
    int i,j,mpawn=0;
    if(currv==2)
        *pawn+=4;
    else if (currv==1)
        *pawn+=6;
    else *pawn+=1;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            if (i!=0)
            {
                if (valid_move_min(currv,currh,i,j,arr)==1)
                {
                    if(arr[i][j]==' ')
                        mpawn++;
                    else mpawn+=2;
            	}
            }
            else if (i==0)
            {
                if (currv==1)
                {
                    if ((j==currh+1||j==currh-1)&&arr[i][j]!=' ')
                        mpawn+=2;
                    else if (j==currh&&arr[i][j]==' ')
                        mpawn++;
        		}
        	}
        }
    return mpawn;
}

int val_cpawn(int currv,int currh,int *cpawn,char arr[][8])
{
    int i,j,mcpawn=0;
    if (currv==5)
        *cpawn+=4;
    else if (currv==6)
        *cpawn+=6;
    else *cpawn+=1;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (i!=7)
            {
                if (valid_move_min(currv,currh,i,j,arr)==1)
                {
                    if (arr[i][j]==' ')
                        mcpawn++;
                    else mcpawn+=2;
            	}
            }
            else if (i==7)
            {
                if (currv==6)
                {
                    if ((j==currh+1||j==currh-1)&&arr[i][j]!=' ')
                        mcpawn+=2;
                    else if (j==currh&&arr[i][j]==' ')
                        mcpawn++;
        		}
        	}
        }
    return mcpawn;
}

int val_knight(int currv,int currh,int *knight,char arr[][8])
{
    int i,j,mknight=0;
    *knight+=3;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mknight++;
                else mknight+=2;
        }
    return mknight;
}

int val_cknight(int currv,int currh,int *cknight,char arr[][8])
{
    int i,j,mcknight=0;
    *cknight+=3;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mcknight++;
                else mcknight+=2;
        }
    return mcknight;
}

int val_bishop(int currv,int currh,int *bishop,char arr[][8])
{
    int i,j,mbishop=0;
    *bishop+=3;
    for (i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mbishop++;
                else mbishop+=2;
        }
    return mbishop;
}

int val_cbishop(int currv,int currh,int *cbishop,char arr[][8])
{
    int i,j,mcbishop=0;
    *cbishop+=3;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if(arr[i][j]==' ')
                    mcbishop++;
                else mcbishop+=2;
        }
    return mcbishop;
}

int val_rook(int currv,int currh,int *rook,char arr[][8])
{
    int i,j,mrook=0;
    *rook+=5;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mrook++;
                else mrook+=2;
        }
    return mrook;
}

int val_crook(int currv,int currh,int *crook,char arr[][8])
{
    int i,j,mcrook=0;
    *crook+=5;
    for (i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr))
            {
                if (arr[i][j]==' ')
                    mcrook++;
                else mcrook+=2;
        	}
        }
    return mcrook;
}

int val_queen(int currv,int currh,int *queen,char arr[][8])
{
    int i,j,mqueen=0;
    *queen+=9;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mqueen++;
                else mqueen+=2;
        }
    return mqueen;
}

int val_cqueen(int currv,int currh,int *cqueen,char arr[][8])
{
    int i,j,mcqueen=0;
    *cqueen+=9;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mcqueen++;
                else mcqueen+=2;
        }
    return mcqueen;
}

int val_king(int currv,int currh,int *king,char arr[][8])
{
    int i,j,mking=0;
    *king+=200;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mking++;
                else mking+=2;
        }
    return mking;
}

int val_cking(int currv,int currh,int *cking,char arr[][8])
{
    int i,j,mcking=0;
    *cking+=200;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
        {
            if (valid_move_min(currv,currh,i,j,arr)==1)
                if (arr[i][j]==' ')
                    mcking++;
                else mcking+=2;
        }
    return mcking;
}

int value_board(char arr[][8])
{   //store value
    int i,j;
    int pawn=0,cpawn=0,knight=0,cknight=0,bishop=0,cbishop=0,rook=0,crook=0,
                        queen=0,cqueen=0,king=0,cking=0;                //These variables will store the value
    int mpawn=0,mcpawn=0,mknight=0,mcknight=0,mbishop=0,mcbishop=0,
    /*store num of poss moves*/ mrook=0,mcrook=0,mqueen=0,mcqueen=0,mking=0,mcking=0;   //Will store the number of moves allowed
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            if (arr[i][j]=='p')
                mcpawn+=val_cpawn(i,j,&cpawn,arr);
            else if (arr[i][j]=='P')
                mpawn+=val_pawn(i,j,&pawn,arr);
            else if (arr[i][j]=='n')
                mcknight+=val_cknight(i,j,&cknight,arr);
            else if (arr[i][j]=='N')
                mknight+=val_knight(i,j,&knight,arr);
            else if (arr[i][j]=='b')
                mcbishop+=val_cbishop(i,j,&cbishop,arr);
            else if (arr[i][j]=='B')
                mbishop+=val_bishop(i,j,&bishop,arr);
            else if (arr[i][j]=='r')
                mcrook+=val_crook(i,j,&crook,arr);
            else if (arr[i][j]=='R')
                mrook+=val_rook(i,j,&rook,arr);
            else if (arr[i][j]=='q')
                mcqueen+=val_cqueen(i,j,&cqueen,arr);
            else if (arr[i][j]=='Q')
                mqueen+=val_queen(i,j,&queen,arr);
            else if (arr[i][j]=='k')
                mcking+=val_cking(i,j,&cking,arr);
            else if (arr[i][j]=='K')
                mking+=val_king(i,j,&king,arr);
        }
    int dou=0,cdou=0,iso=0,ciso=0,blo=0;
    dou=doubled(arr);
    cdou=cdoubled(arr);
    iso=isolated(arr);
    ciso=cisolated(arr);
    blo=blocked(arr);
    float board_val=0;
    board_val=pawn-cpawn+knight-cknight+bishop-cbishop+rook-crook+queen
                            -cqueen+king-cking;
    board_val+=0.1*((pawn*mpawn)-(cpawn*mcpawn)+(knight*mknight)-(cknight*mcknight)
                    +(bishop*mbishop)-(cbishop*mcbishop)+(rook*mrook)-(crook*mcrook)
                    +(queen*mqueen)-(cqueen*mcqueen)+(king*mking)-(cking*mcking));
    board_val+=0.08*(cdou-dou+ciso-iso-blo);
    return board_val;
}






void promote_min(int currv,int currh,char arr[][8])
{
    arr[currv][currh]='Q';
}

void cpromote_min(int currv,int currh,char arr[][8])
{
    arr[currv][currh]='q';
}

int pawn_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if (newposm==' ')							//new position is empty
    {
        if (newv==currv-1)						//moves 1 step forward
        {
            if(newh==currh)						//but in same column
            {
                if (newv==0)
                    promote_min(currv,currh,arr);
                return 1;						//then its VALID
            }
        }
        else if (currv==6&&newv==4)				//first move can be of 2 steps
        {
            if (newh==currh)					//but still in same column
            {
            	if(arr[5][currh]==' ')		//path must be empty
                	return 1;					//then its VALID
            }
    	}
    }
    else if (newposm<='z'&&newposm>='a')			//or it can kill an opponent's piece
    {
        if (newv==currv-1)						//by moving 1 unit forward
        {
            if (newh==currh-1||newh==currh+1)	//but must attack digonally
            {
                if (newv==0)
                    promote_min(currv,currh,arr);
                return 1;						//then its VALID
            }
        }
    }        
    /*else if (enpassant)
    	return 1;*/
    return 0;								//All other moves are INVALID
}

int cpawn_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if (newposm==' ')							//new position is empty
    {
        if (newv==currv+1)						//moves 1 step forward
        {
            if(newh==currh)						//but in same column
            {
                if (newv==7)
                    cpromote_min(currv,currh,arr);
                return 1;						//then its VALID
            }
        }
        else if (currv==1&&newv==3)				//first move can be of 2 steps
        {
            if (newh==currh)					//but still in same column
            {
            	if(arr[2][currh]==' ')		//path must be empty
                	return 1;					//then its VALID
            }
    	}
    }
    else if (newposm<='Z'&&newposm>='A')			//or it can kill an opponent's piece
    {
        if (newv==currv+1)						//by moving 1 unit forward
        {
            if (newh==currh-1||newh==currh+1)	//but must attack digonally
            {
                if (newv==7)
                    cpromote_min(currv,currh,arr);
                return 1;						//then its VALID
            }
        }
    }
    /*else if (enpassant)
    	return 1;*/
    return 0;								//All other moves are INVALID
}

int rook_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if (newv==currv&&(newposm==' '||(newposm<='z'&&newposm>='a')))  //Rook moves horizontally, and new position is empty or occupied by enemy
    {
        if (newh>currh)							//moves to right
        {
            int i;
            for (i=currh+1;i<newh;i++)			//all intermediate places are empty??
                if (arr[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newh<currh)					//moves to left
        {
            int i;
            for (i=currh-1;i>newh;i--)			//all intermediate places are empty??
                if (arr[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        if (currv==7&&currh==0)                 //no castling if true
            leftrook_moved_min=1;
        else if (currv==7&&currh==7)
            rightrook_moved_min=1;
        return 1;								//All others are valid moves
    }
    else if (newh==currh&&(newposm==' '||(newposm<='z'&&newposm>='a'))) //Rook moves vertically, new position is empty or occupied by enemy
    {
        if (newv>currv)							//moves downward
        {
            int i;
            for (i=currv+1;i<newv;i++)			//all intermediate places are empty??
                if (arr[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newv<currv)					//moves upward
        {
            int i;
            for (i=currv-1;i>newv;i--)			//all intermediate places are empty??
                if (arr[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        if (currv==7&&currh==0)                 //no castling if true
            leftrook_moved_min=1;
        else if (currv==7&&currh==7)
            rightrook_moved_min=1;
        return 1;								//All other moves are valid
    }
    return 0;
}

int crook_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if (newv==currv&&(newposm==' '||(newposm<='Z'&&newposm>='A')))  //Rook moves horizontally, and new position is empty or occupied by enemy
    {
        if (newh>currh)							//moves to right
        {
            int i;
            for (i=currh+1;i<newh;i++)			//all intermediate places are empty??
                if (arr[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newh<currh)					//moves to left
        {
            int i;
            for (i=currh-1;i>newh;i--)			//all intermediate places are empty??
                if (arr[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case
        if (currv==0&&currh==0)
            leftcrook_moved_min=1;
        else if (currv==0&&currh==7)
            rightcrook_moved_min=1;
        return 1;								//All others are valid moves
    }
    else if (newh==currh&&(newposm==' '||(newposm<='Z'&&newposm>='A'))) //Rook moves vertically, new position is empty or occupied by enemy
    {
        if (newv>currv)							//moves downward
        {
            int i;
            for (i=currv+1;i<newv;i++)			//all intermediate places are empty??
                if (arr[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newv<currv)					//moves upward
        {
            int i;
            for (i=currv-1;i>newv;i--)			//all intermediate places are empty??
                if (arr[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        return 1;								//All other moves are valid
    }
    return 0;
}

int knight_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if ((newv==currv+2||newv==currv-2)&&(newh==currh+1||newh==currh-1))			//2 steps vertically, 1 step horizontally
        {if (newposm==' '||(newposm<='z'&&newposm>='a'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    else if ((newv==currv+1||newv==currv-1)&&(newh==currh+2||newh==currh-2))	//1 step vertically, 2 steps horizontally
        {if (newposm==' '||(newposm<='z'&&newposm>='a'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    return 0;																//else INVALID
}

int cknight_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if ((newv==currv+2||newv==currv-2)&&(newh==currh+1||newh==currh-1))			//2 steps vertically, 1 step horizontally
        {if (newposm==' '||(newposm<='Z'&&newposm>='A'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    else if ((newv==currv+1||newv==currv-1)&&(newh==currh+2||newh==currh-2))	//1 step vertically, 2 steps horizontally
        {if (newposm==' '||(newposm<='Z'&&newposm>='A'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    return 0;																//else INVALID
}

int bishop_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh)))&&(newposm==' '||(newposm<='z'&&newposm>='a')))	//move along diagonal
    {																						//and new position is empty or enemy's
        if (newv>currv)								//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (arr[currv+i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (arr[currv+i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (arr[currv-i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (arr[currv-i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        return 1;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int cbishop_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh)))&&(newposm==' '||(newposm<='Z'&&newposm>='A')))	//move along diagonal
    {																						//and new position is empty or enemy's
        if (newv>currv)								//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (arr[currv+i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (arr[currv+i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (arr[currv-i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (arr[currv-i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        return 1;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int queen_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    return (rook_min(currv,currh,newv,newh,arr)||bishop_min(currv,currh,newv,newh,arr));	//moves either like a rook or bishop
}

int cqueen_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    return (crook_min(currv,currh,newv,newh,arr)||cbishop_min(currv,currh,newv,newh,arr));	//moves either like a rook or bishop
}

int king_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if(((newv==currv+1)||(newv==currv)||(newv==currv-1))&&((newh==currh-1)||(newh==currh)||(newh==currh-1)))	//Moves 1 step in any dirn.
	{
		if(eyesight_min(newv,newh,arr)==0)							//no piece should be attacking newposition directly
		{
			if(newposm==' '||(newposm<='z'&&newposm>='a'))		//new position must be empty or an enemy piece present there
			{
			    king_moved_min=1;                               //king has moved, no castling now!!!
			    return 1;                                   //VALID move
			}
		}
		else return 0;										//if piece attacking INVALID move
	}
    /*Castling Condition : From (7,4) to either (7,6) or (7,2)
                            No piece must be having direct attack possible for any square through which king moves
                            king and rook must not have moved.*/

	else if ((newv==7)&&(currv==7)&&(((newh==6)&&(eyesight_min(7,5,arr)==0)&&(arr[7][7]=='R')&&(rightrook_moved_min==0))||
                                  ((newh==2)&&(eyesight_min(7,3,arr)==0)&&(arr[7][0]=='R')&&(leftrook_moved_min==0)))&&(currh==4)&&(arr[7][4]=='K'))
    {
        if ((king_moved_min!=1)&&(eyesight_min(currv,currh,arr)==0)&&(eyesight_min(newv,newh,arr)==0))
            return 1;
    }
    return 0;                                          //No other valid move for king
}

int cking_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if(((newv==currv+1)||(newv==currv)||(newv==currv-1))&&((newh==currh-1)||(newh==currh)||(newh==currh-1)))	//Moves 1 step in any dirn.
	{
		if(ceyesight_min(newv,newh,arr)==0)							//no piece should be attacking newposition directly
		{
			if(newposm==' '||(newposm<='Z'&&newposm>='A'))		//new position must be empty or an enemy piece present there
			{
			    cking_moved_min=1;                               //king has moved, no castling now!!!
			    return 1;                                   //VALID move
			}
		}
		else return 0;										//if piece attacking INVALID move
	}
    /*Castling Condition : From (7,4) to either (7,6) or (7,2)
                            No piece must be having direct attack possible for any square through which king moves
                            king and rook must not have moved.*/

	else if ((newv==0)&&(currv==0)&&(((newh==6)&&(ceyesight_min(0,5,arr)==0)&&(arr[0][7]=='r')&&(rightcrook_moved_min==0))||
                                  ((newh==2)&&(ceyesight_min(0,3,arr)==0)&&(arr[0][0]=='r')&&(leftcrook_moved_min==0)))&&(currh==4)&&(arr[0][4]=='k'))
    {
        if ((cking_moved_min!=1)&&(ceyesight_min(currv,currh,arr)==0)&&(ceyesight_min(newv,newh,arr)==0))
            return 1;
    }
    return 0;                                          //No other valid move for king
}

int valid_move_min(int currv,int currh,int newv,int newh,char arr[][8])
{
    if (currentm=='P')                                //Pawn at current position
    	return pawn_min(currv,currh,newv,newh,arr);

    else if (currentm=='R')                                //Rook at current position
        return rook_min(currv,currh,newv,newh,arr);

    else if (currentm=='N')                                //Knight at current position
    	return knight_min(currv,currh,newv,newh,arr);

    else if (currentm=='B')								//Bishop at current position
    	return bishop_min(currv,currh,newv,newh,arr);

    else if (currentm=='Q')								//Queen at current position
    	return queen_min(currv,currh,newv,newh,arr);

    else if (currentm=='K')								//King at current position
    	return king_min(currv,currh,newv,newh,arr);

    else if (currentm=='p')                               //Computer's pawn at current position
        return cpawn_min(currv,currh,newv,newh,arr);

    else if (currentm=='r')                               //Computer's rook at current position
        return crook_min(currv,currh,newv,newh,arr);

    else if (currentm=='n')                               //Computer's knight at current position
        return cknight_min(currv,currh,newv,newh,arr);

    else if (currentm=='b')                               //Computer's bishop at current position
        return cbishop_min(currv,currh,newv,newh,arr);

    else if (currentm=='q')                               //Computer's queen at current position
        return cqueen_min(currv,currh,newv,newh,arr);

    else if (currentm=='k')                               //Computer's king at current position
        return cking_min(currv,currh,newv,newh,arr);

    else if (currentm==' ')                               //No piece at current position
        return 0;
}








void promote(int currv,int currh)
{   char c;
    int k;
    while (k=0)
    {
        printf("\nWhat do you want your pawn to get promoted to: Q/R/B/N :");
        scanf("%c",&c);
        if(c=='Q'||c=='R'||c=='B'||c=='N')
        {
            board[currv][currh]=c;
            k=1;
        }
        else printf("\nIllegal input");
    }
}

void cpromote(int currv,int currh)
{
    board[currv][currh]='q';
}

int pawn(int currv,int currh,int newv,int newh)					//pawn at current position
{
    if (newpos==' ')							//new position is empty
    {
        if (newv==currv-1)						//moves 1 step forward
        {
            if(newh==currh)						//but in same column
            {
                if (newv==0)
                    promote(currv,currh);
                return 1;						//then its VALID
            }
        }
        else if (currv==6&&newv==4)				//first move can be of 2 steps
        {
            if (newh==currh)					//but still in same column
            {
            	if(board[5][currh]==' ')		//path must be empty
                	return 1;					//then its VALID
            }
    	}
    }
    else if (newpos<='z'&&newpos>='a')			//or it can kill an opponent's piece
    {
        if (newv==currv-1)						//by moving 1 unit forward
        {
            if (newh==currh-1||newh==currh+1)	//but must attack digonally
            {
                if (newv==0)
                    promote(currv,currh);
                return 1;						//then its VALID
            }
        }
    }
    /*else if (enpassant)
    	return 1;*/
    return 0;								//All other moves are INVALID
}

int cpawn(int currv,int currh,int newv,int newh)
{
    if (newpos==' ')							//new position is empty
    {
        if (newv==currv+1)						//moves 1 step forward
        {
            if(newh==currh)						//but in same column
            {
                if (newv==7)
                	cpromote(currv,currh);
                return 1;						//then its VALID
        	}
        }
        else if (currv==1&&newv==3)				//first move can be of 2 steps
        {
            if (newh==currh)					//but still in same column
            {
            	if(board[2][currh]==' ')		//path must be empty
                	return 1;					//then its VALID
            }
    	}
    }
    else if (newpos<='Z'&&newpos>='A')			//or it can kill an opponent's piece
    {
        if (newv==currv+1)						//by moving 1 unit forward
        {
            if (newh==currh-1||newh==currh+1)	//but must attack digonally
            {
            	if (newv==7)
            		cpromote(currv,currh);
                return 1;						//then its VALID
    		}
    	}
    }
    /*else if (enpassant)
    	return 1;*/
    return 0;								//All other moves are INVALID
}

int rook(int currv,int currh,int newv,int newh)					//Rook at current position
{
	if (newv==currv&&(newpos==' '||(newpos<='z'&&newpos>='a')))  //Rook moves horizontally, and new position is empty or occupied by enemy
    {
        if (newh>currh)							//moves to right
        {
            int i;
            for (i=currh+1;i<newh;i++)			//all intermediate places are empty??
                if (board[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newh<currh)					//moves to left
        {
            int i;
            for (i=currh-1;i>newh;i--)			//all intermediate places are empty??
                if (board[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        if (currv==7&&currh==0)                 //no castling if true
            leftrook_moved=1;
        else if (currv==7&&currh==7)
            rightrook_moved=1;
        return 1;								//All others are valid moves
    }
    else if (newh==currh&&(newpos==' '||(newpos<='z'&&newpos>='a'))) //Rook moves vertically, new position is empty or occupied by enemy
    {
        if (newv>currv)							//moves downward
        {
            int i;
            for (i=currv+1;i<newv;i++)			//all intermediate places are empty??
                if (board[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newv<currv)					//moves upward
        {
            int i;
            for (i=currv-1;i>newv;i--)			//all intermediate places are empty??
                if (board[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        if (currv==7&&currh==0)                 //no castling if true
            leftrook_moved=1;
        else if (currv==7&&currh==7)
            rightrook_moved=1;
        return 1;								//All other moves are valid
    }
    return 0;
}

int crook(int currv,int currh,int newv,int newh)
{
    if (newv==currv&&(newpos==' '||(newpos<='Z'&&newpos>='A')))  //Rook moves horizontally, and new position is empty or occupied by enemy
    {
        if (newh>currh)							//moves to right
        {
            int i;
            for (i=currh+1;i<newh;i++)			//all intermediate places are empty??
                if (board[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newh<currh)					//moves to left
        {
            int i;
            for (i=currh-1;i>newh;i--)			//all intermediate places are empty??
                if (board[currv][i]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case
        if (currv==0&&currh==0)
            leftcrook_moved=1;
        else if (currv==0&&currh==7)
            rightcrook_moved=1;
        return 1;								//All others are valid moves
    }
    else if (newh==currh&&(newpos==' '||(newpos<='Z'&&newpos>='A'))) //Rook moves vertically, new position is empty or occupied by enemy
    {
        if (newv>currv)							//moves downward
        {
            int i;
            for (i=currv+1;i<newv;i++)			//all intermediate places are empty??
                if (board[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else if (newv<currv)					//moves upward
        {
            int i;
            for (i=currv-1;i>newv;i--)			//all intermediate places are empty??
                if (board[i][currh]!=' ')		//if not
                    return 0;					//INVALID move
        }
        else return 0;							//just in case :P
        return 1;								//All other moves are valid
    }
    return 0;
}

int knight(int currv,int currh,int newv,int newh)												//Knight at current position
{
    if ((newv==currv+2||newv==currv-2)&&(newh==currh+1||newh==currh-1))			//2 steps vertically, 1 step horizontally
        {if (newpos==' '||(newpos<='z'&&newpos>='a'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    else if ((newv==currv+1||newv==currv-1)&&(newh==currh+2||newh==currh-2))	//1 step vertically, 2 steps horizontally
        {if (newpos==' '||(newpos<='z'&&newpos>='a'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    return 0;																//else INVALID
}

int cknight(int currv,int currh,int newv,int newh)
{
    if ((newv==currv+2||newv==currv-2)&&(newh==currh+1||newh==currh-1))			//2 steps vertically, 1 step horizontally
       {if (newpos==' '||(newpos<='Z'&&newpos>='A'))							//new position empty or occ. by enemy
           {return 1;}}															//VALID
    else if ((newv==currv+1||newv==currv-1)&&(newh==currh+2||newh==currh-2))	//1 step vertically, 2 steps horizontally
        {if (newpos==' '||(newpos<='Z'&&newpos>='A'))							//new position empty or occ. by enemy
            {return 1;}}															//VALID
    return 0;																//else INVALID
}

int bishop(int currv,int currh,int newv,int newh)										//Bishop at current position
{
    if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh)))&&(newpos==' '||(newpos<='z'&&newpos>='a')))	//move along diagonal
    {																						//and new position is empty or enemy's
        if (newv>currv)								//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (board[currv+i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (board[currv+i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (board[currv-i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (board[currv-i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        return 1;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int cbishop(int currv,int currh,int newv,int newh)
{
    if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh)))&&(newpos==' '||(newpos<='Z'&&newpos>='A')))	//move along diagonal
    {																						//and new position is empty or enemy's
        if (newv>currv)								//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (board[currv+i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(newv-currv);i++)			//all intermediate positions are empty
                    if (board[currv+i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (board[currv-i][currh+i]!=' ')	//if not
                        return 0;						//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=1;i<(currv-newv);i++)			//all intermediate positions are empty
                    if (board[currv-i][currh-i]!=' ')	//if not
                        return 0;						//INVALID move
            }
        }
        return 1;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int queen(int currv,int currh,int newv,int newh)						//Queen at current position
{
	return (rook(currv,currh,newv,newh)||bishop(currv,currh,newv,newh));	//moves either like a rook or bishop
}

int cqueen(int currv,int currh,int newv,int newh)
{
    return (crook(currv,currh,newv,newh)||cbishop(currv,currh,newv,newh));	//moves either like a rook or bishop
}

int king(int currv,int currh,int newv,int newh)							//King at current position
{
	if(((newv==currv+1)||(newv==currv)||(newv==currv-1))&&((newh==currh-1)||(newh==currh)||(newh==currh-1)))	//Moves 1 step in any dirn.
	{
		if(eyesight(newv,newh)==0)							//no piece should be attacking newposition directly
		{
			if(newpos==' '||(newpos<='z'&&newpos>='a'))		//new position must be empty or an enemy piece present there
			{
			    king_moved=1;                               //king has moved, no castling now!!!
			    return 1;                                   //VALID move
			}
		}
		else return 0;										//if piece attacking INVALID move
	}
	
    /*Castling Condition : From (7,4) to either (7,6) or (7,2)
                            No piece must be having direct attack possible for any square through which king moves
                            king and rook must not have moved.*/
    else if ((newv==7)&&(currv==7)&&(currh==4)&&(king_moved!=1)&&(eyesight(currv,currh)==0)&&(eyesight(newv,newh)==0)&&(board[7][4]=='K'))
    {
    	if ((newh==6)&&(eyesight(7,5)==0)&&(board[7][7]=='R')&&(rightrook_moved==0))
    	{
    		board[7][5]='R';
    		board[7][7]=' ';
    		return 1;
    	}
    	else if ((newh==2)&&(eyesight(7,3)==0)&&(board[7][0]=='R')&&(leftrook_moved==0))
    	{
    		board[7][3]='R';
    		board[7][0]=' ';
    		return 1;
    	}
    }
    return 0;                                          //No other valid move for king
}

int cking(int currv,int currh,int newv,int newh)
{
    if(((newv==currv+1)||(newv==currv)||(newv==currv-1))&&((newh==currh-1)||(newh==currh)||(newh==currh-1)))	//Moves 1 step in any dirn.
	{
		if(ceyesight(newv,newh)==0)							//no piece should be attacking newposition directly
		{
			if(newpos==' '||(newpos<='Z'&&newpos>='A'))		//new position must be empty or an enemy piece present there
			{
			    cking_moved=1;                               //king has moved, no castling now!!!
			    return 1;                                   //VALID move
			}
		}
		else return 0;										//if piece attacking INVALID move
	}
	
    /*Castling Condition : From (7,4) to either (7,6) or (7,2)
                            No piece must be having direct attack possible for any square through which king moves
                            king and rook must not have moved.*/

    else if ((newv==0)&&(currv==0)&&(currh==4)&&(cking_moved!=1)&&(ceyesight(currv,currh)==0)&&(ceyesight(newv,newh)==0)&&(board[0][4]=='K'))
    {
    	if ((newh==6)&&(ceyesight(0,5)==0)&&(board[0][7]=='r')&&(rightcrook_moved==0))
    	{
    		board[7][5]='r';
    		board[7][7]=' ';
    		return 1;
    	}
    	else if ((newh==2)&&(ceyesight(0,3)==0)&&(board[0][0]=='r')&&(leftcrook_moved==0))
    	{
    		board[7][3]='r';
    		board[7][0]=' ';
    		return 1;
    	}
    }
    return 0;                                          //No other valid move for king
}

int valid_move(int currv,int currh,int newv,int newh)
{
    if (current=='P')                                //Pawn at current position
    	return pawn(currv,currh,newv,newh);

    if (current=='R')                                //Rook at current position
        return rook(currv,currh,newv,newh);

    if (current=='N')                                //Knight at current position
    	return knight(currv,currh,newv,newh);

    if (current=='B')								//Bishop at current position
    	return bishop(currv,currh,newv,newh);

    if (current=='Q')								//Queen at current position
    	return queen(currv,currh,newv,newh);

    if (current=='K')								//King at current position
    	return king(currv,currh,newv,newh);

    if (current=='p')                               //Computer's pawn at current position
        return cpawn(currv,currh,newv,newh);

    if (current=='r')                               //Computer's rook at current position
        return crook(currv,currh,newv,newh);

    if (current=='n')                               //Computer's knight at current position
        return cknight(currv,currh,newv,newh);

    if (current=='b')                               //Computer's bishop at current position
        return cbishop(currv,currh,newv,newh);

    if (current=='q')                               //Computer's queen at current position
        return cqueen(currv,currh,newv,newh);

    if (current=='k')                               //Computer's king at current position
        return cking(currv,currh,newv,newh);

    if (current==' ')                               //No piece at current position
        return 0;
}





int printbrd()
{
    int i,j,z;
    for(z=0;z<50;z++)                   //In place of clear screen
        printf("\n");
	printf("  ");
    for(i=0;i<8;i++)
		printf("  %d ",i+1);            // Top column numbers
	printf("\n  _");
	for(i=0;i<8;i++)
		printf("____");                 // First horizontal line
    printf("\n");
    for (i=0;i<8;i++)
    {
        printf("%c |",i+65);              // Left side Characters
        for (j=0;j<8;j++)
            printf(" %c |",board[i][j]);   //print board elements
    	printf("\n  |");
        for (j=0;j<8;j++)
            printf("___|");
	printf("\n");
    }
    FILE *savegame;
    savegame=fopen("SaveGame","w");
    for (i=0;i<8;i++)
    	for(j=0;j<8;j++)
    	{
    		fprintf(savegame,"%c",board[i][j]);
    	}
    fclose(savegame);
    return 0;
}

int makemove(int currv,int currh,int newv,int newh)
{
	char curr,newm;
	curr=board[currv][currh];
	newm=board[newv][newh];
	newm=curr;
	curr=' ';
	board[newv][newh]=newm;
	board[currv][currh]=curr;
	printbrd();
	return 0;
}







int eyesight(int newv,int newh)                                     //checks if some computer's piece on board[][] has a sight on newv,newh
{
    int currv,currh;                                                //vary to each square on board
    for (currv=0;currv<8;currv++)
        for (currh=0;currh<8;currh++)
            if(board[currv][currh]<='z'&&board[currv][currh]>='a')    //if (currv,currh) has any piece of computer
                if (valid_move(currv,currh,newv,newh))          //check if its move to (newv,newh) is possible or not
                    return 1;                                       //if yes, then returns 0
    return 0;                                                       //else returns 1
}

int ceyesight(int newv,int newh)                                    //checks if some user's piece on board[][] has a sight on newv,newh
{
    int currv,currh;                                                //vary to each square on board
    for (currv=0;currv<8;currv++)
        for (currh=0;currh<8;currh++)
            if(board[currv][currh]<='Z'&&board[currv][currh]>='A')
                if (valid_move(currv,currh,newv,newh))
                    return 1;
    return 0;
}

int eyesight_min(int newv,int newh,char arr[][8])
{
    int currv,currh;                                                //vary to each square on board
    for (currv=0;currv<8;currv++)
        for (currh=0;currh<8;currh++)
            if(arr[currv][currh]<='z'&&arr[currv][currh]>='a')    //if (currv,currh) has any piece of computer
                if (valid_move_min(currv,currh,newv,newh,arr))          //check if its move to (newv,newh) is possible or not
                    return 1;                                       //if yes, then returns 0
    return 0;                                                       //else returns 1
}

int ceyesight_min(int newv,int newh,char arr[][8])
{
    int currv,currh;                                                //vary to each square on board
    for (currv=0;currv<8;currv++)
        for (currh=0;currh<8;currh++)
            if(arr[currv][currh]<='Z'&&arr[currv][currh]>='A')
                if (valid_move_min(currv,currh,newv,newh,arr))
                    return 1;
    return 0;
}

void copy_array(int currv,int currh,int newv,int newh,char arr[][8],char narr[][8])      //copies one array to another, then makes a move from current to newpos in the copy
{
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
        {
            narr[i][j]=arr[i][j];
        }
    char *curr,*newm;
	curr=&narr[currv][currh];
	newm=&narr[newv][newh];
	*newm=*curr;
	*curr=' ';
}




int checkby_cpawn(currv,currh,newv,newh)
{
	if(ceyesight(currv,currh))
		return 1;
	else return 0;
}

int checkby_pawn(currv,currh,newv,newh)
{
	if(eyesight(currv,currh))
		return 1;
	else return 0;
}

int checkby_cknight(currv,currh,newv,newh)
{
	if (ceyesight(currv,currh))
		return 1;
	else return 0;
}

int checkby_knight(currv,currh,newv,newh)
{
	if (eyesight(currv,currh))
		return 1;
	else return 0;
}

int checkby_crook(currv,currh,newv,newh)
{
	int i;
	if (currv==newv)						//rook in same horizontal row
	{
		if (currh>newh)						//if rook towards right
		{
			for(i=newh+1;i<=currh;i++)
			{
				if (ceyesight(i,currv))
					return 1;
			}
		}
		else if (currh<newh)				//if rook moves towards left
		{
			for(i=currh;i<newh;i++)
			{
				if(ceyesight(i,currv))
					return 1;
			}
		}
	}
	else if (currh==newh)					//if rook is in same vertical column
	{
		if (currv>newv)
		{
			for(i=newv+1;i<=currv;i++)
			{
				if(ceyesight(i,currh))
					return 1;
			}
		}
		else if (currv<newv)
		{
			for(i=currv;i<newv;i++)
			{
				if(ceyesight(i,currh))
					return 1;
			}
		}
	}
	return 0;
}

int checkby_rook(currv,currh,newv,newh)
{
	int i;
	if (currv==newv)						//rook in same horizontal row
	{
		if (currh>newh)						//if rook towards right
		{
			for(i=newh+1;i<=currh;i++)
			{
				if (eyesight(i,currv))
					return 1;
			}
		}
		else if (currh<newh)				//if rook moves towards left
		{
			for(i=currh;i<newh;i++)
			{
				if(eyesight(i,currv))
					return 1;
			}
		}
	}
	else if (currh==newh)					//if rook is in same vertical column
	{
		if (currv>newv)
		{
			for(i=newv+1;i<=currv;i++)
			{
				if(eyesight(i,currh))
					return 1;
			}
		}
		else if (currv<newv)
		{
			for(i=currv;i<newv;i++)
			{
				if(eyesight(i,currh))
					return 1;
			}
		}
	}
	return 0;
}

int checkby_cbishop(currv,currh,newv,newh)
{					/*IGNORE COMMENTS IN THIS FUNCTION. COPY PASTED FROM ABOVE*/
	if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh))))						//move along diagonal
    {																						
        if (newv>currv)									//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=0;i<(newv-currv);i++)				//all intermediate positions are empty
                    if (ceyesight(currv+i,currh+i))	//if not
                        return 1;							//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=0;i<(newv-currv);i++)				//all intermediate positions are empty
                    if (ceyesight(currv+i,currh-i))	//if not
                        return 1;							//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=0;i<(currv-newv);i++)				//all intermediate positions are empty
                    if (ceyesight(currv-i,currh+i))	//if not
                        return 1;							//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=0;i<(currv-newv);i++)				//all intermediate positions are empty
                    if (ceyesight(currv-i,currh-i))	//if not
                        return 1;							//INVALID move
            }
        }
        return 0;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int checkby_bishop(currv,currh,newv,newh)
{					/*IGNORE COMMENTS IN THIS FUNCTION. COPY PASTED FROM ABOVE*/
	if ((((newv-currv)==(newh-currh))||((newv-currv)==(currh-newh))))						//move along diagonal
    {																						
        if (newv>currv)									//moves downward
        {
            if (newh>currh)								//and right
            {
                int i;
                for (i=0;i<(newv-currv);i++)				//all intermediate positions are empty
                    if (eyesight(currv+i,currh+i))	//if not
                        return 1;							//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=0;i<(newv-currv);i++)				//all intermediate positions are empty
                    if (eyesight(currv+i,currh-i))	//if not
                        return 1;							//INVALID move
            }
        }
        else if (newv<currv)						//moves upward
        {
        	if (newh>currh)								//and right
            {
                int i;
                for (i=0;i<(currv-newv);i++)				//all intermediate positions are empty
                    if (eyesight(currv-i,currh+i))	//if not
                        return 1;							//INVALID move
            }
            else if (newh<currh)						//and left
            {
                int i;
                for (i=0;i<(currv-newv);i++)				//all intermediate positions are empty
                    if (eyesight(currv-i,currh-i))	//if not
                        return 1;							//INVALID move
            }
        }
        return 0;										//All invalid cases covered above, given move is along a diagonal
    }
    return 0;										//INVALID if move not along a diagonal path
}

int checkby_cqueen(currv,currh,newv,newh)
{
	return (checkby_crook(currv,currh,newv,newh)||checkby_cbishop(currv,currh,newv,newh));
}

int checkby_queen(currv,currh,newv,newh)
{
	return (checkby_rook(currv,currh,newv,newh)||checkby_bishop(currv,currh,newv,newh));
}

int user_save_poss(newv,newh)
{
	int currv,currh;                                                //vary to each square on board
    for (currv=0;currv<8;currv++)
        for (currh=0;currh<8;currh++)
        {
            if(board[currv][currh]<='z'&&board[currv][currh]>='a')    //if (currv,currh) has any piece of computer
            {
                if (valid_move(currv,currh,newv,newh))          //check if its move to (newv,newh) is possible or not
				{
					if(board[currv][currh]=='p')
						return checkby_cpawn(currv,currh,newv,newh);
					else if (board[currv][currh]=='n')
						return checkby_cknight(currv,currh,newv,newh);
					else if (board[currv][currh]=='r')			//if rook is attacking, try blocking its path or kill it
						return checkby_crook(currv,currh,newv,newh);
					else if(board[currv][currh]=='b')
						return checkby_cbishop(currv,currh,newv,newh);
					else if (board[currv][currh]=='q')
						return checkby_cqueen(currv,currh,newv,newh);
					else return 1;
				}
			}
		}
	return 1;
}

int comp_save_poss(newv,newh)
{
	int currv,currh;
	for(currv=0;currv<8;currv++)
		for (currh=0;currh<8;currh++)
		{
			if (board[currv][currh]<='Z'&&board[currv][currh]>='A')
			{
				if (valid_move(currv,currh,newv,newh))
				{
					if (board[currv][currh]=='P')
						return checkby_pawn(currv,currh,newv,newh);
					else if (board[currv][currh]=='N')
						return checkby_knight(currv,currh,newv,newh);
					else if (board[currv][currh]=='R')
						return checkby_rook(currv,currh,newv,newh);
					else if (board[currv][currh]=='B')
						return checkby_bishop(currv,currh,newv,newh);
					else if (board[currv][currh]=='Q')
						return checkby_queen(currv,currh,newv,newh);
					else return 1;
				}
			}
		}
	return 1;
}	
			
							
							
							
							
							

int mate(char arr[][8])         //Returns 1 if its mate for the user
{
    int i,j,d=2,k=0;
    for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
            if (arr[i][j]=='K')
            {	
            	k=1;
                break;
            } 
        if (k==1)
            break;
    }
    if (eyesight(i,j))
    {
    	d=0;
        if(i>0)
        {
            if (j>0&&(valid_move(i,j,i-1,j-1)))
                d=1;
            if ((valid_move(i,j,i-1,j)))
                d=1;
            if (j<7&&(valid_move(i,j,i-1,j+1)))
                d=1;
        }
        if (i<7)
        {
            if (j>0&&(valid_move(i,j,i+1,j-1)))
                d=1;
            if ((valid_move(i,j,i+1,j)))
                d=1;
            if (j<7&&(valid_move(i,j,i+1,j+1)))
                d=1;
        }
        if (j>0&&(valid_move(i,j,i,j-1)))
            d=1;
        if (j<7&&(valid_move(i,j,i,j+1)))
            d=1;
        if (user_save_poss(i,j))
        	d=1;
    }
    
    if (d!=0)
        return 0;
    else return 1;
}

int cmate(char arr[][8])
{
    int i,j,d=2,k=0;
    for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
            if (arr[i][j]=='k')
            {	
            	k=1;
                break;
            } 
        if (k==1)
            break;
    }
    if (ceyesight(i,j))
    {
    	d=0;
        if(i>0)
        {
            if (j>0&&(valid_move(i,j,i-1,j-1)))
                d=1;
            if ((valid_move(i,j,i-1,j)))
                d=1;
            if (j<7&&(valid_move(i,j,i-1,j+1)))
                d=1;
        }
        if (i<7)
        {
            if (j>0&&(valid_move(i,j,i+1,j-1)))
                d=1;
            if ((valid_move(i,j,i+1,j)))
                d=1;
            if (j<7&&(valid_move(i,j,i+1,j+1)))
                d=1;
        }
        if (j>0&&(valid_move(i,j,i,j-1)))
            d=1;
        if (j<7&&(valid_move(i,j,i,j+1)))
            d=1;
        if (comp_save_poss(i,j))
        	d=1;
    }
    if (d!=0)
        return 0;
    else return 1;
}




int no_opp()
{
	int i,j;
	for (i=0;i<4;i++)
		for(j=0;j<8;j++)
		{
			if (board[i][j]<='Z'&&board[i][j]>='A')
			{
				return 0;
			}
		}
	return 1;
}

void castle()
{
	if (board[2][5]<'a'&&board[0][6]=='n')
	{
		board[2][5]='n';
		board[0][6]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: A 7 C 6\n");
        fclose(move);
		printf("Moved A 7 C 6");
		capital();
	}
	else if (board[2][6]<'a'&&board[1][6]=='p')
	{
		board[2][6]='p';
		board[1][6]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: B 7 C 7\n");
        fclose(move);
		printf("Moved B 7 C 7");
		capital();
	}
	else if (board[3][7]<'a'&&board[1][7]=='p')
	{
		board[3][7]='p';
		board[1][7]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: B 8 D 8\n");
        fclose(move);
		printf("Moved B 8 D 8");
		capital();
	}
	else if (board[2][7]<'a'&&board[0][5]=='b')
	{
		board[2][7]='b';
		board[0][5]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: A 6 C 8\n");
        fclose(move);
		printf("Moved A 6 C 8");
		capital();
	}
	else if (board[0][6]<'a'&&board[0][4]=='k'&&board[0][5]<'a'&&board[0][7]=='r')
	{
		board[0][6]='k';
		board[0][5]='r';
		board[0][7]=' ';
		board[0][4]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: A 5 A 7\n");
        fclose(move);
		printf("Moved A 5 A 7");
		capital();
	}
	else if (board[2][2]<'a'&&board[0][1]=='n')
	{
		board[2][2]='n';
		board[0][1]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: A 2 C 3\n");
        fclose(move);
		printf("Moved A 2 C 3");
		capital();
	}
	else if (board[2][1]<'a'&&board[1][1]=='p')
	{
		board[2][1]='p';
		board[1][1]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: B 2 C 2\n");
        fclose(move);
		printf("Moved B 2 C 2");
		capital();
	}
	else if (board[3][0]<'a'&&board[1][0]=='p')
	{
		board[3][0]='p';
		board[1][0]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: B 1 D 1\n");
        fclose(move);
		printf("Moved B 1 D 1");
		capital();
	}
	else if (board[2][0]<'a'&&board[0][2]=='b')
	{
		board[2][0]='b';
		board[0][2]=' ';
		printbrd();
		FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: A 3 C 1\n");
        fclose(move);
		printf("\nMoved A 3 C 1");
		capital();
	}
	printbrd();
	capital();
}




float minimax(struct node *parent,int depth,int player)
{
    if (depth==0||value_board(parent->copybrd)>200)
        return value_board(parent->copybrd);

    else if (player == 1)               //computer's move
    {
        float best_value;
        int mycurrv,mycurrh,mynewv,mynewh,debug=56;
        best_value=-99999;
        for (mycurrv=0;mycurrv<8;mycurrv++)
            for(mycurrh=0;mycurrh<8;mycurrh++)
                if (parent->copybrd[mycurrv][mycurrh]<='z'&&parent->copybrd[mycurrv][mycurrh]>='a')
                    for (mynewv=0;mynewv<8;mynewv++)
                        for(mynewh=0;mynewh<8;mynewh++)
                            if(debug=valid_move_min(mycurrv,mycurrh,mynewv,mynewh,parent->copybrd))
                            {
                                struct node *temp;
                                temp=malloc(sizeof(struct node));                             //WHAT TO DO IF MEMORY ALLOCATION FAILS??
                                copy_array(mycurrv,mycurrh,mynewv,mynewh,parent->copybrd,temp->copybrd);
                                temp->child=0;
                                parent->child=temp;

                                float value=value_board(parent->copybrd)+minimax(parent->child,depth-1,0);
                                 free(parent->child);                                            // Is this right?
                                if (value>best_value)
                                {

                                    cnewv=mynewv;
                                    cnewh=mynewh;
                                    ccurrv=mycurrv;
                                    ccurrh=mycurrh;
                                    best_value=value;
                                }
                            }
        return best_value;
    }

    else if (player == 0)
    {
        float best_value;
        int mycurrv,mycurrh,mynewv,mynewh;
        best_value=99999;
        for (mycurrv=0;mycurrv<8;mycurrv++)
            for(mycurrh=0;mycurrh<8;mycurrh++)
                if (parent->copybrd[mycurrv][mycurrh]<='Z'&&parent->copybrd[mycurrv][mycurrh]>='A')
                    for (mynewv=0;mynewv<8;mynewv++)
                        for (mynewh=0;mynewh<8;mynewh++)
                            if(valid_move_min(mycurrv,mycurrh,mynewv,mynewh,parent->copybrd))
                            {
                                struct node *temp;
                                temp=malloc(sizeof(struct node));
                                copy_array(mycurrv,mycurrh,mynewv,mynewh,parent->copybrd,temp->copybrd);
                                temp->child=0;
                                parent->child=temp;

                                float value=minimax(parent->child,depth-1,1);
                                free(parent->child);
                                if (value<best_value)
                                    best_value=value;
                            }
        return best_value;
    }
}


int king_dead()
{
	int i,j,dead=1;
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if (board[i][j]=='K')
				dead=0;
		}
	if (dead==0)
		return 0;
	return 1;
}

int cking_dead()
{
	int i,j,dead=1;
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if (board[i][j]=='k')
				dead=0;
		}
	if (dead==0)
		return 0;
	return 1;
}
		
int capital()
{
    if((!(mate(board)))&&(!(king_dead())))
    {
        char currv=' ',newv=' ';
        int currh=0;
	int newh=0;
        printf("\n\nEnter your move: ");
        scanf("\n%c",&currv);
	scanf("%d ",&currh);
	scanf("%c",&newv);
	scanf("%d",&newh);
	FILE *move;
	move=fopen("Moves","a");
	fprintf(move,"%c %d %c %d\n",currv,currh,newv,newh);
	fclose(move);
	currv=currv-65;
        newv=newv-65;
 	currh=currh-1;
	newh=newh-1;
        currv=(int)currv;
        newv=(int)newv;
	//printf("Moving %d,%d to %d,%d",currv,currh,newv,newh);
        if (valid_move(currv,currh,newv,newh))
        {
            makemove(currv,currh,newv,newh);
            small();
        }
        else
        {
            printf("\nIllegal Move");
            capital();
        }
    }
    else
    {
        printf("\n\tCHECK MATE!!");
        return 0;
    }
}

int small()
{
	if (no_opp())
		castle();
    else if (!(cmate(board))&&(!(cking_dead())))
    {
        int i,j;
        struct node *temp;
        temp=malloc(sizeof(struct node));                   //WHAT TO DO IF MEMORY ALLOCATION FAILS??
        for (i=0;i<8;i++)
            for (j=0;j<8;j++)
            {
                temp->copybrd[i][j]=board[i][j];
            }
        temp->child=0;
        minimax(temp,depth,1);
        FILE *move;
        move=fopen("Moves","a");
        fprintf(move,"Comp: %c %d %c %d\n",ccurrv+65,ccurrh+1,cnewv+65,cnewh+1);
        fclose(move);
        makemove(ccurrv,ccurrh,cnewv,cnewh);
        printf("%c %d %c %d",ccurrv+65,ccurrh+1,cnewv+65,cnewh+1);
        capital();
    }
    else
    {
        printf("YOU WIN!! CONGRATULATIONS!!!");
        return 0;
    }
}

int menu()
{
	char opt;
	int i,j;
	printf("\nStart new game or load last game? (N/L) : ");
	scanf("%c",&opt);
	if (opt=='N')
	{
		printbrd();
		return 0;
	}
	else if (opt=='L')
	{
		FILE *save;
		save=fopen("SaveGame","r");
		for (i=0;i<8;i++)
			for (j=0;j<8;j++)
			{
				fscanf(save,"%c",&board[i][j]);
			}
		fclose(save);
		printbrd();
		capital();
	}
	else
	{
		printf("Invalid Choice");
		menu();
	}
}

int main()
{
    //printbrd();
    menu();
    FILE *move;
    move=fopen("Moves","w");
    fclose(move);
    printf("\nEnter level: ");
    scanf("%d",&depth);
    capital();
    return 0;
}

