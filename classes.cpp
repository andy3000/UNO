#include <iostream>
#include <fstream>
#include "classes.h"
#include "stringLibrary.h"

const char NULL_CHAR = '\0';

//////////////////////////////// CARD /////////////////////////////////

card::card( int r, const char* l )
{
	color = 'c';
	rank = r;
	
	action = new char[ 30 ];
	copyString( action, "action" );
	
	location = new char[ 30 ];
	copyString( location, l );
	
}

card::card( const card &c )
{
	if( this != &c )
	{
		color = c.color;
		rank = c.rank;
		
		action = new char[ 30 ];
		copyString( action, c.action );
		
		location = new char[ 30 ];
		copyString( location, c.location );
	}
}

card::~card()
{
	color = NULL_CHAR;
	rank = 0;
	
	delete[]action;
	action = NULL_CHAR;
	
	delete[]location;
	location = NULL_CHAR;
}

char card::getColor()
{
	return color;
}

int card::getRank()
{
	return rank;
}

void card::operator=( const card &c )
{
	if( this != &c )
	{
		color = c.color;
		rank = c.rank;
		copyString( action, c.action );
		copyString( location, c.location );
	}
}

void card::operator=( const char* c )
{
	copyString( location, c );
}

bool card::operator==( const char c )
{	
	if( c == 'c' )
	{
		if( color == c )
		{
			return true;
		}
	}
	else
	{
		if( rank == c )
		{
			return true;
		}
	}
		
	return false;
}

bool card::operator==( const card &c )
{
	return ( color == c.color );
}

bool card::operator==( const char *c )
{
	return compareStrings( action, c );
}

bool operator>( const card &a, const card &b )
{
	return ( a.color > b.color );
}

bool operator<( const card &a, const card &b )
{
	return ( a.color < b.color );
}

bool card::operator >=( const card &c )
{
	return ( rank >= c.rank );
}

bool card::operator <=( const card &c )
{
	return ( rank <= c.rank );
}

ostream& operator<<( ostream &out, card &c )
{
	out << "Color: " << c.color << endl;
	out << "Rank: " << c.rank << endl;
	out << "Action: " << c.action << endl;
	out << "Location: " << c.location << endl;
	
	return out;
}

ifstream& operator>>( ifstream &fin, card &c )
{
	char* tempString = new char[ 30 ];
	
	fin >> tempString;
	
	if( *tempString == 'w' || *tempString == 'W' ||
	    *tempString == 'd' || *tempString == 'D' )
	{
		copyString( c.action, tempString );
		c.color = 'c';
		c.rank = -1;
	}
	else 
	{
		c.color = *tempString;
		
		fin >> tempString;
		
		if( *tempString >= '0' && *tempString <= '9' )
		{
			c.rank = *tempString - '0';
		}
		else
		{
			copyString( c.action, tempString );
			c.rank = -1;
		}
	}
	
	return fin;
}

//////////////////////////// PLAYER /////////////////////////.//////////

player::player()
{	
	card tempCard;
	
	name = new char[ 30 ];
	copyString( name, "name" );
	
	id = new int[ 5 ];
	
	for( int i = 0; i < 5; i++ )
	{
		id[ i ] = 0;
	}
	
	
	for( int i = 0; i < 7; i++ )
	{
		hand.insertAfter( tempCard );
	}
	
	hand.gotoBeginning();
	
}

player::player( const player &source )
{
	card tempCard;
	
	if( this != &source )
	{
		name = new char[ 30 ];
		copyString( name, source.name );
		
		id = new int[ 5 ];
		
		for( int i = 0; i < 5; i++ )
		{
			id[ i ] = source.id[ i ];
		}
		
		hand = source.hand;
		
		hand.gotoBeginning();
	}
}

player::~player()
{	
	delete[]name;
	name = NULL_CHAR;
	
	delete[]id;
	id = NULL_CHAR;
	
	hand.clear();
}

