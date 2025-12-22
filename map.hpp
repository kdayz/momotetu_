#pragma once
#include <string>
#include <vector>
using namespace std;

#define Num_LineColor 9
#define Max_Number_Station 36
#define Max_Cross 3

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
    string StationName;           // 駅名
    vector<char> LineColor;       // 何線かを表す
    vector<int>  StationNumber;  // 駅の番号
    vector<Station*> transfers;   // 乗り換えできる駅
};

using Map = vector<vector<Station>>;

void Init_Map(Map &map);