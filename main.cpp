#include <ncurses.h>

#include <algorithm>
#include <cstdint>
#include <map>
#include <random>
#include <string>
#include <vector>

#define WidthWorld 20
#define HeightWorld 10

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<unsigned int> dis(0, 2);
uniform_int_distribution<unsigned int> disX(1, 18);
bernoulli_distribution disLuckInShelf(0.3);
uniform_int_distribution<unsigned int> disInShelf(0, 10);
uniform_int_distribution<unsigned int> disY(1, 8);
uniform_int_distribution<unsigned int> disIs(1, 3);
bernoulli_distribution chanceToAddBlockCount(0.6);

vector<array<array<char, WidthWorld>, HeightWorld>> world;

void typingAnimation(int d, string s) {
  for (auto c : s) {
    printw("%c", c);
    refresh();
    napms(d);
  }
}

void typingAnimation(string s) {
  typingAnimation(50, s);
}

void intro() {
  array<string, HeightWorld> scene = {
      "###### #############",
      "#                  #",
      "#                  #",
      "##&                #",
      "#             =    #",
      "##            =    #",
      "#             =    #",
      "#    B         BB  #",
      "#  #           BB  #",
      "################ ###"};
  array<pair<int, int>, 5> characterPos;  // Y X
  characterPos[0] = {3, 2};

  array<char, 5> characterChar = {
      '&', '%'};
  auto printScene = [&scene]() {
    clear();
    for (auto a : scene) {
      printw("%s\n", a.c_str());
      refresh();
    }
  };

  auto cnPos = [&scene, &characterChar, &characterPos](int idx, int x, int y) {
    clear();
    auto* ci = &characterPos[idx];
    scene[ci->first][ci->second] = ' ';
    ci->first += y;
    ci->second += x;
    scene[ci->first][ci->second] = characterChar[idx];
  };
  auto cnPosLoop = [&printScene, &cnPos](int d, int l, int idx, int x, int y) {
    for (int i = 0; i < l; ++i) {
      cnPos(idx, x, y);
      refresh();
      printScene();
      napms(d);
    }
  };
  // Start animation
  clear();
  typingAnimation(1500, "...");
  napms(3000);
  printScene();
  napms(5000);
  typingAnimation("Professor: Why it's just so hard?");
  flushinp();
  getch();
  cnPosLoop(250, 3, 0, 1, 0);
  napms(250);
  cnPosLoop(250, 2, 0, 0, 1);
  cnPosLoop(250, 3, 0, -1, 0);
  napms(4000);
  scene[0][6] = '%';
  characterPos[1] = {0, 6};
  cnPosLoop(250, 4, 1, 0, 1);
  napms(2000);
  typingAnimation("Another Professor: Wasup bro?\n");
  flushinp();
  getch();
  typingAnimation("Professor: I'm fine.\n");
  flushinp();
  getch();
  cnPosLoop(300, 2, 0, 0, -1);
  typingAnimation("Another Professor: Another Experiment, ya?\n");
  flushinp();
  getch();
  typingAnimation("Professor: Just like usual day..\n");
  napms(1000);
  printw("Another Professor: I know you'll say that.\n");
  refresh();
  flushinp();
  getch();
  cnPosLoop(250, 2, 0, 1, -1);
  cnPosLoop(250, 2, 0, 1, 0);
  cnPos(0, 0, -1);
  printScene();
  napms(250);
  scene[0][6] = ' ';
  printScene();
  napms(3000);
  typingAnimation("Another Professor: What is that?\n");
  flushinp();
  getch();
  cnPosLoop(500, 2, 1, -1, 0);
  napms(2000);
  scene[0][6] = '&';
  napms(250);
  cnPosLoop(250, 4, 0, 0, 1);
  typingAnimation("Professor: What are you doing?\n");
  flushinp();
  getch();
  typingAnimation("Another Professor: What about you?\n");
  flushinp();
  getch();
  scene[4][7] = 'B';
  characterPos[2] = {4, 7};
  characterChar[2] = 'B';
  printScene();
  typingAnimation("Professor: I took some salt.\n");
  flushinp();
  getch();
  napms(1000);
  typingAnimation("Professor: ANSWER MY QUESTION!, please.\n");
  flushinp();
  getch();
  typingAnimation("Another Professor: I JUST LOOKING AT YOUR PROJECT! DON'T YOU SEE??.\n");
  flushinp();
  getch();
  typingAnimation("Professor: Sorry I just scared.\n");
  flushinp();
  getch();
  printScene();
  typingAnimation("Another Professor: It's okay... ");
  typingAnimation("But why you scared?\n");
  flushinp();
  getch();
  typingAnimation("Professor: Because THIS!.\n");
  flushinp();
  getch();
  cnPosLoop(250, 1, 2, 0, -1);
  cnPosLoop(250, 2, 2, -1, 0);
  cnPosLoop(250, 1, 2, 0, 1);
  cnPos(1, 5, 0);
  cnPosLoop(250, 1, 2, -1, 0);
  napms(2000);
  typingAnimation("Professor: I scared if my prank failed.\n");
  flushinp();
  getch();
  typingAnimation("Another Professor: Are U sur?\n");
  flushinp();
  getch();
  typingAnimation("Professor: I think not\n");
  flushinp();
  getch();
  clear();
  typingAnimation(250, "One day passed\n");
  flushinp();
  getch();
  clear();
  typingAnimation(100, "theJuniorProgrammer3 Present you: ");
  napms(500);
  typingAnimation(200, "The 'Why Am Here?'\n");
  getch();
  flushinp();

  scene = {
      "###### #############",
      "#                  #",
      "#                  #",
      "##&                #",
      "#             =    #",
      "##            =    #",
      "#             =    #",
      "#    B         BB  #",
      "#  #           BB  #",
      "################ ###"};
  characterPos[0] = {3, 2};
  characterPos[1] = {0, 6};
  printScene();
  napms(3000);
  printw("AAAAA!");
  refresh();
  napms(1500);
  cnPosLoop(50, 2, 0, 2, 0);
  printw("Professor: WHAT IS THAT?!!");
  refresh();
  napms(3000);
  cnPosLoop(100, 2, 1, 0, 1);
  napms(1000);
  printw("Professor: EXPLAIN ME WHAT IS JUST HAPPENED!!\n");
  refresh();
  flushinp();
  getch();
  cnPosLoop(100, 2, 1, 0, -1);
  napms(2000);
  cnPos(1, 8, 4);
  scene[0][6] = '=';
  printScene();
  napms(2000);
  typingAnimation(25, "Another Professor: Oh no, I'm infected, ");
  napms(500);
  typingAnimation(100, "save yourself bro..\n");
  getch();
  printw("Professor: FROM WHAT?!");
  refresh();
  flushinp();
  getch();
  clear();
  typingAnimation("The earthquake occurred suddenly, but it also stopped suddenly.");
  flushinp();
  getch();
  clear();
  typingAnimation(250, "Save yourself. ");
  napms(500);
  printw("HURRY UP!!");
  refresh();
  getch();
  flushinp();
}

