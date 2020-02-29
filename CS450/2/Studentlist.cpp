
#include "Studentlist.h"


/*for the Find and remove ooptions, we look for the name. This returns the node previous to it, because you need that node for removal. has a special case of whehter or not the node is the head
Searches by name, first and last
*/

inline Node<Student>* Studentlist::Index_Before(std::string first, std::string last) {
	Node<Student>* ptr = get_head();
	Node<Student>*prev = nullptr;
	if (ptr == nullptr) {
		return nullptr;
	}
	if (ptr->item.first_name == first && ptr->item.last_name == last) {
		std::cout << "the item is the head" << std::endl;
		return ptr;
	}
	int size = get_size();
	for (int i = 0; i < size; ++i)
	{
		if (ptr->item.first_name == first && ptr->item.last_name == last) {
			std::cout << "returning previous node" << std::endl;
			std::cout << prev->item.first_name << " " << prev->item.last_name << std::endl;
			return prev;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return nullptr; //item in list not found
};

/*This item finds and returns the node from a given name, and null if there is no name in that list*/
inline Node<Student>* Studentlist::Find(std::string first, std::string last) {
	Node<Student>* prev{ Index_Before(first, last) };
	if (prev == nullptr) {
		return prev;
	}
	else if (prev->item.first_name == first && prev->item.last_name == last) { //edge case where the head is the item found
		return prev;
	}
	else {
		return prev->next;
	}
};

/*This function removes an item from the list given some name, and returns a true or false of whether or not the operation occurered. */
inline bool Studentlist::Remove(std::string first, std::string last) {
	Node<Student>* prev{ Index_Before(first,last) };

	if (prev == nullptr)
	{
		return false;
	}
	else if (prev->item.first_name == first && prev->item.last_name == last) { //edge case where the head is the item top be removed
		std::cout << "we are now removing the head" << std::endl;
		Node<Student>* ptr = prev->next;
		Node<Student>* head = get_head();
		head = ptr;
		delete(prev);
		if (ptr == nullptr) {
			Node<Student>* tail = get_tail();
			tail = head;
		}
		int size = get_size();
		set_size(--size);
		return true;
	}
	else {
		Node<Student>* ptr{ prev->next };
		prev->next = ptr->next;
		delete(ptr);
		if (prev->next == nullptr) {
			Node<Student>* tail = get_tail();
			tail = prev;
		}
		int size = get_size();
		set_size(--size);
		return true;
	}
};
