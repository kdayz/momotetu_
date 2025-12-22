#include <iostream>
#include <string>
#include <vector>
#include "map.hpp"
#include "player.hpp"
using namespace std;

int main(void) {
    int total_player;       //プレイヤーの合計
    int max_year;           // 最大年数
    cout << "人数入力: ";
    cin >> total_player;
    cout << "年数入力: ";
    cin >> max_year;

    // マップの初期化
    Map map(Num_LineColor, vector<Station>(Max_Number_Station));
    Init_Map(map);
    
    vector<Station*> Station_List[total_player];

    Player players[total_player];
    for(int i = 0; i < total_player; i++){
        string name;
        cout << i + 1 << "番目の人の名前を入力してください";
        cin >> name;
        Init_Player(players[i], name, )
    }

    int totalplayer;
}