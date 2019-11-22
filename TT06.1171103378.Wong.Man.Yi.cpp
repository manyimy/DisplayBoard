/**********|**********|**********|
Program: TT06.1171103378.Wong.Man.Yi.cpp
Course: Programming Fundamental
Year: 2019/20 Trimester 1
Name: Wong Man Yi
ID: 1171103378
Lecture Section: TC03
Tutorial Section: TT06
Email: 1171103378@student.mmu.edu.my
Phone: 013-9836988
**********|**********|**********/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int DISROW = 20;             //20 display rows and
const int DISCOL = 40;             //40 display columns which is actually displaying
const int MAXROW = 27;             //the actual size of the display board is 27 rows
const int MAXCOL = 190;            //150 columns (max characters 25 * 6 = 150)

char displayBoard[MAXROW][MAXCOL]={};   //global array of display board

string getLine();
void getAnchor(int &, int &);
void printMenu();
int getChoice();
int getTimeStep();
int getSpeed();
void processDisplayBoard(int [], int [], int &, int &, int, bool);
void loopString(string, int &, int &, int);
void delay(int);
void clearScreen();
void display();
void moveUpwards(int&);
void moveDownwards(int&);
void moveLeft();
void moveRight();

//Get user input sentence and errors handling:
//only 25 characters and below including spaces,
//no special characters allowed
string getLine()
{
    string str;         //local variable for string
    bool isalnum;       //boolean to check if the input is alphabet and numbers
    do {
        cout << "Enter a sentence with less than 25 characters including space" << endl;
        getline(cin, str);      //get the whole line of input including spaces

        //Shows error if the sentence entered is too long or no input
        if (str.length()>25)
            cout << "Sentence entered is too long!\n" << endl;
        else if (str.length()<1)
            cout << "Enter at least one character!\n" << endl;

        isalnum=true;       //initialize isalnum to true
        for (char letter:str)   // loop through every letter in variable str
        {
            if (letter != ' ')  //skip the checking if the letter is a space
            {
                if(!(isalpha(letter) || isdigit(letter)))   //if the letter is neither an
                {                                           //alphabet nor a number
                    isalnum=false;                          //assign isalnum to false to
                }                                           //continue the do while loop
            }
        }
        if (isalnum==false)         //Shows the error to user if isalnum is false
            cout << "Invalid input! Enter alphabetic characters only!\n" << endl;
    }while((str.length() > 25 || str.length() < 1) || isalnum==false);      //continue the loop to get input line is input is
                                                                            //too long, too short, not alphabet o not number
    //loop through the string to make every character uppercase
    int ch=0;
    while (str[ch]){
        if(islower(str[ch]))
            str[ch] = toupper(str[ch]);
            ch++;
    }

    return str;     //return back the string which fulfilled the requirement back to main's str
}

//Get anchor dot from the user and errors handling
void getAnchor(int &anchorx, int &anchory)
{
    string snum1, snum2, snum;      //Get the input as string to avoid the program from terminating
    bool digit, limit;              //boolean digit and limit to check if the inputs are numbers in range 0 to 20 and 40

    //do-while loop to check if the numbers are in the limit range
    do{
        //another do while loop to check if the inputs are numbers, if yes, change it to integer
        do{
            digit=true;
            cout << "\nEnter positive coordinate for anchor dot" << endl;
            cout << "(maximum coordinate is 39 19)" << endl;
            cin >> snum1 >> snum2;

            snum=snum1;     //store first string input, snum1, to snum for checking
            for(int j=0; j<2; j++)      //loop two times to check both inputs
            {
                //loop through the string to check if it is digit
                for (unsigned int i = 0; i < snum.length(); i++)
                {
                    if (isdigit(snum[i]) == false)
                        digit = false;
                }
                snum=snum2;
            }
            //Output error to user if input includes non-digit characters
            if (digit==false)
                cout << "Invalid input! Enter numeric numbers only!"<< endl;
        }while(digit==false);

        anchorx = stoi(snum1);
        anchory = stoi(snum2);

        limit = (anchorx >= 0 && anchorx < 40 && anchory >= 0 && anchory < 20);
        if (limit == false)
            cout << "Input has exceeded the limit 40 20" << endl;
    }while(limit == false);
}