void player::setHand( const List<card> &source )
{
	hand = source;
}

void player::setCardInHand( card source )
{
	hand.insertAfter( source );
}

void player::removeCard( card &source )
{
	hand.remove( source );
}

List<card> player::getHand()
{
	return hand;
}

char* player::getName() const
{
	return name;
}

bool player::checkIfHandEmpty()
{
	return ( hand.empty() );
}

void player::operator=( const player &source )
{
	if( this != &source )
	{
		copyString( name, source.name );
		
		for( int i = 0; i < 5; i++ )
		{
			id[ i ] = source.id[ i ];
		}
		
		hand = source.hand;
	}
}

ostream& operator<<( ostream &out, player &source )
{	
	out << source.hand;
	
	return out;
}

ifstream& operator>>( ifstream &fin, player &source )
{	
	// initialize variables
	char* tempString = new char[ 30 ];
	char number;
		
	fin >> tempString;
	copyString( source.name, tempString );
		
	// read in players ID
	for( int i = 0; i < 5; i++ )
	{
		fin >> number;
		number -= '0';
		
		// number is set to single digit
		source.id[ i ] = number;
	}
	
	delete[]tempString;
	tempString = NULL_CHAR;

	return fin;
}

void player::sortColor()
{
	hand.sortOne();
}

void player::sortRank()
{
	hand.sortTwo();
}

void player::sortColorRank()
{
	hand.sortThree();
}

//////////////////////////// GAME //////////////////////////////////////

game::game()
{
	clockwiseRotation = true;
	gameNotFinished = true;
	
	skipFlag = false;
	reverseFlag = false;
	drawTwoFlag = false;
	drawFourFlag = false;
	wildCardFlag = false;	
	
	currentPlayersTurn = 0;
}

void game::endGame()
{
	drawPile.clear();
	discardPile.clear();
	delete[]playersInGame;
}

void game::startGame( Queue <player> &playerSource, Stack <card> &cardSource )
{
	player* tempPlayers = new player[ 10 ];
	card tempCard;
	numberOfPlayers = 0;
	
	if( playerSource.empty() || cardSource.empty() )
	{
		cout << "ERROR: CANNOT START GAME PLEASE ENTER PLAYER'S/CARDS" << endl << endl;
	}
	else
	{
		while( !playerSource.empty() )
		{
			playerSource.dequeue( tempPlayers[ numberOfPlayers ] );	
			numberOfPlayers++;
		}
		
		playersInGame = new player[ numberOfPlayers ];
		
		for( int i = 0; i < numberOfPlayers; i++ )
		{
			playersInGame[ i ] = tempPlayers[ i ];
		}
		
		while( !cardSource.empty() )
		{
			cardSource.pop( tempCard );
			drawPile.push( tempCard );
		}
		
		drawPile.pop( tempCard );
		
		if( tempCard == "draw4" )
		{
			while( tempCard == "draw4" )
			{
				drawPile.push( tempCard );
				createNewDrawPile( drawPile );
				drawPile.pop( tempCard );
			}
		}
		
		tempCard = "discard";
		
		topOfDiscardPile = tempCard;
		
		discardPile.push( topOfDiscardPile );
		
		colorToBeMatched = topOfDiscardPile.getColor();		
	}
	
	if( topOfDiscardPile == "reverse" )
	{
		cout << "DISCARD PILE STARTED WITH REVERSE!" << endl << endl;
		clockwiseRotation = false;
    }	
	
	// if beginning of game
	if( topOfDiscardPile == "wild" )
	{
		cout << "DISCARD PILE STARTED WITH WILDCARD!" << endl << endl;
		
		// move to next player
		moveToNextPlayer();
	  
		// select new color to be matched
		selectColorToBeMatched();
	}
	
    if( topOfDiscardPile == "skip" )
    {
		cout << "DISCARD PILE STARTED WITH SKIP!" << endl << endl;	
			
		moveToNextPlayer();
	}		
   
	if( topOfDiscardPile == "draw2" )
	{
		cout << "DISCARD PILE STARTED WITH DRAW TWO!" << endl << endl;
			
		// move to next player
		moveToNextPlayer();		
		
	   // draw to cards from draw pile and add to players hand
	   for( int i = 0; i < 2; i++ )
	   {
		   // if draw pile doesnt have enough cards then create new draw pile
		   if( drawPile.empty() )
		   {
			   discardPile.pop( topOfDiscardPile );
			   createNewDrawPile( discardPile );
			   discardPile.push( topOfDiscardPile );
			   colorToBeMatched = topOfDiscardPile.getColor();
		   }
		   
		   drawPile.pop( tempCard );
		   
		   tempCard =  playersInGame[ currentPlayersTurn ].getName();
		   
		   playersInGame[ currentPlayersTurn ].setCardInHand( tempCard );
	   }
	   
	   moveToPreviousPlayer();	   
    }		
	
	delete[]tempPlayers;
}

