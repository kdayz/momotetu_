#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>

#define Max_Length_Name_Station 30
#define Max_Cross 3

struct station_struct {
	char name[30];
	char LineColor[Max_Cross] = {};
	int station_number[Max_Cross] = {};
	int same_station_count = 0;//当該駅構造体を含まない
	station_struct* same_station_list[Max_Cross];
};
struct Station_List
{	
	//data容量lengthがcapacityを超えるとき、capacity_dataに新たに動的確保
	//用意したアドレスをdataにコピーする
	int length;
	int capasity;
	station_struct** data;
	station_struct** capasity_data;
};
struct player_struct {
	char name[20];
	int money;
	station_struct *now_station;
};

void a() {
	printf("a");
}
player_struct* Debug_Initial_settings(station_struct *a) {
	player_struct* p_player;

	p_player = (player_struct*)malloc(sizeof(player_struct) * 4);
	if (p_player == NULL) {
		exit(0);
	}
	for (int i = 0; i < 4; i++) {
		
		strcpy((p_player + i)->name, "name");
		(p_player + i)->money = 10000;
		(p_player + i)->now_station = a;
	}
	printf("最初の駅は%sです。\n", a->name);
	return p_player;
}
player_struct* Initial_settings(int* totalplayer,int* Maxyear,station_struct *a) {
	player_struct* p_player;
	printf("人数入力"); scanf("%d", totalplayer);
	printf("年数入力"); scanf("%d", Maxyear);
	p_player = (player_struct*)malloc(sizeof(player_struct) * *(totalplayer));
	if (p_player==NULL) {
		exit(0);
	}
	for (int i = 0; i < *(totalplayer); i++) {
		printf("%d番目の人の名前を入力してください", i + 1);
		scanf("%s", (p_player+i)->name );
		(p_player + i)->money = 10000;
		(p_player + i)->now_station = a;
	}
	printf("最初の駅は%sです。\n", a->name);
	return p_player;
}
//map定義
#define Num_LineColor 9
#define Max_Number_Station 36
int check_line(char* p_name_station,char* station) {
	for (int i = 0; i < Num_LineColor * Max_Number_Station; i++) {
		if (strcmp(p_name_station+i* Max_Length_Name_Station,station)==0) {
			return i/Max_Number_Station;
		}
	}
	return -1;
}
int check_StaNumber(char* p_name_station, char* station) {
	for (int i = 0; i < Num_LineColor * Max_Number_Station; i++) {
		if (strcmp(p_name_station + i* Max_Length_Name_Station, station)==0) {
			return i % Max_Number_Station;
		}
	}
	return -1;
}


int Num_ele_Linecolor(char b) {
	char a[Num_LineColor+1] = "MYSNPTCKI";
	for (int i = 0; i < 100; i++) {
		if (a[i] == b)return i;
	}return -1;
}

void Debug_printstation(station_struct* p_map, int i, int j) {
	station_struct map = *(p_map + i * Max_Number_Station + j);
	printf("%d_%d %d %s,%s,%d%d%d %d %d_%d_%d\n", i, j, p_map + i * Max_Number_Station + j, map.name, map.LineColor, map.station_number[0], map.station_number[1], map.station_number[2],map.same_station_count,
		map.same_station_list[0], map.same_station_list[1], map.same_station_list[2]);

}
void Debug_full_printstation(station_struct* p_map) {
	for (int i = 0; i < Num_LineColor; i++) {
		for (int j = 0; j < Max_Number_Station; j++) {
			Debug_printstation(p_map, i, j);
		}
	}
}

