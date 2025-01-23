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
* <file with definitions of the functions used for the project>
*
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GoFish_Declarations.h"

const int CARDS_PER_PLAYER = 6;
const int MIN_SIZE_ASK = 5;
const int MIN_SIZE_GIVE = 6;
const int MIN_SIZE_COLLECT = 9;
int PLAYER_DRAWN_CARD;
int COMPUTER_DRAWN_CARD;
string command;

int countCards(const vector<int>& data)
{
    int total = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        total += data[i];
    }
    return total;
}

void dealCards(Player& player, Player& computer, vector<int>& deck) 
{
    for (int i = 0; i < CARDS_PER_PLAYER; i++) 
    {
        drawCard(player, deck, PLAYER_DRAWN_CARD);
        drawCard(computer, deck, COMPUTER_DRAWN_CARD);
    }
}

void printHand(const Player& player) 
{
    cout << "Your cards: \n";
    for (int i = 0; i < TOTAL_POWERS; i++) 
    {
        if (player.hand[i] > 0) 
        {
            cout << i + 2 << " (" << player.hand[i] << ") ";
        }
    }
    cout << endl;
}

void printCollected(const Player& player) 
{
    cout << "Collected:";
    for (int i = 0; i < TOTAL_POWERS; i++) 
    {
        if (player.collected[i] == 1) 
        {
            cout << i + 2 << " ";
        }
    }
    cout << endl;
}

void playerTurn(Player& player, Player& computer, vector<int>& deck) 
{
    clearConsole();

    cout << "It's your turn!\n";

    while (!isPartOneOver(player, computer))
    {
      
        if ((countCards(deck) != 0) && (countCards(player.hand) == 0))
        {
            cout << "You have no cards left. Draw one from the deck...\n";

            while (true)
            {
                getline(cin, command);

                if (command == "draw")
                {
                    drawCard(player, deck, PLAYER_DRAWN_CARD);
                    break;
                }
                else
                {
                    cout << "Invalid input! Try again.\n";
                }
            }
            continue;
        }
     
        printHand(player);

        cout << "Enter a command: ";
        
        getline(cin, command);

        if (command.find("ask") == 0 && command.size() >= MIN_SIZE_ASK)
        {
            int power = extractNumber(command, MIN_SIZE_ASK);

            if (power < 0 || power >= TOTAL_POWERS || player.hand[power] == 0) 
            {
                cout << "Invalid input. Try again.\n";
                continue;
            }

            if (computer.hand[power] > 0) 
            {
                cout << "The computer gave you " << computer.hand[power] << " card(s) of power " << power + 2 << ".\n";
                player.hand[power] += computer.hand[power];
                computer.hand[power] = 0;

                continue;
            }
            else 
            {
                cout << "Go fish!\n" << "Please draw.\n";

                while (true)
                {
                    getline(cin, command);

                    if (command == "draw") 
                    {
                        drawCard(player, deck, PLAYER_DRAWN_CARD);
                        break;
                    }
                    else
                    {
                        cout << "Invalid input! Try again.\n";
                    }
                }
                if (PLAYER_DRAWN_CARD == power)
                {
                    cout << "You drew same card! Your turn continues.\n";
                    continue;
                }
                break;

            }
        }
        else if (command.find("collect") == 0 && command.size() >= MIN_SIZE_COLLECT)
        {
            int power = extractNumber(command, MIN_SIZE_COLLECT);

            if (power < 0 || power >= TOTAL_POWERS)
            {
                cout << "Invalid input. Try again.\n";
                continue;
            }

            if (checkAndCollect(player, power)) 
            {
                cout << "You collected all cards of power " << power + 2 << "!\n";
            }
            else
            {
                cout << "You don't have all cards of this power yet.\n";
            }
        }
        else
        {
            cout << "Invalid command. Try again.\n";
        }
    }
}

