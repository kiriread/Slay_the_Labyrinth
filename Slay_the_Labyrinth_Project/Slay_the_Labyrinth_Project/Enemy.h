#pragma once
#include <string>
#include <vector>

struct Enemy {
	std::string Name;
	int HP;
	int ATK;
	int SPD;
};
std::vector<Enemy> RegularEnemy() {
	return {
		{"„C„€„q„|„y„~ „ƒ „{„y„~„w„p„|„€„}", 30, 20, 5},
		{"„O„‚„{ „ƒ „t„…„q„y„~„€„z", 50, 15, 3},
		{"„R„|„y„x„u„~„", 60, 16, 2}
	};
}
std::vector<Enemy> EliteEnemy() {
	return {
		{"„S„‚„€„|„ „Š„p„}„p„~", 50, 40, 5},
		{"„O„s„‚ „}„p„s", 70, 30, 3}
	};
}
std::vector<Enemy> Bosses() {
	return {
		{"„X„v„‚„~„„z „t„‚„p„{„€„~", 90, 50, 5},
		{"„D„u„}„€„~ „{„‚„€„r„y", 70, 30, 8}
	};
}
