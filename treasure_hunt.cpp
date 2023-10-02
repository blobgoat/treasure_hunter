//File: treasure_hunt.cpp
//Author: Jacob Seaman
//Date: 5/6/23
//
//About: allowing the user or an ai to input treasure boxes
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
using std:: string;


/* possible idea: 
x's reveal the adjacent sides as well

for the capital and lower case, the goal of the game is to change the lower case to the capital letters

@ button indicates found treasures
*/
//global constants:
const int boardsize=8;

//board size should be uniform for all possible games, and therefore easy to change as a programmer if the client wants something else. and makes adding more levels easier
int arr[boardsize][boardsize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 11, 11, 11, 11, 0, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, -14},
    {13, 0, -1, 0, 0, 0, 0, 0},
    {-13, -1, 0, -1, 12, 12, 12, 12},
    {13, 0, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, -1, 0},
    {0, 0, 15, 15, 0, 0, 0, 0}
};
  //^global board variable, this program only runs for a single board.
int arrPlayer[boardsize][boardsize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 11, 11, 11, 11, 0, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, -14},
    {13, 0, -1, 0, 0, 0, 0, 0},
    {-13, -1, 0, -1, 12, 12, 12, 12},
    {13, 0, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, -1, 0},
    {0, 0, 15, 15, 0, 0, 0, 0}
};

 bool complete=false; 
  //will change to true when everything is found

  
const string abcde="abcde";
const string ABCDE="ABCDE";
//both are used as a map for determining what character should be inputed into the array.

//global variables:
int pointsForPlayer=0;
int pointsAI=0;
//important for keeping track of treasures found, and you can never unfind a treasure, so it makes sense for it to be a global variable.
int totalTreasureOnPlayerBoard=5;
int totalTreasureOnAIBoard=5;

//counters for making announcements when a chest is found
int bronze=0;
int silver=0;
int gold=0;
int rubies=0;
int vibranium=0;

//method for annoucning what chests have been found at the end of each turn
void announcingTreasureChests(){
if(bronze>=5) {
printf("Bronze chest Found\n");
  }
  if(silver>=4) {
printf("Silver chest Found\n");
  }
  if(gold>=3) {
printf("Gold chest Found\n");
  }
  if(rubies>=2) {
printf("Rubies chest Found\n");
  }
  if(vibranium>=1) {
printf("vibranium chest Found\n");
  }
  
}
//deletes all global variables and constants, in this case just arr
void cleanupFunction(){
  for (int i=0; i<boardsize;i++){
  *arr[i]=NULL;
  }
**arr=NULL;
  
}
//checks to see if all the treasures were found
void checkIfComplete(bool isPlayer){
  int **board;
  int points=pointsForPlayer;
  int totalPoints= 15;
  if(isPlayer){
    points=pointsAI;
    
  }
  if(points>=totalPoints){
    //remember if we are looking at the players board then then that means the AI would have won
    if(isPlayer==false){
      printf("You Win!\n");
    }
    else{
      printf("You so do not Win!\n");
    }
    complete=true;

  }
  
}
/*prints out the contents of a 2D integer array, but translates ints to characters to be printed in the following way:

->0 should be printed as a dash character  -
->-1 should be printed as X
->Any other negative number should be printed as ampersand character @
->Any positive number should also be printed as a dash character -
*/
//also checks to see if the user has won
string show(bool isPlayer){
  //can switch between boards depending on if it is the player one or AI one being referenced
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }
  string output="";
  for(int i=0;i<boardsize; i++){
    for(int j=0;j<boardsize; j++){
      int token=board[i][j];
      if(token>=0){
        output.push_back('-');
      }else {
        if(token==-1){
          output.push_back('X');
        }else{
          output.push_back('@');
        }
        
        }
        
        }
    output.push_back('\n');
    }
  if(isPlayer){
  printf("\t\tHuman player's board:\n%s\n",output.c_str());
  }else{
    printf("\t\tAI player's board:\n%s\n",output.c_str());
  }
  checkIfComplete(isPlayer);
  return output;
}
/*
0 should be printed as -
-1 should be printed as X
Positive numbers 11-15 should be printed as a-e respectively
Negative numbers -11-15 should be printed as A-E respectively
*/
string reveal(bool isPlayer, bool duringMatch){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }
string output="";
  
  for(int i=0;i<boardsize; i++){
    for(int j=0;j<boardsize; j++){
      int token=board[i][j];
      if(token>=0&&token<11||token>15){
        output.push_back('-');
      }else {
        if(token==-1){
          output.push_back('X');
        }else{
          if(token>=11&&token<=15){
            output.push_back(abcde[token-11]);          }else{
              if(token<=-11&&token>=-15){
                output.push_back(ABCDE[-token-11]);
              }else{
                output.push_back('@');
              }
            
            }
          
        }
        
        }
        
        }
    output.push_back('\n');
    }
  if(duringMatch){
  printf("\t\tAI Digging on Your Board:\n%s\n",output.c_str());
  }else{
    printf("\t\tThis is What Your Board Looks Like:\n%s\n",output.c_str());
  }
  
  
  return output;
}
//changes 0 to -1 indicating that it is a shown but not a tile
//changes treasure from positive to negative indicating it has been found
void dig(int row, int collumn, bool isPlayer){
  int **board;
  int points;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
      points=pointsAI;
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
      points=pointsForPlayer;
    }
  int token= board[row][collumn];
  if(token==0){
    board[row][collumn]=-1;
  }else{
    if(token>0){
      board[row][collumn]=-board[row][collumn];
      //game objective, one more point
      
      //check what kind of treasure was found
      //is player-> board. So it should be false if we want to collect stats on the AI's board
if(isPlayer==false){
  pointsForPlayer++;
      if(token==11){
        bronze++;
      }
      if(token==12){
        silver++;
      }
      if(token==13){
        gold++;
      }
      if(token==14){
        rubies++;
      }
      if(token==15){
        vibranium++;
      }
}else{
  pointsAI++;
}
      
      //see if the game finished
      announcingTreasureChests();
      checkIfComplete(isPlayer);
    }else{
      //do nothing
    }
    
  }

}
//changes array so that it matches the offset and length. When the offset amount of elements is reached, the function starts changing each value to the inputed value, until the length is used up, then it stops changing values
//good for modifying specific rows ofrow, maybe there will be a power up which allows several items to be altered at once?
//unsure of what this would be used for given the current game im thinking up
  //if length and offset is greater than size, this function will round off
