#include <ncurses.h>
#include <vector>

using namespace std;

	vector<vector<bool>> world = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}
	};

unsigned int minmax(int i) {
	if(i > 9) return 9;
	if(i < 0) return 0;
	return i;
}
pair<unsigned int, unsigned int> pos = {4, 5};
void changePos(int up, int right) {
	world[pos.first][pos.second] = 0;
	pos.first = minmax(pos.first + up);
	pos.second = minmax(pos.second + right);
	world[pos.first][pos.second] = 1;
}

int main() {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	int inp;
	while(true) {
		refresh();
		for(auto b : world) {
			for(auto c : b) {
				printw("[%s] ", (c == true ? "&" : " "));
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
