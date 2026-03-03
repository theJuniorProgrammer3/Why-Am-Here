#include <ncurses.h>
#include <vector>
#include <random>
#include <map>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<unsigned int> dis(0, 2);
uniform_int_distribution<unsigned int> disIs(1, 3);

vector<vector<string>> world = {
	{
"####################",
"#                  #",
"#             =    #",
"#        &         #",
"#                  #",
"#                  #",
"#   =              #",
"#              =   #",
"#                  #",
"################ ###"
	},
	{
"################ ###",
"#                  #",
"# =                #",
"#                  #",
"#       =          #",
"#                  #",
"#                  #",
"#      =           #",
"#                  #",
"################ ###"
	}
};

vector<unsigned int> pPos = {0, 3, 9};

void changePos(int ud, int rl) {
	world[pPos[0]][pPos[1]][pPos[2]] = ' ';
	if(pPos[1] + ud == world[pPos[0]].size()) {
		if(pPos[0] + 1 < world.size()) {
		pPos[0]++;
		pPos[1] = 0;
		}
	} else if((int)pPos[1] + ud == -1) {
		if(pPos[0] > 0) {
		pPos[0]--;
		pPos[1] = world[pPos[0]].size() - 1;
		}
	}
	if(world[pPos[0]][pPos[1] + ud][pPos[2]] == ' ') pPos[1] += ud;
	if(world[pPos[0]][pPos[1]][pPos[2] + rl] == ' ') pPos[2] += rl;
	world[pPos[0]][pPos[1]][pPos[2]] = '&';
}

map<vector<unsigned int>, vector<int>> shelfList;

void openShelf(vector<unsigned int> pos) {
	nodelay(stdscr, FALSE);
	clear();
	auto isi = shelfList[pos];
	if(isi.empty()) {
		for(int i = 0; i < 10; ++i) {
			shelfList[pos].push_back(disIs(gen));
		}
		isi = shelfList[pos];
	}
	for(auto i : isi) {
		printw("%i ", i);
	}
	refresh();
	getch();
	nodelay(stdscr, TRUE);
}

void inter(char type) {
	vector<unsigned int> pos;
	char itm;
		switch(type) {
			case 'e':
				pos = {pPos[0], pPos[1] - 1, pPos[2]};
				break;
			case 's':
				pos = {pPos[0], pPos[1], pPos[2] - 1};
				break;
			case 'd':
				pos = {pPos[0], pPos[1] + 1, pPos[2]};
				break;
			case 'f':
				pos = {pPos[0], pPos[1], pPos[2] + 1};
				break;
				
		}
	itm = world[pos[0]][pos[1]][pos[2]];
	switch(itm) {
		case '=':
			openShelf(pos);
			break;
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
		napms(17);
		clear();
	}
	endwin();
}
