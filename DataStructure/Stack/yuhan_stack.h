#pragma once
#include<iostream>
class y_node {
public:
    y_node(int data);
    int getData() const;
    void setData(int data);
    y_node* getPrev() const;
    void setPrev(y_node* prev_node);
private:
    int data;
    y_node* prev_node;
};
class y_stack {
public:
    y_stack();
    ~y_stack();
    y_node* getTop() const;
    void setTop(y_node* node);
    void push(int input);
    int pop();
    int Top();
    bool isEmpty();
private:
    y_node* top;
};