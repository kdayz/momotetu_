import pygame
import sys
import random
import math

# --- 初期設定 ---
pygame.init()
SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 900
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("大阪メトロ：全駅統合・完全版")

# 色定義
WHITE = (245, 245, 245)
BLACK = (20, 20, 20)
HIGHLIGHT_COLOR = (255, 255, 0)
TEXT_BG_COLOR = (255, 255, 255, 200)

# プレイヤーカラー
PLAYERS_CONFIG = [
    {"name": "1P 赤", "color": (255, 50, 50)},
    {"name": "2P 青", "color": (50, 100, 255)},
    {"name": "3P 緑", "color": (50, 200, 50)},
    {"name": "4P 黄", "color": (220, 200, 0)},
]

# 路線カラー定義
LINE_COLORS = {
    "M": (229, 23, 31),    # 御堂筋線 (赤)
    "Y": (0, 114, 188),    # 四つ橋線 (青)
    "T": (81, 44, 168),    # 谷町線 (紫)
    "C": (15, 118, 59),    # 中央線 (緑)
    "S": (229, 23, 107),   # 千日前線 (ピンク)
    "K": (102, 51, 0),     # 堺筋線 (茶)
    "N": (169, 204, 81),   # 長堀鶴見緑地線 (黄緑)
    "I": (243, 151, 0),    # 今里筋線 (オレンジ)
    "P": (51, 153, 204),   # 南港ポートタウン線 (水色)
}

# --- 画像読み込み ---
try:
    station_img_raw = pygame.image.load("station.png")
    train_img_raw = pygame.image.load("train.png")
except FileNotFoundError:
    print("エラー：画像ファイルが見つかりません。")
    print("make_images.py を実行して station.png と train.png を作成してください。")
    sys.exit()