void game::mainGame()
{   	
	// do-while card has not been played or game has not finished 
	do
	{
		// call players turn option choices menu
		playTurn();
		   
	    // if card is special make neccesary adjustments
		specialCardAdjustments();
		  
	   // check to see if player's hand is empty 
	   if( playersInGame[ currentPlayersTurn ].checkIfHandEmpty() )
	   {
			// if hand is empty then delcare game won & leave game
			gameFinished();
	   }
	   else
	   {
		   // else move to next players turn
		   if( clockwiseRotation )
		   {
			   moveToNextPlayer();
		   }
		   else
		   {
		       moveToPreviousPlayer();
		   }
	   }
	
	}while( gameNotFinished );	   
	// end do-while loop
}

void game::displayDiscardPile()
{
	// if draw pile is empty then create new draw pile
	if( drawPile.empty() )
	{
	   discardPile.pop( topOfDiscardPile );
	   createNewDrawPile( discardPile );
	   discardPile.push( topOfDiscardPile );
	   colorToBeMatched = topOfDiscardPile.getColor();
	}
	// else display discard pile
	else
	{
		if( topOfDiscardPile.getColor() == 'c' )
		{	
			cout << "COLOR NOW TO BE MATCHED: ";
				
			if( colorToBeMatched == 'b' )
			{
				cout << "BLUE" << endl << endl;
			}
			if( colorToBeMatched == 'g' )
			{
				cout << "GREEN" << endl << endl;
			}
			if( colorToBeMatched == 'r' )
			{
				cout << "RED" << endl << endl;
			}
			if( colorToBeMatched == 'y' )
			{
				cout << "YELLOW" << endl << endl;
			}
		}			
			
		// display the top of discard pile card
		cout << "     DISCARD" << endl;
		cout << "===================" << endl;
		cout << topOfDiscardPile;
		cout << "===================" << endl << endl;
    }
}

void game::displayPlayersHand()
{
	cout << playersInGame[ currentPlayersTurn ];
}

void game::displayTurnOptions()
{
	cout << "================================" << endl;
	cout << "::TURN OPTIONS::" << endl << endl;
	
	cout << "1. DISPLAY HAND & DISCARD PILE" << endl;
	cout << "2. SORT HAND" << endl;
	cout << "3. SELECT CARD" << endl;
	cout << "4. DRAW CARD" << endl << endl;

	cout << "================================" << endl << endl;
	cout << "PLEASE MAKE A CHOICE: ";
}

