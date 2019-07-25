
// Authour: Elise Ratcliffe, enr24
// Partner: Andrea Lissak, al746


/* NOTE: Both of the Arduino files have more or less the same comments
 */



/* 
* The second and third line tell the arduino that the light resistor is connected to pin 0 
* and the LED to pin 13.
*
* lowerLightLimit calibrates the light resistor.
*
* the int created called RECIEVED_NUMBER records the integer sent over via LEDs. It has an
* acceptable range from 1 to 9.
*
* Then initialise the ints lightLevel, bitCounter, waitTime. EXPLANATIONS PENDING.
*
* gameArray creates array of ints - this array is edited when the players enter their values 
* into the serial monitor. The array keeps track of the state of the board.
*
* winnerIs is a string that is used at the end of the game to store whether player one or 
* player two won the game.
*/
#include <elapsedMillis.h>
int lightPin = 0;
int ledPin = 13; 
int lowerLightLimit=800;
int RECEIVED_NUMBER=10; 
int lightLevel;
int bitCounter=0;
int waitTime = 0;
int gameArray[]={9,9,9,9,9,9,9,9,9};
String winnerIs = "no winner yet";


/*
* timeElapsed counts from when the program started running. This is used to figure out when to use the light resistor to
* detect whether the LED is HIGH or LOW.
*
* isMyMove is boolean - as expected it is true when it is the players turn who is running this program. It
* is false when it is the other players turn.
*
* isStarted is, logically, true once the game has begun.
*
* runOnce is a bool that stops resetting the counter timeElapsed
*
* The four bools, binaryCode1 to binaryCode4, create the record the binary number sent across via LED. If the bool is false
* then a zero is stored in its place. True, and a one is stored.
*
* The next four bools, firstDone to fourthDone, are set to true once the binary digit for that position has been stored.
*/
elapsedMillis timeElapsed;
bool isMyMove=true;
bool isStarted=false;
bool runOnce=false;
bool binaryCode1=1;
bool binaryCode2=1;
bool binaryCode3=1;
bool binaryCode4=1;
bool firstDone=false;
bool secondDone=false;
bool thirdDone=false;
bool fourthDone=false;
bool gameIsOver=false;


/*
* Serial.begin(9600) starts communication between the arduino and the computer.
*
* printBoard calls the printBoard method.
*/
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  printBoard();
}


/*
* checkWin is a method that return true if someone has won - if this is the case then
* gameIsOver is also set to true.
*
* if the game isn't over and it's this players move, the program calls the myMove method
*
* if the game isn't over and it isn't this players move, the program calls the otherPlayerMove
* method
*
* if the game isn't over, no matter whether it's this players move or not, gameIsOver is set
* to the same value as checkIfOver - this return true if the game is over (as you would expect).
*
* If gameIsOver is true, the gameOver method is called.
*/
void loop()
{
  gameIsOver=checkWin();
  if(gameIsOver==false) 
  {
    if(isMyMove)
    {
      myMove();
    }
    else
    {
      otherPlayerMove();
    }
    gameIsOver=checkIfOver();
  }
  else
  {
    gameOver();
  }
}

/* When the game ends we must reset all of the values, espetially the booleans,
 * in order to access certain parts of the program, have the possibility for a
 * fresh start and reproduce the same exact features of the first game.
 * 
 * Secondly, this method has a delay statement that grants the two boards on the
 * two screen reset at the same time: since Arduino takes about 4 seconds to print
 * the whole board we set the "waitTime" to 4500 for the sender of the last move
 * and to 0 for the receiver such that the impression is that the two boards
 * refresh simultaneously.
 */
void initialiseAll()
{
  lowerLightLimit=800;
  RECEIVED_NUMBER=10;
  bitCounter=0;
  for(int i=0;i<9;i++)
  {
    gameArray[i]=9;
  }
  
  timeElapsed=0;
  isMyMove=true;
  isStarted=false;
  runOnce=false;
  binaryCode1=1;
  binaryCode2=1;
  binaryCode3=1;
  binaryCode4=1;
  firstDone=false;
  secondDone=false;
  thirdDone=false;
  fourthDone=false;
  gameIsOver=false;
  winnerIs = "no winner yet";
  delay(waitTime);
  waitTime = 0;
  printBoard();
}

