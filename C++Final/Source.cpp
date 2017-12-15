// By Jacob Kryca 
//Additions to Midterm:

//Computer has an active AI that tries to place it's cards next to each other
//The players hand system replaces the proper card
// The win state works
// Fixed a bug that allowed the player to play over RD peices
// Removed Unneeded outputs in the code
// There is a Win State message 
// The players hand system no longer allows the use of the same card several times
// Created a means for the computer to check the board so that it plays within bounds
// Added proper Instructions 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <Windows.h>
#include <conio.h>





using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

// variables and vectors
const char EMPTY = ' ';
const int ROWMAX = 10;// constant for the max number of rows 
const int COLUMNMAX = 10;
const int PLAYERSHAND = 5;
const int COMPUTERSHAND = 5;
int playerCardChoice;
int drawcard;
int DeckSize = 104;
string card;
int playersHandSize = 0;
int computersHandSize = 0;
string playersCard;
string computerCard;
int WinCount = 0;
bool playerHasWon = false;
bool computerFoundCard;
bool computerHasWon = false;

vector<string> deck(DeckSize);
string board[ROWMAX][COLUMNMAX];
vector<string> playersHand(5);
vector<string> computersHand(5);




//function prototypes
void instructions();// displays the instructions for the game

void displayBoard(string board[][COLUMNMAX]);//displays the board

void createDeck(vector<string> &deck);// creates the deck

void displayDeck();// displays the deck for checking purposes

void fillBoard();// creates the board for the player

void fillPlayersHand();// fills the players hand

void displayPlayersHand();// displays the player's hand to screen

void fillComputersHand();// fills the computers hand

string PlayerMove(string question, vector<string> playersHand);// take the player's move

void checkWin(string board[][COLUMNMAX]);// checks if the player has won

void WinnerState();// Displays winner message

void HorizontalWinCount(string board[][COLUMNMAX]);// checks the horizontal board

void VerticleWinCount(string board[][COLUMNMAX]);// checks the board Verticaly if there is a winner

void DiagonalWinCount(string board[][COLUMNMAX]);// checks the board Diagonally

void computerMove();
// void CheckMove();
void placePieceOnBoard(string board[][COLUMNMAX], string playersCard, string question, string JackQuestion);// places the players piece on the board

void placeComputerPieceOnBoard(string board[][COLUMNMAX], string playersCard);// places the computer's piece on the board

bool computerChecksBoard(string board[][COLUMNMAX], vector<string> computersHand); // has the computer check all the spaces next to where it has already played

void testWin(string board[][COLUMNMAX]); // floods a part of the board for an instant win to check the win states


// 

int main()
{
	bool winner = false;
	bool playersTurn = true;

	instructions();
	fillBoard();// set the board equal to the functions return	
	displayBoard(board);// displays the board
	createDeck(deck);// creates the deck
					 //displayDeck();
	fillPlayersHand();// fills the players hand with random cards
	while (winner == false)
	{
		if (playersTurn == true)
		{
			displayPlayersHand();// Displays the players hand

			fillComputersHand();// fills the computers hand
			PlayerMove("What card would you like to play? Please enter 1-5", playersHand);// lets the player choose where they would like to go
			placePieceOnBoard(board, playersCard, "", "What card would you like your Jack to become? Please enter the card type followed by suit in caps ex AS for ace of spades");

			playersTurn = false;
		}
		else
		{
			computerMove();
			placeComputerPieceOnBoard(board, computerCard);

			playersTurn = true;
		}// end of else


		checkWin(board);// looks through the board to see if either player has won

		if (playerHasWon == true)
		{
			for (int i = 0; i < 10; i++)
			{
				cout << " YouWin! \n";

			}
		}// end of if player has won
		if (computerHasWon == true)
		{
			for (int i = 0; i < 10; i++)
				cout << " I'm sorry the computer has beat you.\n";
		}


	}// end of while winner


}// end of int Main

