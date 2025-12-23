#include <iostream>
#include <string>
#include "map.hpp"
#include "player.hpp"
using namespace std;

// Player型構造体の初期化
Player *Init_Player(int totalplayer, Station *p_FirstStation) {
    Player *p_player = new Player[totalplayer];

    // 入力した名前、所持金10000円、最初の駅のポインタで初期化
    for(int i = 0; i < totalplayer; i++){
        string name;
        cout << i + 1 << "番目の人の名前を入力してください: ";
        cin >> name;
        (p_player + i)->name  = name;
        (p_player + i)->money = 10000;
        (p_player + i)->now_station = p_FirstStation;
    }
    return p_player;
}

void Print_Player(Player *player){
    string staname;
    staname = player->now_station->StationName;
    cout << "   名前:   " << player->name << endl;
    cout << "  所持金:  " << player->money << "円" << endl;
    cout << " 現在の駅: " << staname << "駅" << endl;
}