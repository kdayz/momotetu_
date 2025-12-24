#include <iostream>
#include <string>
#include <vector>
#include "map.hpp"
using namespace std;

// ===================マップ定義のヘルパ関数===================

// 今触っている駅名より前に同じ駅名が駅名の集合に存在すれば、その行の値を返す
// なければ現在の駅名の行(路線)の値を返す
int check_Line(const string *OriginStationName, const string &NowStation){
    for(int i = 0; i < Num_LineColor * Max_Number_Station; i++) {
        if(OriginStationName[i] == NowStation){
            return i / Max_Number_Station;
        }
    }
    return -1;
}
// 今触っている駅名より前に同じ駅名が駅名の集合に存在すれば、その列の値を返す
// なければ現在の駅名の列の値を返す
int check_StaNumber(const string *OriginStationName, const string &NowStation){
    for(int i = 0; i < Num_LineColor * Max_Number_Station; i++) {
        if(OriginStationName[i] == NowStation){
            return i % Max_Number_Station;
        }
    }
    return -1;
}

// 全体マップの編集点を二次元座標(i, j)に移動する
Station *pMap(Station *p_Map, int i, int j){
    return p_Map + i * Max_Number_Station + j;
}

// 路線の名前を整数に変更
int Num_Ele_LineColor(char LineColor) {
    switch(LineColor) {
        case 'M': return 0;
        case 'Y': return 1;
        case 'S': return 2;
        case 'N': return 3;
        case 'P': return 4;
        case 'T': return 5;
        case 'C': return 6;
        case 'K': return 7;
        case 'I': return 8;
        default : return -1;
    }
}

// =======================駅マップの定義======================