int setByOffSet(bool vertical, int row, int length,int collumn, int value, bool isPlayer){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }
  if(collumn>=boardsize){
    collumn=boardsize-1;
  }
  if(row>=boardsize){
    row=boardsize-1;
  }
  int repeat=length;
  int collumn_left= boardsize-collumn;
  int row_left=boardsize-row;
  int available_space=collumn_left+row_left*boardsize;
  
if (vertical==true){
  
  
  if(available_space<length){
    repeat=available_space;
  }
  //^above code makes it so that everything should be in bounds
  
  int returning=0;
  bool stop=false;

//just for collumn, can reset i to zero when it increases row
  for (int i=row; !stop;i++){
      
    if(i<boardsize){
      //doesnt do anything unless the values already changed dont extend passed the inputed length
      if( repeat>0){
        if(board[i][collumn]!=value){
        returning++;
      }
      board[i][collumn]=value;
        //need to subtract one from repeat
      repeat--;
      }else{
        stop=true;//ends for loop
      }
    }else{
      if(repeat>0){
        i=-1;
        collumn++;
      }else{
      stop=true;}
    }
    
  }
  return returning;}
  //very similar code, just now it is for when it is across
  else{
    available_space=row_left+collumn_left*boardsize;
    if(available_space<length){
    repeat=available_space;
  }
  //^above code makes it so that everything should be in bounds
  
  int returning=0;
  bool stop=false;

//just for collumn, can reset i to zero when it increases row
  for (int i=collumn; !stop;i++){
      
    if(i<boardsize){
      //doesnt do anything unless the values already changed dont extend passed the inputed length
      if( repeat>0){
        if(arr[row][i]!=value){
        returning++;
      }
      board[row][i]=value;
        //need to subtract one from repeat
      repeat--;
      }else{
        stop=true;//ends for loop
      }
    }else{
      if(repeat>0){
        i=-1;
        row++;
      }else{
      stop=true;}
    }
    
  }
  return returning;
    
  }
  
}


//checking to see if the spot has been dug before
bool validDigSpot(int row, int column, bool isPlayer){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }

    int token=board[row][column];
    
    if(token<0){
      return false;
    }else{
      return true;
    }
    

}