station_struct* pmap(station_struct* p_map, int i, int j) {
	return p_map + i * Max_Number_Station + j;
}
station_struct* define_map(station_struct* p_map) {
	
	char LineColor[Num_LineColor + 1] = "MYSNPTCKI";
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	char sub_name_station[Num_LineColor][Max_Number_Station][30] = {
		{"箕面萱野", "箕面船場阪大前", "千里中央", "桃山台", "緑地公園", "江坂", "東三国",//M
		"新大阪", "西中島南方", "中津", "梅田", "淀屋橋", "本町", "心斎橋", "なんば",
		"大国町", "動物園前", "天王寺", "昭和町", "西田辺", "長居", "あびこ",
		"北花田", "新金岡", "なかもず" },
		{"梅田", "肥後橋", "本町", "心斎橋", "なんば", "大国町", "花園町",//Y
		"岸里", "玉出", "北加賀屋", "住之江公園"},
		{"野田阪神", "玉川", "阿波座", "西長堀", "桜川", "なんば", "日本橋",//S
		"谷町九丁目", "鶴橋", "今里", "新深江", "小路", "北巽", "南巽"},
		{"大正", "ドーム前千代崎", "西長堀", "西大橋", "心斎橋", "長堀橋",//N
		"松屋町", "谷町六丁目", "玉造", "森ノ宮", "大阪ビジネスパーク", "京橋",
		"蒲生四丁目", "今福鶴見", "横堤", "鶴見緑地", "門真南"},
		{"コスモスクエア", "トレードセンター前", "中ふ頭", "ポートタウン西",//P
		"ポートタウン東", "フェリーターミナル", "南港東", "南港口", "平林",
		 "住之江公園"},
		{"大日", "守口", "太子橋今市", "千林大宮", "関目高殿", "野江内代", "都島",//T
		"天神橋筋六丁目", "中崎町", "梅田", "南森町", "天満橋", "谷町四丁目",
		"谷町六丁目", "谷町九丁目", "四天王寺前夕陽ヶ丘", "天王寺", "阿倍野",
		"文の里", "田辺", "駒川中野", "平野", "喜連瓜破", "出戸", "長原", "八尾南"},//C
		{"コスモスクエア", "大阪港", "朝潮橋", "弁天町", "九条", "阿波座", "本町",
		"堺筋本町", "谷町四丁目", "森ノ宮", "緑橋", "深江橋", "高井田", "長田",
		"荒本", "吉田", "新石切", "生駒", "白庭台", "学研北生駒", "学研奈良登美ヶ丘"},
		{"北千里", "山田", "南千里", "千里山", "関大前", "豊津", "吹田", "下新庄",//K
		"淡路", "柴島","天神橋筋六丁目", "扇町", "南森町", "北浜", "堺筋本町", "長堀橋", "日本橋",
		"恵美須町", "動物園前","天下茶屋"},
		{"井高野", "瑞光四丁目", "だいどう豊里", "太子橋今市","清水","新古森市", "関目成育",//I
		"蒲生四丁目", "鴫野", "緑橋", "今里"}
	};
	
	char* p_sub_name_station = &sub_name_station[0][0][0];
	for (int i = 0; i < Num_LineColor; i++) {
		int min_number = line_min_max[i][0];
		for (int j = 0; j < line_min_max[i][1]-line_min_max[i][0]+1; j++) {
			int current_index = j + min_number;
			int first_line = check_line(p_sub_name_station, sub_name_station[i][j]);
			int first_number = check_StaNumber(p_sub_name_station, sub_name_station[i][j]);
			
			pmap(p_map,i, current_index)->LineColor[0]= LineColor[i];
			pmap(p_map, i, current_index)->station_number[0] = current_index;
			strcpy(pmap(p_map, i, current_index)->name, sub_name_station[i][j]);
			if (i == first_line) {
				pmap(p_map, i, current_index)->same_station_list[0]= pmap(p_map, i, current_index);//初期化処理どうしよう
			}
			if (i != first_line) {
				int first_min_number= line_min_max[first_line][0];
				int first_index = first_number + first_min_number;
				station_struct* same_station = pmap(p_map, first_line, first_index);
				station_struct* now = pmap(p_map, i, current_index);
				same_station->same_station_count++;
				int same_station_number = same_station->same_station_count;


				same_station->LineColor[same_station_number] = LineColor[i];
				same_station->station_number[same_station_number] = current_index;
				same_station->same_station_list[same_station_number] = now;
				for (int k = 1; k <= same_station_number; k++) {
					strcpy(same_station->same_station_list[k]->LineColor, same_station->LineColor);
					memcpy(same_station->same_station_list[k]->station_number, same_station->station_number, sizeof(int) * Max_Cross);
					same_station->same_station_list[k]->same_station_count = same_station->same_station_count;
					memcpy(same_station->same_station_list[k]->same_station_list, same_station->same_station_list, sizeof(station_struct*) * Max_Cross);

				}
			}
		}
		
	}
	strcpy((pmap(p_map,Num_ele_Linecolor('T'),20)->name ), "東梅田");
	strcpy((pmap(p_map, Num_ele_Linecolor('Y'), 11)->name), "西梅田");
	strcpy((pmap(p_map, Num_ele_Linecolor('Y'), 14)->name), "四ツ橋");
	
	
	return p_map;

}
//盤面移動
#define Max_Move_List 100

