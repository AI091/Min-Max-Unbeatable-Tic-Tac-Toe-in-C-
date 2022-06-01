  #include <iostream>
#include <algorithm>
using namespace std; 

#define INFINITY 100000

char board[3][3]={ {' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

void display(){
    for (int i=0; i<3; i++){
        for (int j=0 ; j<3 ; j++)
        cout<<"| "<<board[i][j]<<" |" ; 
    cout<<"\n--------------\n";

    }
}
int prompt_input(char player){
    cout<<"Player "<<player<<" turn." <<"Enter a number between 0 and 8"<<'\n'; 
    int pos;
    cin>> pos; 
    return pos; 
}

char check_win( ){

    //Check Diagonals 
    if (board[0][0]==board[1][1]&&board[1][1]==board[2][2]&&board[0][0]!=' ')
        return board[0][0] ; 
    if (board[2][0]==board[1][1]&&board[1][1]==board[0][2]&&board[2][0]!=' ')
        return board[2][0]; 
    //Check Rows
    for (int row=0; row<3; row++){
        if (board[row][0]==board[row][1]&&board[row][1]==board[row][2]&&board[row][0]!=' ')
            return board[row][0] ; 
        }
    //colums check 
    for (int col=0 ; col<3; col++){
    if (board[0][col]==board[1][col]&&board[1][col]==board[2][col]&&board[0][col]!=' ')
        return board[0][col] ; 
        }
    return 0;
}


 void place(char player,int pos){
     if (pos >8 || pos<0){
        cout<<"Invalid Input \n";
        return place(player, prompt_input(player));  
     }

     int row = pos/3 ; 
     int col= pos %3 ;

     if (board[row][col]==' '){
         board[row][col]=player ; 
     } 
     else {
        cout<<"Invalid Input \n";
        return place(player, prompt_input(player)); 
      }
 }
void multi_player(){
    char player='X'; 
    int turn=0; 
    do{

        place(player,prompt_input(player));
        display(); 
        if (check_win())  {cout<<"Player "<<player<<" won"<<"\nWanna play again?\n";
        return;
        }
        player= (player=='X')?'O' :'X';
        turn++; 
    }
    while(!check_win() && turn<9 );
    if (turn == 9){
        cout<<"The Game Ended in a Draw "<<'\n'; 
    }

}
struct Move{
    int row;
    int col; 
};

bool full(){
    for (int row=0 ; row<3; row++){
        for (int col=0 ; col<3 ; col++){
            if (board[row][col]==' ')
                return false ; 
        }
    }
        return true; 
}
int min_max( int depth, bool isMax,int max_depth){
    if (check_win() =='X') 
        return 100; 
    
    if (check_win() =='O') 
        return -100;
    
    if (full()){
        return 0 ; 
    }
    if (depth==max_depth){
        return 0 ; 
    }
    if (isMax){
        int maxi=-INFINITY;
        for (int row=0 ; row<3; row++){
            for (int col=0 ; col<3 ; col++){
                if (board[row][col]!=' ')
                    continue;
                board[row][col]='X'; 
                int result=min_max(depth+1,0,max_depth); 
                board[row][col]=' '; 

                if (result>maxi)
                    maxi=result; 
                }
            
             }
        return maxi; 
    }
    else {
        int mini=INFINITY;
        for (int row=0 ; row<3; row++){
            for (int col=0 ; col<3 ; col++){
                if (board[row][col]!=' ')
                    continue;
                board[row][col]='O'; 
                int result=min_max(depth+1,1,max_depth); 
                board[row][col]=' '; 

                if (result<mini)
                    mini=result; 
                }
            
             }
        return mini; 

    }
}
Move choose_bestMove(char player,int max_depth){
    int best;
    Move best_Move; 
    best_Move.row=-1; 
    best_Move.col=-1;
    if (player=='X')
        best=-10000;
    else 
        best=10000; 
    for (int row=0 ; row<3; row++){
        for (int col=0 ; col<3 ; col++){
            if (board[row][col]!=' ')
                continue; 
            board[row][col]=player; 
            if (player=='X'){
                int eval=min_max(0,0,max_depth); 
                if (eval>best)
                {
                    best=eval; 
                    best_Move.row=row; 
                    best_Move.col=col; 
                }
            }
            else
            {
                int eval=min_max(0,1,max_depth); 
                if (eval<best)
                {
                    best=eval; 
                    best_Move.row=row; 
                    best_Move.col=col; 
                }
            }
            board[row][col]=' ';

        }
    }
    return best_Move;
}



void play_ai(int level,char human){
    char player=human;
    char ai=(human=='O')? 'X' : 'O';   
    
    while ( !full()){
        if (player=='X'){
        int inp=-10; 
        while (!(inp>=0 && inp<=9))
        {
            inp=prompt_input(player); 
        }
        place(player,inp);
        display(); 
        if (check_win())  {
            cout<<"Player "<<player<<" won"<<"\nWanna play again?\n";
            return;
        }
        Move best_Move= choose_bestMove(ai,level*3);
        board[best_Move.row][best_Move.col]=ai; 
        display(); 

        if (check_win()){
            cout<<"AI Won UwU"<<endl ; 
            return; 
        }
        }
        
        
        else {

        Move best_Move= choose_bestMove(ai,level*3);
        board[best_Move.row][best_Move.col]=ai; 
        display(); 

        if (check_win()){
            cout<<"AI Won UwU"<<endl ; 
            return; 
        }
        int inp=-10; 
        while (!(inp>=0 && inp<=9))
        {
            inp=prompt_input(player); 
        }
        place(player,inp);
        display(); 
        if (check_win())  {
            cout<<"Player "<<player<<" won"<<"\nWanna play again?\n";
            return;
 }
    }        
    }


    }



int main(){
    int choice; 
    cout<<"Enter 1 for multiplayer , 2 to play vs computer\n";
    cin >>choice; 
    if (choice==1)
        multi_player();   
    
    else {
        cout<<"Choose the level (1-3) (1 is the easiest , while 3 is unbeatable)\n"; 
        int level ; 
        cin>>level; 
        cout<<"DO you want to play X or O?\n"; 
        char human ; 
        cin>>human; 

        play_ai(level,human);  
    }
    return 0 ; 
}
