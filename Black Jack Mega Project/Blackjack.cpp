#include "Blackjack.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace Blackjack;

void Blackjack::start() {

    int total_betting_money;
    int card_number;
    int card_number_player[21];
    int card_type;
    std::string card_identifier_str;
    std::string point_updater;
    int player_points;
    int dealer_points;
    int bet;
    std::string card_1_str;
    std::string card_2_str;
    int choice;
    int i;
    int x;
    char proceed[20];

    Blackjack::introduction_dialogue();

    std::cout << "How much money are you planning on betting today?";
    std::cout << '\n' << '\n' << "Total betting money: $";
    std::cin >> total_betting_money;

    clear_screen(0, 0);

    while (total_betting_money > 0) {

        std::cout << "\n";
        std::cout << "______________________________________________________________";
        std::cout << "\n\n\n";

        player_points = 0;
        dealer_points = 0;

        std::cout << "Total betting money: $" << total_betting_money << "\n\n";
        std::cout << "How much would you like to bet: $";
        std::cin >> bet;

        total_betting_money = total_betting_money - bet;

        //Shuffling dealer cards

        card_number = shuffle_card_number();
        card_type = shuffle_card_type();
        card_identifier_str = card_identification_str(card_number, card_type);
        Sleep(1000);
        std::cout << "\n\n" << "The dealer starts with a" << card_identifier_str << "\n\n\n";

        //Updating dealer points

        dealer_points = card_rules(card_number, dealer_points);

        //Shuffling 2 player cards

        card_number_player[0] = shuffle_card_number();
        card_type = shuffle_card_type();
        card_1_str = card_identification_str(card_number_player[0], card_type);
        player_points = card_rules(card_number_player[0], player_points);
        Sleep(1000);
        card_number_player[1] = shuffle_card_number();
        card_type = shuffle_card_type();
        card_2_str = card_identification_str(card_number_player[1], card_type);
        player_points = player_points + card_rules(card_number_player[1], player_points);

        std::cout << "You drew a" << card_1_str << " and a" << card_2_str << "\n\n";

        //Updating dealer and player points

        point_updater = point_updater_str(dealer_points, player_points);
        std::cout << point_updater;

        if (player_points < 21) {
            black_gold();
            std::cout << "PLAYER'S TURN" << "\n\n";
            black_white();
        }

        //Likely case: the player will have two different cards and be under 21 points

        choice = 3;
        i = 1;
        x = i - 1;

        while (player_points < 21 && choice != 2) {

            i++;
            x = i - 1;

            //Special case: both player cards drawn are the same type (ex: King and King, 3 and 3)
            //The player will be asked if they want to double down

            if (card_number_player[i] == card_number_player[x]) {
                do {
                    std::cout << "Would you like to double down?" << "\n\n" << "1. Yes" << "\n" << "2. No" << "\n\n" << "Choice: ";
                    std::cin >> choice;
                    std::cout << "\n\n\n";

                    if (choice == 1) {
                        Sleep(1000);
                        total_betting_money = total_betting_money - bet;
                        card_number = shuffle_card_number();
                        card_type = shuffle_card_type();
                        card_identifier_str = card_identification_str(card_number, card_type);

                        std::cout << "You drew a" << card_identifier_str << "\n\n";
                        player_points = player_points + card_rules(card_number, player_points);

                        point_updater = point_updater_str(dealer_points, player_points);
                        std::cout << point_updater;
                        break;
                    }
                    if (choice == 2) {
                        //Passes player back to normal game
                        i--;
                        break;
                    }
                    else {
                        std::cout << "Invalid choice, please try again";
                        continue;
                    }
                } while (true);
            }

            //Normal game commences

            else if (card_number_player[i] != card_number_player[x]) {

                do {
                    std::cout << "1. Hit" << "\n" << "2. Stand" << "\n\n" << "Choice: ";
                    std::cin >> choice;
                    std::cout << "\n\n\n";

                    clear_screen(0, 0);

                    if (choice == 1) {

                        //Creates new card

                        i++;
                        x = i - 1;

                        Sleep(1000);
                        card_number_player[i] = shuffle_card_number();
                        card_type = shuffle_card_type();
                        card_1_str = card_identification_str(card_number, card_type);

                        std::cout << "You drew a" << card_identifier_str << "\n\n";
                        player_points = player_points + card_rules(card_number, player_points);

                        point_updater = point_updater_str(dealer_points, player_points);
                        std::cout << point_updater;

                        if (player_points >= 21) {
                            break;
                        }

                        //Checks for double down condition in normal game

                        else if (card_number_player[i] == card_number_player[x]) {

                            do {
                                std::cout << "Would you like to double down?" << "\n\n" << "1. Yes" << "\n" << "2. No" << "\n\n" << "Choice: ";
                                std::cin >> choice;
                                std::cout << "\n\n\n";

                                if (choice == 1) {
                                    Sleep(1000);
                                    total_betting_money = total_betting_money - bet;
                                    card_number = shuffle_card_number();
                                    card_type = shuffle_card_type();
                                    card_identifier_str = card_identification_str(card_number, card_type);

                                    std::cout << "You drew a" << card_identifier_str << "\n\n";
                                    player_points = player_points + card_rules(card_number, player_points);

                                    point_updater = point_updater_str(dealer_points, player_points);
                                    std::cout << point_updater;
                                    break;
                                }
                                if (choice == 2) {
                                    //Passes player back to normal game
                                    choice++;
                                    break;
                                }
                                else {
                                    std::cout << "Invalid choice, please try again";
                                    continue;
                                }
                            } while (player_points < 21);
                        }
                        if (choice == 2) {
                            break;
                        }
                    }

                    else if (choice == 2) {
                        std::cout << "The dealer will now draw" << "\n\n";
                        break;
                    }
                    else {
                        std::cout << "Invalid choice, try again" << "\n\n";
                        continue;
                    }

                } while (true);
            }
        }

        if (player_points > 21) {
            black_red();
            std::cout << "Bust. You have gone over 21 points";
            black_white();
        }

        else if (player_points == 21) {
            black_green();
            std::cout << "Blackjack. Player wins";
            black_white();
            total_betting_money = total_betting_money + 2 * bet;
        }

        //Dealer plays

        else {

            Sleep(1000);
            black_gold();
            std::cout << "\n\n" << "DEALER'S TURN" << "\n\n";
            black_white();

            while (dealer_points <= 17) {
                Sleep(2000);
                card_number = shuffle_card_number();
                card_type = shuffle_card_type();
                card_identifier_str = card_identification_str(card_number, card_type);
                std::cout << "\n\n" << "The dealer draws a" << card_identifier_str << "\n\n";

                //Updating dealer points

                dealer_points = dealer_points + card_rules(card_number, dealer_points);

                point_updater = point_updater_str(dealer_points, player_points);
                std::cout << point_updater;
            }
            if (dealer_points == 21) {
                Sleep(1000);
                black_red();
                std::cout << "Blackjack. House wins";
                black_white();
            }
            else if (dealer_points == player_points) {
                Sleep(1000);
                black_green();
                std::cout << "Draw";
                black_white();
                total_betting_money = total_betting_money + bet;
            }
            else if ((dealer_points > player_points) && (dealer_points < 21)) {
                Sleep(1000);
                black_red();
                std::cout << "House wins";
                black_white();
            }
            else if (dealer_points > 21) {
                Sleep(1000);
                black_green();
                std::cout << "House is Bust. Player wins";
                black_white();
                total_betting_money = total_betting_money + 2 * bet;
            }
            else if (dealer_points < player_points) {
                Sleep(1000);
                black_green();
                std::cout << "Player wins";
                black_white();
                total_betting_money = total_betting_money + 2 * bet;
            }
        }
        std::cout << "\n\nEnter any key to proceed: ";
        std::cin >> proceed;
        std::cout << "\n\n";
        clear_screen(0, 0);
    }
    if (total_betting_money == 0) {
        std::cout << "\n\n" << "You have run out of betting money, come back another time! \n\n\n\n\n";
    }
    else if (total_betting_money < 0) {
        debt_to_house();
    }
}