void game::playTurn()
{
	int menuChoice;

	do
	{
		cout << "CURRENT PLAYERS TURN: " 
		<< playersInGame[ currentPlayersTurn ].getName() << endl << endl;
						   
		// display menu choice options
		displayTurnOptions();
		   
		cin >> menuChoice;	
			
		if( menuChoice < 1 || menuChoice > 3 )
		{
			cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
		}
		
		if( menuChoice == 1 )
		{
			// display display the current card on discard pile
			   // function: displayDiscardPile
			   displayDiscardPile();
			
			// display player's hand
			   // function: displayPlayersHand
			   displayPlayersHand();
		}
		
		// player has option to sort hand
		   // function: sortPlayersHand
		if( menuChoice == 2 )
		{
			sortPlayersHand();
		}		
	}
	while( menuChoice < 3 || menuChoice > 4 );		   

	// select card that player wants played
	   // function: selectCardToBePlayed
	if( menuChoice == 3 )
	{
		selectCardToBePlayed();
	}

	// draw cards from the draw pile
	   // function: drawCardFromDrawPile
	if( menuChoice == 4 )
	{
		drawCardFromDrawPile();
	}	   
}

bool game::drawCardFromDrawPile()
{
	card tempCard;
	int playerChoice;
	
	do
	{
		cout << "CURRENT PLAYERS TURN: " 
		<< playersInGame[ currentPlayersTurn ].getName() << endl << endl;
		
		// display display the current card on discard pile
		   // function: displayDiscardPile
		   displayDiscardPile();	
		
		// draw card to a temp hand
		drawPile.pop( tempCard );
		tempCard = playersInGame[ currentPlayersTurn ].getName();
				
		// display sort options
		do
		{					
			cout << "================================" << endl;
			cout << "::DRAW OPTIONS::" << endl << endl;
			
			displayDiscardPile();
			
			cout << "    CARD DRAWN" << endl;
			cout << "===================" << endl;
		    cout << tempCard;
		    cout << "===================" << endl << endl << endl;
			
			cout << "1. PLAY CARD" << endl;
			cout << "2. DRAW ANOTHER CARD" << endl << endl;

			cout << "================================" << endl << endl;
			
			cout << "PLEASE MAKE A CHOICE: ";
			cin >> playerChoice;
			
			cout << endl;
			
			if( playerChoice < 1 || playerChoice > 2 )
			{
				cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
			}
		}
		while( playerChoice < 1 || playerChoice > 2 );		
			 
		// if player wants to play card
		if( playerChoice == 1 )
		{
			// check if card is qualified for player
		       // function: checkIfCardQualifedForPlay
		       cardStatus = checkIfCardQualifedForPlay( tempCard );
		       
			if( cardStatus )
			{
				turnNotExecuted = false;
			}	
			else
			{
				cout << "ERROR: CARD NOT PLAYABLE!" << endl;
			}	       
		}
		
		playersInGame[ currentPlayersTurn ].setCardInHand( tempCard );
		   
	}while( turnNotExecuted );
	
	playersInGame[ currentPlayersTurn ].removeCard( topOfDiscardPile );
	topOfDiscardPile = "discard";
	discardPile.push( topOfDiscardPile );
	
	if( topOfDiscardPile.getColor() != 'c' )
	{
		colorToBeMatched = topOfDiscardPile.getColor();
	}
	
	return turnNotExecuted;
}
	