//for checking for treasure chest
//valid if not dug up or if the same treasure exists there and it fits on the board
bool validSpot(bool vertical,int row, int column, int length, int typeTreas, bool isPlayer){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }
if(vertical==true){
  for(int i=row;length>0; i++){
    //need to do this before token is called
    if(i>=boardsize){
      return false;
    }
    int token=board[i][column];
    
    if(token<=16&&token>=11 &&typeTreas!=token||token<0){
      return false;
    }
    length--;

  }
  
  return true;
}else{
  for(int i=column; length>0; i++){
    //need to do this before token is called
    if(i>=boardsize){
      return false;
    }
    int token= board[row][i];
    
    if(token<=16&&token>=11 &&typeTreas!=token||token<0){
      return false;
    }
    length--;

  }
  return true;
}
}
//method for placing chests during set up, first need to differentiate whoose board we are augmenting
bool placeChest(bool vertical, int row, int column, int length, int type, bool isPlayer){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }

  
  if(validSpot(vertical,row,column,length,type,isPlayer)==false){
    printf("invalid spot\n");
    return false;
  }else{
  setByOffSet(vertical, row,length,column,type,isPlayer);
    return true;
    }
}
//clears array, makes it all zero
void clearBoard(bool isPlayer){
  int **board;
    if (isPlayer) {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arrPlayer[i];
        }
    } else {
        board = new int*[boardsize];
        for (int i = 0; i < boardsize; i++) {
            board[i] = arr[i];
        }
    }
  for (int i = 0; i < boardsize; i++) {
    for (int j = 0; j < boardsize; j++) {
        board[i][j] = 0;
    }
  
}
}
//sets board for AI similar to setBoardPlayer. Decided to make it seperate functions due to all the scan commands which were only relevant to the player
void setBoardAI(){
  //set board to zero
  clearBoard(false);

  //need to have a different seed each tim it is called

  int treasure_placed=0;
  while(treasure_placed!=totalTreasureOnAIBoard){
    int randX= rand()%boardsize;
    int randY= rand()%boardsize;
    //needs to be at least 1, but not more than 8
    int length=5-treasure_placed;
    int randBooAcross=rand()%2;
  bool vertical;
    if(randBooAcross==0){
      vertical=true;
    }else{
      vertical=false;
    }
//if there is a valid spot then place treasure chest there
    if (validSpot(vertical,randX,randY,length,11+treasure_placed,false)==true){
      placeChest(vertical, randX, randY, length, 11+treasure_placed,false);
      treasure_placed++;
    }
}
}

//prompts user to input values for location of treasures
//using two different methods for these because of all the scanner requests for this one
void setBoardPlayer(){
  //set player board to zero
  clearBoard(true);

  //need to have a different seed each tim it is called
  printf("you are in charge of inputing the board, because it is funny to watch users struggle.\n");
  
  int treasure_placed=0;
  //doesnt matter at the moment because both are the same\/\/
  while(treasure_placed!=totalTreasureOnPlayerBoard){
    // using character so the scan wont ever break until it tries to load the char themselves
    char x;
    char y;
    //needs to be at least 1, but not more than 8
    char verticalChar;
    int integerLength=5-treasure_placed;
    reveal(true, false);
    printf("FYI-> The length of this treasure is:\n %d\n",integerLength);
    
    printf("input a number being the row you wish the starting point of your treasure box to be:\n");
    scanf(" %c", &x);
    printf("input a number being the column you wish the starting point of your treasure box to be:\n");
    scanf(" %c", &y);
  

    printf("input a letter 't' if you wish this to be vertical alignment, otherwise input the letter 'f':\n");
    scanf(" %c", &verticalChar);
    
  bool vertical;
    //sets boolean to whether or not it should be vertical
    if(verticalChar=='t'||verticalChar=='T'){
      vertical=true;
    }else{
      if(verticalChar=='f'||verticalChar=='F'){
      vertical=false;
      }
    }


//if there is a valid spot then place treasure chest there
    //converting from characters to int within the return statment, this makes it so the code wont break by scaning for integers when the user may have not inputed one
    if (validSpot(vertical,(int)x-(int)'0',(int)y-(int)'0',integerLength,11+treasure_placed,true)==true){
      printf("placing the %d chest!\n",treasure_placed+1);
      placeChest(vertical,(int)x-(int)'0',(int)y-(int)'0',integerLength,11+treasure_placed,true);

      treasure_placed++;
    }else{
      printf("please try again, the location you selected was invalid\n");
    }
}
}
//initiates the game, this is where all the user inputs go into. Like pseudo main
  void play(){
    while(complete==false){
      //players turn \/\/\/
    bool playerTurn=true;
      while(playerTurn){
      
      char rowC;
      char columnC;
      show(false);
      announcingTreasureChests();
      printf("input a row:\n");
      scanf(" %c",&rowC);
      printf("input a column:\n");
      scanf(" %c", &columnC);
      int row=(int) rowC-(int)'0';
      int column= (int) columnC-(int)'0';
      
      if(validDigSpot(row,column,false)){
        dig(row,column,false);
        playerTurn=false;
      }else{
        printf("you already dug there!\n");
      }
    }
    
      //end of players turn ^^^
      //begining of AI's turn \/\/\/
      bool aITurn=true;
      while(aITurn){


    int randX= rand()%boardsize;
    int randY= rand()%boardsize;

//if there is a valid spot then place treasure chest there
    if (validDigSpot(randX,randY,true)==true){
      dig( randX, randY, true);
      aITurn=false;
      reveal(true,true); 
    }
      }
      //want to show board after AI made an attack
     
    }
  }

  



int main (int argc, char** argv){
srand(time(NULL));
  //sets AI board with 5 treasures placed
  setBoardAI();

  //initiates manual set up
  setBoardPlayer();
  reveal(true,false);

  //initiates the game method
  play();

  
  cleanupFunction();
  
  return 0;
}
