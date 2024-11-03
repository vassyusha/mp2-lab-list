

#include <iostream>
#include "tlist.h"
//---------------------------------------------------------------------------
template <class T>
TList<T> solution(const TList<T>& l1, const TList<T>& l2) {
	TList<T> l;
	TList<T>::iterator it1 = l1.begin(), it2 = l2.begin(), it = l.begin();
	if (it2 == l2.end()) l = l1;
	else if (it1 == l1.end()) l = l2; //если l1 пустой, то просто 
	else {
		if (l1.at(it1) < l2.at(it2)) {        //вставляем 1 элемент
			it = l.insert_front(l1.at(it1));
			++it1;
		}
		else {
			it = l.insert_front(l2.at(it2));
			++it2;
		}
		while (it1 != l1.end() && it2 != l2.end()) {//пока есть из чего выбирать выбираем и двигаем указатели
			if (l1.at(it1) < l2.at(it2)) {
				it = l.insert_after(l1.at(it1), it);
				++it1;
			}
			else {
				it = l.insert_after(l2.at(it2), it);
				++it2;
			}
		}
		if (it1 == l1.end()) for (; it2 != l2.end(); ++it2) it = l.insert_after(l2.at(it2), it);
		else for (; it1 != l1.end(); ++it1) it = l.insert_after(l1.at(it1), it);
	}
	return l;
}


int main()
{
	TList<int> l1, l2;
	TList<int> l;
	TList<int>::iterator it1 = l1.insert_front(1), it2 = l2.insert_front(0);

	for (int i = 1; i < 10; i++) {
		it1 = l1.insert_after(2 * i + 1, it1);
		it2 = l2.insert_after(2 * i, it2);
	}
	std::cout << l1 << "\n" << l2 << "\n";
	
	it1 = l1.begin();
	it2 = l2.begin();

	l = solution(l1, l2);
	std::cout << l;

	return 0;
}
//---------------------------------------------------------------------------