# ==========================================
# 1. 駅データ (JSON形式)
# ==========================================
raw_data = {
    "M6": {"StationName": "箕面萱野", "LineColor": "M", "StationNumber": 6},
    "M7": {"StationName": "箕面船場阪大前", "LineColor": "M", "StationNumber": 7},
    "M8": {"StationName": "千里中央", "LineColor": "M", "StationNumber": 8},
    "M9": {"StationName": "桃山台", "LineColor": "M", "StationNumber": 9},
    "M10": {"StationName": "緑地公園", "LineColor": "M", "StationNumber": 10},
    "M11": {"StationName": "江坂", "LineColor": "M", "StationNumber": 11},
    "M12": {"StationName": "東三国", "LineColor": "M", "StationNumber": 12},
    "M13": {"StationName": "新大阪", "LineColor": "M", "StationNumber": 13},
    "M14": {"StationName": "西中島南方", "LineColor": "M", "StationNumber": 14},
    "M15": {"StationName": "中津", "LineColor": "M", "StationNumber": 15},
    "M16": {"StationName": "梅田", "LineColor": "M", "StationNumber": 16, "Transfer": ["Y11", "T20"]},
    "M17": {"StationName": "淀屋橋", "LineColor": "M", "StationNumber": 17},
    "M18": {"StationName": "本町", "LineColor": "M", "StationNumber": 18, "Transfer": ["C16", "Y13"]},
    "M19": {"StationName": "心斎橋", "LineColor": "M", "StationNumber": 19, "Transfer": ["Y14", "N15"]},
    "M20": {"StationName": "なんば", "LineColor": "M", "StationNumber": 20, "Transfer": ["Y15", "S16"]},
    "M21": {"StationName": "大国町", "LineColor": "M", "StationNumber": 21, "Transfer": ["Y16"]},
    "M22": {"StationName": "動物園前", "LineColor": "M", "StationNumber": 22, "Transfer": ["K19"]},
    "M23": {"StationName": "天王寺", "LineColor": "M", "StationNumber": 23, "Transfer": ["T27"]},
    "M24": {"StationName": "昭和町", "LineColor": "M", "StationNumber": 24},
    "M25": {"StationName": "西田辺", "LineColor": "M", "StationNumber": 25},
    "M26": {"StationName": "長居", "LineColor": "M", "StationNumber": 26},
    "M27": {"StationName": "あびこ", "LineColor": "M", "StationNumber": 27},
    "M28": {"StationName": "北花田", "LineColor": "M", "StationNumber": 28},
    "M29": {"StationName": "新金岡", "LineColor": "M", "StationNumber": 29},
    "M30": {"StationName": "なかもず", "LineColor": "M", "StationNumber": 30},

    "Y11": {"StationName": "西梅田", "LineColor": "Y", "StationNumber": 11, "Transfer": ["M16", "T20"]},
    "Y12": {"StationName": "肥後橋", "LineColor": "Y", "StationNumber": 12},
    "Y13": {"StationName": "本町", "LineColor": "Y", "StationNumber": 13, "Transfer": ["M18", "C16"]},
    "Y14": {"StationName": "四ツ橋", "LineColor": "Y", "StationNumber": 14, "Transfer": ["M19", "N15"]},
    "Y15": {"StationName": "なんば", "LineColor": "Y", "StationNumber": 15, "Transfer": ["M20", "S16"]},
    "Y16": {"StationName": "大国町", "LineColor": "Y", "StationNumber": 16, "Transfer": ["M21"]},
    "Y17": {"StationName": "花薗町", "LineColor": "Y", "StationNumber": 17},
    "Y18": {"StationName": "岸里", "LineColor": "Y", "StationNumber": 18},
    "Y19": {"StationName": "玉出", "LineColor": "Y", "StationNumber": 19},
    "Y20": {"StationName": "北加賀屋", "LineColor": "Y", "StationNumber": 20},
    "Y21": {"StationName": "住之江公園", "LineColor": "Y", "StationNumber": 21, "Transfer": ["P18"]},

    "S11": {"StationName": "野田阪神", "LineColor": "S", "StationNumber": 11},
    "S12": {"StationName": "玉川", "LineColor": "S", "StationNumber": 12},
    "S13": {"StationName": "阿波座", "LineColor": "S", "StationNumber": 13, "Transfer": ["C15"]},
    "S14": {"StationName": "西長堀", "LineColor": "S", "StationNumber": 14, "Transfer": ["N13"]},
    "S15": {"StationName": "桜川", "LineColor": "S", "StationNumber": 15},
    "S16": {"StationName": "なんば", "LineColor": "S", "StationNumber": 16, "Transfer": ["M20", "Y15"]},
    "S17": {"StationName": "日本橋", "LineColor": "S", "StationNumber": 17, "Transfer": ["K17"]},
    "S18": {"StationName": "谷町九丁目", "LineColor": "S", "StationNumber": 18, "Transfer": ["T25"]},
    "S19": {"StationName": "鶴橋", "LineColor": "S", "StationNumber": 19},
    "S20": {"StationName": "今里", "LineColor": "S", "StationNumber": 20, "Transfer": ["I21"]},
    "S21": {"StationName": "新深江", "LineColor": "S", "StationNumber": 21},
    "S22": {"StationName": "小路", "LineColor": "S", "StationNumber": 22},
    "S23": {"StationName": "北巽", "LineColor": "S", "StationNumber": 23},
    "S24": {"StationName": "南巽", "LineColor": "S", "StationNumber": 24},

    "N11": {"StationName": "大正", "LineColor": "N", "StationNumber": 11},
    "N12": {"StationName": "ドーム前", "LineColor": "N", "StationNumber": 12},
    "N13": {"StationName": "西長堀", "LineColor": "N", "StationNumber": 13, "Transfer": ["S14"]},
    "N14": {"StationName": "西大橋", "LineColor": "N", "StationNumber": 14},
    "N15": {"StationName": "心斎橋", "LineColor": "N", "StationNumber": 15, "Transfer": ["M19", "Y14"]},
    "N16": {"StationName": "長堀橋", "LineColor": "N", "StationNumber": 16, "Transfer": ["K16"]},
    "N17": {"StationName": "松屋町", "LineColor": "N", "StationNumber": 17},
    "N18": {"StationName": "谷町六丁目", "LineColor": "N", "StationNumber": 18, "Transfer": ["T24"]},
    "N19": {"StationName": "玉造", "LineColor": "N", "StationNumber": 19},
    "N20": {"StationName": "森ノ宮", "LineColor": "N", "StationNumber": 20, "Transfer": ["C19"]},
    "N21": {"StationName": "大阪BP", "LineColor": "N", "StationNumber": 21},
    "N22": {"StationName": "京橋", "LineColor": "N", "StationNumber": 22},
    "N23": {"StationName": "蒲生四丁目", "LineColor": "N", "StationNumber": 23, "Transfer": ["I18"]},
    "N24": {"StationName": "今福鶴見", "LineColor": "N", "StationNumber": 24},
    "N25": {"StationName": "横堤", "LineColor": "N", "StationNumber": 25},
    "N26": {"StationName": "鶴見緑地", "LineColor": "N", "StationNumber": 26},
    "N27": {"StationName": "門真南", "LineColor": "N", "StationNumber": 27},

    "P9": {"StationName": "コスモ", "LineColor": "P", "StationNumber": 9, "Transfer": ["C10"]},
    "P10": {"StationName": "トレードC", "LineColor": "P", "StationNumber": 10},
    "P11": {"StationName": "中ふ頭", "LineColor": "P", "StationNumber": 11},
    "P12": {"StationName": "Pタウン西", "LineColor": "P", "StationNumber": 12},
    "P13": {"StationName": "Pタウン東", "LineColor": "P", "StationNumber": 13},
    "P14": {"StationName": "フェリーT", "LineColor": "P", "StationNumber": 14},
    "P15": {"StationName": "南港東", "LineColor": "P", "StationNumber": 15},
    "P16": {"StationName": "南港口", "LineColor": "P", "StationNumber": 16},
    "P17": {"StationName": "平林", "LineColor": "P", "StationNumber": 17},
    "P18": {"StationName": "住之江公園", "LineColor": "P", "StationNumber": 18, "Transfer": ["Y21"]},

    "T11": {"StationName": "大日", "LineColor": "T", "StationNumber": 11},
    "T12": {"StationName": "守口", "LineColor": "T", "StationNumber": 12},
    "T13": {"StationName": "太子橋今市", "LineColor": "T", "StationNumber": 13, "Transfer": ["I14"]},
    "T14": {"StationName": "千林大宮", "LineColor": "T", "StationNumber": 14},
    "T15": {"StationName": "関目高殿", "LineColor": "T", "StationNumber": 15},
    "T16": {"StationName": "野江内代", "LineColor": "T", "StationNumber": 16},
    "T17": {"StationName": "都島", "LineColor": "T", "StationNumber": 17},
    "T18": {"StationName": "天六", "LineColor": "T", "StationNumber": 18, "Transfer": ["K11"]},
    "T19": {"StationName": "中崎町", "LineColor": "T", "StationNumber": 19},
    "T20": {"StationName": "東梅田", "LineColor": "T", "StationNumber": 20, "Transfer": ["M16", "Y11"]},
    "T21": {"StationName": "南森町", "LineColor": "T", "StationNumber": 21, "Transfer": ["K13"]},
    "T22": {"StationName": "天満橋", "LineColor": "T", "StationNumber": 22},
    "T23": {"StationName": "谷町四", "LineColor": "T", "StationNumber": 23, "Transfer": ["C18"]},
    "T24": {"StationName": "谷町六", "LineColor": "T", "StationNumber": 24, "Transfer": ["N18"]},
    "T25": {"StationName": "谷町九", "LineColor": "T", "StationNumber": 25, "Transfer": ["S18"]},
    "T26": {"StationName": "四天王寺", "LineColor": "T", "StationNumber": 26},
    "T27": {"StationName": "天王寺", "LineColor": "T", "StationNumber": 27, "Transfer": ["M23"]},
    "T28": {"StationName": "阿倍野", "LineColor": "T", "StationNumber": 28},
    "T29": {"StationName": "文の里", "LineColor": "T", "StationNumber": 29},
    "T30": {"StationName": "田辺", "LineColor": "T", "StationNumber": 30},
    "T31": {"StationName": "駒川中野", "LineColor": "T", "StationNumber": 31},
    "T32": {"StationName": "平野", "LineColor": "T", "StationNumber": 32},
    "T33": {"StationName": "喜連瓜破", "LineColor": "T", "StationNumber": 33},
    "T34": {"StationName": "出戸", "LineColor": "T", "StationNumber": 34},
    "T35": {"StationName": "長原", "LineColor": "T", "StationNumber": 35},
    "T36": {"StationName": "八尾南", "LineColor": "T", "StationNumber": 36},

    "C9": {"StationName": "夢洲", "LineColor": "C", "StationNumber": 9},
    "C10": {"StationName": "コスモ", "LineColor": "C", "StationNumber": 10, "Transfer": ["P9"]},
    "C11": {"StationName": "大阪港", "LineColor": "C", "StationNumber": 11},
    "C12": {"StationName": "朝潮橋", "LineColor": "C", "StationNumber": 12},
    "C13": {"StationName": "弁天町", "LineColor": "C", "StationNumber": 13},
    "C14": {"StationName": "九条", "LineColor": "C", "StationNumber": 14},
    "C15": {"StationName": "阿波座", "LineColor": "C", "StationNumber": 15, "Transfer": ["S13"]},
    "C16": {"StationName": "本町", "LineColor": "C", "StationNumber": 16, "Transfer": ["M18", "Y13"]},
    "C17": {"StationName": "堺筋本町", "LineColor": "C", "StationNumber": 17, "Transfer": ["K15"]},
    "C18": {"StationName": "谷町四", "LineColor": "C", "StationNumber": 18, "Transfer": ["T23"]},
    "C19": {"StationName": "森ノ宮", "LineColor": "C", "StationNumber": 19, "Transfer": ["N20"]},
    "C20": {"StationName": "緑橋", "LineColor": "C", "StationNumber": 20, "Transfer": ["I20"]},
    "C21": {"StationName": "深江橋", "LineColor": "C", "StationNumber": 21},
    "C22": {"StationName": "高井田", "LineColor": "C", "StationNumber": 22},
    "C23": {"StationName": "長田", "LineColor": "C", "StationNumber": 23},
    "C24": {"StationName": "荒本", "LineColor": "C", "StationNumber": 24},
    "C25": {"StationName": "吉田", "LineColor": "C", "StationNumber": 25},
    "C26": {"StationName": "新石切", "LineColor": "C", "StationNumber": 26},
    "C27": {"StationName": "生駒", "LineColor": "C", "StationNumber": 27},
    "C28": {"StationName": "白庭台", "LineColor": "C", "StationNumber": 28},
    "C29": {"StationName": "北生駒", "LineColor": "C", "StationNumber": 29},
    "C30": {"StationName": "登美ヶ丘", "LineColor": "C", "StationNumber": 30},

    "K11": {"StationName": "天六", "LineColor": "K", "StationNumber": 11, "Transfer": ["T18"]},
    "K12": {"StationName": "扇町", "LineColor": "K", "StationNumber": 12},
    "K13": {"StationName": "南森町", "LineColor": "K", "StationNumber": 13, "Transfer": ["T21"]},
    "K14": {"StationName": "北浜", "LineColor": "K", "StationNumber": 14},
    "K15": {"StationName": "堺筋本町", "LineColor": "K", "StationNumber": 15, "Transfer": ["C17"]},
    "K16": {"StationName": "長堀橋", "LineColor": "K", "StationNumber": 16, "Transfer": ["N16"]},
    "K17": {"StationName": "日本橋", "LineColor": "K", "StationNumber": 17, "Transfer": ["S17"]},
    "K18": {"StationName": "恵美須町", "LineColor": "K", "StationNumber": 18},
    "K19": {"StationName": "動物園前", "LineColor": "K", "StationNumber": 19, "Transfer": ["M22"]},
    "K20": {"StationName": "天下茶屋", "LineColor": "K", "StationNumber": 20},

    "I11": {"StationName": "井高野", "LineColor": "I", "StationNumber": 11},
    "I12": {"StationName": "瑞光四", "LineColor": "I", "StationNumber": 12},
    "I13": {"StationName": "豊里", "LineColor": "I", "StationNumber": 13},
    "I14": {"StationName": "太子橋", "LineColor": "I", "StationNumber": 14, "Transfer": ["T13"]},
    "I15": {"StationName": "清水", "LineColor": "I", "StationNumber": 15},
    "I16": {"StationName": "新森古市", "LineColor": "I", "StationNumber": 16},
    "I17": {"StationName": "関目生育", "LineColor": "I", "StationNumber": 17},
    "I18": {"StationName": "蒲生四", "LineColor": "I", "StationNumber": 18, "Transfer": ["N23"]},
    "I19": {"StationName": "鴫野", "LineColor": "I", "StationNumber": 19},
    "I20": {"StationName": "緑橋", "LineColor": "I", "StationNumber": 20, "Transfer": ["C20"]},
    "I21": {"StationName": "今里", "LineColor": "I", "StationNumber": 21, "Transfer": ["S20"]},
}

