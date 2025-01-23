/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Gena Genova
* @idnumber 9MI0600073
* @compiler VC
*
* <file with declarations for the functions used in the project>
*
*/

#pragma once

#include <vector>

using namespace std;

const int TOTAL_POWERS = 13;

struct Player 
{
    vector<int> hand;         // Cards in hand 
    vector<bool> collected;   // Collected sets 
};

int countCards(const vector<int>& data);

// Deal cards to players
void dealCards(Player& player, Player& computer, vector<int>& deck);

// Print the player's hand
void printHand(const Player& player);

// Player's turn
void playerTurn(Player& player, Player& computer, vector<int>& deck);

// Computer's turn
void computerTurn(Player& computer, Player& player, vector<int>& deck);

// Draw a card from the deck
void drawCard(Player& player, vector<int>& deck, int& drawnCard);

// Check and collect cards of a specific power
bool checkAndCollect(Player& player, int power);

// Check if the first part of the game is over
bool isPartOneOver(const Player& player, const Player& computer);

// Count the total number of cards
int countCollected(const vector<bool>& data);

// Print the player's collected sets
void printCollected(const Player& player);

// Player's turn for the second part of the game
void playerTurnPartTwo(Player& player, Player& computer, vector<int>& deck);

// Computer's turn for the second part of the game
void computerTurnPartTwo(Player& computer, Player& player, vector<int>& deck);

// Check if the game is over
bool isGameOver(const Player& player, const Player& computer);

//Extract the number written in the command
int extractNumber(string& command, int minSize);

// Clear the console for cleaner look
void clearConsole();