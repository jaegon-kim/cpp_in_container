#include <iostream>
#include <cstring>
#include <ctime>
#include <utility/dump.hpp>

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



using namespace std;
namespace a02_06 {


#define N 1000               // 맵 크기: 1000x1000
#define MAX_SPACESHIPS 10000 // Spaceship 개수

    // 전역 맵: 각 셀의 높이 (0 ~ 124)
    int map[N][N];
    // 배치 여부를 기록하는 occupancy 맵 (0: free, 1: occupied)
    int occupied[N][N];

    // Spaceship 정보 구조체
    typedef struct {
        int w, h;       // 원래 가로, 세로 폭 (2 ~ 5)
        int x, y;       // 착륙 시 좌측 상단 좌표
        int orientation;// 0: 원래 모양, 1: 90도 회전 (즉, 폭과 높이가 교환됨)
        int placed;     // 1이면 착륙 결정됨, 0이면 미배치
    } Spaceship;

    Spaceship ships[MAX_SPACESHIPS];

    /* init 함수
    - 1000x1000 맵에 랜덤 높이(0~124)를 지정합니다.
    - 1만 대의 Spaceship에 대해 가로, 세로 폭을 2~5 사이의 랜덤값으로 지정합니다.
    - occupancy 배열을 초기화합니다.
    */
    void init() {
        int i, j;
        srand((unsigned)time(NULL));
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                map[i][j] = rand() % 125; // 0 ~ 124
                occupied[i][j] = 0;
            }
        }
        // 각 spaceship의 폭을 랜덤하게 지정 (2~5)
        for (i = 0; i < MAX_SPACESHIPS; i++){
            ships[i].w = rand() % 4 + 2; // 결과: 2,3,4,5 중 하나
            ships[i].h = rand() % 4 + 2;
            ships[i].placed = 0; // 아직 배치되지 않음
        }
    }

    /* heightCondition 함수
    좌측 상단 (i,j)에서 가로 길이 w, 세로 길이 h인 직사각형의
    네 꼭지점의 높이 차이가 6 이하이면 1, 아니면 0을 반환합니다.
    */
    int heightCondition(int i, int j, int w, int h) {
        int h1 = map[i][j];
        int h2 = map[i][j + w - 1];
        int h3 = map[i + h - 1][j];
        int h4 = map[i + h - 1][j + w - 1];
        int maxVal = h1, minVal = h1;
        if (h2 > maxVal) maxVal = h2;
        if (h3 > maxVal) maxVal = h3;
        if (h4 > maxVal) maxVal = h4;
        if (h2 < minVal) minVal = h2;
        if (h3 < minVal) minVal = h3;
        if (h4 < minVal) minVal = h4;
        return (maxVal - minVal <= 6);
    }

    /* areaFree 함수
    좌측 상단 (i,j)에서 가로 w, 세로 h인 영역이 모두 free(occupied==0)인지 검사합니다.
    */
    int areaFree(int i, int j, int w, int h) {
        int a, b;
        for (a = i; a < i + h; a++){
            for (b = j; b < j + w; b++){
                if (occupied[a][b] != 0)
                    return 0;
            }
        }
        return 1;
    }

    /* markOccupied 함수
    좌측 상단 (i,j)에서 가로 w, 세로 h인 영역을 occupied로 표시합니다.
    */
    void markOccupied(int i, int j, int w, int h) {
        int a, b;
        for (a = i; a < i + h; a++){
            for (b = j; b < j + w; b++){
                occupied[a][b] = 1;
            }
        }
    }

    /* process 함수
    각 spaceship에 대해 (i,j) (행,열) 순으로 가능한 위치를 탐색합니다.
    두 방향(원래 모양과 90도 회전한 모양) 중 하나라도
    - 맵의 범위 내에 있고,
    - 해당 영역이 아직 사용되지 않았으며,
    - 네 꼭지점의 높이차 조건을 만족하면,
    해당 위치에 spaceship을 착륙시킵니다.
    
    마지막에 각 spaceship의 결정 정보를 (x y effective_width effective_height orientation)
    1만 줄에 걸쳐 출력합니다. (착륙하지 못한 경우 -1 -1 0 0 0)
    */
    void process() {
        int s;
        // 각 spaceship에 대해 위치 탐색 (그리디하게 좌측 상단부터)
        for (s = 0; s < MAX_SPACESHIPS; s++){
            int placed = 0;
            int i, j;
            // 순회: 맵의 모든 셀에 대해 검사
            for (i = 0; i < N && !placed; i++){
                for (j = 0; j < N && !placed; j++){
                    // 1) orientation 0: 원래 모양 (w, h)
                    int w0 = ships[s].w;
                    int h0 = ships[s].h;
                    if (i + h0 <= N && j + w0 <= N) {
                        if (areaFree(i, j, w0, h0) && heightCondition(i, j, w0, h0)) {
                            ships[s].x = i;
                            ships[s].y = j;
                            ships[s].orientation = 0;
                            ships[s].placed = 1;
                            markOccupied(i, j, w0, h0);
                            placed = 1;
                            break;
                        }
                    }
                    // 2) orientation 1: 90도 회전 (단, 정사각형이 아니면)
                    if (ships[s].w != ships[s].h) {
                        int w1 = ships[s].h; // 회전 후 가로 폭
                        int h1 = ships[s].w; // 회전 후 세로 폭
                        if (i + h1 <= N && j + w1 <= N) {
                            if (areaFree(i, j, w1, h1) && heightCondition(i, j, w1, h1)) {
                                ships[s].x = i;
                                ships[s].y = j;
                                ships[s].orientation = 1;
                                ships[s].placed = 1;
                                markOccupied(i, j, w1, h1);
                                placed = 1;
                                break;
                            }
                        }
                    }
                }
            }
            // 만약 배치에 실패하면 ships[s].placed는 0인 상태로 남습니다.
        }
        
        // 각 spaceship에 대해 결정 정보를 출력합니다.
        // 출력 형식: x y effective_width effective_height orientation
        // (effective_width, effective_height는 orientation에 따라 결정됩니다.)
        int sOut;
        for (sOut = 0; sOut < MAX_SPACESHIPS; sOut++){
            if (ships[sOut].placed) {
                int effectiveW = (ships[sOut].orientation == 0 ? ships[sOut].w : ships[sOut].h);
                int effectiveH = (ships[sOut].orientation == 0 ? ships[sOut].h : ships[sOut].w);
                printf("%d %d %d %d %d\n", ships[sOut].x, ships[sOut].y, effectiveW, effectiveH, ships[sOut].orientation);
            } else {
                // 배치 실패한 경우 (-1로 표시)
                // printf("-1 -1 0 0 0\n");
            }
        }
    }

    /* main 함수: init과 process를 차례로 호출 */
    void test(){
        init();
        process();
        return;
    }


}

void test_a02_06_space_ship() {
    PRINT_FUNC_NAME;
    a02_06::test();
}