void instructions()
{
	cout << "The objective of the game is to get 5 spaces in a row\n" << endl;
	cout << "You start with 5 cards each turn and must decide what card to play depending on it's corresponding board location\n" << endl;
	cout << "The cards are read card position followed by suit. Example AS is Ace of Spades. This is same for the board\n" << endl;
	cout << "The board is read starting from the top left Row 1 Column " << endl << " if you move left 1 it is Row 1 Column 2\n" << endl << "and if you move down from Row 1 Column 1 it is Row 2 Column 1\n" << endl;
	cout << "JS stands for Jacks, Jacks are wild cards\n";
	cout << "Once you play the place where you played will be changed to a BL for blue the computer changes where it played to RD for Red\n" << endl;
	cout << "Good Luck!\n";

}



void testWin(string board[][COLUMNMAX])
{
	int row = 0;
	int column = 0;
	for (row; row < 5; row++)
	{
		board[row][column] = "BL";
		column++;
	}

}// Allows the user to flood a area to test winstates

void displayBoard(string board[][COLUMNMAX])// runs through the array printing each column then row
{
	for (int row = 0; row < ROWMAX; row++)
	{

		for (int column = 0; column < COLUMNMAX; column++)
		{
			if (board[row][column] == "BL")
			{
				SetConsoleTextAttribute(console, 8);
			}

			cout << board[row][column] << "|";

		}
		cout << endl;
	}
}//end of displayBoard

void fillBoard()// fills the sequence board
{
	board[0][0] = "  "; board[0][1] = ("2S"); board[0][2] = "3S";  board[0][3] = "4S";  board[0][4] = "5S";  board[0][5] = "6S";  board[0][6] = "7S"; board[0][7] = "8S"; board[0][8] = "9S"; board[0][9] = "  ";
	board[1][0] = "6C"; board[1][1] = ("5C"); board[1][2] = "4C";  board[1][3] = "3C";  board[1][4] = "2C";  board[1][5] = "AH";  board[1][6] = "KH"; board[1][7] = "QH"; board[1][8] = "XH"; board[1][9] = "XS";
	board[2][0] = "7C"; board[2][1] = ("AS"); board[2][2] = "2D";  board[2][3] = "3D";  board[2][4] = "4D";  board[2][5] = "5D";  board[2][6] = "6D"; board[2][7] = "7D"; board[2][8] = "9H"; board[2][9] = "QS";
	board[3][0] = "8C"; board[3][1] = ("KS"); board[3][2] = "6C";  board[3][3] = "5C";  board[3][4] = "4C";  board[3][5] = "3C";  board[3][6] = "2C"; board[3][7] = "8D"; board[3][8] = "8H"; board[3][9] = "KS";
	board[4][0] = "9C"; board[4][1] = ("QS"); board[4][2] = "7C";  board[4][3] = "6H";  board[4][4] = "5H";  board[4][5] = "4H";  board[4][6] = "AH"; board[4][7] = "9D"; board[4][8] = "7H"; board[4][9] = "AS";
	board[5][0] = "XC"; board[5][1] = ("XS"); board[5][2] = "8C";  board[5][3] = "7H";  board[5][4] = "2H";  board[5][5] = "3H";  board[5][6] = "KH"; board[5][7] = "XD"; board[5][8] = "6H"; board[5][9] = "2D";
	board[6][0] = "QC"; board[6][1] = ("9S"); board[6][2] = "9C";  board[6][3] = "8H";  board[6][4] = "9H";  board[6][5] = "XH";  board[6][6] = "QH"; board[6][7] = "QD"; board[6][8] = "5H"; board[6][9] = "3D";
	board[7][0] = "KC"; board[7][1] = ("8S"); board[7][2] = "XC";  board[7][3] = "QC";  board[7][4] = "KC";  board[7][5] = "AC";  board[7][6] = "AD"; board[7][7] = "KD"; board[7][8] = "4H"; board[7][9] = "4D";
	board[8][0] = "AC"; board[8][1] = ("7S"); board[8][2] = "6S";  board[8][3] = "5S";  board[8][4] = "4S";  board[8][5] = "3S";  board[8][6] = "2S"; board[8][7] = "2H"; board[8][8] = "3H"; board[8][9] = "5D";
	board[9][0] = "  "; board[9][1] = ("AD"); board[9][2] = "KD";  board[9][3] = "QD";  board[9][4] = "XD";  board[9][5] = "9D";  board[9][6] = "8D"; board[9][7] = "7D"; board[9][8] = "6D"; board[9][9] = "  ";
}// end of fillBoard