void Blackjack::introduction_dialogue() {

    char proceed[20];

    std::cout << "Welcome to Blackjack! The rules of the game are simple, you have to keep drawing cards to get as close to 21 points as possible." << "\n\n";
    //Sleep(5000);
    std::cout << "You win if:" << "\n\n" << "1. You have more points than the dealer" << "\n" << "2. You reach 21 points" << "\n\n";
    //Sleep(5000);
    std::cout << "You lose if:" << "\n\n" << "1. You have less points than the dealer" << "\n" << "2. You have over 21 points" << "\n\n";
    //Sleep(5000);
    std::cout << "Points:" << "\n\n" << "1. Ace is a soft 10 points; they become 1 point once you go over 21 points" << "\n";
    std::cout << "2. All face cards (Jack, Queen, King) are 10 points" << "\n" << "3. Normal cards are worth as many points as the card" << "\n\n";
    //Sleep(4000);
    std::cout << "SPECIAL BONUS" << "\n\n" << "If you draw two identical cards (in value, not suit), you can double down, where you double your bet, but you have to draw one card as a consequence" << "\n\n";
    //Sleep(7000);
    std::cout << "Enter any key to proceed: ";
    std::cin >> proceed;
    std::cout << "\n\n";
    clear_screen(0, 0);
}

