#include <ncurses.h>
#include <vector>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<unsigned int> dis(0, 2);

vector<vector<string>> world = {
	{
"####################",
"#                  #",
"#                  #",
"#        &         #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"#                  #",
"################ ###"
	}
};

unsigned int minmax(int i) {
	if(i > 19) return 19;
	if(i < 0) return 0;
	return i;
}
vector<unsigned int> pPos = {0, 3, 9};

void changePos(int ud, int rl) {
	world[pPos[0]][pPos[1]][pPos[2]] = ' ';
	world[pPos[0]][pPos[1] + ud][pPos[2]] == '#' ? : pPos[1] += ud;
	world[pPos[0]][pPos[1]][pPos[2] + rl] == '#' ? : pPos[2] += rl;
	world[pPos[0]][pPos[1]][pPos[2]] = '&';
}


int main() {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
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
		if(inp == KEY_RIGHT) {
			changePos(0, 1);
		} else if(inp == KEY_LEFT) {
			changePos(0, -1);
		} else if(inp == KEY_UP) {
			changePos(-1, 0);
		} else if(inp == KEY_DOWN) {
			changePos(1, 0);
		} else if(inp == 'q') {
			break;
		}
		napms(17);
		clear();
	}
	endwin();
}