# ==========================================
# 2. 座標の手動定義（乗換駅合体版）
# ==========================================
pos_map = {}

# グリッド定数
COL_Y = 500
COL_M = 1000
COL_K = 1500
COL_T = 2000
COL_I = 2500

ROW_SHINOSAKA = 500
ROW_UMEDA = 1000
ROW_HONMACHI = 1500
ROW_SHINSAIBASHI = 2000
ROW_NAMBA = 2500
ROW_TENNOJI = 3000

# (A) 路線ごとの基本配置
# 御堂筋線 (M)
for i in range(6, 31):
    pos_map[f"M{i}"] = (COL_M, ROW_SHINOSAKA + (i-13)*100)

# 四つ橋線 (Y)
for i in range(11, 22):
    pos_map[f"Y{i}"] = (COL_Y, ROW_UMEDA + (i-11)*170)

# 堺筋線 (K)
for i in range(11, 21):
    pos_map[f"K{i}"] = (COL_K, 800 + (i-11)*230)

# 谷町線 (T)
for i in range(11, 37):
    pos_map[f"T{i}"] = (COL_T, 200 + (i-11)*100)

# 今里筋線 (I)
for i in range(11, 22):
    pos_map[f"I{i}"] = (COL_I, 500 + (i-11)*150)

# 中央線 (C)
for i in range(9, 31):
    pos_map[f"C{i}"] = (COL_M + (i-16)*250, ROW_HONMACHI)