/*
* This method return true if there is a winner and false if there isn't.
* It also resets the value of winnerIs when there is a winner.
*
* if the board is set up in such a way that one player occupies three
* squares in a row, column, or diagonal, an if statement is enterd.
*
* This is determined by looking at the values in gameArray. All initial
* values in gameArray are 9. The are set to 1 if the player of this 
* program uses the square and 0 if the other player uses it.
*
* this if statement will set isAWinner to true and winnerIs the a string
* that holds who the winner is.
*
* the method then return isAWinner.
*/
bool checkWin()
{
  bool isAWinner=false;
  
  if (gameArray[0]==1 && gameArray[1] == 1 && gameArray[2] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  } 
  
  if (gameArray[0]==0 && gameArray[1] == 0 && gameArray[2] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[3]==1 && gameArray[4] == 1 && gameArray[5] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[3]==0 && gameArray[4] == 0 && gameArray[5] == 0) {    
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[6]==1 && gameArray[7] == 1 && gameArray[8] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[6]==0 && gameArray[7] == 0 && gameArray[8] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[0]==1 && gameArray[3] == 1 && gameArray[6] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[0]==0 && gameArray[3] == 0 && gameArray[6] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[1]==1 && gameArray[4] == 1 && gameArray[7] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[1]==0 && gameArray[4] == 0 && gameArray[7] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[2]==1 && gameArray[5] == 1 && gameArray[8] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[2]==0 && gameArray[5] == 0 && gameArray[8] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[0]==1 && gameArray[4] == 1 && gameArray[8] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[0]==0 && gameArray[4] == 0 && gameArray[8] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  if (gameArray[2]==1 && gameArray[4] == 1 && gameArray[6] == 1) {
    isAWinner = true;
    winnerIs = "player two.";
  }
  
  if (gameArray[2]==0 && gameArray[4] == 0 && gameArray[6] == 0) {
    isAWinner = true;
    waitTime = 4500;
    winnerIs = "player one.";
  }
  
  return isAWinner;
  
}

/* This method is accessed in the main loop if and only if the variable "gameIsOver"
 * is true. If it is, then the method tells who the winner is and then the value
 * of "gameIsOver" is immediately changed to false in the initialisation method,
 * thus allowing the program to access other parts of the loop.
 */
void gameOver()
{
  Serial.println("The winner is " + winnerIs);
  initialiseAll();
}

/*
 * This  method checks for the case where all the cells of the board are
 * occupied: we start by assuming they are, and if we meet a case where
 * they are not, we change the value of the boolean (that will remain the
 * same since we set it to true just at the beginning).
 */
bool checkIfOver()
{
  bool allOccupied=true;
  for(int i=0;i<9;i++)
  {
    if(gameArray[i]==9)
    {
      allOccupied=false;
    }
  }
  return allOccupied;
}

/* This method collects the cell position (between 1 and 9) from the input
 * textfield of the serial monitor, checks if it's a number, checks if it's
 * in the range and finally checks if the wanted position is already occupied
 * by a cross or a circle.
 * 
 * If all goes well, the board with the updated move is shown and the message
 * of the current position is sent to the other arduino using the "sendCodedNumber(intX)"
 * that codifies the number intX related tho the cell position.
 */
void myMove()
{
  if (Serial.available() > 0)
  {
    char x = Serial.read();
    if ((x >= '1') && (x <= '9'))
    {
      int intX=x-'0';
      if((0==gameArray[intX-1])||(1==gameArray[intX-1]))
      {
        Serial.println("Occupied.");
      }
      else
      {
        gameArray[intX-1]=0; 
        printBoard();
        gameIsOver=checkWin();
        
        sendCodedNumber(intX);
        runOnce=false;
        isMyMove=false;
        isStarted=false;
        lowerLightLimit=800;
         firstDone=false;
         secondDone=false;
         thirdDone=false;
         fourthDone=false;
      }
    }
    else
    {
    }
  }
}

/* Even if this method looks repetitive and fairly simple, it is indeed the heart
 * of the program since it codifies numbers into binary and binary into light
 * pulses; the first blink is to notify the receiver (or slave) that a coded
 * message is about to be sent, the receiver is aware that this notice lasts
 * 100ms.
 * 
 * here's a table that more clearly shows the correspondance between
 * decimals and binary (we used a different codification from the usual binary conversion):
 * 
 * 1: 1000
 * 2: 0100
 * 3: 1100
 * 4: 0010
 * 5: 1010
 * 6: 0110
 * 7: 1110
 * 8: 0001
 * 9: 1001
 * 
 * (It's basically binary the other way around, we did this to start sending
 * the least significant binary digits first)
 */
void sendCodedNumber(int intX)
{
    switch(intX)
    {
     case 1:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(300);
            break;
     case 2:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(200);
            break;
     case 3:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(200);
            digitalWrite(ledPin, LOW);
            delay(200);
            break;
     case 4:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(200);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            break;
     case 5:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            break;
     case 6:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            break;
     case 7:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            break;
     case 8:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            break;
     case 9:digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, LOW);
            delay(100);
            digitalWrite(ledPin, HIGH);
            delay(100);
            digitalWrite(ledPin, LOW);
            break;
     
     default:Serial.println("unrecognized number");
     break;
    }
    
}

