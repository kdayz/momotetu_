#include <iostream>
#include <string>
#include "map.hpp"
#include "player.hpp"
using namespace std;

void Init_Player(Player &player, string input_name, const Station &station) {
    player.name  = input_name;
    player.money = 10000;
    player.now_station = &station;
}

void Print_Player(Player &player){
    cout << "   名前:   " << player.name << endl;
    cout << "  所持金:  " << player.money << "円" << endl;
    cout << " 現在の駅: " << player.now_station << "駅" << endl;
}