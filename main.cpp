#include <iostream>
#include <string>
#include <vector>
#include "map.hpp"
#include "player.hpp"
using namespace std;

int main(void) {
    // 路線数x最大駅数の駅構造体２次元配列を用意
    Station Map[Num_LineColor][Max_Number_Station];
    Station *p_Map = &Map[0][0];
    p_Map = define_map(p_Map);      // マップのロード

    int total_player;               //プレイヤーの合計
    int max_year;                   // 最大年数
    cout << "人数入力: ";
    cin >> total_player;
    cout << "年数入力: ";
    cin >> max_year;

    Player *p_player;
    p_player = Init_Player(total_player, pMap(p_Map, Num_Ele_LineColor('M'),18));
    Print_Player(p_player);
}