void game::selectCardToBePlayed()
{
	int playerChoice;
	
	// display display the current card on discard pile
	   // function: displayDiscardPile
	   displayDiscardPile();
	
	// display player's hand
	   // function: displayPlayersHand
	   displayPlayersHand();	
	
   turnNotExecuted = playersCardSelection();
   
   if( turnNotExecuted )
   {
	   cout << "ERROR: CAN'T PLAY CARD! " << endl; 
   	
		do
		{
			do
			{	
				cout << "================================" << endl;
				cout << "::HAND OPTIONS::" << endl << endl;
				
				cout << "1. DISPLAY HAND & DISCARD PILE" << endl;
				cout << "2. SELECT A CARD" << endl;
				cout << "3. DRAW A CARD" << endl << endl;

				cout << "================================" << endl << endl;
				
				cout << "PLEASE MAKE A CHOICE: ";
				cin >> playerChoice;
				
				cout << endl;
				
				if( playerChoice < 1 || playerChoice > 3 )
				{
					cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
				}
			}
			while( playerChoice < 1 || playerChoice > 3 );
			
			if( playerChoice == 1 )
			{
				// display display the current card on discard pile
				   // function: displayDiscardPile
				   displayDiscardPile();
				
				// display player's hand
				   // function: displayPlayersHand
				   displayPlayersHand();				
			}
			if( playerChoice == 2 )
			{
				// display display the current card on discard pile
				   // function: displayDiscardPile
				   displayDiscardPile();
				
				// display player's hand
				   // function: displayPlayersHand
				   displayPlayersHand();			
				
				// get players card selection
				   // function: playersCardSelection
				   turnNotExecuted = playersCardSelection();
				   
				   if( turnNotExecuted )
				   {
					   cout << "ERROR: CAN'T PLAY CARD! " << endl; 
				   }
			}
			if( playerChoice == 3 )
			{
				turnNotExecuted = drawCardFromDrawPile();
			}
			
		}while( turnNotExecuted );
		
	}
	
	turnNotExecuted = true;
}

bool game::playersCardSelection()
{
	List <card> tempHand = playersInGame[ currentPlayersTurn ].getHand();
	card tempCard;
	
	int cardSelection;
	int cardCount = 1;
	
	tempHand.gotoBeginning();
	
	while( tempHand.gotoNext() )
	{
		cardCount++;
	}
	
	tempHand.gotoBeginning();
	
	do
	{		
		cout << "PLEASE SELECT A CARD OR PUSH ZERO TO DRAW CARD: ";
		cin >> cardSelection;
		
		if( cardSelection < 0 || cardSelection > cardCount )
		{
			cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
		}
	}
	while( cardSelection < 0 || cardSelection > cardCount );
		    
	if( cardSelection == 0 )
	{
		turnNotExecuted = drawCardFromDrawPile();
		return turnNotExecuted;
	}
		
	for( int i = 0; i < ( cardSelection - 1 ); i++ )
	{
		tempHand.gotoNext();
	}
	
	tempHand.getCursor( tempCard );
	
	// check if card is qualified for player
	cardStatus = checkIfCardQualifedForPlay( tempCard );

	if( cardStatus )
	{
		tempHand.remove( topOfDiscardPile );
		topOfDiscardPile = "discard";
		discardPile.push( topOfDiscardPile );
		
		if( topOfDiscardPile.getColor() != 'c' )
		{
			colorToBeMatched = topOfDiscardPile.getColor();
		}
		
		playersInGame[ currentPlayersTurn ].setHand( tempHand );
		return false;
	}

	return true;
}

