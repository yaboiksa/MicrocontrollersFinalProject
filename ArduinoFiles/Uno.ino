
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

    byte currX = Column;
    byte currY = Heights[Column];

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
    // II. If won output win

    // I. Check everything
    //      a. Check down
    if (Heights[x] == 4){
        for (byte i = 0; i < count; i++)
        {
            /* code */
        }
        
    }



}


void setup(){}

void loop(){

    
}