/*
* If it is the other players move, this method is entered. When this method is entered, the
* light resistor is set to read, so it can detect changes in the light levels due to the 
* blinking of the other arduinos LED.
*
* if the light is on or if the game has started, we enter the first if statement. If further,
* isStarted is false and runOnce is false, the time is reset, isStarted is set to true and runOnce
* is set to true. This if statement is entered when the game first begins.
*
* If it isn't the start of the game and if runOnce isn't true, then the mehtod startReceiving is
* called.
*/
void otherPlayerMove()
{
   lightLevel = analogRead(lightPin);
   
   if ((lightLevel<lowerLightLimit) || (isStarted))
   {
     if((!isStarted)&&(!runOnce))//runOnce: stop resetting the counter 
     {
      
       timeElapsed=0;
       isStarted=true;
       runOnce=true;
     }
     startReceiving();
   }
}

/*
* If the time is between 125ms and 175ms, and if the first binary digit has not been
* recorded, then firstDone is set to true. Also, if the LED is on, the first digit
* recorded in the binary number is 1. Otherwise it's 0.
*
* If the time is between 225ms and 275ms, and if the second binary digit has not been
* recorded, then secondDone is set to true. Also, if the LED is on, the first digit
* recorded in the binary number is 1. Otherwise it's 0.
*
* The same is true for times between 325 and 375, and 425 and 475.
*
* After this, no matter what the previous results, the method displayNumber is called.
*/
void startReceiving()
{
  
  if((timeElapsed>125)&&(timeElapsed<175)&&(!firstDone))
  {
    firstDone=true;
    if(lightLevel<lowerLightLimit)
    {
      binaryCode1=1;
    }
    else
    {
      binaryCode1=0;
    }
  }
  if((timeElapsed>225)&&(timeElapsed<275)&&(!secondDone))
  {
    secondDone=true;
    if(lightLevel<lowerLightLimit)
    {
      binaryCode2=1;
    }
    else
    {
      binaryCode2=0;
    }
  }
  if((timeElapsed>325)&&(timeElapsed<375)&&(!thirdDone))
  {
    thirdDone=true;
    if(lightLevel<lowerLightLimit)
    {
      binaryCode3=1;
    }
    else
    {
      binaryCode3=0;
    }
  }
  if((timeElapsed>425)&&(timeElapsed<475)&&(!fourthDone))
  {
    fourthDone=true;
    if(lightLevel<lowerLightLimit)
    {
      binaryCode4=1;
    }
    else
    {
      binaryCode4=0;
    }
    displayNumber();
  }
}