void print_station(station_struct a) {
	printf("%s:", a.name);
	for (int i = 0; i < 3; i++) {
		if (a.station_number[i] == 0) {
			break;
		}
		printf("%c%d,", a.LineColor[i], a.station_number[i]);
	}
}
void print_station_list(Station_List a) {
	for (int i = 0; i < a.length-1; i++) {
		print_station(*(a.data[i]));
		printf(" ");
	}if (a.length != 0) {
		print_station(*(a.data[a.length - 1]));
	}
	printf("\n");
}
Station_List define_Station_List(int size) {
	Station_List b;
	b.length = 0;
	b.capasity = size;
	b.data = (station_struct**)malloc(sizeof(station_struct*) * size);
	return b;
}
Station_List append_station(Station_List a, station_struct *b) {//リストaに駅bを追加
	if (a.length >= a.capasity) {

	}
	a.data[a.length] = b;
	a.length++;
	
	return a;	
}
Station_List delite_station(Station_List a, station_struct *b) {//リストaから駅bをすべて削除
	
	for (int j = 0; j <= b->same_station_count; j++) {
		for (int i = 0; i < a.length; i++) {
			if (a.data[i] == b->same_station_list[j]) {
				// i番目を削除し、それ以降を左に詰める
				for (int k = i; k < a.length - 1; k++) {
					a.data[k] = a.data[k + 1];
				}
				a.length--;
				i--; 
				break;
			}
		}
	}
	return a;
	
}
Station_List delite_station(Station_List a, Station_List b) {
	for (int i = 0; i < b.length; i++) {
		a=delite_station(a, b.data[i]);
	}
	
	return a;
}
Station_List append_station(Station_List a, Station_List b) {//リストaの後ろにリストbの内容を追加	
	
	if (a.length + b.length > a.capasity) {
		Station_List c = a;
		free(a.data);
		a = define_Station_List(2*(a.length + b.length));
		a = append_station(a, c);
	}
	for (int i = 0; i < b.length; i++) {
		a.data[i + a.length] = b.data[i];
	}a.length += b.length;
	return a;
}
Station_List safe_append_station(Station_List a, Station_List b) {//リストaの後ろにリストbの内容を被りなく追加
	a = delite_station(a, b);
	a = append_station(a, b);
	return a;
}
Station_List safe_append_station(Station_List a, station_struct *b) {//リストaの後ろにリストbの内容を被りなく追加
	Station_List c = define_Station_List(1);
	c = append_station(c, b);
	a=safe_append_station(a, c);
	free(c.data);
	return a;
}

void test(station_struct* p_map) {
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	for (int i = 0; i < Num_LineColor; i++) {
		int min_number = line_min_max[i][0];
		for (int j = 0; j < line_min_max[i][1] - line_min_max[i][0] + 1; j++) {
			int current_index = j + min_number;
			printf("%d_%d %s\n", i, current_index, pmap(p_map, i, current_index)->name);
		}
	}
}


