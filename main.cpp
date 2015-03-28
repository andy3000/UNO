////////////////////////////////////////////////////////////////////////
//////////////////////////// HEADER FILES //////////////////////////////
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstdlib>
//#include "listP.h"
//#include "queueP.cpp"
#include "classes.h"
//#include "stringLibrary.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
//////////////////////////// GLOBAL CONSTANTS //////////////////////////
////////////////////////////////////////////////////////////////////////

// standard string length
const int STR_LEN = 30;
const int MAX_CARDS = 108;

// null char
const char NULL_CHAR = '\0';

////////////////////////////////////////////////////////////////////////
/////////////////////// FUNCTION PROTOTYPES ////////////////////////////
////////////////////////////////////////////////////////////////////////
       
/*
purpose: displays menu options
*/
void displayMenu(); 

/*
purpose: this function deals the cards to the player in sequential 
* order and returns the number of cards that have been dealt
*/
void dealToPlayers( Queue<player> &, List<card> & );
               
/*
purpose: this function gives the user the ability to choose a player 
* and sort their hand. it prompts the user for player & sort type and
* then it sorts that players hand.
*/            
void sortPlayersHand( Queue <player> & );
       
////////////////////////////////////////////////////////////////////////
//////////////////////////// MAIN FUNCTION /////////////////////////////
////////////////////////////////////////////////////////////////////////