void createDeck(vector<string> &deck)
{
	deck[0] = ("AS");
	deck[1] = ("2S");
	deck[2] = ("3S");
	deck[3] = ("4S");
	deck[4] = ("5S");
	deck[5] = ("6S");
	deck[6] = ("7S");
	deck[7] = ("8S");
	deck[8] = ("9S");
	deck[9] = ("XS");
	deck[10] = ("JS");
	deck[11] = ("QS");
	deck[12] = ("KS");
	deck[13] = ("AD");
	deck[14] = ("2D");
	deck[15] = ("3D");
	deck[16] = ("4D");
	deck[17] = ("5D");
	deck[18] = ("6D");
	deck[19] = ("7D");
	deck[20] = ("8D");
	deck[21] = ("9D");
	deck[22] = ("XD");
	deck[23] = ("JS");
	deck[24] = ("KD");
	deck[25] = ("AH");
	deck[26] = ("2H");
	deck[27] = ("3H");
	deck[28] = ("4H");
	deck[29] = ("5H");
	deck[30] = ("6H");
	deck[31] = ("7H");
	deck[32] = ("8H");
	deck[33] = ("9H");
	deck[34] = ("XH");
	deck[35] = ("JS");
	deck[36] = ("QH");
	deck[37] = ("KH");
	deck[38] = ("AC");
	deck[39] = ("2C");
	deck[40] = ("3C");
	deck[41] = ("4C");
	deck[42] = ("5C");
	deck[43] = ("6C");
	deck[44] = ("7C");
	deck[45] = ("8C");
	deck[46] = ("9C");
	deck[47] = ("XC");
	deck[48] = ("JS");
	deck[49] = ("QC");
	deck[50] = ("KC");
	deck[51] = ("QD");
	deck[52] = ("AS");
	deck[53] = ("2S");
	deck[54] = ("3S");
	deck[55] = ("4S");
	deck[56] = ("5S");
	deck[57] = ("6S");
	deck[58] = ("7S");
	deck[59] = ("8S");
	deck[60] = ("9S");
	deck[61] = ("XS");
	deck[62] = ("JS");
	deck[63] = ("QS");
	deck[64] = ("KS");
	deck[65] = ("AD");
	deck[66] = ("2D");
	deck[67] = ("3D");
	deck[68] = ("4D");
	deck[69] = ("5D");
	deck[70] = ("6D");
	deck[71] = ("7D");
	deck[72] = ("8D");
	deck[73] = ("9D");
	deck[74] = ("XD");
	deck[75] = ("JS");
	deck[76] = ("KD");
	deck[77] = ("AH");
	deck[78] = ("2H");
	deck[79] = ("3H");
	deck[80] = ("4H");
	deck[81] = ("5H");
	deck[82] = ("6H");
	deck[83] = ("7H");
	deck[84] = ("8H");
	deck[85] = ("9H");
	deck[86] = ("XH");
	deck[87] = ("JH");
	deck[88] = ("QH");
	deck[89] = ("KH");
	deck[90] = ("AC");
	deck[91] = ("2C");
	deck[92] = ("3C");
	deck[93] = ("4C");
	deck[94] = ("5C");
	deck[95] = ("6C");
	deck[96] = ("7C");
	deck[97] = ("8C");
	deck[98] = ("9C");
	deck[99] = ("XC");
	deck[100] = ("JS");
	deck[101] = ("QC");
	deck[102] = ("KC");
	deck[103] = ("QD");
}

void displayDeck()
{
	for (int i = 0; i < 104; i++)
	{
		cout << deck[i];
	}
}

