#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

int main()
{
	char check;

	//	스플래시 출력
	printf("201907011 이석재의 행복한 2학년 2학기 VC++ 실습\n");

	//	무한루프
	while (1) {
		//	사용자로부터 값 입력
		printf("command>");
		check = _getch();
		//	ESC를 입력한경우 종료
		if (check == 27) {
			printf("ESC \n과제는 이클래스가 아닌 GIT에 올리자.\n");
			break;
		}
		//	사용자가 입력한 문자 출력
		printf("%c\n", check);

		//	조건문으로 비교
		if (check == 'q') {
			printf("qwer 화이팅.\n");
		}
		else if (check == 'w') {
			printf("과제 너무 좋다.\n");
		}
		else if (check == 'e') {
			printf("담주부턴 과제량 3배다.\n");
		}
		else if (check == 'r') {
			printf("행복합니다.\n");
		}
		else {
			printf("잘못된 입력값입니다.\n");
		}
	}
}