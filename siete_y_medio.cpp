#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

int main() {
	/* --STATEMENTS-- */
	int bet;
	bool win = false;
	bool Bustp = false;
	bool Bustd = false;
	//create player and dealer and give player money
	Player* dude = new Player(100);
	Player* dealer = new Player(1000);
	Hand* dealerH = new Hand();
	Hand* dudeH = new Hand();

	//game loop
	while ((*dude).change() != 0 || (*dealer).change() > 100) {
		//Ask player for bet
		cout << "How much money are you going to bet? \n";
		cin >> bet;

		//deal cards
		(*dealerH).give();
		(*dudeH).give();

		//show cards
		cout << "Your cards are: \n";
		(*dudeH).show();

		string answer;

		//ask player if they want another card, while loop 
		cout << "Would you like another card? (y/n) \n";
		cin >> answer;
		//round loop
		while (answer == "y" && (*dudeH).count() <= 7.5) {
			(*dudeH).give();
			cout << "Your cards are: \n";
			(*dudeH).show();
			cout << "Would you like another card? (y/n) \n";
			cin >> answer;
		}

		string answerd;
		while (answerd == "y") {
			(*dealerH).give();
			if ((*dealerH).count() < 5.5)
				answerd = "y";
			else
				answerd = "n";
		}

		//vector subscript out of range
		if ((*dudeH).count() > 7.5)
			Bustp = true;
		cout << "got past player bust. \n"; 

		if ((*dealerH).count() > 7.5)
			Bustd = true;

		cout << "got passed the bust if statements. \n"; 

		//show everyones hand 
		cout << "The dealer has: \n";
		(*dealerH).show();
		cout << "You have: \n";
		(*dudeH).show();

		//game outcome
		//1. if player is closer to dealer to 7.5 or the dealer busts and the player does not, player wins 
		if ((Bustd && !Bustp) || (*dudeH).count() > ((*dealerH).count() && !Bustp)) {
			cout << "You win the round! \n";
			(*dude).exchange(bet);
			(*dealer).exchange(-bet);
			cout << "Yor now have " << (*dude).change() << " dollars. \n";
		}
		//2. if dealer is closer to 7.5, or the player busts, dealer wins
		else if ((!Bustd && Bustp) || (*dudeH).count() < ((*dealerH).count() && !Bustd)) {
			cout << "You lose the round. \n"; 
			(*dude).exchange(-bet);
			(*dealer).exchange(bet);
			cout << "You now have " << (*dude).change() << " dollars. \n";
		}
			//3. if player and dealer both bust, dealer wins ((house advantage) 
		else if (Bustp && Bustd) {
			cout << "You lose the round. \n";
			(*dude).exchange(-bet);
			(*dealer).exchange(bet);
			cout << "Yor now have " << (*dude).change() << " dollars. \n";
		}
			//4. Both playaer and dealer have the same count, no money is exchanged
		else {
			cout << "It is a tie. You still have " << (*dude).change() << endl; 
		}
		bet = 0; 

		//loop
	}

	if ((*dude).change() == 1000)
		cout << "Congratulations! You won! \n";
	else
		cout << "Sorry, you lose. You're out of money." << endl; 
	delete dude;
	delete dealer;
	delete dealerH; 
	delete dudeH; 

	return 0;
}