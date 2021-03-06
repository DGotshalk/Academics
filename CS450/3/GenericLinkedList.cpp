//LinkedList
//Contains a class LinkedList, which handles the general structure of the linked list, 
//and the Node class, which contain the generic object that will be inserted into the lit
// 
//Drew Gotshalk
//2020-01-24

#include <iostream>
#include "GenericLinkedList.h"
/*
 * Generic Node class that will accept any value or class as its input into the constructor,
*/


/*this function inserts an item at the end of a list*/


template<class T>
void LinkedList<T>::Append(const T item) {
	Node<T>* newNode = new Node<T>{ item };
	if (tail == nullptr) {
		tail = newNode;
		if (head == nullptr) {
			head = newNode;
		}
	}
	else {

		Node<T>* ptr = tail;
		Node<T>* newNode = new Node<T>{ item };
		ptr->next = newNode;
		tail = newNode;

	}
	++size;
	update_index();
};


/*
 * this is a function that will go to a given index, and insert a node in the list
 * at that index
 */
template<class T>
void LinkedList<T>::Insert(const T item, int index) {
	if (index == size + 1) {
		Append(item);
		return;
	}
	if (index == 1) {
		Node<T>* newNode = new Node<T>{ item };
		Node<T>* ptr = head;
		head = newNode;
		newNode->next = ptr;
		++size;
		if (index == size) {
			tail = newNode;
		}
	}
	else {
		Node<T>* newNode = new Node<T>{ item };
		Node<T>* prev{ Index_Before(index) };
		Node<T>* ptr{ prev->next };
		prev->next = newNode;
		newNode->next = ptr;
		++size;
		if (index == size) {
			tail = newNode;
		}
	}
	update_index();
};

/* for the insert and remove operations, its important to have a trailing pointer to keep track of the item before
 * the item you want, and for the find function i can just give it the pointer of the item before, and point forwards*/
template<class T>
Node<T>* LinkedList<T>::Index_Before(int index) {
	if (index > size + 1) {
		return nullptr;
	};
	Node<T>* ptr = head;
	Node<T>*prev = nullptr;
	for (int i = 0; i < index - 1; ++i) {
		prev = ptr;
		ptr = ptr->next;
	}
	return prev;
};

/*This item finds and returns the node from a given index, does nothing if item does not exist*/
template<class T>
Node<T>* LinkedList<T>::Find(int index) {
	if (index == 1) {
		return head;
	}
	Node<T>* prev{ Index_Before(index) };
	return prev->next;
};

/*This function removes an item from the list given some index, does nothing if index does not exist */
template<class T>
void LinkedList<T>::Remove(int index) {
	Node<T>* prev{ Index_Before(index) };
	Node<T>* ptr{ prev->next };
	prev->next = ptr->next;
	delete(ptr);
	if (index == size) {
		tail = prev->next;
	}
	--size;
	update_index();
};
//updates the internal index of all the items in the linked list 
template<class T>
void LinkedList<T>::update_index() {
	Node<T> * ptr = head;
	for (int i = 0; i < size; ++i) {
		if (ptr == nullptr) {
			break;
		}
		ptr->index = i + 1;
		ptr = ptr->next;
	}

}

/*This function takes an array of items of our type, and populates them into the linked list*/
template<class T>
void LinkedList<T>::Add_Range(T* stuff, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < size; ++j) {
			if (stuff[i] == Find(i)->item) {
				break;
			}
		}
		Append(stuff[i]);
	}
};