array<unsigned int, 3> pPos = {0, 3, 9};

void phase1Passed() {
  nodelay(stdscr, FALSE);
  array<string, HeightWorld> scene;
  array<pair<int, int>, 5> characterPos;  // Y X
  for (int i = 0; i < HeightWorld; ++i) {
    for (int j = 0; j < WidthWorld; ++j) {
      scene[i][j] = world[pPos[0]][i][j];
      if (scene[i][j] == '&') {
        characterPos[0] = {i, j};
      }
    }
  }

  array<char, 5> characterChar = {
      '&'};
  auto printScene = [&scene]() {
    clear();
    for (auto a : scene) {
      printw("%s\n", a.c_str());
    }
    refresh();
  };

  auto cnPos = [&scene, &characterChar, &characterPos](int idx, int x, int y) {
    clear();
    auto* ci = &characterPos[idx];
    scene[ci->first][ci->second] = ' ';
    ci->first += y;
    ci->second += x;
    scene[ci->first][ci->second] = characterChar[idx];
  };
  auto cnPosLoop = [&printScene, &cnPos](int d, int l, int idx, int x, int y) {
    for (int i = 0; i < l; ++i) {
      cnPos(idx, x, y);
      refresh();
      printScene();
      napms(d);
    }
  };
  // Start animation
  clear();
  refresh();
  napms(3000);
  typingAnimation("Professor escaped from the long hall.");
  flushinp();
  getch();
  printScene();
  napms(3000);
  scene[characterPos[0].first][characterPos[0].second] = ' ';  // TODO: FIX THIS IDK WHY IT DOESNT WORK
  printScene();
  flushinp();
  getch();
}
void mainMenu() {
  while (true) {
    clear();
    printw("#####################################\n");
    printw(R"(__        ___          ___
\ \      / / |__  _   |__ \
 \ \ /\ / /| '_ \| | | |/ /
  \ V  V / | | | | |_| |_|
   \_/\_/  |_| |_|\__, (_)
                  |___/)");
    printw("\n#####################################\n");
    printw("p to start the game | q to quit the game\n");
    refresh();
    char c = getch();
    if (c == 'p') break;
    switch (c) {
      case 'q':
        endwin();
        exit(0);
        break;
      default:
        printw("Invalid choice");
        refresh();
        napms(1000);
        break;
    }
  }
  // intro();
}
void initWorld() {
  vector<vector<string>> worldS = {
      {"#####=##############",
       "#                  #",
       "#             =    #",
       "##       &         #",
       "#                  #",
       "##        B        #",
       "#   =              #",
       "#              =   #",
       "#      E           #",
       "################ ###"},
      {"################ ###",
       "#                  #",
       "# =                #",
       "#           B      #",
       "#       =          #",
       "#                  #",
       "#              E   #",
       "#      =           #",
       "#                  #",
       "################ ###"}};
  world.resize(2);
  for (int i = 0; i < HeightWorld; ++i) {
    for (int j = 0; j < WidthWorld; ++j) {
      world[0][i][j] = worldS[0][i][j];
    }
  }
  for (int i = 0; i < HeightWorld; ++i) {
    for (int j = 0; j < WidthWorld; ++j) {
      world[1][i][j] = worldS[1][i][j];
    }
  }
}
vector<uint8_t> doors = {16, 16};
vector<vector<pair<unsigned int, unsigned int>>> enemies = {  // Y, X
    {{8, 7}},
    {{6, 15}}};