void fillPlayersHand()
{
	srand(time(0));

	for (int i = 0; i < PLAYERSHAND; i++)
	{

		drawcard = rand() % DeckSize;// creates a random number to chose a spot from the deck vector
		card = deck[drawcard]; // sets the card equal to the randomly drawn card
		playersHand[i] = card; // passes the card into the player's hand

		deck.erase(deck.begin() + drawcard);// removes the sport from the deck where the card was drawn
		DeckSize--; // decreases the decksize inorder to prevent you from drawing a nothing card

	}// end of for loop

}// end of Fill Players Hand

void displayPlayersHand()
{
	for (int i = 0; i < PLAYERSHAND; i++)
	{
		cout << " Card " << i + 1 << ": " << playersHand[i] << " \n";

	}// end of for loop


}// end of displayPlayersHand

void fillComputersHand()
{

	for (int i = 0; i < PLAYERSHAND; i++)
	{
		drawcard = rand() % DeckSize;// creates a random number to chose a spot from the deck vector
		card = deck[drawcard]; // sets the card equal to the randomly drawn card
		computersHand[i] = card; // passes the card into the player's hand
								 // cout << computersHand[i];// checks players hand REMOVE THIS LATER
		deck.erase(deck.begin() + drawcard);// removes the sport from the deck where the card was drawn
		DeckSize--; // decreases the decksize inorder to prevent you from drawing a nothing card

	}// end of for loop
}

string PlayerMove(string question, vector<string> playersHand)
{
	int num;
	do
	{

		cout << question;
		cin >> playerCardChoice;
		num = static_cast<int> (playerCardChoice);
	} while (num >= 5);

	int num2 = num - 1;
	playersCard = playersHand[num2];
	//playersHand.erase(playersHand.begin() + (num2));
	playersHand[num2] = "  ";
	playersHandSize--;
	fillPlayersHand();
	return playersCard;
}

void placePieceOnBoard(string board[][COLUMNMAX], string playersCard, string question, string JackQuestion)
{

	if (playersCard == "JS")
	{
		cout << JackQuestion;
		cin >> playersCard;
	}

	while (playersCard == "RD")
	{
		cout << JackQuestion;
		cin >> playersCard;
	}




	for (int row = 0; row < ROWMAX; row++)
	{

		for (int column = 0; column < COLUMNMAX; column++)
		{

			if (board[row][column] == playersCard)
			{
				cout << "Would you like to use the space at row " << row + 1 << " and column " << column + 1 << " please enter y/n" << question;
				cin >> question;
				if (question == "y")
				{
					board[row][column] = "Bl";

					row = ROWMAX;
					column = COLUMNMAX;
					displayBoard(board);

				}//end of if

			}// end of for if

		}// end of for row

	}// end of column





}// placePieceOnBoard end

void computerMove()
{
	if (computerChecksBoard(board, computersHand) == false)
	{
		int computerChoice = rand() % 5;
		computerCard = computersHand[computerChoice];
	}




}// end of computer move

void placeComputerPieceOnBoard(string board[][COLUMNMAX], string computerCard)
{
	//computerCard = "2S";
	int row = 0;
	int column;
	if (computerCard == "JS")
	{
		row = rand() % 10;
		column = rand() % 10;

		board[row][column] = "RD";



	}
	else {
		for (row; row < ROWMAX; row++)
		{
			column = 0;
			for (column; column < COLUMNMAX; column++)
			{

				if (board[row][column] == computerCard)
				{


					board[row][column] = "RD";


					displayBoard(board);

					return;


				}// end of for if

			}// end of for row

		}// end of for column

	}// end of else
}

void WinState()
{

}// end of winState



void checkWin(string board[][COLUMNMAX])
{
	int row = 0;
	int column = 0;
	for (row; row < ROWMAX; row++)
	{
		column = 0;
		for (column; column < COLUMNMAX; column++)
		{
			if (board[row][column] == "BL")
			{
				HorizontalWinCount(board);
				VerticleWinCount(board);
				DiagonalWinCount(board);
			}
			// end of while loop

		}// end of for column loop

	}// end of for row loop

	return;
}

