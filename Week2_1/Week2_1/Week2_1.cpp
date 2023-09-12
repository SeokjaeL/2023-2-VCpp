#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

int main()
{
	char check;

	//	스플래시 출력
	printf("     201907011\n");
	printf("     이석재님의\n");
	printf("     Application\n");

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
		if (check == 'p') {
			printf("나는 과제를 겁나 잘하는 학생이다.\n");
		}
		else if (check == 'f') {
			printf("나는 과제가 너무 즐겁다.\n");
		}
		else if (check == 'j') {
			printf("교수님 과제 더 내주세요.\n");
		}
		else {
			printf("잘못된 입력값입니다.\n");
		}
	}
}