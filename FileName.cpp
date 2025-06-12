#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <stdlib.h>

#define Max_Length_Name_Station 30
#define Max_Cross 3

struct station_struct {
	char name[30];
	char LineColor[Max_Cross] = {};
	int station_number[Max_Cross] = {};
	int same_station_count = 0;//“–ŠY‰w\‘¢‘Ì‚ğŠÜ‚Ü‚È‚¢
	station_struct* same_station_list[Max_Cross];
};
struct Station_List
{
	int length;
	int capasity;
	station_struct** data;
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
	printf("Å‰‚Ì‰w‚Í%s‚Å‚·B\n", a->name);
	return p_player;
}
player_struct* Initial_settings(int* totalplayer,int* Maxyear,station_struct *a) {
	player_struct* p_player;
	printf("l”“ü—Í"); scanf("%d", totalplayer);
	printf("”N”“ü—Í"); scanf("%d", Maxyear);
	p_player = (player_struct*)malloc(sizeof(player_struct) * *(totalplayer));
	if (p_player==NULL) {
		exit(0);
	}
	for (int i = 0; i < *(totalplayer); i++) {
		printf("%d”Ô–Ú‚Ìl‚Ì–¼‘O‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢", i + 1);
		scanf("%s", (p_player+i)->name );
		(p_player + i)->money = 10000;
		(p_player + i)->now_station = a;
	}
	printf("Å‰‚Ì‰w‚Í%s‚Å‚·B\n", a->name);
	return p_player;
}
//map’è‹`
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
		{"–¥–ÊŠ–ì", "–¥–Ê‘Dêã‘å‘O", "ç—¢’†‰›", "“R‘ä", "—Î’nŒö‰€", "]â", "“ŒO‘",//M
		"V‘åã", "¼’†“‡“ì•û", "’†’Ã", "”~“c", "—„‰®‹´", "–{’¬", "SÖ‹´", "‚È‚ñ‚Î",
		"‘å‘’¬", "“®•¨‰€‘O", "“V‰¤›", "º˜a’¬", "¼“c•Ó", "’·‹", "‚ ‚Ñ‚±",
		"–k‰Ô“c", "V‹à‰ª", "‚È‚©‚à‚¸" },
		{"”~“c", "”ìŒã‹´", "–{’¬", "SÖ‹´", "‚È‚ñ‚Î", "‘å‘’¬", "‰Ô‰€’¬",//Y
		"Šİ—¢", "‹Êo", "–k‰Á‰ê‰®", "Z”V]Œö‰€"},
		{"–ì“cã_", "‹Êì", "ˆ¢”gÀ", "¼’·–x", "÷ì", "‚È‚ñ‚Î", "“ú–{‹´",//S
		"’J’¬‹ã’š–Ú", "’ß‹´", "¡—¢", "V[]", "¬˜H", "–k’F", "“ì’F"},
		{"‘å³", "ƒh[ƒ€‘Oç‘ãè", "¼’·–x", "¼‘å‹´", "SÖ‹´", "’·–x‹´",//N
		"¼‰®’¬", "’J’¬˜Z’š–Ú", "‹Ê‘¢", "Xƒm‹{", "‘åãƒrƒWƒlƒXƒp[ƒN", "‹‹´",
		"Š—¶l’š–Ú", "¡•Ÿ’ßŒ©", "‰¡’ç", "’ßŒ©—Î’n", "–å^“ì"},
		{"ƒRƒXƒ‚ƒXƒNƒGƒA", "ƒgƒŒ[ƒhƒZƒ“ƒ^[‘O", "’†‚Ó“ª", "ƒ|[ƒgƒ^ƒEƒ“¼",//P
		"ƒ|[ƒgƒ^ƒEƒ““Œ", "ƒtƒFƒŠ[ƒ^[ƒ~ƒiƒ‹", "“ì`“Œ", "“ì`Œû", "•½—Ñ",
		 "Z”V]Œö‰€"},
		{"‘å“ú", "çŒû", "‘¾q‹´¡s", "ç—Ñ‘å‹{", "ŠÖ–Ú‚“a", "–ì]“à‘ã", "“s“‡",//T
		"“V_‹´‹Ø˜Z’š–Ú", "’†è’¬", "”~“c", "“ìX’¬", "“V–‹´", "’J’¬l’š–Ú",
		"’J’¬˜Z’š–Ú", "’J’¬‹ã’š–Ú", "l“V‰¤›‘O—[—zƒ–‹u", "“V‰¤›", "ˆ¢”{–ì",
		"•¶‚Ì—¢", "“c•Ó", "‹îì’†–ì", "•½–ì", "Šì˜A‰Z”j", "oŒË", "’·Œ´", "”ª”ö“ì"},//C
		{"ƒRƒXƒ‚ƒXƒNƒGƒA", "‘åã`", "’©’ª‹´", "•Ù“V’¬", "‹ãğ", "ˆ¢”gÀ", "–{’¬",
		"ä‹Ø–{’¬", "’J’¬l’š–Ú", "Xƒm‹{", "—Î‹´", "[]‹´", "‚ˆä“c", "’·“c",
		"r–{", "‹g“c", "VÎØ", "¶‹î", "”’’ë‘ä", "ŠwŒ¤–k¶‹î", "ŠwŒ¤“Ş—Ç“o”üƒ–‹u"},
		{"–kç—¢", "R“c", "“ìç—¢", "ç—¢R", "ŠÖ‘å‘O", "–L’Ã", "“c", "‰ºV¯",//K
		"’W˜H", "Ä“‡","“V_‹´‹Ø˜Z’š–Ú", "î’¬", "“ìX’¬", "–k•l", "ä‹Ø–{’¬", "’·–x‹´", "“ú–{‹´",
		"Œb”ü{’¬", "“®•¨‰€‘O","“V‰º’ƒ‰®"},
		{"ˆä‚–ì", "Œõl’š–Ú", "‚¾‚¢‚Ç‚¤–L—¢", "‘¾q‹´¡s","´…","VŒÃXs", "ŠÖ–Ú¬ˆç",//I
		"Š—¶l’š–Ú", "°–ì", "—Î‹´", "¡—¢"}
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
				pmap(p_map, i, current_index)->same_station_list[0]= pmap(p_map, i, current_index);//‰Šú‰»ˆ—‚Ç‚¤‚µ‚æ‚¤
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
	strcpy((pmap(p_map,Num_ele_Linecolor('T'),20)->name ), "“Œ”~“c");
	strcpy((pmap(p_map, Num_ele_Linecolor('Y'), 11)->name), "¼”~“c");
	strcpy((pmap(p_map, Num_ele_Linecolor('Y'), 14)->name), "lƒc‹´");
	
	
	return p_map;

}
//”Õ–ÊˆÚ“®
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
Station_List append_station(Station_List a, station_struct *b) {//ƒŠƒXƒga‚É‰wb‚ğ’Ç‰Á
	a.data[a.length] = b;
	a.length++;
	
	return a;	
}
Station_List delite_station(Station_List a, station_struct *b) {
	
	for (int j = 0; j <= b->same_station_count; j++) {
		for (int i = 0; i < a.length; i++) {
			if (a.data[i] == b->same_station_list[j]) {
				// i”Ô–Ú‚ğíœ‚µA‚»‚êˆÈ~‚ğ¶‚É‹l‚ß‚é
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
Station_List append_station(Station_List a, Station_List b) {//ƒŠƒXƒga‚ÌŒã‚ë‚ÉƒŠƒXƒgb‚Ì“à—e‚ğ’Ç‰Á	
	
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
Station_List safe_append_station(Station_List a, Station_List b) {//ƒŠƒXƒga‚ÌŒã‚ë‚ÉƒŠƒXƒgb‚Ì“à—e‚ğ”í‚è‚È‚­’Ç‰Á
	a = delite_station(a, b);
	a = append_station(a, b);
	return a;
}
Station_List safe_append_station(Station_List a, station_struct *b) {//ƒŠƒXƒga‚ÌŒã‚ë‚ÉƒŠƒXƒgb‚Ì“à—e‚ğ”í‚è‚È‚­’Ç‰Á
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


Station_List* move_list(Station_List* list,station_struct* p_map,player_struct player,int dice) {
	//‰Šú‰»
	for (int i = 0; i <= dice; i++) {
		*(list+i)= define_Station_List(Max_Move_List);
	}
	*(list) = append_station(*(list), player.now_station);
	print_station_list(*(list));
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	
	
	for (int i = 1; i <= dice; i++) {
		Station_List lastlist = *(list + i - 1);
		for (int j = 0; j < lastlist.length; j++) {//i”Ô–Ú‚É“’B‚Å‚«‚é‚·‚×‚Ä‚Ìƒ}ƒX‚É‚Â‚¢‚ÄÀs
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
	while (input_data[i] == '\0') {
		if (input_data[i] - '0' >= 0 && input_data[i] - '9' <= 0) {
			memory = (int)(input_data[i]);
			sta_number = sta_number * 10 + memory;
		}
		else {
			return false_cv;
		}
	}if (line_min_max[line][0] <= sta_number && line_min_max[line][1] >= sta_number) {
		return pmap(p_map, line, sta_number);
	}

}

int main(void) {
	station_struct map[Num_LineColor][Max_Number_Station];
	station_struct* p_map = &map[0][0];
	p_map=define_map(p_map);
	
	int totalplayer = 4;
	player_struct* player;
	int Maxyaer = 1;
	char LineColor[Num_LineColor + 1] = "MYSNPTCKI";
	int line_min_max[Num_LineColor][2] = { {6,30},{11,21},{11,24},{11,27},{9,18},{11,36},{9,23},{1,20},{11,21} };
	//player=Initial_settings(&totalplayer, &Maxyaer,map[Num_ele_Linecolor('S')][10]);
	player = Debug_Initial_settings(pmap(p_map,Num_ele_Linecolor('Y'),13));
	Station_List list[7];
	Station_List* p_list = list;
	//Debug_full_printstation(p_map);
	p_list = move_list(p_list, p_map, *(player), 4);
	char player_input_data[Max_Length_Name_Station];
	for (int year = 1; year <= Maxyaer; year++) {
		for (int count_month = 0; count_month < 4; count_month++) {
			int month = (count_month + 4) % 12;
			printf("%d”N–Ú%dŒ\n",year,month);
			for (int player_id = 0; player_id < totalplayer; player_id++) {
				int dice = rand() % 6 + 1;
				printf("%d\n", dice);
				p_list = move_list(p_list, p_map, *(player+player_id), dice);
				print_station_list(list[dice]);
				station_struct* memory = p_map;
				printf("i‚Ş‰w‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
				scanf("%s", player_input_data);
				memory = inputdata_convert_station(p_map, player_input_data);
				while (memory==p_map) {
					printf("“ü—ÍƒGƒ‰[‚Å‚·B‚à‚¤ˆê“x“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
					scanf("%s", player_input_data);
					memory = inputdata_convert_station(p_map, player_input_data);

				}
				(player + player_id)->now_station = memory;
			}
		}
	}
	
	
}