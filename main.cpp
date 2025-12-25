#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "map.hpp"
#include "player.hpp"
using namespace std;

// 乱数生成器の初期化
random_device rd;   // ハードウェア乱数生成機
mt19937 mt(rd());   // メルセンヌ・ツイスタ法の生成器
// 1~6までの一様分布の乱数を生成(サイコロ)
uniform_int_distribution<int> Dice(1, 6);

// 入力された駅を駅構造体にして返却(不正な入力にはマップそのものを返す)
Station *inputdata_convert_station(Station *p_map, char *player_input_data){
    Station *wrong_input = p_map;
    // 路線の種類
    const char LineColors[Num_LineColor + 1] = "MYSNPTCKI";
    // その路線における最小番号と最大番号
    const int Line_Min_Max[Num_LineColor][2] = {
        {6,  30},   // 御堂筋線
        {11, 21},   // 四つ橋線
        {11, 24},   // 千日前線
        {11, 27},   // 長堀鶴見緑地線
        {9,  18},   // ニュートラム
        {11, 36},   // 谷町線
        {9,  23},   // 中央線
        {1,  20},   // 堺筋線
        {11, 21}    // 今里ライナー
    };
    int line = Num_Ele_LineColor(*(player_input_data));

    if(line < 0) return wrong_input;

    int i = 1;
    int temp = 0;
    int StaNum = 0;
    while(player_input_data[i] != '\0'){
        temp = player_input_data[i] - '0';
        if(temp >= 0 && temp <= 9){
            StaNum = StaNum * 10 + temp;
        }
        else {
            return wrong_input;
        }
        i++;
    }
    if(Line_Min_Max[line][0] <= StaNum && Line_Min_Max[line][1] >= StaNum){
        return pMap(p_map, line, StaNum);
    }
    else {
        return wrong_input;
    }
}

int main(void) {
    // マップの初期化
    // 路線数x最大駅数の駅構造体２次元配列を用意
    Station Map[Num_LineColor][Max_Number_Station];
    Station *p_Map = &Map[0][0];
    p_Map = Define_Map(p_Map);      // マップのロード

    // プレイヤーの初期化
    int total_player;               // プレイヤー人数の合計
    int max_year;                   // 最大年数

    cout << "人数入力: ";
    cin >> total_player;
    cout << "年数入力: ";
    cin >> max_year;

    Player *p_player;
    p_player = Init_Player(total_player, pMap(p_Map, Num_Ele_LineColor('M'),18));

    // 駅リストを7個分確保(六マス先に進む＋予備)
    Station_List list[7];
    Station_List *p_list = list;

    char player_input_data[Max_Length_Name_Station];
    for(int year = 1; year <= max_year; year++){
        for(int count_month = 0; count_month < 12; count_month++){
            int month = (count_month + 4) % 12;
            cout << year << "年目 " << month << "月" << endl;

            for(int player_id = 0; player_id < total_player; player_id++){
                int dice = Dice(mt);        //サイコロをふる
                cout << "サイコロの出目: " << dice << endl;
                p_list = Move_List(p_list, p_Map, p_player + player_id, dice);
                print_station_list(p_list[dice]);       //サイコロの出目の駅リストを表示

                // プレイヤーの入力に合わせてマスを進める
                Station *temp = p_Map;
                cout << "進む駅を入力してください: ";
                cin >> player_input_data;
                temp = inputdata_convert_station(p_Map, player_input_data);
                while(temp == p_Map){
                    cout << "入力エラーです。アルファベット1文字の路線名と駅番号を入力してください" << endl;
                    cout << "もう一度入力してください: ";
                    cin >> player_input_data;
                    temp = inputdata_convert_station(p_Map, player_input_data);
                }
                // マスの移動
                (p_player + player_id)->now_station = temp;
            }
        }
    }
}