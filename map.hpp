#pragma once
#include <string>
#include <vector>
#include "player.hpp"
using namespace std;

#define Max_Length_Name_Station 30
#define Num_LineColor 9
#define Max_Number_Station 36
#define Max_Cross 3
#define Max_Move_List 100

// 路線の名前を数字で呼び出して文字を返す
enum class Line {
    M,  // 御堂筋線
    Y,  // 四つ橋線
    S,  // 千日前線
    N,  // 長堀鶴見緑地線
    P,  // ニュートラム
    T,  // 谷町線
    C,  // 中央線
    K,  // 堺筋線
    I   // 今里ライナー
};

// 駅の構造体
struct Station{
    string StationName;                      // 駅名
    string LineColor[Max_Cross] = {};          // 何線かを表す(複数ある)
    int  StationNumber[Max_Cross] = {};      // 駅の番号(複数ある)
    int same_station_count = 0;              // 別の路線の同じ駅の個数
    Station *same_station_list[Max_Cross];   // 別の路線の同じ駅のポインタ
};

// 駅の構造体のリスト
// 駒を進めるときの停まれる駅の探索に使う
struct Station_List{
    int length;                     // 駅リストの要素数
    int capasity;                   // 駅リストの容量
    Station **station_arr;          // 駅を表すポインタの配列
};

// 全体マップの編集点を二次元座標(i, j)に移動する
Station *pMap(Station *p_map, int i, int j);
// 路線の名前を整数に変更
int Num_Ele_LineColor(char LineColor);


// マップ定義関数
Station *Define_Map(Station *p_map);
// プレイヤーを移動させる関数
Station_List *Move_List(Station_List *p_list, Station *p_map, Player *p_player, int dice);


// 駅を表示
void print_station(Station station);
// 駅リストに含まれる駅全てを表示
void print_station_list(Station_List list);