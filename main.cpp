#include <cstdint>
#include <ncurses.h>
#include <string>
#include <vector>
#include <random>
#include <map>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<unsigned int> dis(0, 2);
uniform_int_distribution<unsigned int> disX(1, 18);
bernoulli_distribution disLuckInShelf(0.3);
uniform_int_distribution<unsigned int> disInShelf(0, 10);
uniform_int_distribution<unsigned int> disY(1, 8);
uniform_int_distribution<unsigned int> disIs(1, 3);

vector<vector<string>> world = {
	{
"####################",
"#                  #",
"#             =    #",
"#        &         #",
"#                  #",
"#         B        #",
"#   =              #",
"#              =   #",
"#      E           #",
"################ ###"
	},
	{
"################ ###",
"#                  #",
"# =                #",
"#           B      #",
"#       =          #",
"#                  #",
"#              E   #",
"#      =           #",
"#                  #",
"################ ###"
	}
};

vector<uint8_t> doors = {16, 16};
vector<vector<pair<unsigned int, unsigned int>>> enemies = { // Y, X
	{{8, 7}},
	{{6, 15}}
};
void addWorld() {
	vector<string> w = {
"####################",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"####################"
	};
	w[0][doors.back()] = ' ';
	for(int i = 0; i < 3; ++i) {
		w[disY(gen)][disX(gen)] = '=';
	}
		w[disY(gen)][disX(gen)] = 'B';
		w[disY(gen)][disX(gen)] = 'B';
		pair<unsigned int, unsigned int> en = {disY(gen), disX(gen)};
		enemies.push_back({en});
		w[en.first][en.second] = 'E';
		en = {disY(gen), disX(gen)};
		enemies.back().push_back(en);
		w[en.first][en.second] = 'E';
	doors.push_back(disX(gen));
	w[9][doors.back()] = ' ';
	world.push_back(w);	
}

vector<unsigned int> pPos = {0, 3, 9};

void changePos(int ud, int rl) {
	world[pPos[0]][pPos[1]][pPos[2]] = ' ';
	if(pPos[1] + ud == 10) { // world Y size - 1 + 1
		pPos[0]++;
		pPos[1] = 0;
		if(pPos[0] >= world.size()) {
			addWorld();
		}
	} else if((int)pPos[1] + ud == -1) {
		if(pPos[0] > 0) {
		pPos[0]--;
		pPos[1] = 9; // world Y size - 1
		}
	}
	if(world[pPos[0]][pPos[1] + ud][pPos[2]] == ' ') pPos[1] += ud;
	if(world[pPos[0]][pPos[1]][pPos[2] + rl] == ' ') pPos[2] += rl;
	world[pPos[0]][pPos[1]][pPos[2]] = '&';
}

map<vector<unsigned int>, vector<int>> shelfList;

string intToItem(int i) {
	switch(i) {
		case 0:
			return "Empty";
			break;
		case 1:
			return "Cash";
			break;
		case 2:
			return "Atropine";
			break;
		default: // case 3, but no warning
			return "Glucose";
			break;
	}
}

void openShelf(vector<unsigned int> pos) {
	nodelay(stdscr, FALSE);
	clear();
	auto isi = shelfList[pos];
	if(isi.empty()) {
		int itemCount = disInShelf(gen);
		itemCount %= disLuckInShelf(gen) ? 10 : 4;
		if(itemCount == 0) {
			shelfList[pos].push_back(0);
		} else {
			for(int i = 0; i < itemCount; ++i) {
				shelfList[pos].push_back(disIs(gen));
			}
		}
		isi = shelfList[pos];
	}
	for(auto i : isi) {
		printw("%s ", intToItem(i).c_str());
	}
	refresh();
	getch();
	nodelay(stdscr, TRUE);
}

map<char, pair<int, int>> direction = { // xhar, Y, X
					// I will optimize later
 {'e', {-1, 0}},
 {'u', {-1, 0}},
 {'s', {0, -1}},
 {'h', {0, -1}},
 {'d', {1, 0}},
 {'j', {1, 0}},
 {'f', {0, 1}},
 {'k', {0, 1}},
};

void inter(char type) {
	vector<unsigned int> pos;
	char itm;
	pos = {pPos[0], pPos[1] + direction[type].first, pPos[2] + direction[type].second};
	itm = world[pos[0]][pos[1]][pos[2]];
	switch(itm) {
		case '=':
			openShelf(pos);
			break;
	}
}