void game::specialCardAdjustments()
{
	card tempCard;
	
	// if skip flag true
	if( skipFlag )
	{
		if( clockwiseRotation )
		{
			// increment players turn
			moveToNextPlayer();
		}
		else
		{
			moveToPreviousPlayer();
		}
    }
	// if drawTwo flag true
	if( drawTwoFlag )
	{
		if( clockwiseRotation )
		{
			// increment players turn
			moveToNextPlayer();
		}
		else
		{
			moveToPreviousPlayer();
		}	
		
	   // draw to cards from draw pile and add to players hand
	   for( int i = 0; i < 2; i++ )
	   {
		   // if draw pile doesnt have enough cards then create new draw pile
		   if( drawPile.empty() )
		   {
			   discardPile.pop( topOfDiscardPile );
			   createNewDrawPile( discardPile );
			   discardPile.push( topOfDiscardPile );
			   colorToBeMatched = topOfDiscardPile.getColor();
		   }
		   
		   drawPile.pop( tempCard );
		   
		   tempCard =  playersInGame[ currentPlayersTurn ].getName();
		   
		   playersInGame[ currentPlayersTurn ].setCardInHand( tempCard );
	   }
    } 
	// if reverse flag true
	if( reverseFlag )
	{
	   if( clockwiseRotation )
	   {
		   clockwiseRotation = false;
	   } 
	   else
	   {
		   clockwiseRotation = true;
	   }
    }
	// if wild card flag true
	if( wildCardFlag )
	{
		selectColorToBeMatched();
	}
    // if drawFour flag true
    if( drawFourFlag )
    {
		if( clockwiseRotation )
		{
			// increment players turn
			moveToNextPlayer();
		}
		else
		{
			moveToPreviousPlayer();
		}	
		
	   // draw to cards from draw pile and add to players hand
	   for( int i = 0; i < 4; i++ )
	   {
		   // if draw pile doesnt have enough cards then create new draw pile
		   if( drawPile.empty() )
		   {
			   discardPile.pop( topOfDiscardPile );
			   createNewDrawPile( discardPile );
			   discardPile.push( topOfDiscardPile );
			   colorToBeMatched = topOfDiscardPile.getColor();
		   }
		   
		   drawPile.pop( tempCard );
		   
		   tempCard =  playersInGame[ currentPlayersTurn ].getName();
		   
		   playersInGame[ currentPlayersTurn ].setCardInHand( tempCard );
	   }		
    }
	// set all flags back to false
	skipFlag = false;
	reverseFlag = false;
	drawTwoFlag = false;
	drawFourFlag = false;
	wildCardFlag = false;
}

void game::createNewDrawPile( Stack <card> &source )
{
	List <card> tempDeck;
	card tempCard;
	
   // set top of discard pile to top of discard pile card
   
   // pop all cards into a temp deck list
   while( !source.empty() )
   {
	   source.pop( tempCard );
	   tempCard = "draw";
	   tempDeck.insertAfter( tempCard );
   }
   
   // shuffle the cards
   for( int i = 0; i < 1000; i++ )
   {
	   tempDeck.shuffleList();
   }
   
   tempDeck.gotoBeginning();
   
   // push list into draw pile
   while( !tempDeck.empty() )
   {
	   tempDeck.remove( tempCard );
	   drawPile.push( tempCard );
   }
}

bool game::checkIfCardQualifedForPlay( card &source )
{
	List <card> tempHand = playersInGame[ currentPlayersTurn ].getHand();
	card tempCard;
	
	if( source == "skip" )
	{
		if( topOfDiscardPile == "skip" )
		{
			skipFlag = true;
			return true;
		}
		
		skipFlag = true;
	}
	if( source == "draw2" )
	{
		if( topOfDiscardPile == "draw2" )
		{
			drawTwoFlag = true;
			return true;
		}
		
		drawTwoFlag = true;
	}
	if( source == "reverse" )
	{
		if( topOfDiscardPile == "reverse" )
		{
			reverseFlag = true;
			return true;
		}
		
		reverseFlag = true;
	}
	if( source == "wild" )
	{
		wildCardFlag = true;
		return true;
	}
	// if drawFour is selected then check to see if
	// player doesn't have any cards with colors to be matched	
	if( source == "draw4" )
	{		
		// move cursor to first card
		tempHand.gotoBeginning();
		
		tempHand.getCursor( tempCard );
		
		if( tempCard.getColor() == colorToBeMatched )
		{
			if( tempCard.getColor() != 'c' )
			{			
				cout << "ERROR: CAN'T PLAY DRAW FOUR BECAUSE ";
				cout << "THERE IS A PLAYABLE CARD IN HAND!" << endl;
				return false;
			}
		}		
		
		while( tempHand.gotoNext() )
		{
			tempHand.getCursor( tempCard );
			
			if( tempCard.getColor() == colorToBeMatched )
			{
				if( tempCard.getColor() != 'c' )
				{					
					cout << "ERROR: CAN'T PLAY DRAW FOUR BECAUSE ";
					cout << "THERE IS A PLAYABLE CARD IN HAND!" << endl;
					return false;
				}
			}			
		}
		
		selectColorToBeMatched();
		drawFourFlag = true;
		return true;

	}
	// else check if to be played matches rank or color
	else
	{
		if( source.getColor() == colorToBeMatched )
		{
			return true;
		}
		if( source.getRank() == topOfDiscardPile.getRank() )
		{
			if( source.getRank() != -1 )
			{
				return true;
			}
		}
	}
	
	return false;
}

