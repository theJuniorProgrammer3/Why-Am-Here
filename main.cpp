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
"#                  #",
"################ ###"
	},
	{
"################ ###",
"#                  #",
"# =                #",
"#           B      #",
"#       =          #",
"#                  #",
"#                  #",
"#      =           #",
"#                  #",
"################ ###"
	}
};

vector<uint8_t> doors = {16, 16};
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



int main() {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	int inp;
	while(true) {
		refresh();
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
		clear();
	}
	endwin();
}
