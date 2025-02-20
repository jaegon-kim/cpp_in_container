#include <iostream>
#include <cstring>
#include <ctime>
#include <utility/dump.hpp>
using namespace std;

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