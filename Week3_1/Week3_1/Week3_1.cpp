#include <iostream>
#include <vector>
#include <chrono>
#include <conio.h>
//  방향키 여부를 확인할 값을 매크로 상수로 정의 (방향키는 기본 문자의 1 Byte와는 다르게 2 Byte (224, 키값)를 가지는 확장키)
#define DIRECTION 224 
//  방향키와 ESC에 해당하는 아스키 코드값 매크로 상수로 정의
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
using namespace std;                                                //  표준 네임스페이스를 사용하겠다는 선언

int main() {
    int userinput;                                                  // 사용자가 입력한 키의 아스키코드 값을 저장할 변수
    vector<int> command;                                            // 사용자가 입력한 커맨드를 저장할 벡터
    chrono::milliseconds duration(300);                             // 입력받는 시간은 300ms로 설정

    //  스플래시 출력
    cout << "=======================================================================================================" << endl;
    cout << "대전액션 커맨드를 만들어보자!! 201907011 이석재" << endl;
    cout << "커맨드는 키보드 입력이 감지될 때부터 " << duration.count() << "ms 동안 입력을 받습니다." << endl;
    cout << "=======================================================================================================" << endl;

    auto startTime = chrono::high_resolution_clock::now();          //  시작 시간을 저장할 변수 선언
    bool isStartTimeSet = false;                                    //  시작 시간 설정 여부를 저장할 변수

    while (true) {
        if (_kbhit()) { // 키보드가 입력되면
            //  시작 시간이 설정되어 있지 않다면
            if (!isStartTimeSet) {
                startTime = chrono::high_resolution_clock::now();   // 시작 시간을 현재시간으로 설정
                isStartTimeSet = true;                              // 시작 시간 설정 여부를 true로 변경
            }
            userinput = _getch();                                   // 사용자가 입력한 커맨드를 userinput에 저장
            //  입력한 키가 방향키이면
            if (userinput == DIRECTION) {
                userinput = _getch();                               //  한번 더 _getch()함수를 사용하여 userinput에 저장(why? 특수키기 때문에 _getch()함수를 한번 더 사용)
            }
            // ESC키가 눌릴경우 프로그램 종료
            if (userinput == ESC) {
                cout << "프로그램을 종료합니다." << endl;
                break;
            }

            command.push_back(userinput);  // 벡터에 입력된 커맨드를 추가
        }

        auto currentTime = chrono::high_resolution_clock::now();                                    //  현재시간을 담을 변수를 선언 후 현재시간 값을 저장
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime);    //  경과시간을 담을 변수를 선언 후 현재시간과 시작시간의 차이를 계산하여 경과시간 값을 저장

        //  시작시간이 설정되어 있고, 경과시간이 설정시간(300ms)보다 큰 경우(시간 종료)
        if (isStartTimeSet && elapsedTime >= duration) { 
            //  커맨드가 3자리 이상인 경우
            if (command.size() >= 3) {
                //  해당하는 커맨드에 따라 처리
                if (command[command.size() - 3] == DOWN && command[command.size() - 2] == RIGHT && command[command.size() - 1] == 'a') {
                    cout << "아도겐! =o" << endl;
                }
                else if (command[command.size() - 3] == RIGHT && command[command.size() - 2] == DOWN && command[command.size() - 1] == 's') {
                    cout << "소류겐! =o" << endl;
                }
                else if (command[command.size() - 3] == LEFT && command[command.size() - 2] == RIGHT && command[command.size() - 1] == 'a') {
                    cout << "화이아 아도겐!! =o" << endl;
                }
                else if(command[command.size() - 3] == LEFT && command[command.size() - 2] == RIGHT && command[command.size() - 1] == 's') {
                    cout << "화이아 소류겐!! =o" << endl;
                }
            }

            command.clear();                //  커맨드 벡터를 초기화
            isStartTimeSet = false;         //  시작 시간 설정 여부를 false로 변경
            continue;                       //  반복문의 맨 위로 이동
        }
    }
    return 0;
}
