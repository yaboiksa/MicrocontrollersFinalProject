
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

//
// Display Initialization
//
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=184,TS_RT=916,TS_TOP=953,TS_BOT=193; // Calibrated pretty well

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, currentcolor;
uint8_t Orientation = 3;    //LANDSCAPE

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//
// End of Display Initialization
//

//
// Game related Initialization
//
enum Player{
    NoPlayer,
    Player1,
    Player2
};

Player Board[7][7];
unsigned char Heights[7] = {0, 0, 0, 0, 0, 0, 0};
Player currPlayer = Player1;
bool Won = false;
//
// End of Game Initializations
//

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
    //          a. up left 
    //      d. Check right diagonal
    //          } For all checks
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

            // II. If won output win
            if (connectedPieces == 4){
                Won = true;
                return;
            }
        }
    }


    //      c. Check left diagonal
    connectedPieces = 1;
    if (((x >= 0) || (x <= 6)) && ((y >= 0) || (y <= 6))){
        // check the end points to see which direction to check
        if ((x == 0) || (y == 0)){
            dir = true;
        }
        if ((x == 6) || (y == 6)){
            dir = false;
        }

        // check the lower left diaginal then switch to upper diaginal
        for ( i = 1; i < 5; i++){
            //  }Check left side
            if((Board[y - i][x - i] == currPlayer) && dir == false){
                connectedPieces++;
            }
            else{
                dir = true;
            }
            
            //  }Check right side
            if((Board[y + i][x + i] == currPlayer) && dir == true){
                connectedPieces++;
            }
            else{
                dir = false;
            }

            // } Check if at endpoints
            if ((x == 0) || (x - i == 0) && ((y == 0) || (y - i == 0)))
                    dir = true;
            if ((x == 6) || (x - i == 6) && ((y == 6) || (y - i == 6)))
                    dir = false;

            // II. If won output win
            if (connectedPieces == 4){
                Won = true;
                return;
            }
        }
    }

    //      d. Check right diagonal
    connectedPieces = 1;
    if (((x >= 0) || (x <= 6)) && ((y >= 0) || (y <= 6))){
        // check the end points to see which direction to check
        if ((x == 0) || (y == 0)){
            dir = true;
        }
        if ((x == 6) || (y == 6)){
            dir = false;
        }


        // check the lower left diaginal then switch to upper diaginal
        for ( i = 1; i < 5; i++){
            //  }Check left side
            if((Board[y + i][x - i] == currPlayer) && dir == false){
                connectedPieces++;
            }
            else{
                dir = true;
            }
            
            //  }Check right side
            if((Board[y - i][x + i] == currPlayer) && dir == true){
                connectedPieces++;
            }
            else{
                dir = false;
            }

            // } Check if at endpoints
            if ((x == 0) || (x - i == 0) && ((y == 0) || (y - i == 0)))
                    dir = true;
            if ((x == 6) || (x - i == 6) && ((y == 6) || (y - i == 6)))
                    dir = false;

            // II. If won output win
            if (connectedPieces == 4){
                Won = true;
                return;
            }
        }
    }
}

void display(void){
    // I. Draw the board
    // II. Draw the controls
    // III. Draw the Pieces/holes

    // I. Draw the board
    tft.fillScreen(WHITE);
    tft.fillRect(0, BOXSIZE, BOXSIZE * 8, BOXSIZE * 7, YELLOW);
    tft.fillRect(0, BOXSIZE, BOXSIZE / 2, BOXSIZE * 7, BLUE);
    tft.fillRect(BOXSIZE * 15/2, 0, BOXSIZE / 2, BOXSIZE * 7, BLUE);

    // II. Draw the controls
    for (int j = 0;  j < 7; j++){
        tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*j),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*j),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*j), BOXSIZE /2, BLUE);
        tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*j), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, BLUE);
    }

    // III. Draw the Pieces/holes
    for (int column = 0; column < 7; column++){
        for (int row = 6; row >= 0; row--){
            if(Board[column][row] == NoPlayer)
                tft.fillCircle(BOXSIZE * (column + 1), (BOXSIZE * 7/10 ) * (row + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, WHITE);
            else if(Board[column][row] == Player1)
                tft.fillCircle(BOXSIZE * (column + 1), (BOXSIZE * 7/10 ) * (row + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, RED);
            else if(Board[column][row] == Player2)
                tft.fillCircle(BOXSIZE * (column + 1), (BOXSIZE * 7/10 ) * (row + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, BLACK);
        }   
    }
    
    
}

void showStartScreen(void){

}

void setup(void){
    delay(5000);

    uint16_t tmp;

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);

    BOXSIZE = tft.width() / 8;
}

void loop(void){

    
}