//Function to print out the display choice menu
void printMenu()
{
    cout << endl;
    cout << "Enter number of direction for the sentence to move to" << endl;
    cout << "1. Moving upwards" << endl;
    cout << "2. Moving downwards" << endl;
    cout << "3. Moving to the left" << endl;
    cout << "4. Moving to the right" << endl;
    cout << "5. Stationary" << endl;
}


//Function to get the direction to move
int getChoice()
{
    string c;       //store input c as string to check if it fulfill requirements
    bool inrange, cDigit;   //boolean to check if the input is number in range 1 to 5
    int choice;     //store the integer for c after checking
    do{
        inrange=true;

        do{
            cDigit=true;

            printMenu();
            cin >> c;

            //loop through the input and check if it is digit and is in range 1 to 5
            //if not, boolean cDigit or/and inrange set to false, shows error
            //then continue to get input
            for (int i = 0; i < c.length(); i++)
            {
                if (isdigit(c[i]) == false)
                    cDigit = false;
            }
            if(cDigit==false)
                cout << "Invalid input! Enter a number from the menu!" << endl;
            else{
                choice = stoi(c);
                cDigit=true;
            }
        }while (cDigit==false);

        if ((choice <= 5) && (choice >= 1))
            inrange == true;
        else{
            cout << "\nChoose a number from the menu" << endl;
            inrange = false;
        }
    }while(inrange==false);

    return choice;
}


//Function to get timestep from user and errors handling
int getTimeStep()
{
    unsigned long int timestep;
    string ts;
    bool isnum;
    do{
        isnum=true;
        cout << "\nEnter desired time step" << endl;
        cin >> ts;

        //loop through the input to check if it is digit
        //show errors if it's not and continue to get input
        for (int i=0; i<ts.length(); i++)
        {
            if(isdigit(ts[i])==false)
            {
                isnum = false;
            }
        }
        if (isnum == false)
        {
            cout << "Invalid input!" << endl;
        }
        else
        {
            timestep = stoi(ts);
        }
    }while(isnum==false);


    return timestep;
}


//Function to get sentence's moving speed and errors handling
int getSpeed()
{
    string v;
    int speed;
    bool isnum, inrange;

    do{
        inrange=true;

        do{
            isnum=true;
            //Get input from user
            cout << "\nEnter the moving speed for sentence \n"
                 << "(1 to 10, 1 as slowest and 10 as fastest)" << endl;
            cin >> v;

            //loop through the input
            for (int i=0; i<v.length(); i++)
            {
                //check if every character is digit
                if(isdigit(v[i])==false)
                {
                    isnum = false;
                }
            }
            //Show error if any of the character is not digit
            if (isnum == false)
            {
                cout << "Invalid input! \nEnter numbers from 1 to 10" << endl;
            }
            //if every character is digit, convert into integer data type speed
            else
            {
                speed = stoi(v);
            }
        }while(isnum==false);       //continue to get input if any of the character is not digit

        //check if speed if in range 1 to 10
        if(speed >= 1 && speed <= 10)
        {
            inrange = true;
        }
        //show error if it's not in range
        else
        {
            inrange = false;
            cout << "Enter numbers from 1 to 10 only" << endl;
        }
    }while(inrange==false);     //continue to get input if it is not in range


    return speed;
}


