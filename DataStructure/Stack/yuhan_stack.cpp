#include "yuhan_stack.h"
// y_node Ŭ������ ������ ����
y_node::y_node(int data) {
	this->data = data;
	this->prev_node = nullptr;
}

// y_node Ŭ������ data ��������� ���� getter �޼ҵ� ����
int y_node::getData() const {
	return this->data;
}

// y_node Ŭ������ data ��������� ���� setter �޼ҵ� ����
void y_node::setData(int data) {
	this->data = data;
}

// y_node Ŭ������ prev_node ��������� ���� getter �޼ҵ� ����
y_node* y_node::getPrev() const {
	return this->prev_node;
}

// y_node Ŭ������ prev_node ��������� ���� setter �޼ҵ� ����
void y_node::setPrev(y_node* prev_node) {
	this->prev_node = prev_node;
}

// y_stack Ŭ������ ������ ����
y_stack::y_stack() {
	this->top = nullptr;
}

// y_stack Ŭ������ �Ҹ��� ����
y_stack::~y_stack() {
	// ������ ����������� pop() ������ ��� �ݺ���
	while (!isEmpty()) {
		pop();
	}
}

// y_stack Ŭ������ top ��������� ���� getter �޼ҵ� ����
y_node* y_stack::getTop() const {
	return this->top;
}

// y_stack Ŭ������ top ��������� ���� setter �޼ҵ� ����
void y_stack::setTop(y_node* node) {
	this->top = node;
}

// y_stack Ŭ������ push ���� ����
void y_stack::push(int input) {
	// ���ο� ��带 ����
	y_node* node = new y_node(input);
	node->setPrev(top);
	setTop(node);
}

// y_stack Ŭ������ pop ���� ����
int y_stack::pop() {
	// ���࿡ ������ ����ִٸ� ���� ���
	if (isEmpty()) {
		std::cout << "Stack is Empty" << std::endl;
		return -1;
	}
	// ���� top ����� �ּҰ��� node�� ����
	y_node* node = getTop();
	// top ����� �����͸� data ������ ����
	int data = node->getData();
	// top�� ���� ��带 ����Ű���� ��
	top = node->getPrev();
	// top�� �ش��ϴ� ��带 ����
	delete node;
	// data ���� return
	return data;
}

// y_stack Ŭ������ Top ���� ����
int y_stack::Top() {
	// ���࿡ ������ ����ִٸ� ���� ���
	if (isEmpty()) {
		std::cout << "Stack is Empty" << std::endl;
		return -1;
	}
	// top�� ���� return
	return getTop()->getData();
}

// y_stack Ŭ������ isEmpty ���� ����
bool y_stack::isEmpty() {
	// top ��尡 �������� �ʴ� ���(���ÿ� �����Ͱ� ���� ���) true�� ��ȯ �ƴ� ��� false�� ��ȯ
	return getTop() == nullptr;
}