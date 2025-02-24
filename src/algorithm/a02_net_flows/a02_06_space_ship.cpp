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


// 이 문제는 NP Hard 문제로서 Ford Fulkerson으로 풀 수 없다.
// Greedy로 유사 optimal로 풀 수 있다.
// algorithm/a04_greedy/a04_01_spaceship.cpp를 참고 할 것

using namespace std;
namespace a02_06 {

    void test(){
        return;
    }

}

void test_a02_06_space_ship() {
    PRINT_FUNC_NAME;
    a02_06::test();
}