# 長堀鶴見緑地線 (N)
for i in range(11, 28):
    pos_map[f"N{i}"] = (COL_M + (i-15)*250, ROW_SHINSAIBASHI)

# 千日前線 (S)
for i in range(11, 25):
    pos_map[f"S{i}"] = (COL_M + (i-16)*250, ROW_NAMBA)

# 南港ポートタウン線 (P)
for i in range(9, 19):
    # C10基準で下に伸ばす
    c10_x = COL_M + (10-16)*250
    pos_map[f"P{i}"] = (c10_x, ROW_HONMACHI + (i-9)*120)


# (B) ★強制合体（Hub Overwrite）★
# ここで指定した座標に全ての路線が集まります
HUB_POSITIONS = {
    # 梅田・西梅田・東梅田
    "M16": (COL_M, ROW_UMEDA),
    "Y11": (COL_Y, ROW_UMEDA),      # 西梅田は少し離す
    "T20": (COL_M+150, ROW_UMEDA),  # 東梅田は少し右

    # 本町 (M, C, Y) -> 完全合体
    "M18": (COL_M, ROW_HONMACHI),
    "C16": (COL_M, ROW_HONMACHI),
    "Y13": (COL_M-150, ROW_HONMACHI), # Y本町は少し左に置かないと線が重なりすぎる

    # 心斎橋 (M, N, Y)
    "M19": (COL_M, ROW_SHINSAIBASHI),
    "N15": (COL_M, ROW_SHINSAIBASHI),
    "Y14": (COL_Y, ROW_SHINSAIBASHI), # 四ツ橋

    # なんば (M, S, Y) -> 完全合体
    "M20": (COL_M, ROW_NAMBA),
    "S16": (COL_M, ROW_NAMBA),
    "Y15": (COL_M, ROW_NAMBA), 

    # 天王寺・動物園前
    "M22": (COL_M, 2900),
    "K19": (COL_M, 2900), # 動物園前合体
    "M23": (COL_M, ROW_TENNOJI),
    "T27": (COL_M, ROW_TENNOJI), # 天王寺合体

    # 天六・南森町
    "K11": (COL_K, 800),
    "T18": (COL_K, 800), # 天六合体
    "K13": (COL_K, 1100),
    "T21": (COL_K, 1100), # 南森町合体

    # 堺筋本町
    "K15": (COL_K, ROW_HONMACHI),
    "C17": (COL_K, ROW_HONMACHI), # 合体

    # 日本橋
    "K17": (COL_K, ROW_NAMBA),
    "S17": (COL_K, ROW_NAMBA), # 合体

    # 谷町四
    "T23": (COL_T, ROW_HONMACHI),
    "C18": (COL_T, ROW_HONMACHI), # 合体

    # 谷町六
    "T24": (COL_T, ROW_SHINSAIBASHI),
    "N18": (COL_T, ROW_SHINSAIBASHI), # 合体

    # 谷町九
    "T25": (COL_T, ROW_NAMBA),
    "S18": (COL_T, ROW_NAMBA), # 合体

    # その他
    "M21": (COL_M, 2750), 
    "Y16": (COL_M, 2750), # 大国町合体
    
    "C15": (COL_Y, ROW_HONMACHI), 
    "S13": (COL_Y, ROW_HONMACHI), # 阿波座合体(Y軸上)

    "N20": (2200, ROW_HONMACHI), 
    "C19": (2200, ROW_HONMACHI), # 森ノ宮合体

    "I20": (COL_I, ROW_HONMACHI),
    "C20": (COL_I, ROW_HONMACHI), # 緑橋合体

    "I18": (COL_I, 1700),
    "N23": (COL_I, 1700), # 蒲生四合体

    "I21": (COL_I, ROW_NAMBA),
    "S20": (COL_I, ROW_NAMBA), # 今里合体
}
pos_map.update(HUB_POSITIONS)


