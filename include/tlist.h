#pragma once
#include <iostream>
template<typename T>
class TList {
protected:
	struct Node {
		Node* next;
		T value;

		Node(Node* next, T value):next(next), value(value){}
	};
	size_t sz = 0;
	Node* first = nullptr;

public:

	TList(int n = 0) {//constructor
		if (n < 0) throw "incorrect size";
		this->sz = n;
		while (n--) {
			Node* temp = new Node(this->first, 0);
			this->first = temp;
		}
	}

	~TList() {//destructor
		this->clear();
	}

	void clear(){
		Node* curr;
		while (this->first != nullptr) {
			curr = this->first->next;
			delete this->first;
			this->first = curr;
		}
		sz = 0;
	}

	TList(const TList& other) {//copy constructor
		if (other.sz != 0) {
			this->sz = other.sz;
			Node* curr1 = other.first; //èäåì ïî ýëåìåíòàì êîïèðóåìîãî ñïèñêà
			Node* curr2 = new Node(nullptr, curr1->value); //òî, êóäà êîïèðóåì ýëåìåíòû ñïèñêà
			this->first = curr2;

			while (!curr1) {//ïîêà ýëåìåíò ñóùåñòâóåò
				Node* next1 = curr1->next; 
				if (!next1) break; //ïðîâåðÿåì åñòü ëè â êîïèðóåìîì ñïèñêå ñëåäóþùèé ýëåìåíò
				curr2->next = new Node(nullptr, next1->value); //åñëè åñòü, òî êîïèðóåì ñëåäóþùèé ýëåìåíò
				curr2 = curr2->next; //äâèãàåìñÿ ïî êîïèðóåìîìó ñïèñêó
				curr1 = curr1->next; //è ïî òîìó, êóäà êîïèðóåì
			}
		}
	}

	TList& operator=(const TList& other) {//operator=
		if(this == &other) return *this;
		this->clear();
		this->sz = other.sz;
		if (other.sz != 0) {
			Node* curr1 = other.first;
			Node* curr2 = new Node(nullptr, curr1->value);
			this->first = curr2;
			while (!curr1) {
				Node* next1 = curr1->next; 
				if (!next1) break; 
				curr2->next = new Node(nullptr, next1->value); 
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
		return *this;
	}

	TList(TList&& other) {//move constructor
		this->sz = other.sz;
		this->first = other.first;

		other.sz = 0;
		other.first = nullptr;
	}

	TList& operator=(TList&& other) {
		this->sz = other.sz;
		this->first = other.first;

		other.sz = 0;
		other.first = nullptr;

		return *this;
	}

	size_t size() const {
		return this->sz;
	}

	class iterator {
	public:
		Node* it = nullptr;
		TList* list = nullptr;
	public:
		iterator(Node* node, TList* list): it(node), list(list){}

		Node& operator*() { return *(this->it); }
		Node operator*() const { return *(this->it); }

		iterator& operator++() {
			this->it = this->it->next;
			return *this;
		}

		bool operator!=(iterator iter) const {
			return (this->it != iter.it);
		}

		bool operator==(iterator iter) const {
			return (this->it == iter.it);
		}
	};

	iterator begin() {
		return iterator(this->first, this);
	}

	iterator end() { return iterator(nullptr, this); }

	T& at(iterator it) { return (*it).value; }
	T at(iterator it) const { return (*it).value; }

	//insert'û è erase'û

	iterator insert_after(T data, iterator prev) {
		//if(prev == this->begin()) return insert_front(data);
		Node* tmp = new Node(nullptr, data);
		tmp->next = prev.it->next;
		prev.it->next = tmp;
		this->sz++;
		return iterator(tmp, this);
	}

	iterator insert_front(T data) {
		this->first = new Node(first, data);
		this->sz++;
		return iterator(this->first, this);
	}

	iterator erase_after(iterator prev) {
		//if(prev == this->begin()) return erase_front();
		Node* tmp = prev.it->next;
		if (tmp) {
			prev.it->next = prev.it->next->next;
			delete tmp;
		}
		this->sz--;
		return iterator(prev.it->next, this);
	}

	iterator erase_front() {
		Node* tmp = this->first->next;
		delete this->first;
		this->first = tmp;
		this->sz--;
		return iterator(this->first, this);
	}

	//ñðàâíåíèå
	bool operator==(const TList& other) {
		if (this->sz != other.sz) return false;

		Node* curr1 = this->first, curr2 = other.first;
		for (int i = 0; i < this->sz; i++) {
			if (curr1 != curr2) return false;
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		return true;
	}

	bool operator!=(const TList& other) {
		return !((*this) == other);
	}

	//friend ostream& operator<<(ostream& ostr, const TList& l)
	//{
	//	for (TList::iterator it = l.begin(); it != l.end(); ++it) {
	//		ostr << (*it)->value << " "
	//	}
	//	//Node* curr = this->first;
	//	//while (curr) {
	//	//	ostr << curr->value << " ";
	//	//	curr = curr->next;
	//	//}
	//	return ostr;
	//}
};
