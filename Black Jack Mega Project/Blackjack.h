#pragma once

#include <string>

namespace Blackjack
{
	void start();
	void introduction_dialogue();
	int shuffle_card_number();
	int shuffle_card_type();
	std::string card_identification_str(int, int);
	int card_rules(int, int);
	std::string point_updater_str(int, int);
	void debt_to_house();
	void clear_screen(int, int);
	void fix_cin();
	void black_white();
	void black_gold();
	void black_green();
	void black_red();
}