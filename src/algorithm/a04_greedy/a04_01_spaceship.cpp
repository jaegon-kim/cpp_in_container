#include <iostream>
#include <cstring>
#include <ctime>
#include <utility/dump.hpp>
using namespace std;

namespace a04_01 {
    //const static int N = 1000;
    //const static int NUM_SPACESHIPS = 10000;
    //const static int MAX_H = 124;

    const static int N = 30;
    const static int NUM_SPACESHIPS = 100;
    const static int MAX_H = 62;

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

    void init(int m[][N], int o[][N], Spaceship s[]) {
        srand((unsigned)time(NULL));
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                m[y][x] = rand() % (MAX_H + 1);
                o[y][x] = 0;
            }
        }
        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            s[i].w = rand() % 4 + 2;
            s[i].h = rand() % 4 + 2;
            s[i].orientation = 0;
            s[i].landing = 0;
        }
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

    int occupy(int m[][N], int o[][N], Spaceship s[], int s_i) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
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
        }
        return 0;
    }

    void process(int m[][N], int o[][N], Spaceship s[]) {

        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            occupy(m, o, s, i);
        }
    }

    int score(Spaceship s[]) {
        int total_score = 0;
        for (int i = 1; i <= NUM_SPACESHIPS; i++) {
            if (s[i].w < s[i].h) {
                total_score += (s[i].w * s[i].h * s[i].w);
            } else {
                total_score += (s[i].w * s[i].h * s[i].h);
            }
        }
        return total_score;
    }

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

    void test() {
        init(map, occupied, spaceships);
        process(map, occupied, spaceships);
        //dump_map(map);
        //cout << endl;
        dump_map(occupied);
        cout << "score: " << score(spaceships) << endl;
    }
}


void test_a04_01_spaceship() {
    PRINT_FUNC_NAME;
    a04_01::test();
}