#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
int main()
{
	//	스플래시 출력
	printf("*************************************************\n");
	printf("201907011 이석재의 행복한 2학년 2학기 VC++ 실습\n");
	printf("*************************************************\n");

	//	무한루프(전체 프로그램)
	while (true) {
		//	변수 정의
		char show_input;				//	사용자가 입력한 글자 출력을 위해 값을 저장할 변수
		char user_input;				//	사용자가 입력한 글자를 저장하기 위한 변수(입력한 명령어가 한자리인 경우만 사용)
		int user_strlen = 0;			//	사용자가 입력한 명령어의 길이를 저장할 변수

		printf("commnad>");

		//	무한루프(키보드 입력 부분)
		while (true) {
			//	키보드가 입력되면
			if (_kbhit()) {
				show_input = _getch();	//	사용자가 입력한 글자를 show_input 변수에 저장
				// 사용자가 esc를 입력하면 즉시 종료
				if (show_input == 27) {
					printf("\n어..... 나가시는건가요?\n");
					exit(0);
				}
				//	엔터키가 입력되면 키보드 입력 루프 탈출
				else if (show_input == 13) {
					break;
				}
				//	사용자가 입력한 문자가 esc가 아니면
				else {
					putchar(show_input);	//	커맨드 창에 명령어 출력
					//	사용자가 첫 글자를 입력한 경우 입력한 글자를 user_input 변수에 저장하고 명령어 자릿수 1증가
					if (user_strlen == 0) {
						user_input = show_input;
						user_strlen++;
					}
					//	두자리 부터는 명령어 자릿수만 증가
					else {
						user_strlen++;
					}
				}
			}
		}
		//	입력한 글자가 2자리 이상이거나, 사용자가 입력하지 않고 엔터키를 누른경우(user_strlen == 0) 오류 출력
		if (user_strlen >= 2 || user_strlen == 0) {
			printf("\n404 Not Found..... 알 수 없는 명령어 입니다.\n");
			continue;
		}
		//	사용자의 입력에 따라 출력
		if (user_input == 'q') {
			printf("\nqwer 화이팅\n");
		}
		else if (user_input == 'w') {
			printf("\n과제 너무 좋다\n");
		}
		else if (user_input == 'e') {
			printf("\n담주부턴 과제량 3배다\n");
		}
		else if (user_input == 'r') {
			printf("\n행복합니다.\n");
		}
		//	해당 명령어가 아닌 경우 오류 출력
		else {
			printf("\n404 Not Found..... 알 수 없는 명령어 입니다.\n");
		}
	
	}

	return 0;
}