# ==========================================
# 3. ノードと接続の生成
# ==========================================
all_nodes = []
node_indices = {}
connections = {}

# ノード生成
for key, data in raw_data.items():
    if key not in pos_map: continue
    
    new_node = {
        "type": "station",
        "id": key,
        "name": data["StationName"],
        "color": LINE_COLORS.get(data["LineColor"], BLACK),
        "pos": pos_map[key]
    }
    all_nodes.append(new_node)
    idx = len(all_nodes) - 1
    node_indices[key] = idx
    connections[idx] = []

# 線路生成
lines = {}
for key in raw_data.keys():
    line_char = key[0]
    if line_char not in lines: lines[line_char] = []
    lines[line_char].append(key)

for line_char, station_keys in lines.items():
    sorted_keys = sorted(station_keys, key=lambda k: int(k[1:]))
    for i in range(len(sorted_keys) - 1):
        k1 = sorted_keys[i]
        k2 = sorted_keys[i+1]
        
        if k1 in node_indices and k2 in node_indices:
            idx1 = node_indices[k1]
            idx2 = node_indices[k2]
            
            p1 = all_nodes[idx1]["pos"]
            p2 = all_nodes[idx2]["pos"]
            dist = math.sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2)
            
            # 密度：150pxにつき1マス
            num_tracks = max(1, int(dist / 150))
            
            prev_idx = idx1
            line_color = all_nodes[idx1]["color"]
            
            for j in range(1, num_tracks + 1):
                t = j / (num_tracks + 1)
                bx = p1[0] + (p2[0] - p1[0]) * t
                by = p1[1] + (p2[1] - p1[1]) * t
                
                track_node = {
                    "type": "track",
                    "name": "",
                    "pos": (bx, by),
                    "color": line_color
                }
                all_nodes.append(track_node)
                new_idx = len(all_nodes) - 1
                connections[new_idx] = []
                
                connections[prev_idx].append(new_idx)
                connections[new_idx].append(prev_idx)
                prev_idx = new_idx
            
            connections[prev_idx].append(idx2)
            connections[idx2].append(prev_idx)