//Create display board by looping the input string and added the
//display of every character to the array displayboard
void loopString(string sentence, int &dbrow, int &dbcol, int anchory)
{
    //declare array for each alphabet and numeric character
    //row and column that contain #
    int Arow[16] = {0,1,1,2,2,3,3,4,4,4,4,4,5,5,6,6},
        Acol[16] = {2,1,3,0,4,0,4,0,1,2,3,4,0,4,0,4},
        Brow[20] = {0,0,0,0,1,1,2,2,3,3,3,3,4,4,5,5,6,6,6,6},
        Bcol[20] = {0,1,2,3,0,4,0,4,0,1,2,3,0,4,0,4,0,1,2,3},
        Crow[13] = {0,0,0,1,1,2,3,4,5,5,6,6,6},
        Ccol[13] = {1,2,3,0,4,0,0,0,0,4,1,2,3},
        Drow[18] = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,6,6},
        Dcol[18] = {0,1,2,3,0,4,0,4,0,4,0,4,0,4,0,1,2,3},
        Erow[18] = {0,0,0,0,0,1,2,3,3,3,3,4,5,6,6,6,6,6},
        Ecol[18] = {0,1,2,3,4,0,0,0,1,2,3,0,0,0,1,2,3,4},
        Frow[14] = {0,0,0,0,0,1,2,3,3,3,3,4,5,6},
        Fcol[14] = {0,1,2,3,4,0,0,0,1,2,3,0,0,0},
        Grow[16] = {0,0,0,1,1,2,3,4,4,4,4,5,5,6,6,6},
        Gcol[16] = {1,2,3,0,4,0,0,0,2,3,4,0,4,1,2,3},
        Hrow[17] = {0,0,1,1,2,2,3,3,3,3,3,4,4,5,5,6,6},
        Hcol[17] = {0,4,0,4,0,4,0,1,2,3,4,0,4,0,4,0,4},
        Irow[15] = {0,0,0,0,0,1,2,3,4,5,6,6,6,6,6},
        Icol[15] = {0,1,2,3,4,2,2,2,2,2,0,1,2,3,4},
        Jrow[10] = {0,1,2,3,4,5,5,6,6,6},
        Jcol[10] = {4,4,4,4,4,0,4,1,2,3},
        Krow[14] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6},
        Kcol[14] = {0,4,0,3,0,2,0,1,0,2,0,3,0,4},
        Lrow[11] = {0,1,2,3,4,5,6,6,6,6,6},
        Lcol[11] = {0,0,0,0,0,0,0,1,2,3,4},
        Mrow[17] = {0,0,1,1,1,1,2,2,2,3,3,4,4,5,5,6,6},
        Mcol[17] = {0,4,0,1,3,4,0,2,4,0,4,0,4,0,4,0,4},
        Nrow[17] = {0,0,1,1,2,2,2,3,3,3,4,4,4,5,5,6,6},
        Ncol[17] = {0,4,0,4,0,1,4,0,2,4,0,3,4,0,4,0,4},
        Orow[16] = {0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,6},
        Ocol[16] = {1,2,3,0,4,0,4,0,4,0,4,0,4,1,2,3},
        Prow[15] = {0,0,0,0,1,1,2,2,3,3,3,3,4,5,6},
        Pcol[15] = {0,1,2,3,0,4,0,4,0,1,2,3,0,0,0},
        Qrow[17] = {0,0,0,1,1,2,2,3,3,4,4,4,5,5,6,6,6},
        Qcol[17] = {1,2,3,0,4,0,4,0,4,0,2,4,0,3,1,2,4},
        Rrow[18] = {0,0,0,0,1,1,2,2,3,3,3,3,4,4,5,5,6,6},
        Rcol[18] = {0,1,2,3,0,4,0,4,0,1,2,3,0,2,0,3,0,4},
        Srow[15] = {0,0,0,1,1,2,3,3,3,4,5,5,6,6,6},
        Scol[15] = {1,2,3,0,4,0,1,2,3,4,0,4,1,2,3},
        Trow[11] = {0,0,0,0,0,1,2,3,4,5,6},
        Tcol[11] = {0,1,2,3,4,2,2,2,2,2,2},
        Urow[15] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,6},
        Ucol[15] = {0,4,0,4,0,4,0,4,0,4,0,4,1,2,3},
        Vrow[13] = {0,0,1,1,2,2,3,3,4,4,5,5,6},
        Vcol[13] = {0,4,0,4,0,4,0,4,0,4,1,3,2},
        Wrow[17] = {0,0,1,1,2,2,3,3,4,4,4,5,5,5,5,6,6},
        Wcol[17] = {0,4,0,4,0,4,0,4,0,2,4,0,1,3,4,0,4},
        Xrow[13] = {0,0,1,1,2,2,3,4,4,5,5,6,6},
        Xcol[13] = {0,4,0,4,1,3,2,1,3,0,4,0,4},
        Yrow[10] = {0,0,1,1,2,2,3,4,5,6},
        Ycol[10] = {0,4,0,4,1,3,2,2,2,2},
        Zrow[15] = {0,0,0,0,0,1,2,3,4,5,6,6,6,6,6},
        Zcol[15] = {0,1,2,3,4,4,3,2,1,0,0,1,2,3,4},
        row0[19] = {0,0,0,1,1,2,2,2,3,3,3,4,4,4,5,5,6,6,6},
        col0[19] = {1,2,3,0,4,0,3,4,0,2,4,0,1,4,0,4,1,2,3},
        row1[10] = {0,1,1,2,3,4,5,6,6,6},
        col1[10] = {2,1,2,2,2,2,2,1,2,3},
        row2[15] = {0,0,0,1,1,2,3,3,4,5,6,6,6,6,6},
        col2[15] = {1,2,3,0,4,4,2,3,1,0,0,1,2,3,4},
        row3[15] = {0,0,0,0,0,1,2,3,3,4,5,5,6,6,6},
        col3[15] = {0,1,2,3,4,4,3,2,3,4,0,4,1,2,3},
        row4[14] = {0,1,1,2,2,3,3,4,4,4,4,4,5,6},
        col4[14] = {3,2,3,1,3,0,3,0,1,2,3,4,3,3},
        row5[17] = {0,0,0,0,0,1,2,2,2,2,3,4,5,5,6,6,6},
        col5[17] = {0,1,2,3,4,0,0,1,2,3,4,4,0,4,1,2,3},
        row6[16] = {0,0,0,1,2,3,3,3,3,4,4,5,5,6,6,6},
        col6[16] = {2,3,4,1,0,0,1,2,3,0,4,0,4,1,2,3},
        row7[11] = {0,0,0,0,0,1,2,3,4,5,6},
        col7[11] = {0,1,2,3,4,4,3,2,1,1,1},
        row8[17] = {0,0,0,1,1,2,2,3,3,3,4,4,5,5,6,6,6},
        col8[17] = {1,2,3,0,4,0,4,1,2,3,0,4,0,4,1,2,3},
        row9[16] = {0,0,0,1,1,2,2,3,3,3,3,4,5,6,6,6},
        col9[16] = {1,2,3,0,4,0,4,1,2,3,4,4,3,0,1,2},
        rowSpace[48] = {},
        colSpace[48] = {};

    //loop through the input sentence and add the display of every character back to array displayboard
    for (char letter:sentence)
    {
        bool isspace=false;
        switch (letter)
        {
            case 'A':processDisplayBoard(Arow, Acol, dbrow, dbcol, anchory, isspace);break;
            case 'B':processDisplayBoard(Brow, Bcol, dbrow, dbcol, anchory, isspace);break;
            case 'C':processDisplayBoard(Crow, Ccol, dbrow, dbcol, anchory, isspace);break;
            case 'D':processDisplayBoard(Drow, Dcol, dbrow, dbcol, anchory, isspace);break;
            case 'E':processDisplayBoard(Erow, Ecol, dbrow, dbcol, anchory, isspace);break;
            case 'F':processDisplayBoard(Frow, Fcol, dbrow, dbcol, anchory, isspace);break;
            case 'G':processDisplayBoard(Grow, Gcol, dbrow, dbcol, anchory, isspace);break;
            case 'H':processDisplayBoard(Hrow, Hcol, dbrow, dbcol, anchory, isspace);break;
            case 'I':processDisplayBoard(Irow, Icol, dbrow, dbcol, anchory, isspace);break;
            case 'J':processDisplayBoard(Jrow, Jcol, dbrow, dbcol, anchory, isspace);break;
            case 'K':processDisplayBoard(Krow, Kcol, dbrow, dbcol, anchory, isspace);break;
            case 'L':processDisplayBoard(Lrow, Lcol, dbrow, dbcol, anchory, isspace);break;
            case 'M':processDisplayBoard(Mrow, Mcol, dbrow, dbcol, anchory, isspace);break;
            case 'N':processDisplayBoard(Nrow, Ncol, dbrow, dbcol, anchory, isspace);break;
            case 'O':processDisplayBoard(Orow, Ocol, dbrow, dbcol, anchory, isspace);break;
            case 'P':processDisplayBoard(Prow, Pcol, dbrow, dbcol, anchory, isspace);break;
            case 'Q':processDisplayBoard(Qrow, Qcol, dbrow, dbcol, anchory, isspace);break;
            case 'R':processDisplayBoard(Rrow, Rcol, dbrow, dbcol, anchory, isspace);break;
            case 'S':processDisplayBoard(Srow, Scol, dbrow, dbcol, anchory, isspace);break;
            case 'T':processDisplayBoard(Trow, Tcol, dbrow, dbcol, anchory, isspace);break;
            case 'U':processDisplayBoard(Urow, Ucol, dbrow, dbcol, anchory, isspace);break;
            case 'V':processDisplayBoard(Vrow, Vcol, dbrow, dbcol, anchory, isspace);break;
            case 'W':processDisplayBoard(Wrow, Wcol, dbrow, dbcol, anchory, isspace);break;
            case 'X':processDisplayBoard(Xrow, Xcol, dbrow, dbcol, anchory, isspace);break;
            case 'Y':processDisplayBoard(Yrow, Ycol, dbrow, dbcol, anchory, isspace);break;
            case 'Z':processDisplayBoard(Zrow, Zcol, dbrow, dbcol, anchory, isspace);break;
            case '0':processDisplayBoard(row0, col0, dbrow, dbcol, anchory, isspace);break;
            case '1':processDisplayBoard(row1, col1, dbrow, dbcol, anchory, isspace);break;
            case '2':processDisplayBoard(row2, col2, dbrow, dbcol, anchory, isspace);break;
            case '3':processDisplayBoard(row3, col3, dbrow, dbcol, anchory, isspace);break;
            case '4':processDisplayBoard(row4, col4, dbrow, dbcol, anchory, isspace);break;
            case '5':processDisplayBoard(row5, col5, dbrow, dbcol, anchory, isspace);break;
            case '6':processDisplayBoard(row6, col6, dbrow, dbcol, anchory, isspace);break;
            case '7':processDisplayBoard(row7, col7, dbrow, dbcol, anchory, isspace);break;
            case '8':processDisplayBoard(row8, col8, dbrow, dbcol, anchory, isspace);break;
            case '9':processDisplayBoard(row9, col9, dbrow, dbcol, anchory, isspace);break;
            case ' ':isspace=true; processDisplayBoard(rowSpace, colSpace, dbrow, dbcol, anchory, isspace);break;
        }
    }
}

