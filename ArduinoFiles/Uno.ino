
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>




// SUIT was a play tester
// EASTER EGG addon --- change the thing to squares and use the BLACK background green and orange



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
#define ORANGE  0xFAE0
#define ORANGE2 0xF9E0
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
    // II. Display said update
    // III. Check if win condition is met
    // IV. Switch which player

    unsigned char currX = Column;
    unsigned char currY = Heights[Column];

    // I. Place the Piece
    Board[currY][currX] = currPlayer;
    Heights[Column] += 1;


    // II. Display said update
    display();

    // III. Check if win condition is met
    checkWin(currY, currX);
    if (Won == true)
        return;      

    // IV. Switch which player
    if (currPlayer == Player1){
        currPlayer = Player2;
    }
    else{
        currPlayer = Player1;
    }


}

void checkWin(unsigned char y, unsigned char x) {
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

    // I. Check everything
    //      a. Check down
    if (Heights[x] >= 4) {
        connectedPieces = 1;
        for (i = 1; i < 5; i++) {
            if (Board[y - i][x] != currPlayer) {
                break;
            }
            connectedPieces++;
        }

        // II. If won output win
        if (connectedPieces == 4) {
            Won = true;
            return;
        }
    }
    //      b. Check horizontal
    connectedPieces = 1;
    if ((x >= 0) || (x <= 6)) {
        //  }Check left side
        for (i = 1; i < 5; i++) {
            if (x - i >= 0) {
                if (Board[y][x - i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        //  }Check right side
        for (i = 1; i < 5; i++) {
            if (x + i <= 6) {
                if (Board[y][x + i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        // II. If won output win
        if (connectedPieces >= 4) {
            Won = true;
            return;
        }
    }

    //      c. Check left diagonal
    connectedPieces = 1;
    if (((x >= 0) || (x <= 6)) && ((y >= 0) || (y <= 6))) {

        //  }Check left side
        for (i = 1; i < 5; i++) {
            if ((x - i >= 0) && (y - i >= 0)) {
                if (Board[y - i][x - i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        //  }Check right side
        for (i = 1; i < 5; i++) {
            if ((x + i <= 6) && (y + i <= 6)) {
                if (Board[y + i][x + i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        // II. If won output win
        if (connectedPieces >= 4) {
            Won = true;
            return;
        }
    }

    //      d. Check right diagonal
    connectedPieces = 1;
    if (((x >= 0) || (x <= 6)) && ((y >= 0) || (y <= 6))) {

        //  }Check left side
        for (i = 1; i < 5; i++) {
            if ((x - i >= 0) && (y + i  <= 6)) {
                if (Board[y + i][x - i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        //  }Check right side
        for (i = 1; i < 5; i++) {
            if ((x + i <= 6) && (y - i >= 0)) {
                if (Board[y - i][x + i] == currPlayer) {
                    connectedPieces++;
                }
                else {
                    break;
                }
            }
        }

        // II. If won output win
        if (connectedPieces >= 4) {
            Won = true;
            return;
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
    tft.fillRect(BOXSIZE * 15/2, BOXSIZE, BOXSIZE / 2, BOXSIZE * 7, BLUE);

    // II. Draw the controls
    for (int j = 0;  j < 7; j++){
        tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*j),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*j),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*j), BOXSIZE /2, BLUE);
        tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*j), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, BLUE);
    }

    // III. Draw the Pieces/holes
    for (int column = 0; column < 7; column++){
        for (int row = 0; row < 7; row++){
            if(Board[6 - column][row] == NoPlayer)
                tft.fillCircle(BOXSIZE * (row + 1), (BOXSIZE * 7/10 ) * (column + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, WHITE);
            else if(Board[6 - column][row] == Player1)
                tft.fillCircle(BOXSIZE * (row + 1), (BOXSIZE * 7/10 ) * (column + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, RED);
            else if(Board[6 - column][row] == Player2)
                tft.fillCircle(BOXSIZE * (row + 1), (BOXSIZE * 7/10 ) * (column + 1) + (BOXSIZE/2) + 7, (BOXSIZE * 3/5) /2, BLACK);
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

    display();

}

void loop(void){
    // I. Initialize touch
    // II. Initialize the current competing colors
    // III. Check for the pressure threshhold and map the x and y position
    // IV. Check regions for piece addition
    //      a. Bound check to ensure they dont overflow the board
    //      b. Place the piece at the specified column
    //      c. Indicator of the last piece that has been placed and where


    // I. Initialize touch
    uint16_t xpos, ypos;  //screen coordinates
    tp = ts.getPoint();   //tp.x, tp.y are ADC values

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    // II. Initialize the current competing colors
    if (currPlayer == Player1){
        currentcolor = RED;
    }
    else {
        currentcolor = BLACK;
    }

    // III. Check for the pressure threshhold and map the x and y position
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        // most mcufriend have touch (with icons) that extends below the TFT
        // screens without icons need to reserve a space for "erase"
        // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
        //
        // Calibration is true for PORTRAIT. tp.y is always long dimension 
        // map to your current pixel orientation
        switch (Orientation) {
            case 0:
                xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
                ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
                break;
            case 1:
                xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
                ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
                break;
            case 2:
                xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
                ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
                break;
            case 3:
                xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
                ypos = map(tp.x, TS_LEFT, TS_RT, 0, tft.height());
                break;
        }

        // IV. Check regions for piece addition
        if (ypos < BOXSIZE) {
            if (xpos < BOXSIZE + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[0] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(0);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2), BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 2 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[1] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(1);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 3 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[2] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(2);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*2),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*2),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*2), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*2), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 4 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[3] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(3);  
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*3),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*3),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*3), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*3), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 5 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[4] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(4);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*4),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*4),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*4), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*4), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 6 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[5] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(5);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*5),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*5),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*5), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*5), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
            else if (xpos < BOXSIZE * 7 + BOXSIZE/2) {
                // a. Bound check to ensure they dont overflow the board
                if (Heights[6] <= 6){
                    // b. Place the piece at the specified column
                    putPiece(6);
                    // c. Indicator of the last piece that has been placed and where
                    tft.fillTriangle((BOXSIZE / 2) + (BOXSIZE / 2) + (BOXSIZE*6),BOXSIZE * 3/4,(BOXSIZE / 4)  + (BOXSIZE / 2) + (BOXSIZE*6),BOXSIZE /2,(BOXSIZE * 3/4) + (BOXSIZE / 2) + (BOXSIZE*6), BOXSIZE /2, currentcolor);
                    tft.fillRect((BOXSIZE * 4/10) + (BOXSIZE / 2) + (BOXSIZE*6), BOXSIZE /10, BOXSIZE /5, BOXSIZE * 2/5, currentcolor);
                }
            } 
        }
    }
}