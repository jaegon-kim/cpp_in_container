#include <iostream>
#include <cstring>
#include <utility/dump.hpp>

using namespace std;
namespace a02_06 {

    static const int MAP_SIZE = 1'000;
    static const int SHIP_NUM = 10'000;
    static const int SHIP_SZ_MIN = 2;
    static const int SHIP_SZ_MAX = 5;
    static const int SHIP_TYPE_NUM = (SHIP_SZ_MAX - SHIP_SZ_MIN + 1) * (SHIP_SZ_MAX - SHIP_SZ_MIN + 1);

    struct Ship {
        int w;
        int h;
    };

    int map2[MAP_SIZE][MAP_SIZE];
    int graph[SHIP_TYPE_NUM][MAP_SIZE * MAP_SIZE];
    Ship ship[SHIP_NUM];
    
    void test() {

    }
}

void test_a02_06_space_ship() {
    PRINT_FUNC_NAME;
}