void computerTurn(Player& computer, Player& player, vector<int>& deck) 
{
    clearConsole();
    printHand(player);

    cout << "The computer's turn...\n";

    while (!isPartOneOver(player, computer))
    {
        
        if ((countCards(deck) != 0) && (countCards(computer.hand) == 0))
        {
            cout << "The computer has no cards left. It draws one from the deck...\n";
            drawCard(computer, deck, COMPUTER_DRAWN_CARD);
            continue;
        }

        if (checkAndCollect(computer, COMPUTER_DRAWN_CARD))
        {
            cout << "The computer collected all cards of power " << COMPUTER_DRAWN_CARD + 2 << "!\n";
        }

        

        int power = rand() % TOTAL_POWERS;   //Choose random card for the computer to ask
        if (computer.hand[power] == 0)      //Check if the computer has the card first
        {
            continue;
        }

        cout << "The computer asks for cards of power " << power + 2 << ".\n";

        if (player.hand[power] > 0) 
        {
            while (true)
            {
                getline(cin, command);
                if (command.find("give") == 0 && command.size() >= MIN_SIZE_GIVE)
                {
                    int givenPower = extractNumber(command, MIN_SIZE_GIVE);

                    if (givenPower < 0 || givenPower >= TOTAL_POWERS)
                    {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }

                    if (givenPower == power)
                    {
                        cout << "You gave " << player.hand[power] << " card(s) of power " << power + 2 << ".\n";
                        computer.hand[power] += player.hand[power];
                        player.hand[power] = 0;
                        printHand(player);
                        break;
                    }
                    else
                    {
                        cout << "Invalid input! Try again.\n";
                    }
                }
                else
                {
                    cout << "Invalid input! Try again.\n";
                }
            }

            if (checkAndCollect(computer, power)) 
            {
                cout << "The computer collected all cards of power " << power + 2 << "!\n";
            }
        }
        else
        {
            while (true)
            {
                getline(cin, command);
                if (command == "go fish")
                {
                    drawCard(computer, deck, COMPUTER_DRAWN_CARD);

                    break;
                }
                else
                {
                    cout << "Invalid input! Try again!\n";
                }
            }
            if (COMPUTER_DRAWN_CARD == power)
            {
                cout << "The computer drew same card! Computer's turn continues.\n";
                continue;
            }
            break;  // End the computer's turn 
        }
    }
}

void drawCard(Player& player, vector<int>& deck, int& drawnCard)
{
    if (deck.empty())
    {
        cout << "There are no cards in the deck!\n";
        return;
    }
    while (true)
    {
        int card = rand() % TOTAL_POWERS;
        if (deck[card] != 0)
        {
            drawnCard = card;
            player.hand[card]++;
            deck[card]--;
            break;
        }

    }
}

bool checkAndCollect(Player& player, int power) 
{
    if (player.hand[power] == 4) 
    {
        player.hand[power] = 0;
        player.collected[power] = 1;
        return true;
    }
    return false;
}

bool isPartOneOver(const Player& player, const Player& computer)
{
    return countCollected(player.collected) + countCollected(computer.collected) == TOTAL_POWERS;
}

int countCollected(const vector<bool>& data) 
{
    int total = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i])
        {
            total += 1;
        }
    }
    return total;
}

void playerTurnPartTwo(Player& player, Player& computer, vector<int>& deck)
{
    clearConsole();

    while (countCollected(player.collected) != TOTAL_POWERS) 
    {
        cout << "Enter a command: ";

        getline(cin, command);

        if (command.find("ask") == 0 && command.size() >= MIN_SIZE_ASK)
        {
            int power = extractNumber(command, MIN_SIZE_ASK);

            if (power < 0 || power >= TOTAL_POWERS) 
            {
                cout << "Invalid input. Try again.\n";
                continue;
            }

            if (computer.collected[power] == 1 )
            {
                cout << "The computer gave you " << power + 2 << "'s.\n";
                player.collected[power] = 1;
                computer.collected[power] = 0;
            }
            else
            {
                cout << "Go fish!\n";
                break;
            }
          
        }
        else
        {
            cout << "Invalid input! Try again.\n";
        }
    }
}

void computerTurnPartTwo(Player& computer, Player& player, vector<int>& deck)
{
    clearConsole();

    while (countCollected(computer.collected) != TOTAL_POWERS)
    {
        printCollected(player);

        int power = rand() % TOTAL_POWERS;
 
        cout << "The computer asks for cards of power " << power + 2 << ".\n";

        if (player.collected[power] == 1)
        {
            while (true)
            {
                getline(cin, command);
                if (command.find("give") == 0 && command.size() >= MIN_SIZE_GIVE)
                {
                    int givenPower = extractNumber(command, MIN_SIZE_GIVE);

                    if (givenPower < 0 || givenPower >= TOTAL_POWERS)
                    {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }

                    if (givenPower == power)
                    {
                        cout << "You gave to the computer " << power + 2 << "'s.\n";
                        computer.collected[power] = 1;
                        player.collected[power] = 0;
                        break;
                    }
                    else
                    {
                        cout << "Invalid input! Try again.\n";
                    }
                }
                else
                {
                    cout << "Invalid input! Try again.\n";
                }
            }
        }
        else
        {
            while (true)
            {
                getline(cin, command);
                if (command == "go fish")
                {
                    break;
                }
                else
                {
                    cout << "Invalid input! Try again!\n";
                }
            }
            break;
        }

    }
}

bool isGameOver(const Player& player, const Player& computer)
{
    return (countCollected(player.collected) == TOTAL_POWERS || countCollected(computer.collected) == TOTAL_POWERS);
}

int extractNumber(string& command, int minSize)
{
    int power = command[minSize - 1] - '0';  // Extract the first digit of power
    if (command.size() > minSize && command[minSize] >= '0' && command[minSize] <= '9')
    {
        power = power * 10 + (command[minSize] - '0');
    }
    return power -= 2;  // Adjust the power to match the index
}

void clearConsole()
{
    system("cls");
}
