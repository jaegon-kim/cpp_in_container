#include <iostream>
#include <cstring>
#include <ctime>
#include <utility/dump.hpp>
using namespace std;

/*
0 ~ 124 사이의 높낮이 차이가 있는 1000x1000의 2차원 맵이 주어집니다. 이 맵에 1만대의 Spaceship을 착륙시키려고 합니다. 
 Spaceship은 가로폭과 세로폭이 있는 사각형 모양이고, 가로폭과 세로폭은 2 ~ 5 사이의 크기를 갖습니다. 
 Spaceship의 4개의 꼭지점의 높이차가 6을 초과하는 지역에는  착륙시킬 수 없습니다.
 또, Spaceship은 90도 회전할 수 있습니다. 

가장 높은 스코어를 획득할 수 있도록 최대한 많은 Spaceship을 착륙시킬 수 있는 process 함수를 작성해 주세요.
c언어로 작성을 부탁드립니다.

 init과 process 함수가 있고, init에서 1000x1000의 2차원 맵에 랜덤하게 높이를 지정하고 Spaceship의 크기를 랜덤하게 지정합니다.
 process에서 어떤 Spaceship을 어디에, 어느 방향으로 착륙시킬지를 결정하면 됩니다. 
 기본적으로 많은 Spaceship을 착륙시킬 수록 고득점이며, Spaceship의 가로폭이 w, 세로폭이 h라고 했을 때 1대당 구체적인 스코어 획득량은 w * h * MIN(w,h) 입니다.

* Related Site
(Stack Overflow)
https://stackoverflow.com/questions/7342389/generalizing-the-algorithm-for-domino-tiling
(검색어)
tiling a rectangular grid biparite graph

* Polyomino Tiler
(Web Test) https://gfredericks.com/things/polyominoes
*/




namespace a04_01 {
    const static int N = 1000;
    const static int NUM_SPACESHIPS = 10000;
    const static int MAX_H = 124;
    // const static int N = 30;
    // const static int NUM_SPACESHIPS = 100;
    // const static int MAX_H = 62;

    int map[N][N]; // (y, x)
    int occupied[N][N];

    struct Spaceship {
        int h;
        int w;
        int orientation;

        int y;
        int x;
        int landing;
    };

    Spaceship spaceships[NUM_SPACESHIPS + 1];

