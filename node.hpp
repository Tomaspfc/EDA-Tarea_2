#pragma once
#include <string>

namespace eda {

class Node {
private:
	std::string data;
	Node* ptrNext;
public:
	Node();
	Node(std::string _data, Node* next = nullptr);
	void setData(std::string _data);
	void setNext(Node* _next);
	std::string getData();
	Node* getNext();
	void print();
	virtual ~Node();
};

} /* namespace eda */