//Process the display board by looping the array passed from function loopString
void processDisplayBoard(int arrRow[], int arrCol[], int &dbrow, int &dbcol, int anchory, bool isspace)
{
    int elems=0;        //the number of element inside the alphabet row and col array
    dbrow=19-anchory;       //let the string start displaying at anchor dot

    //for every row that is correspond to element of array arrRow and
    //for every column that is correspond to element of array arrCol,
    //put '#' to it, else put ' ' to it to display the corresponding character
    for( int row=0; row < 8; ++row, ++dbrow ){
        for( int col=0; col < 6; ++col, ++dbcol ){
            if(!isspace){               //check if it is a space to prevent any # is put into the board when it is space
                if( row == arrRow[ elems ] && col == arrCol[ elems ] ){     //if the number of row and the number of columns are the same as the elements of the arrays
                    displayBoard[ dbrow ][ dbcol ]='#';                     //put #
                    elems++;                                                //and move to the next elements to repeat the check
                }
                else{                                                       //else, just leave it empty with ' '
                    displayBoard[ dbrow ][ dbcol ]=' ';
                }
            }
            else{                                           //if is a space, leave every row and col empty ' '
                displayBoard[ dbrow ][ dbcol ]=' ';
            }
            if( col == 5 ){
                if( row == 7 ){     //if it reaches the 5th column and 7th row which means the end of the letter displaying board
                    ++dbcol;        //make it add one more column to a new character
                }
                else if( row < 7 ){     //else if it is at 5th column but not 7th row,
                    dbcol -= 6;         //make it back to the beginning of the letter board column to replace the # at the right place
                }
            }
        }
    }
}