int main()
{
	// intialize variables 
		
		// intialize srand for random numbers
		srand( time( NULL ) );
		
		// decks
		List <card> unshuffled;
		List <card> shuffled;
		
		Stack <card> draw( 94 );
		Stack <card> discard;
		
		// players
		player tempPlayer;
		Queue <player> playersInGame;
		
		game unoGame;
		
		// files
		ifstream finDeck;
		ifstream finPlayer;
		
		char* deckFile = new char [ STR_LEN ];
		char* playerFile = new char [ STR_LEN ];

		// misc
		char userMenuChoice;
		int numberOfPlayers;
		card tempCard;
    
    // tests used in program
    
       // menu loop
	   bool continueProgram = true;
	   
	   // prevents user from manipulating 
	   // deck if deck has not been input
	   bool choiceFlag = true;
	   
	   // prevents user from dealing cards
	   // if the deck has not been shuffled
	   bool shuffleFlag = true;
	   
	   // prevents user from displaying players
	   // hand if cards have not been dealt
	   bool dealFlag = true;
	   
	   // lets user know deck has been input
	   bool deckInput = false;	
	   
	   // lets user know players have been input
	   bool playerInput = false;	

    // repeat menu until user quits
	do
	{
		// display menu
		displayMenu();
		
		// get users menu selection
		cin >> userMenuChoice;		
		cout << endl;
		
		// switch for menu choices
		switch( userMenuChoice )
		{
			// case one: input the deck
			case '1':
			
				// if deck has already been input inform user
				if( deckInput )
				{
					cout << "::DECK HAS ALREADY BEEN INPUT::" << endl 
					     << endl;
				}
				
				// else input the deck
				else
				{					
					// prompt user for input file name
					cout << "PLEASE ENTER THE NAME OF THE INPUT FILE: ";
					cin >> deckFile;
					
					cout << endl;
					
					finDeck.clear();
					finDeck.open( deckFile );				
					
					// if file open proceed to read in deck
					if( finDeck.good() )
					{
					    // inform user that information processing 
						cout << "...READING IN DECK..." << endl << endl;
						
						// read in cards from file
						for( int i = 0; i < MAX_CARDS; i++ )
						{
							finDeck >> tempCard;
							tempCard = "unshuffled";
							unshuffled.insertAfter( tempCard );
						}
						
						unshuffled.gotoBeginning();
					
						// change flags accordingly
						// it is now okay to manipulate deck
						// as well as warn user deck is already input
						deckInput = true;
						choiceFlag = false;
						
						finDeck.close();
					}
					
					// else file not found warning & must try again
					else
					{
						cout << "ERROR: FILE NOT FOUND" << endl << endl;
						choiceFlag = true;
					}
				
				}
   
		    // break statement
		    break;
		    
		    // case two: input the players
		    case '2':
		    
		        // if players are already input warn user
				if( playerInput )
				{
					cout << "::PLAYERS HAVE ALREADY BEEN INPUT::" 
					     << endl << endl;
				}
				
				// else read in players
				else
				{
					// prompt user for input file name
					cout << "PLEASE ENTER THE NAME OF THE INPUT FILE: ";
					cin >> playerFile;
					
					finPlayer.clear();
					finPlayer.open( playerFile );
					
					cout << endl;

					// if file is good proceed to read in players
					if( finPlayer.good() )
					{
						// ask user until number of players
						// within the range is given
						do
						{
						cout << "PLEASE ENTER THE NUMBER OF PLAYERS: ";
						cin >> numberOfPlayers;	
						}while( numberOfPlayers < 2 || numberOfPlayers > 10 );
						
						cout << endl;
						
						// inform user that information processing
						cout << "...READING IN PLAYERS..." << endl 
						     << endl;
						
						// read in players from file
						for( int i = 0; i < numberOfPlayers; i++ )
						{
							finPlayer >> tempPlayer;
							playersInGame.enqueue( tempPlayer );
						}       
						   
						playerInput = true;
						
						finPlayer.close();
					}
					
					// else file not found & must try again
					else
					{
						cout << "ERROR: FILE NOT FOUND" << endl << endl;
					}
					
				}
				
				// break statement
				break;
			
			// case three: shuffle the deck
			case '3':
			
			    // if no deck is input warn user can't shuffle deck
				if( choiceFlag )
				{
					cout << "::PLEASE INPUT DECK TO SHUFFLE DECK::" 
					     << endl << endl;
				}
				
			    // else shuffle the deck
				else
				{
					if( dealFlag )
					{
						// inform user that information processing
						cout << "...SHUFFLING DECK..." << endl << endl;
						
						if( shuffleFlag )
						{
							// move unshuffled deck to shuffled deck
							for( int i = 0; i < MAX_CARDS; i++ )
							{
								unshuffled.getCursor( tempCard );
								unshuffled.gotoNext();
								tempCard = "shuffled";
								shuffled.insertAfter( tempCard );
							}
							
							unshuffled.gotoBeginning();
							shuffled.gotoBeginning();
						}

						for( int i = 0; i < 1000; i++ )
						{	
							shuffled.shuffleList();
						}
						
						shuffleFlag = false;
					}
					else
					{
						cout << "ERROR: CARDS HAVE ALREADY BEEN DEALT " << endl;
						cout << "::CANNOT SHUFFLE THE DECK::" << endl << endl;
					}
				}
			
			    // break statement
				break;	

			// case four: deal the cards
			case '4': 
			
			    // if no deck is input warn user can't output deck
				if( !playerInput || shuffleFlag )
				{
					cout << "::PLEASE INPUT PLAYERS/SHUFFLE DECK TO DEAL CARDS::" 
					     << endl << endl;
				}

				// if deck has been input & deck has been shuffled
				// then go again and deal the cards
				else if( deckInput && !shuffleFlag && playerInput )
				{
					// if cards have been dealt do not deal again 
					if( dealFlag )
					{
						// inform user that information processing
						cout << "...DEALING THE CARDS..." << endl 
							 << endl;
							 
						dealToPlayers( playersInGame, shuffled );
						
						while( !shuffled.empty() )
						{
							shuffled.remove( tempCard );
							tempCard = "draw";
							draw.push( tempCard );
						} 
						
						////////////game startGame( playersInGame, draw );                 
						
						dealFlag = false;
					}
					
					// else tell user cards have bene dealt
					else
					{
						cout << "::CARDS HAVE ALREADY BEEN DEALT::" 
						     << endl << endl;
					}						
					
				}					
				
				// break statement
				break;	
				
			// case five: start the game
			case '5':
			
				if( !shuffleFlag && !dealFlag )
				{
					unoGame.startGame( playersInGame, draw );
					
					unoGame.mainGame();
					
					unoGame.endGame();
					
					continueProgram = false;
				}
				else
				{
					cout << "ERROR: CANNOT START GAME PLEASE ENTER PLAYER'S/CARDS" << endl << endl;
				}
			
			    // break statement
				break;										

			// case six: quit the program
			case '6':

				// thank user for using the program
				cout << "THANK YOU FOR USING THE PROGRAM!" << endl 
				     << endl;
				
				// change continue flag to exit do/while loop
				continueProgram = false;
			
			    // break statement
				break;
	
			// default case for invalid input
			default:
			
				cout << "ERROR: PLEASE ENTER CHOICE AGAIN!" << endl
				     << endl;
				
				// break statement
				break;
			
		}
	}while( continueProgram ); // end of loop

	return 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////// FUNCTION IMPLEMENTATIONS ////////////////////////
////////////////////////////////////////////////////////////////////////

void displayMenu()
{
	cout << "..::WELCOME TO UNO::.." << endl << endl;
	
	cout << "1. INPUT THE DECK " << endl;
	cout << "2. INPUT THE PLAYERS " << endl;
	cout << "3. SHUFFLE THE DECK " << endl;
	cout << "4. DEAL CARDS" << endl;
	cout << "5. START GAME" << endl;
	cout << "6. QUIT PROGRAM " << endl << endl;
	
	cout << "PLEASE SELECT A NUMBER CHOICE: ";
}                  

void dealToPlayers( Queue<player> &source, List<card> &shuffled )
{
	// initialize varibles
	List <card> cardsNeededToBeDealt;
	player* playerPointer = new player[ 10 ];
	card tempCard;
	
	int numberOfPlayers = 0;
	
	while( !source.empty() )
	{
		source.dequeue( playerPointer[ numberOfPlayers ] );
		numberOfPlayers++;
	}
	
	List<card>* tempHands = new List<card>[ numberOfPlayers ];
	
	for( int i = 0; i < ( numberOfPlayers * 7 ); i++ )
	{
		shuffled.remove( tempCard );
		cardsNeededToBeDealt.insertAfter( tempCard );
	}
	
	cardsNeededToBeDealt.gotoBeginning();
	
	for( int i = 0; i < 7; i++ )
	{
		for( int j = 0; j < numberOfPlayers; j++ )
		{
			cardsNeededToBeDealt.remove( tempCard );
			tempCard = playerPointer[ j ].getName();
			tempHands[ j ].insertAfter( tempCard );
		}
	}	
	
	for( int i = 0; i < numberOfPlayers; i++ )
	{	
		playerPointer[ i ].setHand( tempHands[ i ] );
	}
	
	for( int i = 0; i < numberOfPlayers; i++ )
	{
		source.enqueue( playerPointer[ i ] );
	}
	
	delete[]playerPointer;
	playerPointer = NULL;
}

