#include <iostream>
#include <string>
#include <vector>
#include "map.hpp"
using namespace std;

// ===================駅マップの定義関数のヘルパ関数===================

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
Station *pMap(Station *p_map, int i, int j){
    return p_map + i * Max_Number_Station + j;
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


// =======================駅マップの定義関数======================

// マップ定義関数
Station *Define_Map(Station *p_map) {
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
            // 現在の現実準拠の駅番号(路線図参照)
            int StaNum = start + j;
            // 今扱っている駅より前に同じ駅名があればその二次元座標(なければ現在の座標)を取得
            int first_row    = check_Line(p_OriginStationName, StationNames[i][j]);       // 行
            int first_column = check_StaNumber(p_OriginStationName, StationNames[i][j]);  // 列

            // 現在の駅名の情報をマップに登録
            pMap(p_map, i, StaNum)->StationName      = StationNames[i][j];
            pMap(p_map, i, StaNum)->LineColor[0]     = LineColors[i];
            pMap(p_map, i, StaNum)->StationNumber[0] = StaNum;

            // 現在の駅名が初出の場合、乗り換えリストの頭に現在の駅のポインタを設定
            if(i == first_row){
                pMap(p_map, i, StaNum)->same_station_list[0] = pMap(p_map, i, StaNum);
            }
            // 現在の駅名が既出の場合
            if(i != first_row){
                int first_min_number = Line_Min_Max[first_row][0];
                // 最初に出てきたときの駅番号(ex:本町駅ならM18の18)
                int first_StaNum = first_min_number + first_column;
                // 最初に出てきた路線での構造体と現在の路線での構造体
                Station *same_station = pMap(p_map, first_row, first_StaNum);
                Station *now_station  = pMap(p_map, i, StaNum);

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
    pMap(p_map, Num_Ele_LineColor('T'), 20)->StationName = "東梅田";
    pMap(p_map, Num_Ele_LineColor('Y'), 11)->StationName = "西梅田";
    pMap(p_map, Num_Ele_LineColor('Y'), 14)->StationName = "四ツ橋";
    return p_map;
}



// =======================マップ移動関数のヘルパ関数======================

// 駅リストの初期化
Station_List init_station_list(int size){
    Station_List list;
    list.length = 0;
    list.capasity = size;
    list.station_arr = (Station**)malloc(sizeof(Station*) * size);
    return list;
}

// 駅リストに駅を追加する
Station_List append_station(Station_List list, Station *station){
    // これ以上渡された駅リストに駅を追加できないときは何もしない
    if (list.length >= list.capasity){

    }
    list.station_arr[list.length] = station;
    list.length++;

    return list;
}
// 駅リストaに駅リストbに含まれるすべての駅を追加
Station_List append_station(Station_List list_a, Station_List list_b){
    for(int i = 0; i < list_b.length; i++){
        list_a = append_station(list_a, list_b.station_arr[i]);
    }
    return list_a;
}

// 駅リストから駅を削除する
Station_List delete_station(Station_List list, Station *station){
    // 渡された駅が持つ乗り換え可能な駅ごと駅リストから削除する

    for(int j = 0; j <= station->same_station_count; j++){
        for(int i = 0; i < list.length; i++){
            // 駅リストが持つ駅配列のi番目が渡された駅のもつ乗り換え可能な駅もしくはその駅自身のとき
            if(list.station_arr[i] == station->same_station_list[j]){
                // i番目を削除してそれ以降を詰めていく
                for(int k = i; k < list.length - 1; k++){
                    list.station_arr[k] = list.station_arr[k + 1];
                }
                list.length--;
                // i--;
                break;
            }
        }
    }
    return list;
}
// 駅リストaから駅リストbに含まれる駅をすべて削除
Station_List delete_station(Station_List list_a, Station_List list_b){
    for(int i = 0; i < list_b.length; i++){
        list_a = delete_station(list_a, list_b.station_arr[i]);
    }

    return list_a;
}

// 駅リストaの後ろに駅リストbに含まれる駅を被りなくすべて追加
Station_List safe_append_station(Station_List list_a, Station_List list_b){
    // 駅リストaとbの被っている駅を一旦削除
    list_a = delete_station(list_a, list_b);
    // 削除後追加し直す
    list_a = append_station(list_a, list_b);

    return list_a;
}
// 駅リストの後ろに駅を被りなく追加
Station_List safe_append_station(Station_List list, Station *station){
    // 一時的に一駅保存するだけの駅リストを作る
    Station_List temp_list = init_station_list(1);
    temp_list = append_station(temp_list, station);
    list = safe_append_station(list, temp_list);
    free(temp_list.station_arr);

    return list;
}
// masashi
void a(){
    cout << "a" << endl;
}

// =======================マップ移動関数======================

// マップ移動関数
Station_List *Move_List(Station_List *p_list, Station *p_map, Player *p_player, int dice){
    // 進めるマス分の駅リストの初期化
    for(int i = 0; i <= dice; i++){
        *(p_list + i) = init_station_list(Max_Move_List);
    }
    *(p_list) = append_station(*(p_list), p_player->now_station);
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

    for(int i = 1; i <= dice; i++){
        // 駅リストの配列のi番目を現在の駅リストとして呼び出し
        Station_List lastlist = *(p_list + i - 1);

        for(int j = 0; j < lastlist.length; j++){
            // 現在の駅リストのj番目の駅を呼び出し
            Station now_station = *(lastlist.station_arr[j]);
            // 乗り換えできる路線数
            int can_move_line = lastlist.station_arr[j]->same_station_count + 1;
            // 一つ前もしくは後ろの駅のすべてを保存するための駅リスト
            Station_List One_Station_Step_Memory = init_station_list(2 * Max_Cross);

            for(int k = 0; k < can_move_line; k++){
                int now_LineNumber    = Num_Ele_LineColor(*now_station.LineColor[k].c_str());
                int now_StationNumber = now_station.StationNumber[k];
                int now_min_max[2] = { Line_Min_Max[now_LineNumber][0], Line_Min_Max[now_LineNumber][1] };
                int count = 0;

                // 現在の駅番号より一つ小さい番号がその路線の最小番号以上のとき
                if(now_StationNumber - 1 >= now_min_max[0]){
                    // 一つ後ろの駅を追加
                    One_Station_Step_Memory = safe_append_station(One_Station_Step_Memory, pMap(p_map, now_LineNumber, now_StationNumber - 1));
                }
                // 現在の駅番号より一つ大きい番号がその路線の最大番号以下のとき
                if(now_StationNumber + 1 <= now_min_max[1]){
                    // 一つ前の駅を追加
                    One_Station_Step_Memory = safe_append_station(One_Station_Step_Memory, pMap(p_map, now_LineNumber, now_StationNumber + 1));
                }
                // 現在の駅番号がその路線の番号の範囲外のときはなにもしない
            }
            *(p_list + i) = safe_append_station(*(p_list + i), One_Station_Step_Memory);
        }

        if (i > 1){
            *(p_list + i) = delete_station(*(p_list + i), *(p_list + i - 2));
        }
    }
    return p_list;
}


// =======================デバッグ用関数======================

// 駅を表示
void print_station(Station station){
    cout << station.StationName;
    for(int i = 0; i < Max_Cross; i++){
        if(station.StationNumber[i] == 0)
            break;
        cout << station.LineColor[i] << station.StationNumber[i];
    }
}
// 駅リストに含まれる駅全てを表示
void print_station_list(Station_List list){
    for(int i = 0; i < list.length - 1; i++){
        print_station(*(list.station_arr[i]));
        cout << ", ";
    }
    if(list.length - 1 != 0) {
        print_station(*(list.station_arr[list.length - 1]));
    }
    cout << endl;
}