void addWorld() {
  array<array<char, WidthWorld>, HeightWorld> w;
  static const vector<string> wS = {
      "####################",
      "#                  #",
      "#                  #",
      "#                  #",
      "#                  #",
      "#                  #",
      "#                  #",
      "#                  #",
      "#                  #",
      "####################"};
  for (int i = 0; i < HeightWorld; ++i) {
    copy(wS[i].begin(), wS[i].end(), w[i].begin());
  }

  w[0][doors.back()] = ' ';
  for (int i = 0; i < 3; ++i) {
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

array<int, 9> inventory = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int blockCount = 0;
unsigned int health = 100 + 1;  // this is 100
unsigned int energy = 100 + 1;  // this is 100
;
unsigned int energyClock = 0;

void changePos(int ud, int rl) {
  if (energy > 1) {
    world[pPos[0]][pPos[1]][pPos[2]] = ' ';
    if (pPos[1] + ud == HeightWorld) {  // world Y size - 1 + 1
      pPos[0]++;
      pPos[1] = 0;
      if (pPos[0] >= world.size()) {
        addWorld();
      }
    } else if ((int)pPos[1] + ud == -1) {
      if (pPos[0] > 0) {
        pPos[0]--;
        pPos[1] = HeightWorld - 1;  // world Y size - 1
      }
    }
    if (world[pPos[0]][pPos[1] + ud][pPos[2]] == ' ') pPos[1] += ud;
    if (world[pPos[0]][pPos[1]][pPos[2] + rl] == ' ') pPos[2] += rl;
    world[pPos[0]][pPos[1]][pPos[2]] = '&';
    energyClock = 0;
    energy--;
  }
}

map<vector<unsigned int>, vector<int>> shelfList;

enum item { EMPTY,
            CASH,
            ATROPINE,
            GLUCOSE,
            BLOCK };
string intToItem(int i) {
  switch (i) {
    case EMPTY:
      return "Empty";
      break;
    case CASH:
      return "Cash";
      break;
    case ATROPINE:
      return "Atropine";
      break;
    case GLUCOSE:
      return "Glucose";
      break;
    default:  // case 4/BLOCK, but no warning
      return "Block";
      break;
  }
}

void openInventory() {
  printw("Inventory contains: \n");
  for (auto i : inventory) {
    printw("%s ", intToItem(i).c_str());
  }
  printw("\n");
}

void openShelf(vector<unsigned int> pos) {
  char choiceC;
  int choice;
  nodelay(stdscr, FALSE);
  while (true) {
    clear();
    printw("Shelf contains: \n");
    auto isi = shelfList[pos];
    if (isi.empty()) {
      int itemCount = disInShelf(gen);
      itemCount %= disLuckInShelf(gen) ? 10 : 4;
      if (itemCount == 0) {
        shelfList[pos].push_back(0);
      } else {
        for (int i = 0; i < itemCount; ++i) {
          shelfList[pos].push_back(disIs(gen));
        }
      }
      isi = shelfList[pos];
    }
    for (auto i : isi) {
      printw("%s ", intToItem(i).c_str());
    }
    printw("\n");
    openInventory();
    choiceC = getch();
    refresh();
    int emptySpace = find(inventory.begin(), inventory.end(), 0) - inventory.begin();
    if (isdigit(choiceC)) {
      if (emptySpace != 9) {
        choice = choiceC - '0';
        if (choice > 0) {
          inventory[emptySpace] = shelfList[pos][choice - 1];
          shelfList[pos][choice - 1] = 0;
        } else {
          printw("Invalid index!\n");
          refresh();
          napms(1500);
        }
      } else {
        printw("Inventory is full\n");
        getch();
      }
    } else {
      break;
    }
  }
  nodelay(stdscr, TRUE);
}

void useItem(int item) {
  switch (item) {
    case EMPTY:
      break;
    case ATROPINE:
      health += 3;
      break;
    case GLUCOSE:
      energy += 3;
      break;
  }
}

void useInventory() {
  nodelay(stdscr, FALSE);
  clear();
  openInventory();
  char choiceC = getch();
  refresh();
  int choice;
  if (isdigit(choiceC)) {
    choice = choiceC - '0';
    if (choice > 0 && choice <= 9) {
      useItem(inventory[choice - 1]);
      inventory[choice - 1] = EMPTY;
    } else {
      printw("Invalid index!\n");
      refresh();
      napms(700);
    }
  }
  nodelay(stdscr, TRUE);
}

map<char, pair<int, int>> direction = {
    // char, Y, X
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
bool revrse = false;  // cuz ambigous std::reverse
void inter(char type) {
  vector<unsigned int> pos;
  char itm;
  pos = {pPos[0], pPos[1] + direction[type].first, pPos[2] + direction[type].second};
  itm = world[pos[0]][pos[1]][pos[2]];
  switch (itm) {
    case '=':
      openShelf(pos);
      break;
    case 'B': {
      int emptySpace = find(inventory.begin(), inventory.end(), EMPTY) - inventory.begin();
      if (emptySpace != 9) {
        if (!chanceToAddBlockCount(gen)) {
          inventory[emptySpace] = BLOCK;
        } else {
          blockCount++;
        }
        world[pos[0]][pos[1]][pos[2]] = ' ';
      } else {
        printw("Inventory is full\n");
        refresh();
        getch();
      }
      break;
    }
    case ' ':
      int blockidx = find(inventory.begin(), inventory.end(), BLOCK) - inventory.begin();
      if (blockidx != 9) {
        inventory[blockidx] = EMPTY;
        world[pos[0]][pos[1]][pos[2]] = 'B';
      }
      break;
  }
}

void push(char type) {
  array<unsigned int, 3> pos;
  pos = {pPos[0], pPos[1] + direction[type].first, pPos[2] + direction[type].second};
  char itm;
  itm = world[pos[0]][pos[1]][pos[2]];
  if (itm == 'B' && !revrse) {
    if (pos[1] == HeightWorld - 1) {  // 9
      world[pPos[0]][pPos[1]][pPos[2]] = ' ';
      pPos = pos;
      world[pos[0]][9][pos[2]] = '&';
      if (pos[0] + 1 >= world.size()) addWorld();
      world[pos[0] + 1][1][pos[2]] = 'B';
    } else if (pos[1] == 0) {
      world[pPos[0]][pPos[1]][pPos[2]] = ' ';
      pPos = pos;
      world[pos[0]][0][pos[2]] = '&';
      world[pos[0] - 1][8][pos[2]] = 'B';
    } else if (world[pos[0]][pos[1] + direction[type].first][pos[2] + direction[type].second] == ' ') {
      world[pos[0]][pos[1] + direction[type].first][pos[2] + direction[type].second] = 'B';
      world[pPos[0]][pPos[1]][pPos[2]] = ' ';
      pPos = pos;
      world[pos[0]][pos[1]][pos[2]] = '&';
    }
  } else if (itm == 'B' && revrse) {
    if (world[pPos[0]][pPos[1] + direction[type].first * -1][pPos[2] + direction[type].second * -1] == ' ') {
      world[pos[0]][pos[1]][pos[2]] = ' ';
      world[pPos[0]][pPos[1]][pPos[2]] = 'B';
      pPos[1] += direction[type].first * -1;
      pPos[2] += direction[type].second * -1;
      world[pPos[0]][pPos[1]][pPos[2]] = '&';
    }
  }
}
#ifdef NaturalEnemyMovement
uint8_t moveToWhat(pair<int, int> enemyPos) {  // Y, X
  static map<pair<uint8_t, uint8_t>, uint8_t> lookupTable;
  int dx = pPos[2] - enemyPos.second;
  int dy = pPos[1] - enemyPos.first;
  auto pos = lookupTable.find({dx, dy});
  uint8_t toWhat;
  if (pos == lookupTable.end()) {
    float ang = atan2(dy, dx);
    ang *= 57.3;  // 180 / PI
    if (ang < 0) ang += 360;
    // 0 = right
    // 1 = bottom right
    // 2 = bottom
    // 3 = bottom left
    // 4 = left
    // 5 = upper left
    // 6 = up
    // 7 = upper right

    toWhat = round(ang / 45);
    lookupTable[{dx, dy}] = toWhat;
  } else {
    toWhat = pos->second;
  }
  return static_cast<uint8_t>(toWhat);
}
#else
// AI gen / VIBECODED:
uint8_t moveToWhat(pair<int, int> enemyPos) {
  int dx = pPos[2] - enemyPos.second;
  int dy = pPos[1] - enemyPos.first;

  if (dx == 0 && dy == 0) return 0;  // Diam atau default kanan

  if (dx > 0) {               // Sisi KANAN (Sudut -45 sampai 45)
    if (dy > 0) return 1;     // Kanan Bawah
    if (dy < 0) return 7;     // Kanan Atas
    return 0;                 // Tepat Kanan
  } else if (dx < 0) {        // Sisi KIRI (Sudut 135 sampai 225)
    if (dy > 0) return 3;     // Kiri Bawah
    if (dy < 0) return 5;     // Kiri Atas
    return 4;                 // Tepat Kiri
  } else {                    // Sisi VERTIKAL MURNI (dx == 0)
    return (dy > 0) ? 2 : 6;  // 2 = Bawah, 6 = Atas
  }
}
#endif

void gameOver() {
  nodelay(stdscr, FALSE);
  clear();
  printw("#####################################\n");
  printw(R"(  ____                         ___
 / ___| __ _ _ __ ___   ___   / _ \__   _____ _ __
| |  _ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__|
| |_| | (_| | | | | | |  __/ | |_| |\ V /  __/ |
 \____|\__,_|_| |_| |_|\___|  \___/  \_/ \___|_|
 )");
  printw("#####################################\n");
  printw("Press any key to exit...");
  refresh();
  napms(1000);
  getch();
}

unsigned int enemiesClock = 0;

int main() {
  initscr();
  noecho();
  initWorld();
  mainMenu();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  int inp;
  map<array<unsigned int, 2>, uint8_t> enemiesMemory;  // [enemy's floor, 'a' below] [type]
  while (true) {
    clear();
    if (blockCount == 200) {
      phase1Passed();
      goto endGame;
    }
    if (energy < 101 && energyClock == 600) {
      energy++;
      energyClock = 0;
    }
    energyClock++;
    // Enemy Movement, basic first...
    if (enemiesClock == 30) {  // After 30 frame
      vector<pair<unsigned int, unsigned int>> theEnemies = enemies[pPos[0]];
      enemiesClock = 0;
      for (unsigned int a = 0; a < theEnemies.size(); ++a) {
        pair<unsigned int, unsigned int>* ta = &theEnemies[a];
        if (world[pPos[0]][ta->first + 1][ta->second] == '&' || world[pPos[0]][ta->first - 1][ta->second] == '&' || world[pPos[0]][ta->first][ta->second + 1] == '&' || world[pPos[0]][ta->first][ta->second - 1] == '&') {
          if (health == 0) {
            gameOver();
            goto endGame;
          } else {
            health--;
          }
        } else {
          world[pPos[0]][ta->first][ta->second] = ' ';
          auto mtwRes = moveToWhat(*ta);
          switch (mtwRes) {
            case 0:
              ta->second++;
              break;
            case 1:
              ta->second++;
              ta->first++;
              break;
            case 2:
              ta->first++;
              break;
            case 3:
              ta->first++;
              ta->second--;
              break;
            case 4:
              ta->second--;
              break;
            case 5:
              ta->second--;
              ta->first--;
              break;
            case 6:
              ta->first--;
              break;
            default:  // 7 or 8
              ta->first--;
              ta->second++;
              break;
          }
          auto iten = enemiesMemory.find({pPos[0], a});
          if (world[pPos[0]][ta->first][ta->second] == ' ') {
            enemiesMemory.erase({pPos[0], a});
            enemies[pPos[0]][a] = *ta;
            world[pPos[0]][ta->first][ta->second] = 'E';
          } else if (iten != enemiesMemory.end()) {
            *ta = enemies[pPos[0]][a];
            switch (iten->second) {
              case 0:
              case 4:
                ta->first++;
                break;
              case 2:
              case 6:
                ta->second++;
                break;
              case 1:
                if (world[pPos[0]][ta->first + 1][ta->second] == ' ') {
                  ta->first++;
                } else {
                  ta->second++;
                }
                break;
              case 3:
                if (world[pPos[0]][ta->first + 1][ta->second] == ' ') {
                  ta->first++;
                } else {
                  ta->second--;
                }
                break;
              case 5:
                if (world[pPos[0]][ta->first - 1][ta->second] == ' ') {
                  ta->first--;
                } else {
                  ta->second--;
                }
                break;
              default:
                if (world[pPos[0]][ta->first - 1][ta->second] == ' ') {
                  ta->first--;
                } else {
                  ta->second++;
                }
                break;
            }
            if (world[pPos[0]][ta->first][ta->second] == ' ') {
              enemies[pPos[0]][a] = *ta;
              world[pPos[0]][ta->first][ta->second] = 'E';
            } else {
              world[pPos[0]][enemies[pPos[0]][a].first][enemies[pPos[0]][a].second] = 'E';
            }
          } else {  // No empty grid and no memory
            *ta = enemies[pPos[0]][a];
            enemiesMemory[{pPos[0], a}] = mtwRes;
            world[pPos[0]][ta->first][ta->second] = 'E';
          }
        }
      }
    }
    enemiesClock++;
    for (auto b : world[pPos[0]]) {
      for (auto c : b) {
        printw("%c", c);
      }
      printw("\n");
    }
    printw("Pu%s mode\n", (revrse ? "ll" : "sh"));
    printw("Energy: %i\n", energy - 1);
    printw("Health: %i\n", health - 1);
    inp = getch();
    if (inp == KEY_RIGHT)
      changePos(0, 1);
    else if (inp == KEY_LEFT)
      changePos(0, -1);
    else if (inp == KEY_UP)
      changePos(-1, 0);
    else if (inp == KEY_DOWN)
      changePos(1, 0);
    else if (inp == 'q')
      break;
    else if (inp == 'r')
      revrse = !revrse;
    else if (inp == 'i')
      useInventory();
    if (inp == 'e' || inp == 's' || inp == 'd' || inp == 'f') inter(inp);
    if (inp == 'u' || inp == 'h' || inp == 'j' || inp == 'k') push(inp);
    napms(17);
    refresh();
  }
endGame:
  endwin();
}