void push(char type) {
	vector<unsigned int> pos;
	char itm;
	pos = {pPos[0], pPos[1] + direction[type].first, pPos[2] + direction[type].second};
	itm = world[pos[0]][pos[1]][pos[2]];
	if(itm == 'B') {
			if(pos[1] == 9) { // world pos 0 size - 1
				world[pos[0]][9][pos[2]] = ' ';
				if(pos[0] + 1 >= world.size()) addWorld();
				world[pos[0] + 1][1][pos[2]] = 'B';
			} else if(pos[1] == 0) {
				world[pos[0]][0][pos[2]] = ' ';
				world[pos[0] - 1][8][pos[2]] = 'B';
			} else if(world[pos[0]][pos[1] + direction[type].first][pos[2] + direction[type].second] == ' ') {
			world[pos[0]][pos[1]][pos[2]] = ' ';
				world[pos[0]][pos[1] + direction[type].first][pos[2] + direction[type].second] = itm;
			}

	}
}
#ifdef NaturalEnemyMovement
uint8_t moveToWhat(pair<int, int> enemyPos) { // Y, X
	int dx = pPos[2] - enemyPos.second; 
	int dy = pPos[1] - enemyPos.first; 
	float ang = atan2(dy, dx);
	ang *= 57.3; // 180 / PI
		     // temp, later will use radian for speed
	if(ang < 0) ang += 360;
	// to make it fair with player...
	// 0 = kanan
	// 1 = kanan bawah
	// 2 = bawah
	// 3 = kiri bawah
	// 4 = kiri
	// 5 = kiri atas
	// 6 = atas
	// 7 = kanan atas
	return static_cast<uint8_t>(round(ang / 45));
}
#else
// AI gen:
uint8_t moveToWhat(pair<int, int> enemyPos) {
    int dx = pPos[2] - enemyPos.second;
    int dy = pPos[1] - enemyPos.first;

    if (dx == 0 && dy == 0) return 0; // Diam atau default kanan

    if (dx > 0) {         // Sisi KANAN (Sudut -45 sampai 45)
        if (dy > 0) return 1;      // Kanan Bawah
        if (dy < 0) return 7;      // Kanan Atas
        return 0;                  // Tepat Kanan
    }
    else if (dx < 0) {    // Sisi KIRI (Sudut 135 sampai 225)
        if (dy > 0) return 3;      // Kiri Bawah
        if (dy < 0) return 5;      // Kiri Atas
        return 4;                  // Tepat Kiri
    }
    else {                // Sisi VERTIKAL MURNI (dx == 0)
        return (dy > 0) ? 2 : 6;   // 2 = Bawah, 6 = Atas
    }
}
#endif

unsigned int enemiesClock = 0;



int main() {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	int inp;
	map<array<unsigned int, 2>, uint8_t> enemiesMemory; // [enemy's floor, 'a' below] [type]
	while(true) {
		clear();
		// Enemy Movement, basic first...
		vector<pair<unsigned int, unsigned int>> theEnemies = enemies[pPos[0]];
		if(enemiesClock == 30) { // After 30 frame
		enemiesClock = 0;
		for(unsigned int a = 0; a < theEnemies.size(); ++a) {
			auto mtwRes = moveToWhat(theEnemies[a]);
			world[pPos[0]][theEnemies[a].first][theEnemies[a].second] = ' ';
			switch(mtwRes) {
				case 0:
					theEnemies[a].second++;
					break;
				case 1:
					theEnemies[a].second++;
					theEnemies[a].first++;
					break;
				case 2:
					theEnemies[a].first++;
					break;
				case 3:
					theEnemies[a].first++;
					theEnemies[a].second--;
					break;
				case 4:
					theEnemies[a].second--;
					break;
				case 5:
					theEnemies[a].second--;
					theEnemies[a].first--;
					break;
				case 6:
					theEnemies[a].first--;
					break;
				default: // 7 or 8
					theEnemies[a].first--;
					theEnemies[a].second++;
					break;

			}
			if(world[pPos[0]][theEnemies[a].first][theEnemies[a].second] == ' ') {
			enemiesMemory.erase({pPos[0], a});
			enemies[pPos[0]][a] = theEnemies[a];
			world[pPos[0]][theEnemies[a].first][theEnemies[a].second] = 'E';
			} else if(enemiesMemory.find({pPos[0], a}) != enemiesMemory.end()) {
			theEnemies = enemies[pPos[0]];
			switch (enemiesMemory[{pPos[0], a}]) {
				case 0: case 4:
					theEnemies[a].first++;
					break;
				case 2: case 6:
					theEnemies[a].second++;
					break;
				case 1:
					if(world[pPos[0]][theEnemies[a].first + 1][theEnemies[a].second] == ' ') {
						theEnemies[a].first++;
					} else {
						theEnemies[a].second++;
					}
					break;
				case 3:
					if(world[pPos[0]][theEnemies[a].first + 1][theEnemies[a].second] == ' ') {
						theEnemies[a].first++;
					} else {
						theEnemies[a].second--;
					}
					break;
				case 5:
					if(world[pPos[0]][theEnemies[a].first - 1][theEnemies[a].second] == ' ') {
						theEnemies[a].first--;
					} else {
						theEnemies[a].second--;
					}
					break;
				default:
					if(world[pPos[0]][theEnemies[a].first - 1][theEnemies[a].second] == ' ') {
						theEnemies[a].first--;
					} else {
						theEnemies[a].second++;
					}
					break;
			}
			enemies[pPos[0]][a] = theEnemies[a];
			} else {
				theEnemies = enemies[pPos[0]];
				enemiesMemory[{pPos[0], a}] = mtwRes;
			}
			world[pPos[0]][theEnemies[a].first][theEnemies[a].second] = 'E';
		}
		}
		enemiesClock++;
		for(auto b : world[pPos[0]]) {
			for(auto c : b) {
				//printw("[%c]", (c == "p" ? "&" : " ));
				printw("%c", c);
			}
			printw("\n");
		}
		inp = getch();
		if(inp == KEY_RIGHT) changePos(0, 1);
		else if(inp == KEY_LEFT) changePos(0, -1);
		else if(inp == KEY_UP) changePos(-1, 0);
		else if(inp == KEY_DOWN) changePos(1, 0);
		else if(inp == 'q') break;
		if(inp == 'e' || inp == 's' || inp == 'd' || inp == 'f') inter(inp);
		if(inp == 'u' || inp == 'h' || inp == 'j' || inp == 'k') push(inp);
		napms(17);
		refresh();
	}
	endwin();
}
