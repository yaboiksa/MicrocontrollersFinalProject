
enum Player{
    Player1,
    Player2
};

Player Board[7][7];
byte Heights[7] = {0, 0, 0, 0, 0, 0, 0};
Player currPlayer = Player1;

void putPiece(byte Column){
    // I. Place the Piece
    // II. Check if win condition is met
    // III. Switch which player

    int currX = Column; // refactor to byte later
    int currY = Heights[Column]; // refactor to byte later

    // I. Place the Piece
    Board[currY][currX] = currPlayer;
    Heights[Column] += 1;

    // II. Check if win condition is met
    checkWin(currY, currX);

    // III. Switch which player
    if (currPlayer == Player1){
        currPlayer = Player2;
    }
    else{
        currPlayer = Player1;
    }
}

void checkWin(byte y, byte x){
    // I. Check everything
    //      a. Check down
    //      b. Check horizontal
    //      c. Check left diagonal
    //      d. Check right diagonal
    //          }Check left side
    //          } And check right side
    //          } And check if at endpoints
    // II. If won output win

    int connectedPieces; // refactor to byte later
    int i; // refactor to byte later
    bool dir = false; // refactor?

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
        
        if (connectedPieces == 4){
            // Win
        }
    }
    //      b. Check horizontal
    connectedPieces = 1;
    if ((x >= 0) || (x <= 6)){
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
        }
    }


    




}


void setup(){}

void loop(){

    
}