#include "yuhan_stack.h"
int main() {
	// ������ ������ �����ϰ�, ���
	y_stack stack;
	int result;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);

	result = stack.Top();
	std::cout << "���� ������ top ���� " << result << std::endl;

	for (int i = 0; i < 5; i++) {
		result = stack.pop();
		std::cout << i + 1 << "��° pop ���� ����� " << result << std::endl;
	}
}