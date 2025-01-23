
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
* <file with main function for the project>
*
*/


#include <iostream>
#include <string>
#include "GoFish_Declarations.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Initialize random number generator

    vector<int> deck(TOTAL_POWERS, 4); // Each power starts with 4 cards
    Player player = { vector<int>(TOTAL_POWERS, 0), vector<bool>(TOTAL_POWERS, 0) };
    Player computer = { vector<int>(TOTAL_POWERS, 0), vector<bool>(TOTAL_POWERS, 0) };

    cout << "Go fish!\n" 
        << "Key words:\n" << "deal - start game\n" << "draw - draw card from deck\n" << "ask <power>\n" << "collect <power>\n" 
        << "give <power>\n" << "go fish - you don't have cards from this power\n" 
        << "Notice! Cards J, Q, K, A -> 11, 12, 13, 14!\n";

    string command;
    while (true) 
    {
        getline(cin, command);
        if (command == "deal") 
        {
            dealCards(player, computer, deck);
            break;
        }
        else 
        {
            cout << "Invalid command. Type 'deal' to start the game.\n";
        }
    }

    bool playerTurnFlag = true;  // Player's turn flag

    while (!isPartOneOver(player, computer)) 
    {
        if (playerTurnFlag) 
        {
            playerTurn(player, computer, deck);
            
            playerTurnFlag = false;  // Switch turn to computer
        }
        else 
        {
            computerTurn(computer, player, deck);

            playerTurnFlag = true;  // Switch turn to player
        }
    }

    clearConsole();

    cout << "Key words for the second part of the game:\n" << "go - start second part\n" << "ask <power>\n" << "give <power>\n" << "go fish - you don't have this power\n";

    playerTurnFlag = true;

    while (true)
    {
        getline(cin, command);
        if (command == "go")
        {
            break;
        }
        else
        {
            cout << "Invalid command. Type 'go' to start.\n";
        }
    }

    while (!isGameOver(player, computer))
    {

        if (playerTurnFlag)
        {
            playerTurnPartTwo(player, computer, deck);
           
            playerTurnFlag = false;  // Switch turn to computer
        }
        else
        {
            computerTurnPartTwo(computer, player, deck);
        
            playerTurnFlag = true;  // Switch turn to player
        }
    }

    if (countCollected(player.collected) == TOTAL_POWERS)
    {
        cout << "You are the winner!!!";
    }
    else
    {
        cout << "The computer wins! Better luck next time!";
    }

    return 0;
}


