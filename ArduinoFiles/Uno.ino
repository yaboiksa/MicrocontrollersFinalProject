
enum Player{
    Player1,
    Player2
};

Player Board[7][7];
int Heights[7] = {0, 0, 0, 0, 0, 0, 0};
Player currPlayer = Player1;

void putPiece(int Column){
    // I. Place the Piece
    // II. Check if win condition is met
    // III. Switch which player

    int currX = Column;
    int currY = Heights[Column];

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

void checkWin(int y, int x){
    // I. Check everything
    //      a.
    // II. If won output winscreen
}


void setup(){}

void loop(){

    
}