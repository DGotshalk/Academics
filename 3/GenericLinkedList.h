#pragma once
//Defualt node class that goes into the list
template<typename T>
struct Node {
	Node() : next{ nullptr }, item{ NULL } {};
	Node(const T thing) : next{ nullptr }, item{ thing } {};
	Node(const Node<T>* node) : next{ node->next }, item{ node->item }, index{ node->index } {};
	Node<T> *next;
	T item;
	int index;
};

/*generic linked list class, which can insert into any position, remove from any position, and find and node at a given position*/

template<class T>
class LinkedList {
private:
	Node<T> *head;
	Node<T> *tail;
	int size;
public:
	LinkedList() : head{ nullptr }, tail{ nullptr }, size{ 0 } {};
	void Append(const T item);
	void Insert(const T item, int index);
	Node<T>* Find(int index);
	void Remove(int index);
	Node<T>* Index_Before(int index);
	Node<T>* get_head() { return head; }; //Used to grab the head for the purposed of iterating through the list
	Node<T>* get_tail() { return tail; };
	int get_size() { return size; };
	void update_index();
	void Add_Range(T* stuff, int n);
};