Station_List* move_list(Station_List* list,station_struct* p_map,player_struct player,int dice) {//diceで到達可能マスを返却
	//初期化
	for (int i = 0; i <= dice; i++) {
		*(list+i)= define_Station_List(Max_Move_List);
	}
	*(list) = append_station(*(list), player.now_station);
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	
	
	for (int i = 1; i <= dice; i++) {
		Station_List lastlist = *(list + i - 1);
		for (int j = 0; j < lastlist.length; j++) {//i番目に到達できるすべてのマスについて実行
			station_struct now_station = *(lastlist.data[j]);
			int can_move_line = lastlist.data[j]->same_station_count+1;
			Station_List One_station_step_memory = define_Station_List(2*Max_Cross);
			
			for (int k = 0; k < can_move_line; k++) {
				int now_linenumber = Num_ele_Linecolor(now_station.LineColor[k]);
				int now_station_number = now_station.station_number[k];
				int now_min_max[2] = { line_min_max[now_linenumber][0],line_min_max[now_linenumber][1] };
				int count = 0;
				
				if (now_station_number - 1 >= now_min_max[0]) {
					
					One_station_step_memory=safe_append_station(One_station_step_memory, pmap(p_map, now_linenumber, now_station_number - 1));
					
				}
				if (now_station_number + 1 <= now_min_max[1]) {
					
					One_station_step_memory = safe_append_station(One_station_step_memory, pmap(p_map, now_linenumber, now_station_number + 1));
					
				}
				
			}
			*(list + i) = safe_append_station(*(list + i), One_station_step_memory);
		}
		
		if (i > 1) {
			
			*(list + i) = delite_station(*(list + i), *(list + i - 2));
		}
	}

	return list;
}


station_struct* inputdata_convert_station(station_struct* p_map,char* input_data) {
	station_struct* false_cv = p_map;
	char LineColor[Num_LineColor + 1] = "MYSNPTCKI";
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	int line = Num_ele_Linecolor(*(input_data));
	if (line < 0)return false_cv;
	int i = 1;
	int memory = 0;
	int sta_number = 0;
	while (input_data[i] != '\0') {
		memory = input_data[i] - '0';
		if (memory>= 0 && memory<= 9) {
			sta_number = sta_number * 10 + memory;
		}
		else {
			return false_cv;
		}
		i++;
	}if (line_min_max[line][0] <= sta_number && line_min_max[line][1] >= sta_number) {
		return pmap(p_map, line, sta_number);
	}
	else {
		return false_cv;
	}
}

int main(void) {
	station_struct map[Num_LineColor][Max_Number_Station];
	station_struct* p_map = &map[0][0];
	p_map=define_map(p_map);
	
	int totalplayer = 4;
	player_struct* player;
	int Maxyaer = 4;
	char LineColor[Num_LineColor + 1] = "MYSNPTCKI";
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	player=Initial_settings(&totalplayer, &Maxyaer,pmap(p_map,Num_ele_Linecolor('S'),10));
	//player = Debug_Initial_settings(pmap(p_map,Num_ele_Linecolor('Y'),13));
	Station_List list[7];
	Station_List* p_list = list;
	
	p_list = move_list(p_list, p_map, *(player), 4);
	char player_input_data[Max_Length_Name_Station];
	for (int year = 1; year <= Maxyaer; year++) {
		for (int count_month = 0; count_month < 4; count_month++) {
			int month = (count_month + 4) % 12;
			printf("%d年目%d月\n",year,month);
			for (int player_id = 0; player_id < totalplayer; player_id++) {
				int dice = rand() % 6 + 1;
				printf("%d\n", dice);
				p_list = move_list(p_list, p_map, *(player+player_id), dice);
				print_station_list(list[dice]);
				station_struct* memory = p_map;
				printf("進む駅を入力してください:");
				scanf("%s", player_input_data);
				memory = inputdata_convert_station(p_map, player_input_data);
				while (memory==p_map) {
					printf("入力エラーです。もう一度入力してください:");
					scanf("%s", player_input_data);
					memory = inputdata_convert_station(p_map, player_input_data);

				}

				//ここでイベント処理
				(player + player_id)->now_station = memory;
			}
		}
	}
	
	
}
