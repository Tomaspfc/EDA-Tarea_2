#pragma once

namespace eda {

class Stack {
private:
	Node* head;
public:
	Stack();
	void push(std::string val);
	void push(Node* node);
	void pop();
	Node* top();
	bool isEmpty();
	void clear();
	virtual ~Stack();
};

} /* namespace eda */