void game::sortPlayersHand()
{	
	// initialize variables
	int sortType;

		// display sort options
		do
		{
			displayPlayersHand();					
			
			cout << "================================" << endl;
			cout << "::SORT OPTIONS::" << endl << endl;
			
			cout << "1. COLOR" << endl;
			cout << "2. RANK" << endl;
			cout << "3. COLOR & RANK" << endl << endl;

			cout << "================================" << endl << endl;
			cout << "PLEASE CHOOSE SORT TYPE: ";
			cin >> sortType;
			
			if( sortType < 1 || sortType > 3 )
			{
				cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
			}
		}
		while( sortType < 1 || sortType > 3 );
		
		cout << endl;
		
		if( sortType == 1 )
		{
			playersInGame[ currentPlayersTurn ].sortColor();
		}
		
		if( sortType == 2 )
		{
			playersInGame[ currentPlayersTurn ].sortRank();
		}
		
		if( sortType == 3 )
		{
			playersInGame[ currentPlayersTurn ].sortColorRank();
		}
	
	cout << endl << endl;
}

void game::moveToNextPlayer()
{
	currentPlayersTurn++;
	currentPlayersTurn = currentPlayersTurn % numberOfPlayers;
}

void game::moveToPreviousPlayer()
{
	currentPlayersTurn--;
	
	if( currentPlayersTurn == -1 )
	{
		currentPlayersTurn = numberOfPlayers;
		currentPlayersTurn--;
	}
	
	currentPlayersTurn = currentPlayersTurn % numberOfPlayers;
}

void game::selectColorToBeMatched()
{
	int playerChoice;
	
	do
	{		
		cout << "================================" << endl;
		cout << "::COLOR OPTIONS::" << endl << endl;
		
		cout << "1. BLUE" << endl;
		cout << "2. GREEN" << endl;
		cout << "3. RED" << endl;
		cout << "4. YELLOW" << endl << endl;

		cout << "================================" << endl << endl;
		cout << "PLEASE CHOOSE COLOR: ";
		cin >> playerChoice;
		
		if( playerChoice < 1 || playerChoice > 4 )
		{
			cout << "ERROR: PLEASE CHOOSE AGAIN!" << endl << endl;
		}
	}
	while( playerChoice < 1 || playerChoice > 4 );
	
	if( playerChoice == 1 )
	{
		colorToBeMatched = 'b';
	}
	if( playerChoice == 2 )
	{
		colorToBeMatched = 'g';
	}
	if( playerChoice == 3 )
	{
		colorToBeMatched = 'r';
	}
	if( playerChoice == 4 )
	{
		colorToBeMatched = 'y';
	}
	
	cout << "COLOR NOW TO BE MATCHED: ";
	
	if( colorToBeMatched == 'b' )
	{
		cout << "BLUE" << endl;
	}
	if( colorToBeMatched == 'g' )
	{
		cout << "GREEN" << endl;
	}
	if( colorToBeMatched == 'r' )
	{
		cout << "RED" << endl;
	}
	if( colorToBeMatched == 'y' )
	{
		cout << "YELLOW" << endl;
	}		
}

void game::gameFinished()
{
	cout << "CONGRATULATIONS " << playersInGame[ currentPlayersTurn ].getName()
	     << "! YOU HAVE WON THE GAME!" << endl;
	gameNotFinished = false;
}
