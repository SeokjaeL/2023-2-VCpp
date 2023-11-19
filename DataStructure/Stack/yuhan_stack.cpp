#include "yuhan_stack.h"
// y_node 클래스의 생성자 구현
y_node::y_node(int data) {
	this->data = data;
	this->prev_node = nullptr;
}

// y_node 클래스의 data 멤버변수에 대한 getter 메소드 구현
int y_node::getData() const {
	return this->data;
}

// y_node 클래스의 data 멤버변수에 대한 setter 메소드 구현
void y_node::setData(int data) {
	this->data = data;
}

// y_node 클래스의 prev_node 멤버변수에 대한 getter 메소드 구현
y_node* y_node::getPrev() const {
	return this->prev_node;
}

// y_node 클래스의 prev_node 멤버변수에 대한 setter 메소드 구현
void y_node::setPrev(y_node* prev_node) {
	this->prev_node = prev_node;
}

// y_stack 클래스의 생성자 구현
y_stack::y_stack() {
	this->top = nullptr;
}

// y_stack 클래스의 소멸자 구현
y_stack::~y_stack() {
	// 스택이 비워질때까지 pop() 연산을 계속 반복함
	while (!isEmpty()) {
		pop();
	}
}

// y_stack 클래스의 top 멤버변수에 대한 getter 메소드 구현
y_node* y_stack::getTop() const {
	return this->top;
}

// y_stack 클래스의 top 멤버변수에 대한 setter 메소드 구현
void y_stack::setTop(y_node* node) {
	this->top = node;
}

// y_stack 클래스의 push 연산 구현
void y_stack::push(int input) {
	// 새로운 노드를 만듬
	y_node* node = new y_node(input);
	node->setPrev(top);
	setTop(node);
}

// y_stack 클래스의 pop 연산 구현
int y_stack::pop() {
	// 만약에 스택이 비어있다면 오류 출력
	if (isEmpty()) {
		std::cout << "Stack is Empty" << std::endl;
		return -1;
	}
	// 현재 top 노드의 주소값을 node에 저장
	y_node* node = getTop();
	// top 노드의 데이터를 data 변수에 저장
	int data = node->getData();
	// top이 이전 노드를 가리키도록 함
	top = node->getPrev();
	// top에 해당하는 노드를 삭제
	delete node;
	// data 값을 return
	return data;
}

// y_stack 클래스의 Top 연산 구현
int y_stack::Top() {
	// 만약에 스택이 비어있다면 오류 출력
	if (isEmpty()) {
		std::cout << "Stack is Empty" << std::endl;
		return -1;
	}
	// top의 값을 return
	return getTop()->getData();
}

// y_stack 클래스의 isEmpty 연산 구현
bool y_stack::isEmpty() {
	// top 노드가 존재하지 않는 경우(스택에 데이터가 없는 경우) true값 반환 아닌 경우 false값 반환
	return getTop() == nullptr;
}