//Function to move the display upward one row and wrap around
void moveUpwards(int& anchor)
{
    char store[DISCOL];
    if(anchor<11){      // if the while letter has appeared on screen
        for (int s=0; s<DISCOL; ++s)        //store the first row of the display board inside store array
        {
            store[s]=displayBoard[0][s];
        }
        for(int row=1; row<DISROW; ++row){      //move the rows one row upwards starting from second row to first row and so on
            for (int col=0; col<DISCOL; ++col){
                displayBoard[row-1][col] = displayBoard[row][col];
            }
        }
        for(int s=0; s<DISCOL; ++s){        //store back the first row to the last row
            displayBoard[DISROW-1][s] = store[s];
        }
    }
    else        //else if the letter has not yet appear as a whole on the screen
    {
        for(int row=1; row<MAXROW; ++row){      //move the letter one row upward in the array
            for (int col=0; col<DISCOL; ++col){
                displayBoard[row-1][col] = displayBoard[row][col];
            }
        }
    }
}

//Function to move display downward one row
void moveDownwards(int& anchor)
{
    char store[DISCOL];
    for (int s=0; s<DISCOL; ++s)        //store the last row inside store array
    {
        store[s] = displayBoard[MAXROW-1][s];
    }
    for(int row=MAXROW-1; row>=0; --row){       //move the letters one row down starting from the third last row to second last row
        for (int col=0; col<DISCOL; ++col){
            displayBoard[row+1][col] = displayBoard[row][col];
        }
    }
    for(int s=0; s<DISCOL; ++s){        //store back the last row to the first row
        displayBoard[0][s] = store[s];
    }
}

