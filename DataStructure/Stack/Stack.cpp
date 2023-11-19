#include "yuhan_stack.h"
int main() {
	// 구현한 스택을 생성하고, 사용
	y_stack stack;
	int result;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);

	result = stack.Top();
	std::cout << "현재 스택의 top 값은 " << result << std::endl;

	for (int i = 0; i < 5; i++) {
		result = stack.pop();
		std::cout << i + 1 << "번째 pop 연산 결과는 " << result << std::endl;
	}
}