void HorizontalWinCount(string board[][COLUMNMAX])
{
	int row = 0;
	int colum = 0;
	while (board[row][colum] == "BL")
	{
		WinCount++;
		row++;

		if (WinCount == 5)
		{
			playerHasWon = true;

		}// end o f IF winCount

	}	 // end of while

	WinCount = 0;// zeros out the win counter if 

	while (board[row][colum] == "RD")
	{
		WinCount++;
		row++;

		if (WinCount == 5)
		{
			computerHasWon = true;

		}// end o f IF winCount

	}	 // end of while

	WinCount = 0;// zeros out the win counter if 

}// end of Horizontal Win Count



void VerticleWinCount(string board[][COLUMNMAX])
{
	int row = 0;
	int colum = 0;
	while (board[row][colum] == "BL")
	{
		WinCount++;
		colum++;

		if (WinCount == 5)
		{
			playerHasWon = true;

		}// end o f IF winCount

	}	 // end of while player

	WinCount = 0;

	while (board[row][colum] == "RD")
	{
		WinCount++;
		colum++;

		if (WinCount == 5)
		{
			computerHasWon = true;

		}// end o f IF winCount

	}	 // end of while

	WinCount = 0;// zeros out the win counter if 


}// end of checkWinVerticle

void DiagonalWinCount(string board[][COLUMNMAX])
{
	int row = 0;
	int colum = 0;
	while (board[row][colum] == "BL")
	{
		WinCount++;
		row++;
		colum++;

		if (WinCount == 5)
		{
			playerHasWon = true;

		}// end o f IF winCount

	}	 // end of while diagonal left to right

	WinCount = 0;
	row == 0;
	colum == 0;

	while (board[row][colum] == "RD")
	{
		WinCount++;
		row++;
		colum++;

		if (WinCount == 5)
		{
			computerHasWon = true;

		}// end o f IF winCount

	}	 // end of while

	WinCount = 0;// zeros out the win counter if 


	WinCount = 0;
	row = 0;
	colum = 0;
	while (board[row][colum] == "BL")
	{
		WinCount++;
		row++;
		colum--;
		if (WinCount == 5)
		{
			playerHasWon = true;
			// cout << "YouWin";
		}// end o f IF winCount

	}// end of while diagonal right to left

	WinCount = 0;
	row == 0;
	colum == 0;

	while (board[row][colum] == "RD")
	{
		WinCount++;
		row++;
		colum--;

		if (WinCount == 5)
		{
			computerHasWon = true;

		}// end o f IF winCount

	}	 // end of while

	WinCount = 0;// zeros out the win counter if 
}// end of DiagonalWinCount

bool computerChecksBoard(string board[][COLUMNMAX], vector<string> computersHand)
{
	int row = 0;
	int column = 0;
	int tempRow = 0;
	int tempColumn = 0;
	int row2 = 0;
	int column2 = 0;

	for (row; row < 10; row++)// initial interation through board to check for computer's piece
	{
		column = 0;
		for (column; column < 10; column++)
		{
			if (board[row][column] == "RD")// if a piece is found moves the search back a row and column to check a 3x3 if the computer has any neighboring cards
			{

				row2 = row - 1;
				tempRow = row2 + 2;

				column2 = column - 1;
				tempColumn = column2 + 2;

				for (row2; row2 < tempRow; row2++)// interates through the constricted grid 
				{
					if (row2 < 0 || row2 >= 11)// prevents the computer from checking outside of the board
					{
						continue;
					}

					for (column2; column2 < tempColumn; column2++)// interates through the constricted grid
					{
						if (column2 < 0 || column2 >= 11)// prevents that computer from checking outside of the board
						{
							continue;
						}
						for (int i = 0; i < 4; i++)// interates through the computer's hand to see if it has the card for the neighboring space
						{
							if (board[row][column] == computersHand[i])
							{
								computersHand[i] = computerCard;// if the computer has the card it will place it where it can
								return true;
							}// end of if Board == computerHand

						}// end of for int i 

					}// end of for colum temp colum

				}// end of for row temp row




			}// end of if board = RD

		}// end of for column

	}//end of for row

}// computer checks board
