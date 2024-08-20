#include <iostream>
#include <cstring>
#include <ctime>
#include <utility/dump.hpp>

/*
 1000x1000의 높낮이 차이가 있는 2차원 맵이 주어집니다. 이 맵에 1만대의 Spaceship을 착륙시키는 문제입니다.
 Spaceship은 가로폭과 세로폭이 있고, 맨 끝 4개의 꼭지점의 높이차가 6을 초과하는 지역에는 착륙시킬 수 없습니다.
 또, 우주선은 90도 회전할 수 있습니다.

 init과 process 함수가 주어지고, init에서 맵 정보를, process에서 어떤 Spaceship을 어디에,
 어느 방향으로 착륙시킬지를 결정하면 됩니다.
 기본적으로 많은 Spaceship을 착륙시킬 수록 고득점이며, 1대당 구체적인 스코어 획득량은 w * h * MIN(w,h) 입니다.

* Related Site
(Stack Overflow)
https://stackoverflow.com/questions/7342389/generalizing-the-algorithm-for-domino-tiling
(검색어)
tiling a rectangular grid biparite graph

* Polyomino Tiler
(Web Test) https://gfredericks.com/things/polyominoes

*/



using namespace std;
namespace a02_06 {

    static const int MAP_SIZE = 1'000;
    static const int MAP_HEIGHT_BASE = 125; // map height range 0 ~ 124
    static const int SHIP_NUM = 10'000;
    static const int SHIP_SZ_MIN = 2;
    static const int SHIP_SZ_MAX = 5;
    static const int SHIP_TYPE_CNT_MAX = SHIP_SZ_MAX * SHIP_SZ_MAX;

    struct Ship {
        int w;
        int h;
    };

    int map_g[MAP_SIZE][MAP_SIZE];
    Ship ship_g[SHIP_NUM];
    int ship_t_cnt_g[SHIP_TYPE_CNT_MAX];
    
    void generate_map(int map[][MAP_SIZE], int map_size) {        
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                map[i][j] = rand() % MAP_HEIGHT_BASE; // 0 ~ 124
            }
        }
    }

    void dump_map(int map[][MAP_SIZE], int map_size) {        
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                cout << "(" << i << ", " << j << "): " << map[i][j] << endl;
            }
        }
    }

    void generate_ship(Ship ship[], int ship_cnt) {
        for (int i = 0; i < ship_cnt; i++) {
            ship[i].w = SHIP_SZ_MIN + rand() % (SHIP_SZ_MAX - SHIP_SZ_MIN + 1);
            ship[i].h = SHIP_SZ_MIN + rand() % (SHIP_SZ_MAX - SHIP_SZ_MIN + 1);
        }
    }

    void dump_ship(Ship ship[], int ship_cnt) {
        for (int i = 0; i < ship_cnt; i++) {
            cout << "(" << i << "): " << ship[i].w << ", " << ship[i].h << endl;
        }
    }

    int cnt_ship_type(Ship ship[], int ship_cnt, int ship_cnt_p_type[]) {
        int cnt[SHIP_SZ_MAX + 1][SHIP_SZ_MAX + 1];
        memset(cnt, 0, sizeof(cnt));

        for (int i = 0; i < ship_cnt; i++) {
            cnt[ship[i].w][ship[i].h]++;
        }

        int cnt_idx = 0;
        for (int i = SHIP_SZ_MAX; i >= SHIP_SZ_MIN; i--) {
            for (int j = i; j >= SHIP_SZ_MIN; j--) {
                if (i == j) {
                    ship_cnt_p_type[cnt_idx] = cnt[i][j];
                } else {
                    ship_cnt_p_type[cnt_idx] = cnt[i][j] + cnt[j][i];
                }
                cnt_idx++; 
            }
        }
        return cnt_idx;
    }

    void dump_ship_type(int ship_cnt_p_type[], int size_ship_type) {
        int sum = 0;
        int w = 5, h = 5;

        for (int i = 0; i < size_ship_type; i++) {
            cout << i << "(" << w << ", " << h << "): " << ship_cnt_p_type[i] << endl;
            sum += ship_cnt_p_type[i];
            h--;
            if (h < SHIP_SZ_MIN) {
                w--;
                h = w;
            }
        }
        cout << "total: " << sum << endl;
    }

    void test() {
        srand((int)time(NULL));
        generate_map(map_g, MAP_SIZE);
        generate_ship(ship_g, SHIP_NUM);
        //dump_map(map_g, MAP_SIZE);
        //dump_ship(ship_g, SHIP_NUM);
        memset(ship_t_cnt_g, 0, sizeof(ship_t_cnt_g));
        int size_ship_type = cnt_ship_type(ship_g, SHIP_NUM, ship_t_cnt_g);
        dump_ship_type(ship_t_cnt_g, size_ship_type);
    }
}

void test_a02_06_space_ship() {
    PRINT_FUNC_NAME;
    a02_06::test();
}