/*
* In this method we look at the binary number sent over via the LED and translate
* it into decimal. Storing this decimal in RECEIVED_NUMBER.
*
* gameArray is then edited. Indexing into the array using (RECEIVED_NUMBER - 1)
* as gameArray starts at 0, and the labeling of the boxes in our game starts
* at 1. At this position, the 9 stored there at the beginning of the program
* is replaced by a 1. It cannot be zero as we are dealing with RECIEVED_NUMBER,
* the program only recieves a number when dealing with the other arduino.
*
* The board is then printed to the serial monitor using the printBoard method.
* The program then checks if there is a winner, using the checkWinner method. If
* there is, then gameOver will be set to true.
*
* Finally, isMyMove is set to true, as the other player has just played. 
*/
void displayNumber()
{
    if((binaryCode1==1)&&(binaryCode2==0)&&(binaryCode3==0)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=1;
    }
    if((binaryCode1==0)&&(binaryCode2==1)&&(binaryCode3==0)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=2;
    }
    if((binaryCode1==1)&&(binaryCode2==1)&&(binaryCode3==0)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=3;
    }
    if((binaryCode1==0)&&(binaryCode2==0)&&(binaryCode3==1)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=4;
    }
    if((binaryCode1==1)&&(binaryCode2==0)&&(binaryCode3==1)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=5;
    }
    if((binaryCode1==0)&&(binaryCode2==1)&&(binaryCode3==1)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=6;
    }
    if((binaryCode1==1)&&(binaryCode2==1)&&(binaryCode3==1)&&(binaryCode4==0))
    {
      RECEIVED_NUMBER=7;
    }
    if((binaryCode1==0)&&(binaryCode2==0)&&(binaryCode3==0)&&(binaryCode4==1))
    {
      RECEIVED_NUMBER=8;
    }
    if((binaryCode1==1)&&(binaryCode2==0)&&(binaryCode3==0)&&(binaryCode4==1))
    {
      RECEIVED_NUMBER=9;
    }
    
    gameArray[RECEIVED_NUMBER-1]=1;
    printBoard();
    gameIsOver=checkWin();
    isMyMove=true;
}


//LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT//
//LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT//
//LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT LAYOUT//


//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
/////////////////////////////              /////////////////////////////////////
//////////////////////////////            //////////////////////////////////////
///////////////////////////////          ///////////////////////////////////////
////////////////////////////////        ////////////////////////////////////////
/////////////////////////////////      /////////////////////////////////////////
//////////////////////////////////    //////////////////////////////////////////
///////////////////////////////////  ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