# 乗り換え接続（徒歩）
for key, data in raw_data.items():
    if "Transfer" in data and key in node_indices:
        idx1 = node_indices[key]
        for target_key in data["Transfer"]:
            if target_key in node_indices:
                idx2 = node_indices[target_key]
                connections[idx1].append(idx2)
                connections[idx2].append(idx1)

# ==========================================
# ゲーム変数
# ==========================================
start_node_id = node_indices["M13"]
players = []
for config in PLAYERS_CONFIG:
    players.append({
        "name": config["name"],
        "color": config["color"],
        "pos_idx": start_node_id, 
        "history": [],
    })

current_player_id = 0
remaining_steps = 0
dice_value = 0
state = "WAIT_DICE"
reachable_nodes = []

# カメラ初期位置
camera_offset_x = -COL_M + SCREEN_WIDTH/2
camera_offset_y = -ROW_UMEDA + SCREEN_HEIGHT/2
zoom_scale = 0.3 # 広域視点

def to_screen(pos):
    wx, wy = pos
    sx = (wx * zoom_scale) + camera_offset_x + SCREEN_WIDTH/2
    sy = (wy * zoom_scale) + camera_offset_y + SCREEN_HEIGHT/2
    return (sx, sy)

def to_world(pos):
    sx, sy = pos
    wx = (sx - SCREEN_WIDTH/2 - camera_offset_x) / zoom_scale
    wy = (sy - SCREEN_HEIGHT/2 - camera_offset_y) / zoom_scale
    return (wx, wy)