    void dump_map(int o[][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (o[i][j]) {
                    printf("%3d, ", o[i][j]);
                } else {
                    printf("   , ");
                }
            }
            printf("\n");
        }
    }

    void dump_ship(Spaceship * s_ptr) {
        cout << "(";
        cout << "h:" << s_ptr->h << ", w:" << s_ptr->w << ")";
        cout << endl;
    }

    void init_ship(Spaceship s[]) {
        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            s[i].y = 0;
            s[i].x = 0;
            s[i].orientation = 0;
            s[i].landing = 0;
        }
    }

    void init_map(int m[][N]) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                m[y][x] = 0;
            }
        }
    }

    void init(int m[][N], int o[][N], Spaceship s[]) {
        srand((unsigned)time(NULL));
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                m[y][x] = rand() % (MAX_H + 1);
            }
        }
        init_map(o);

        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            s[i].w = rand() % 4 + 2;
            s[i].h = rand() % 4 + 2;
        }
        init_ship(s);
        //for (int i = 1; i <= NUM_SPACESHIPS; i++) {
        //    dump_ship(&s[i]);
        //}
    }

    int occupiable(int y, int x, int m[][N], int o[][N], int s_w, int s_h) {
        int y_e = y + s_h - 1;
        if (y < 0 || y_e >= N) {
            return 0;
        }
        int x_e = x + s_w - 1;
        if (x < 0 || x_e >= N) {
            return 0;
        }

        int min_d = m[y][x];
        int max_d = m[y][x];

        if (min_d > m[y][x_e]) min_d = m[y][x_e];
        if (min_d > m[y_e][x]) min_d = m[y_e][x];
        if (min_d > m[y_e][x_e]) min_d = m[y_e][x_e];

        if (max_d < m[y][x_e]) max_d = m[y][x_e];
        if (max_d < m[y_e][x]) max_d = m[y_e][x];
        if (max_d < m[y_e][x_e]) max_d = m[y_e][x_e];

        if ((max_d - min_d) > 6) {
            return 0;
        }

        for (int i = y; i <= y_e; i++) {
            for (int j = x; j <= x_e; j++) {
                if (o[i][j]) {
                    return 0;
                }
            }
        }

        return 1;
    }

    void update_occupied(int y, int x, int o[][N], int s_w, int s_h, int s_n) {
        int y_e = y + s_h - 1;
        int x_e = x + s_w - 1;

        for (int i = y; i <= y_e; i++) {
            for (int j = x; j <= x_e; j++) {
                o[i][j] = s_n;
            }
        }
    }

    int occupy(int m[][N], int o[][N], Spaceship s[], int s_i, int start_x, int start_y) {
        for (int y = start_y; y < N; y++) {
            for (int x = start_x; x < N; x++) {
                if (occupiable(y, x, m, o, s[s_i].w, s[s_i].h)) {
                    update_occupied(y, x, o, s[s_i].w, s[s_i].h, s_i);
                    s[s_i].y = y;
                    s[s_i].x = x;
                    s[s_i].orientation = 0;
                    s[s_i].landing = 1;
                    return 1;
                } 

                if (occupiable(y, x, m, o, s[s_i].h, s[s_i].w)) {
                    update_occupied(y, x, o, s[s_i].h, s[s_i].w, s_i);
                    s[s_i].y = y;
                    s[s_i].x = x;
                    s[s_i].orientation = 1;
                    s[s_i].landing = 1;
                    return 1;
                } 
            }
            start_x = 0;
        }
        return 0;
    }

    void update_ordered_ship(Spaceship s[], int ordered_s[][4][NUM_SPACESHIPS + 1]) {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ordered_s[i][j][0] = 0;
            }
        }

        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            int idx = (++ordered_s[s[i].h - 2][s[i].w - 2][0]);
            ordered_s[s[i].h - 2][s[i].w - 2][idx] = i;
            // dump_ship(&s[i]);
            // cout << "h:" << s[i].h << ", w:" << s[i].w << ", ";
            // cout << "len: " << ordered_s[s[i].h - 2][s[i].w - 2][0] << ", ";
            // cout << "added idx: " << ordered_s[s[i].h - 2][s[i].w - 2][idx] << ", ";
            // cout << endl;
        }
    }

    void process(int m[][N], int o[][N], Spaceship s[]) {
        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            occupy(m, o, s, i, 0, 0);
        }
    }

   int ordered_ship[4][4][NUM_SPACESHIPS + 1];

    void process_ordered(int m[][N], int o[][N], Spaceship s[]) {

        update_ordered_ship(s, ordered_ship);

        int sz_set[][2] = { // sorted with score
            {3, 3}, 
            {3, 2}, {2, 3},
            {2, 2},
            {3, 1}, {1, 3},
            {2, 1}, {1, 2},
            {1, 1},
            {3, 0}, {0, 3},
            {2, 0}, {0, 2},
            {1, 0}, {0, 1},
            {0, 0}
        };

        for (int sz_idx = 0; sz_idx < 16; sz_idx++) {
            int i = sz_set[sz_idx][0];
            int j = sz_set[sz_idx][1];

            int len = ordered_ship[i][j][0];
            //cout << "(i: " << i << ", " << j << ") len: " << len <<endl;

            int start_x = 0, start_y = 0;
            for (int idx = 1; idx <= len ; idx++) {
                int s_idx = ordered_ship[i][j][idx];
                if (!occupy(m, o, s, s_idx, start_x, start_y)) {
                    break;
                }

                if (!s[s_idx].orientation) {
                    start_x = s[s_idx].x + s[s_idx].w;
                } else {
                    start_x = s[s_idx].x + s[s_idx].h;
                }
                start_y = s[s_idx].y;

            }
        }
    }

    int score(Spaceship s[]) {
        int total_score = 0;
        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            if (!s[i].landing) {
                continue;
            }

            if (s[i].w < s[i].h) {
                total_score += (s[i].w * s[i].h * s[i].w);
            } else {
                total_score += (s[i].w * s[i].h * s[i].h);
            }
        }
        return total_score;
    }

    void test() {
        init(map, occupied, spaceships);
        
        // process(map, occupied, spaceships);
        // //dump_map(map);
        // //cout << endl;
        // //dump_map(occupied);
        // cout << "score: " << score(spaceships) << endl;
        // init_map(occupied);
        // init_ship(spaceships);

        process_ordered(map, occupied, spaceships);
        //dump_map(map);
        //cout << endl;
        //dump_map(occupied);
        cout << "score: " << score(spaceships) << endl;

    }
}


void test_a04_01_spaceship() {
    PRINT_FUNC_NAME;
    a04_01::test();
}