// These chars* store each line of the board, these are explained above printBoard. 
char* line1p01[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p02[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p03[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p04[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p05[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p06[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p07[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p08[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p09[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p10[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line1p11[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };

char* line2p01[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p02[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p03[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p04[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p05[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p06[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p07[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p08[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p09[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p10[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line2p11[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };

char* line3p01[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p02[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p03[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p04[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p05[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p06[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p07[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p08[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p09[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p10[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };
char* line3p11[] = { "                     " , "         ###         " , "                     " , "         ###         " , "                     " };


/* This method calls the 34 methods below it and prints the board. In order to
 * place the right symbols in the right position the method checks the
 * "gameArray[]" array, so that it can be called from any part of the program.
 * 
 * What each "lineXpY()" (where x and y are values used to name the methods)
 * does is to print a full line of text that will eventually build up the large
 * symbols we see in the game (each line already contains in itself the
 * information of one of the three "macro-board-cells" line).
 * 
 * By concatenating all of the "mini-lines" the larger board starts taking shape.
 */
void printBoard()
{
  Serial.println();
  Serial.println();
  line1p1();
  line1p2();
  line1p3();
  line1p4();
  line1p5();
  line1p6();
  line1p7();
  line1p8();
  line1p9();
  line1p100();
  line1p110();

printHorizontal();

  line2p1();
  line2p2();
  line2p3();
  line2p4();
  line2p5();
  line2p6();
  line2p7();
  line2p8();
  line2p9();
  line2p100();
  line2p110();

printHorizontal();

  line3p1();
  line3p2();
  line3p3();
  line3p4();
  line3p5();
  line3p6();
  line3p7();
  line3p8();
  line3p9();
  line3p100();
  line3p110();
  
  Serial.println();
  Serial.println();
}


/* This method simply draws the horizontal lines of the macro board (with a
 * total of 4 lines: 2 blank ones and 2 hashed
 * 
 */
void printHorizontal()
{
  for (int i=0; i<5; i++) {
    Serial.print("          ");
  }
  Serial.println();
  for (int i=0; i<5; i++) {
    Serial.print("#####################");
  }
  Serial.println();
  for (int i=0; i<5; i++) {
    Serial.print("#####################");
  }               
  Serial.println();
  for (int i=0; i<5; i++) {
    Serial.print("          ");
  }
  Serial.println();
}


/* THIS FIRST METHOD IS FAIRLY SIMILAR TO THE 32 BELOW IT, BUT NOT FAIRLY
 * SIMILAR ENOUGH TO GATHER THE COMMON FEATURES IN A SINGLE FUNCTION, SO WE ARE
 * JUST GOING TO COMMENT THIS ONE AS A REPRESENTATIVE OF THE OTHERS.
 * 
 * The method mainly consists of a for loop that runs 3 times, one for each
 * column. It checks the first three elements of the "gameArray" and sets
 * values 0, 2, 6 of "line1p01[]". If the element in the "gameArray" is blank (9),
 * then it stores blank characters, if the element is a circle (0), then it prints
 * part of the circle, if the element is a cross (1), then it prints part of the cros.
 * 
 * Infact, if we try to imagine the shapes of the top of the circle and the top
 * of the cross shape, they look like that.
 */
void line1p1()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p01[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p01[i*2]="       #######       ";
    }
    else if(gameArray[i]==1)
    {
      line1p01[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p01[i]);
  }
  Serial.println();
}


void line1p2()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p02[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p02[i*2]="    #############    ";
    }
    else if(gameArray[i]==1)
    {
      line1p02[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p02[i]);
  }
  Serial.println();
}


void line1p3()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p03[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p03[i*2]="  #################  ";
    }
    else if(gameArray[i]==1)
    {
      line1p03[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p03[i]);
  }
  Serial.println();
}


void line1p4()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p04[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p04[i*2]=" ################### ";
    }
    else if(gameArray[i]==1)
    {
      line1p04[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p04[i]);
  }
  Serial.println();
}


void line1p5()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p05[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p05[i*2]="#####################";
    }
    else if(gameArray[i]==1)
    {
      line1p05[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p05[i]);
  }
  Serial.println();
}


void line1p6()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p06[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p06[i*2]="#####################";
    }
    else if(gameArray[i]==1)
    {
      line1p06[i*2]="         ###         ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p06[i]);
  }
  Serial.println();
}


void line1p7()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p07[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p07[i*2]="#####################";
    }
    else if(gameArray[i]==1)
    {
      line1p07[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p07[i]);
  }
  Serial.println();
}


void line1p8()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p08[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p08[i*2]=" ################### ";
    }
    else if(gameArray[i]==1)
    {
      line1p08[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p08[i]);
  }
  Serial.println();
}


void line1p9()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p09[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p09[i*2]="  #################  ";
    }
    else if(gameArray[i]==1)
    {
      line1p09[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p09[i]);
  }
  Serial.println();
}


void line1p100()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p10[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p10[i*2]="    #############    ";
    }
    else if(gameArray[i]==1)
    {
      line1p10[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p10[i]);
  }
  Serial.println();
}


void line1p110()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i]==9)
    {
      line1p11[i*2]="                     ";
    }
    else if(gameArray[i]==0)
    {
      line1p11[i*2]="       #######       ";
    }
    else if(gameArray[i]==1)
    {
      line1p11[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line1p11[i]);
  }
  Serial.println();
}



void line2p1()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p01[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p01[i*2]="       #######       ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p01[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p01[i]);
  }
  Serial.println();
}


void line2p2()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p02[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p02[i*2]="    #############    ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p02[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p02[i]);
  }
  Serial.println();
}


void line2p3()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p03[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p03[i*2]="  #################  ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p03[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p03[i]);
  }
  Serial.println();
}


void line2p4()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p04[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p04[i*2]=" ################### ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p04[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p04[i]);
  }
  Serial.println();
}


void line2p5()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p05[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p05[i*2]="#####################";
    }
    else if(gameArray[i+3]==1)
    {
      line2p05[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p05[i]);
  }
  Serial.println();
}


void line2p6()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p06[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p06[i*2]="#####################";
    }
    else if(gameArray[i+3]==1)
    {
      line2p06[i*2]="         ###         ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p06[i]);
  }
  Serial.println();
}


void line2p7()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p07[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p07[i*2]="#####################";
    }
    else if(gameArray[i+3]==1)
    {
      line2p07[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p07[i]);
  }
  Serial.println();
}


void line2p8()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p08[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p08[i*2]=" ################### ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p08[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p08[i]);
  }
  Serial.println();
}


void line2p9()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p09[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p09[i*2]="  #################  ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p09[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p09[i]);
  }
  Serial.println();
}


void line2p100()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p10[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p10[i*2]="    #############    ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p10[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p10[i]);
  }
  Serial.println();
}


void line2p110()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+3]==9)
    {
      line2p11[i*2]="                     ";
    }
    else if(gameArray[i+3]==0)
    {
      line2p11[i*2]="       #######       ";
    }
    else if(gameArray[i+3]==1)
    {
      line2p11[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line2p11[i]);
  }
  Serial.println();
}


void line3p1()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p01[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p01[i*2]="       #######       ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p01[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p01[i]);
  }
  Serial.println();
}


void line3p2()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p02[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p02[i*2]="    #############    ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p02[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p02[i]);
  }
  Serial.println();
}


void line3p3()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p03[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p03[i*2]="  #################  ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p03[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p03[i]);
  }
  Serial.println();
}


