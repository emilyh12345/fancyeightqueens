//Emily Haller fancy 8 queens 
#include<iostream> 
#include<cstdlib>
using namespace std;

void nextRow(int q[], int &c);
void nextColumn(int q[], int &c);
void backtrack(int q[], int &c);
void print (int q[], int c);
bool okay(int q[], int c);

void nextColumn(int q[], int &c){
    c++; //increment column number to continue to check if queen can be placed
    if(c==8){
        print (q,c); //if at column 8 we have a solution so print it
    }else{
        nextRow(q,c); //otherwise check next row since haven't found a solution yet
    }
}

void nextRow(int q[], int &c){
    q[c]++; //increment row to continue to check if queen can be placed
    if (q[c]==8){ 
        q[c]=-1; //reset to row -1 so can later increment to row 0
        backtrack(q,c); // if at column 8 then backtrack since its off the board and nothing worked
    }
    if (okay(q,c)) nextColumn(q,c);   //if the queen can be placed then go to next column to find next queen placement
    nextRow(q,c); //otherwise go to next row to find the queens placement in that columm
}

bool okay(int q[], int c){ //function to test if queen can be placed there
    for(int i=0; i<c; i++){ //loops through the array to check if queen passes row test
        if(q[i]==q[c]) return false; 
    }
    for(int i=0; i<c; i++){ //loops through the array to check if passes upper diagonal test
        if((c-i)==(q[c]-q[i])) return false;
    }
    for (int i=0; i<c; i++){ //loops through the array to check if passes lower diagonal test
        if ((c-i)==abs(q[c]-q[i])) return false;
    }
    return true; //indicates all tests were passes
}

void backtrack(int q[], int&c){
    c--; //go back a column 
    if (c==-1){
        exit(1); //if get to nonexistent column -1 terminate since all solutions were found
    }
    nextRow(q,c); //otherwise go to next row since haven't found all solutions
}

void print (int q[], int c) {
    static int solutions=0;
    solutions++; //increment number of solution counter to keep track of amount of solutions
    cout<< "Solution " << solutions << endl;
    for(int col=0; col<8; col++){ //prints 1D array of each possible solution by iterating through array q
        cout << q[col] << " ";
    }
    cout << endl;
    typedef char box[5][7]; //creates box which is a 5 by 7 character array
    box bb, wb, *board[8][8]; //declare a black box, white box, and a 8 by 8 array of pointers to boxes
    for (int r=0; r<5; r++){ //loop to fill 5 by 7 boxes
        for (int c=0; c<7; c++){
            bb[r][c]= 'X'; // fill black boxes with Xs
            wb[r][c] =' '; // fill white boxes with spaces 
        }
    }

    // define black and white queens
    static box bq={ {'X', 'X', 'X', 'X', 'X', 'X', 'X'}, //define black queen(if theres a black box that should have a queen in it, it will point to this box and print this design)
                    {'X', ' ', 'X', ' ', 'X', ' ', 'X'},
                    {'X', ' ', 'X', ' ', 'X', ' ', 'X'},
                    {'X', ' ', ' ', ' ', ' ', ' ', 'X'},
                    {'X', 'X', 'X', 'X', 'X', 'X', 'X'} };

    static box wq={ {' ', ' ', ' ', ' ', ' ', ' ', ' '}, //define white queen(if theres a white box that should have a queen in it, it will point to this box and print this design)
                    {' ', 'X', ' ', 'X', ' ', 'X', ' '},
                    {' ', 'X', ' ', 'X', ' ', 'X', ' '},
                    {' ', 'X', 'X', 'X', 'X', 'X', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' '} };
    
    for (int r=0; r<8; r++){ 
        for (int c=0; c<8; c++){
            if ((r+c) % 2 ==0){ //if its a black box
                board[r][c] = &bb; //initialize that place on board to the address of the black box
            } else { //if its a white box
                board[r][c]= &wb; //initialize that place on board to the address of the white box
            } 
        } 
    }

   //placing the black and white queens on the board
    for(int r=0; r<8 ; r++){
        for(int c=0; c<8 ; c++){
            if (r==q[c]){ //in this box a queen should be placed
                if ((r+c) % 2 == 0) board[r][c]=&bq; //if its a black box assign the address of a black queen to the box pointer array
                else board[r][c]=&wq; //otherwise if its a white box assign the address of a white queen to the box pointer array
            }
        } 
    }

    for(int i=0; i<8; i++){ //refers to board rows
        for (int r=0; r<5; r++){ //refers to box rows
            for (int j=0; j<8; j++){ //refers to board columns
                for (int c=0; c<7; c++){ //refers to box columns
                    box *currentBox=board[i][j]; //refer to the current box thats being pointed to in order to get the row and column
                    cout << (*board[i][j])[r][c]; //print the row and column of the current box by dereferencing the current box 
                }
            }
            cout << endl;
        }
    }
    backtrack(q,c); //go back to find more solutions
}

int main(){
    int q[8]={0}, c=0; //initialize array and column to 0s to start
    q[0]=0; //place queen in top left corner
    nextColumn(q, c);
    return 0;
}