def get_reachable_indices(start_idx, steps, prohibited_prev_idx):
    current_states = {(start_idx, prohibited_prev_idx)}
    for _ in range(steps):
        next_states = set()
        for curr, prev in current_states:
            for neighbor in connections.get(curr, []):
                if neighbor != prev:
                    next_states.add((neighbor, curr))
        current_states = next_states
    return list({state[0] for state in current_states})

font = pygame.font.Font("C:/Windows/Fonts/msgothic.ttc", 16)
big_font = pygame.font.Font(None, 40)
clock = pygame.time.Clock()
is_dragging = False
last_mouse_pos = (0, 0)

# --- メインループ ---
running = True
while running:
    current_p = players[current_player_id]

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        
        elif event.type == pygame.MOUSEWHEEL:
            mx, my = pygame.mouse.get_pos()
            wx_before, wy_before = to_world((mx, my))
            zoom_speed = 0.05
            new_zoom = zoom_scale + zoom_speed if event.y < 0 else zoom_scale - zoom_speed
            zoom_scale = max(0.05, min(2.0, new_zoom))
            wx_after, wy_after = to_world((mx, my))
            camera_offset_x += (wx_after - wx_before) * zoom_scale
            camera_offset_y += (wy_after - wy_before) * zoom_scale
        
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                is_dragging = True
                last_mouse_pos = pygame.mouse.get_pos()
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1: is_dragging = False
        elif event.type == pygame.MOUSEMOTION:
            if is_dragging:
                mx, my = pygame.mouse.get_pos()
                camera_offset_x += mx - last_mouse_pos[0]
                camera_offset_y += my - last_mouse_pos[1]
                last_mouse_pos = (mx, my)

        elif event.type == pygame.KEYDOWN:
            if state == "WAIT_DICE":
                if event.key == pygame.K_SPACE:
                    dice_value = random.randint(1, 6)
                    remaining_steps = dice_value
                    current_p["history"] = [current_p["pos_idx"]]
                    reachable_nodes = get_reachable_indices(current_p["pos_idx"], remaining_steps, -1)
                    state = "MOVING"

            elif state == "MOVING":
                cx, cy = all_nodes[current_p["pos_idx"]]["pos"]
                target_idx = -1
                input_vec = None
                if event.key == pygame.K_LEFT:  input_vec = (-1, 0)
                elif event.key == pygame.K_RIGHT: input_vec = (1, 0)
                elif event.key == pygame.K_UP:    input_vec = (0, -1)
                elif event.key == pygame.K_DOWN:  input_vec = (0, 1)

                if input_vec:
                    for neighbor_idx in connections.get(current_p["pos_idx"], []):
                        nx, ny = all_nodes[neighbor_idx]["pos"]
                        dx, dy = nx - cx, ny - cy
                        match = False
                        if input_vec[0] == 1 and dx > 1: match = True
                        elif input_vec[0] == -1 and dx < -1: match = True
                        elif input_vec[1] == 1 and dy > 1: match = True
                        elif input_vec[1] == -1 and dy < -1: match = True
                        if match:
                            target_idx = neighbor_idx
                            break
                if target_idx != -1:
                    history = current_p["history"]
                    if len(history) >= 2 and target_idx == history[-2]:
                        current_p["pos_idx"] = target_idx
                        remaining_steps += 1
                        history.pop()
                    else:
                        current_p["pos_idx"] = target_idx
                        remaining_steps -= 1
                        history.append(target_idx)
                    if remaining_steps == 0:
                        current_p["history"] = []
                        reachable_nodes = []
                        current_player_id = (current_player_id + 1) % 4
                        state = "WAIT_DICE"
                    else:
                        prev_node = history[-2] if len(history) >= 2 else -1
                        reachable_nodes = get_reachable_indices(current_p["pos_idx"], remaining_steps, prev_node)

    screen.fill(WHITE)

    # 線の描画
    line_width = max(2, int(6 * zoom_scale))
    drawn_edges = set()
    for idx, neighbors in connections.items():
        p1 = to_screen(all_nodes[idx]["pos"])
        for n_idx in neighbors:
            if (idx, n_idx) in drawn_edges or (n_idx, idx) in drawn_edges: continue
            p2 = to_screen(all_nodes[n_idx]["pos"])
            color = all_nodes[idx]["color"]
            if all_nodes[idx]["type"] == "station" and all_nodes[n_idx]["type"] == "station":
                # 駅同士の直接連絡（乗り換え）はグレー
                pygame.draw.line(screen, (200, 200, 200), p1, p2, int(line_width))
            else:
                pygame.draw.line(screen, color, p1, p2, line_width)
            drawn_edges.add((idx, n_idx))

    # ノード
    station_size = max(10, int(36 * zoom_scale))
    track_size = max(4, int(10 * zoom_scale))
    scaled_station = pygame.transform.smoothscale(station_img_raw, (station_size, station_size))
    
    for node in all_nodes:
        sx, sy = to_screen(node["pos"])
        if sx < -50 or sx > SCREEN_WIDTH+50 or sy < -50 or sy > SCREEN_HEIGHT+50: continue

        if node["type"] == "station":
            rect = scaled_station.get_rect(center=(sx, sy))
            screen.blit(scaled_station, rect)
            
            if zoom_scale > 0.2:
                txt = font.render(node["name"], True, BLACK)
                y_offset = station_size/2 + 5
                # IDによって上下に散らして重なり防止
                if int(node["id"][1:]) % 2 == 0: y_offset = -y_offset - 15
                
                txt_rect = txt.get_rect(center=(sx, sy + y_offset))
                bg = txt_rect.inflate(4, 2)
                s = pygame.Surface((bg.width, bg.height), pygame.SRCALPHA)
                s.fill(TEXT_BG_COLOR)
                screen.blit(s, bg)
                screen.blit(txt, txt_rect)
        else:
            pygame.draw.rect(screen, node["color"], (sx-track_size/2, sy-track_size/2, track_size, track_size))

    # プレイヤー
    pt_size = int(28 * zoom_scale)
    scaled_train = pygame.transform.smoothscale(train_img_raw, (pt_size, pt_size))
    offsets = [(-6, -6), (6, -6), (-6, 6), (6, 6)]
    
    for i, p in enumerate(players):
        px, py = to_screen(all_nodes[p["pos_idx"]]["pos"])
        ox, oy = offsets[i][0]*zoom_scale, offsets[i][1]*zoom_scale
        r = pygame.Rect(0, 0, pt_size+6, pt_size+6)
        r.center = (px+ox, py+oy)
        pygame.draw.rect(screen, p["color"], r, border_radius=4)
        screen.blit(scaled_train, scaled_train.get_rect(center=(px+ox, py+oy)))
        if i == current_player_id:
             pygame.draw.polygon(screen, p["color"], [
                (px+ox, py+oy-pt_size/2-5), (px+ox-5, py+oy-pt_size/2-15), (px+ox+5, py+oy-pt_size/2-15)
            ])

    # ハイライト
    if state == "MOVING":
        for idx in reachable_nodes:
            hx, hy = to_screen(all_nodes[idx]["pos"])
            rad = int(22 * zoom_scale) if all_nodes[idx]["type"] == "station" else int(12 * zoom_scale)
            pygame.draw.circle(screen, HIGHLIGHT_COLOR, (hx, hy), rad)

    # UI
    turn_bg = pygame.Surface((300, 60))
    turn_bg.fill(WHITE)
    pygame.draw.rect(turn_bg, players[current_player_id]["color"], turn_bg.get_rect(), 4)
    screen.blit(turn_bg, (20, 20))
    screen.blit(big_font.render(f"Turn: {players[current_player_id]['name']}", True, BLACK), (30, 35))

    if state == "WAIT_DICE":
        msg = big_font.render("Press SPACE", True, BLACK)
        screen.blit(msg, (SCREEN_WIDTH/2 - 100, 50))
    elif state == "MOVING":
        msg = big_font.render(f"Dice: {dice_value} Rem: {remaining_steps}", True, BLACK)
        screen.blit(msg, (SCREEN_WIDTH/2 - 100, 50))

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
sys.exit()