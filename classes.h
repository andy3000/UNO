#ifndef __CLASSES_H_
#define __CLASSES_H_
#include <iostream>
#include "listP.cpp"
#include "StackP.cpp"
#include "queueP.cpp"

using namespace std;

class card
{
	public:
		
		// constructors
		card( int = -1, const char* = "location" );
		card( const card & );
		~card();
		
		char getColor();
		int getRank();
		
		void operator=( const card & );
		void operator=( const char * );
		
		bool operator==( const char );
		bool operator==( const char * );
		bool operator==( const card & );
		
		bool operator >=( const card & );
		bool operator <=( const card & );
		friend bool operator>( const card &, const card & );
		friend bool operator<( const card &, const card & );
		
		friend ostream& operator<<( ostream &, card & );
		friend ifstream& operator>>( ifstream &, card & );
		
	private:
	
		char color;
		int rank;
		char* action;
		char* location;
	
};

class player
{
	public:
		
		player();
		player( const player & );
		~player();
		
		void setHand( const List<card> & );
		void setCardInHand( card );
		void removeCard( card & );
		
		List<card> getHand();
		char* getName() const;
		
		bool checkIfHandEmpty();
		
		void sortColor();
		void sortRank();
		void sortColorRank();
		
		void operator=( const player & );
		
		friend ostream& operator<<( ostream &, player & );
		friend ifstream& operator>>( ifstream &, player & );
	
	private:
	
		char* name;
		int* id;
		List <card> hand;
};

class game : public player
{
	public:
	
		game();

		void startGame( Queue <player> &, Stack <card> & );
		void mainGame();
		void endGame();
		void displayDiscardPile();
		void displayPlayersHand();
		void displayTurnOptions();
		void playTurn();
		void specialCardAdjustments();
		void sortPlayersHand();
		void createNewDrawPile( Stack <card> & );
		void gameFinished();
		void moveToNextPlayer();
		void moveToPreviousPlayer();
		void selectColorToBeMatched();
		bool drawCardFromDrawPile();
		void selectCardToBePlayed();
		bool playersCardSelection();
		bool checkIfCardQualifedForPlay( card & );
	
	private:
	
		player* playersInGame;
		Stack <card> discardPile;
		Stack <card> drawPile;
		
		char colorToBeMatched;
		
		int numberOfPlayers;
		int currentPlayersTurn;
		
		card topOfDiscardPile;
		card cardSelectedToBePlayed;
		
		bool clockwiseRotation;
		bool specialCardPlayed;
		
		bool gameNotFinished;
		bool cardStatus;
		bool turnNotExecuted;
		
		bool skipFlag;
		bool reverseFlag;
		bool drawTwoFlag;
		bool drawFourFlag;
		bool wildCardFlag;
};

#endif