int Blackjack::shuffle_card_number() {

    std::srand((unsigned int)time(NULL));

    int card_number = std::rand() % 13 + 1;  // card_number in the range 1 to 13

    return card_number;
}

int Blackjack::shuffle_card_type() {

    std::srand((unsigned int)time(NULL));

    int card_type = std::rand() % 4 + 1; // card_type in the range 1 to 4

    return card_type;
}

std::string Blackjack::card_identification_str(int card_number, int card_type) {

    std::string card_number_str;
    std::string card_type_str;

    //Identifying the card number

    switch (card_number) {
    case 1:
        card_number_str = " Ace";
        break;
    case 2:
        card_number_str = " 2";
        break;
    case 3:
        card_number_str = " 3";
        break;
    case 4:
        card_number_str = " 4";
        break;
    case 5:
        card_number_str = " 5";
        break;
    case 6:
        card_number_str = " 6";
        break;
    case 7:
        card_number_str = " 7";
        break;
    case 8:
        card_number_str = " 8";
        break;
    case 9:
        card_number_str = " 9";
        break;
    case 10:
        card_number_str = " 10";
        break;
    case 11:
        card_number_str = " Jack";
        break;
    case 12:
        card_number_str = " Queen";
        break;
    case 13:
        card_number_str = " King";
        break;
    default:
        card_number_str = " ERROR (card_number_str) ";
    }

    //Identifying the card type

    switch (card_type) {
    case 1:
        card_type_str = " of Hearts";
        break;
    case 2:
        card_type_str = " of Diamonds";
        break;
    case 3:
        card_type_str = " of Spades";
        break;
    case 4:
        card_type_str = " of Clubs";
        break;
    default:
        card_type_str = "ERROR (card_type_str)";
    }

    //combining the card number with the card type

    std::string card_identifier_str = card_number_str + card_type_str;

    return card_identifier_str;
}

int Blackjack::card_rules(int card_number, int points) {

    int card_to_points{};

    if (card_number > 10) {
        card_to_points = 10;
    }
    else if (card_number == 1) {
        if (points + 11 > 21) {
            card_to_points = 1;
        }
        else {
            card_to_points = 11;
        }
    }
    else if (card_number <= 10 && card_number > 1) {
        card_to_points = card_number;
    }
    else {
        card_to_points = 0;
    }

    return card_to_points;
}

std::string Blackjack::point_updater_str(int dealer_points, int player_points) {

    std::string dealer_points_str = std::to_string(dealer_points);
    std::string player_points_str = std::to_string(player_points);

    std::string point_updater = "Dealer: " + dealer_points_str + '\n' + "Player: " + player_points_str + '\n' + '\n';

    return point_updater;
}

void Blackjack::debt_to_house() {
    clear_screen(0, 0);
    int choice;
    black_red();
    std::cout << '\n' << '\n' << "YOU ARE IN DEBT TO THE HOUSE";
    std::cout << '\n' << '\n' << "How do you plan on repaying the casino?";
    std::cout << '\n' << '\n' << "1. I don't plan on paying back the casino" << '\n' << "2. I will keep betting more money" << '\n' << "3. I will work hard to pay back my debt" << '\n' << '\n';
    black_white();
    std::cout << '\n' << '\n' << "Choice: ";
    std::cin >> choice;

    black_red();

    switch (choice) {
    case 1:
        std::cout << "\n\nKneecaps. Hand them over \n\n\n\n\n";
        break;
    case 2:
        std::cout << "\n\nok cool \n\n\n\n\n";
        break;
    case 3:
        std::cout << '\n' << "How frozen I became and powerless then,";
        std::cout << '\n' << "Ask it not, reader, for I write it not,";
        std::cout << '\n' << "Because all language would be insufficient.";
        std::cout << '\n' << "I did not die, and I alive remained not.";
        std::cout << '\n' << "Think for thyself now, hast though ought of wit,";
        std::cout << '\n' << "What I became, being of both deprived.";
        std::cout << "\n\n\n\n\n";
        break;
    }
}

void Blackjack::clear_screen(int x, int y) {
    // Clears the console screen
    std::cout << "\033[2J\033[1;1H";
    // puts the cursor back to the top left when (x, y) = (0, 0)
    std::cout << "\033[" << y << ";" << x << "H";
}

void Blackjack::fix_cin() {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

//Black background, white font
void Blackjack::black_white() {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 15);
}
void Blackjack::black_gold() {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);
}
void Blackjack::black_green() {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 10);
}
void Blackjack::black_red() {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 12);
}