//Function to move the letters one row left
void moveLeft()
{
    for(int row=0; row<DISROW; ++row){      //move the second column to the first column and so on
        for (int col=1; col<MAXCOL; ++col){
            displayBoard[row][col-1] = displayBoard[row][col];
        }
    }
}

//Function to move the letters to the right
void moveRight()
{
    for(int row=0; row<DISROW; ++row){      //move the first column to the second column and so on
        for (int col=MAXCOL; col>=0; --col){
            displayBoard[row][col+1] = displayBoard[row][col];
        }
    }
}

//Function to display the display board
void display()
{
    for (int row=0; row<20; ++row){             //Display only 20 rows
        for (int col=0; col<DISCOL; ++col){     //and 40 columns
            cout << displayBoard[row][col];
        }
        cout << endl;
    }
}

//Function to determine the speed of the sentence move
//based on the the input user enter from 1 to 10
void delay(int speed)
{
   for( int i = 0; i < 300000000/speed; ++i )
   { }
}

//Function to clear the screen
void clearScreen()
{
   system( "cls" );
}

//Main Function
int main()
{
    string str;
    int anchorx, anchory, choice, anchor,
        speed, dbrow, dbcol;
    unsigned long int timestep;

    str=getLine();  //Get user input and set to string variable str

    getAnchor(anchorx, anchory);    //Get anchor dot coordinate x and y
    dbrow = 19 - anchory;           //Set the display board starting row
    dbcol = anchorx;                //an starting column
    anchor=dbrow;           //anchor to identify if the letter has appears fully on the screen

    choice = getChoice();       //get how the user wants to display the sentence

    if(choice != 5){            //if display choice is not stationary
        timestep = getTimeStep();       //get the time step
        speed = getSpeed();             //and the speed
    }

    loopString(str, dbrow, dbcol, anchory);     //process the display board

    switch(choice){
        case 1:             //if choice is to move upwards
            clearScreen();
            display();          //display the display board first in case it moves too fast and doesn't show where it start
            delay(speed);       //let the display stay for awhile
            for(unsigned long int times=0; times<timestep; ++times){      //display the display board and move it upwards and display again
                clearScreen();                              //repeat it according to how many time step user want it to move
                moveUpwards(anchor);
                display();
                delay(speed);
                --anchor;           //to indicate the letter has moved one row upwards, when it reaches 12, it means it has fully appears on screen
            }
            break;
        case 2:             //if the choice is move downwards
            clearScreen();
            display();
            delay(speed);
            for(unsigned long int times=0; times<timestep; ++times){      //display the display board and move it one row downwards and repeat according to how many time step user wants
                clearScreen();
                moveDownwards(anchor);
                display();
                delay(speed);
            }
            break;
        case 3:             //if the choice is move to the left
            clearScreen();
            display();
            delay(speed);
            for(unsigned long int times=0; times<timestep; ++times){      //display the display board and move one columns to the left and repeat
                clearScreen();
                moveLeft();
                display();
                delay(speed);
            }
            break;
        case 4:             //if the choice is move to the right
            clearScreen();
            display();
            delay(speed);
            for(unsigned long int times=0; times<timestep; ++times){      //display the display board and move the columns one step to the right
                clearScreen();
                moveRight();
                display();
                delay(speed);
            }
            break;
        case 5:
            clearScreen();
            display();          //display the board straight away
            break;
    }

    return 0;
}