void line3p4()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p04[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p04[i*2]=" ################### ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p04[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p04[i]);
  }
  Serial.println();
}


void line3p5()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p05[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p05[i*2]="#####################";
    }
    else if(gameArray[i+6]==1)
    {
      line3p05[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p05[i]);
  }
  Serial.println();
}


void line3p6()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p06[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p06[i*2]="#####################";
    }
    else if(gameArray[i+6]==1)
    {
      line3p06[i*2]="         ###         ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p06[i]);
  }
  Serial.println();
}


void line3p7()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p07[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p07[i*2]="#####################";
    }
    else if(gameArray[i+6]==1)
    {
      line3p07[i*2]="        #####        ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p07[i]);
  }
  Serial.println();
}


void line3p8()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p08[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p08[i*2]=" ################### ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p08[i*2]="      ##     ##      ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p08[i]);
  }
  Serial.println();
}


void line3p9()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p09[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p09[i*2]="  #################  ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p09[i*2]="     ##       ##     ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p09[i]);
  }
  Serial.println();
}


void line3p100()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p10[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p10[i*2]="    #############    ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p10[i*2]="  ####         ####  ";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p10[i]);
  }
  Serial.println();
}


void line3p110()
{
  for (int i=0; i<3; i++)
  {
    if(gameArray[i+6]==9)
    {
      line3p11[i*2]="                     ";
    }
    else if(gameArray[i+6]==0)
    {
      line3p11[i*2]="       #######       ";
    }
    else if(gameArray[i+6]==1)
    {
      line3p11[i*2]="######         ######";
    }
  }
  for (int i=0; i<5; i++) {
    Serial.print(line3p11[i]);
  }
  Serial.println();
}