// マップ定義関数
Station *define_map(Station *p_Map) {
    // 路線の種類
    const char LineColors[Num_LineColor + 1] = "MYSNPTCKI";

    // その路線における最小番号と最大番号(本家に準拠、路線図参照)
    // (ex)御堂筋線: min=6, max=30
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

    //駅名の集合
    const string StationNames[Num_LineColor][Max_Number_Station] = {
        //御堂筋線:M
        {"箕面萱野", "箕面船場阪大前", "千里中央", "桃山台", "緑地公園", "江坂", "東三国",
		"新大阪", "西中島南方", "中津", "梅田", "淀屋橋", "本町", "心斎橋", "なんば",
		"大国町", "動物園前", "天王寺", "昭和町", "西田辺", "長居", "あびこ",
		"北花田", "新金岡", "なかもず" },
        //四つ橋線:Y
		{"梅田", "肥後橋", "本町", "心斎橋", "なんば", "大国町", "花園町",
		"岸里", "玉出", "北加賀屋", "住之江公園"},
        //千日前線:S
		{"野田阪神", "玉川", "阿波座", "西長堀", "桜川", "なんば", "日本橋",
		"谷町九丁目", "鶴橋", "今里", "新深江", "小路", "北巽", "南巽"},
        //長堀鶴見緑地線:N
		{"大正", "ドーム前千代崎", "西長堀", "西大橋", "心斎橋", "長堀橋",
		"松屋町", "谷町六丁目", "玉造", "森ノ宮", "大阪ビジネスパーク", "京橋",
		"蒲生四丁目", "今福鶴見", "横堤", "鶴見緑地", "門真南"},
        //ニュートラム:P
		{"コスモスクエア", "トレードセンター前", "中ふ頭", "ポートタウン西",
		"ポートタウン東", "フェリーターミナル", "南港東", "南港口", "平林",
		"住之江公園"},
        //谷町線:T
		{"大日", "守口", "太子橋今市", "千林大宮", "関目高殿", "野江内代", "都島",
		"天神橋筋六丁目", "中崎町", "梅田", "南森町", "天満橋", "谷町四丁目",
		"谷町六丁目", "谷町九丁目", "四天王寺前夕陽ヶ丘", "天王寺", "阿倍野",
		"文の里", "田辺", "駒川中野", "平野", "喜連瓜破", "出戸", "長原", "八尾南"},
        //中央線:C
		{"コスモスクエア", "大阪港", "朝潮橋", "弁天町", "九条", "阿波座", "本町",
		"堺筋本町", "谷町四丁目", "森ノ宮", "緑橋", "深江橋", "高井田", "長田",
		"荒本", "吉田", "新石切", "生駒", "白庭台", "学研北生駒", "学研奈良登美ヶ丘"},
        //堺筋線:S
		{"北千里", "山田", "南千里", "千里山", "関大前", "豊津", "吹田", "下新庄",
		"淡路", "柴島","天神橋筋六丁目", "扇町", "南森町", "北浜", "堺筋本町", "長堀橋",
        "日本橋", "恵美須町", "動物園前","天下茶屋"},
        //今里ライナー:I
		{"井高野", "瑞光四丁目", "だいどう豊里", "太子橋今市","清水","新古森市",
        "関目成育", "蒲生四丁目", "鴫野", "緑橋", "今里"}
    };

    // ここからマップの初期化処理
    const string *p_OriginStationName = &StationNames[0][0];  // 探索の原点のポインタを保存
    for(int i = 0; i < Num_LineColor; ++i){
        // 現在の路線における先頭のポインタ
        int start = Line_Min_Max[i][0];

        for (int j = 0; j < Line_Min_Max[i][1] - Line_Min_Max[i][0] + 1; j++) {
            // 現在の現実準拠の駅の番号(路線図参照)
            int StaNum = start + j;
            // 今扱っている駅より前に同じ駅名があればその二次元座標(なければ現在の座標)を取得
            int first_row    = check_Line(p_OriginStationName, StationNames[i][j]);       // 行
            int first_column = check_StaNumber(p_OriginStationName, StationNames[i][j]);  // 列

            // 現在の駅名の情報をマップに登録
            pMap(p_Map, i, StaNum)->StationName      = StationNames[i][j];
            pMap(p_Map, i, StaNum)->LineColor[0]     = LineColors[i];
            pMap(p_Map, i, StaNum)->StationNumber[0] = StaNum;

            // 現在の駅名が初出の場合、乗り換えリストの頭に現在の駅のポインタを設定
            if(i == first_row){
                pMap(p_Map, i, StaNum)->same_station_list[0] = pMap(p_Map, i, StaNum);
            }
            // 現在の駅名が既出の場合
            if(i != first_row){
                int first_min_number = Line_Min_Max[first_row][0];
                // 最初に出てきたときの駅の番号(ex:本町駅ならM18の18)
                int first_StaNum = first_min_number + first_column;
                // 最初に出てきた路線での構造体と現在の路線での構造体
                Station *same_station = pMap(p_Map, first_row, first_StaNum);
                Station *now_station  = pMap(p_Map, i, StaNum);

                same_station->same_station_count++;
                int same_station_number = same_station->same_station_count;
                // 最初に出てきている駅に現在の路線の情報を登録
                // ex:四つ橋線で本町駅(御堂筋線で既出)ならY13の'Y'と「13」とマップにおけるポインタを登録
                same_station->LineColor[same_station_number]         = LineColors[i];
                same_station->StationNumber[same_station_number]     = StaNum;
                same_station->same_station_list[same_station_number] = now_station;
                for(int k = 1; k <= same_station_number; k++){
                    copy(
                        same_station->LineColor,
                        same_station->LineColor + Max_Cross,
                        same_station->same_station_list[k]->LineColor
                    );
                    copy(
                        same_station->StationNumber,
                        same_station->StationNumber + Max_Cross,
                        same_station->same_station_list[k]->StationNumber
                    );
                    same_station->same_station_list[k]->same_station_count = same_station->same_station_count;
                    copy(
                        same_station->same_station_list,
                        same_station->same_station_list + Max_Cross,
                        same_station->same_station_list[k]->same_station_list
                    );
                }
            }
        }
    }
    cout << Num_Ele_LineColor('T') << endl;
    pMap(p_Map, Num_Ele_LineColor('T'), 20)->StationName = "東梅田";
    pMap(p_Map, Num_Ele_LineColor('Y'), 11)->StationName = "西梅田";
    pMap(p_Map, Num_Ele_LineColor('Y'), 14)->StationName = "四ツ橋";
    return p_Map;
}