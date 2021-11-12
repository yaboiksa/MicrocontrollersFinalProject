
enum Player{
    Player1,
    Player2
};

Player Board[7][7];
unsigned char Heights[7] = {0, 0, 0, 0, 0, 0, 0};
Player currPlayer = Player1;
bool Won = false;

void putPiece(unsigned char Column){
    // I. Place the Piece
    // II. Check if win condition is met
    // III. Switch which player

    unsigned char currX = Column;
    unsigned char currY = Heights[Column];

    // I. Place the Piece
    Board[currY][currX] = currPlayer;
    Heights[Column] += 1;

    // II. Check if win condition is met
    checkWin(currY, currX);
    if (Won == true)
        return;      

    // III. Switch which player
    if (currPlayer == Player1){
        currPlayer = Player2;
    }
    else{
        currPlayer = Player1;
    }
}

void checkWin(unsigned char y, unsigned char x){
    // I. Check everything
    //      a. Check down
    //      b. Check horizontal
    //      c. Check left diagonal
    //      d. Check right diagonal
    //          ] For all checks
    //          } Check left side
    //          } And check right side
    //          } And check if at endpoints
    // II. If won output win

    unsigned char connectedPieces;
    unsigned char i;
    bool dir = false;

    // I. Check everything
    //      a. Check down
    if (Heights[x] >= 4){
        connectedPieces = 1;
        for (i = 1; i < 5; i++){
            if(Board[y - i][x] != currPlayer){
                break;
            }
            connectedPieces++;
        }
        
        // II. If won output win
        if (connectedPieces == 4){
            Won = true;
            return;
        }
    }
    //      b. Check horizontal
    connectedPieces = 1;
    if ((x >= 0) || (x <= 6)){ // ?
        if (x == 0){
            dir = true;
        }

        for ( i = 1; i < 5; i++){
            //  }Check left side
            if((Board[y][x - i] == currPlayer) && dir == false){
                connectedPieces++;
            }
            else{
                dir = true;
            }
            
            //  }Check right side
            if((Board[y][x + i] == currPlayer) && dir == true){
                connectedPieces++;
            }
            else{
                dir = false;
            }

            // } Check if at endpoints
            if ((x == 0) || (x - i == 0))
                    dir = true;
            if ((x == 6) || (x - i == 6))
                    dir = false;

            // II. If won output win
            if (connectedPieces == 4){
                Won = true;
                return;
            }
        }
    }


    //      c. Check left diagonal
    

    //      d. Check right diagonal





}

void display(){
    
}

void setup(){}

void loop(){

    
}