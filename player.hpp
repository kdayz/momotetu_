#include <string>
#include "map.hpp"
using namespace std;

struct Player{
    string name;                // プレイヤーの名前
    int money;                  // プレイヤーの所持金
    const Station *now_station; // 現在の駅のポインタ
};

void Init_Player(Player &player, string input_name, const Station &station);