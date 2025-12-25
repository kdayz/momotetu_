#pragma once
// #include "map.hpp"
using namespace std;

struct Station;

struct Player{
    string name;                // プレイヤーの名前
    int money;                  // プレイヤーの所持金
    Station *now_station;       // 現在の駅のポインタ
};

Player *Init_Player(int totalplayer, Station *p_FirstStation);

void Print_Player(Player *player);