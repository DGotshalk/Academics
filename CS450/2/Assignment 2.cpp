// Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "Studentlist.h"

#include <sstream>

void control_loop(Studentlist& studentlist);
void output(Studentlist& studentlist);
void Insert(Studentlist& studentlist);
void Find(Studentlist& studentlist, bool type);
void Remove(Studentlist& studentlist, bool type);
int Indexcheck(Studentlist& studentlist);
Student create_student();
void Append(Studentlist& studentlist);

int main() {
	Studentlist studentlist;
	std::cout << "This is a specified generic type linked list that currently holds a student struct" << std::endl;
	control_loop(studentlist);

	return 0;
}


int decision_process(Studentlist& studentlist) {
	std::cout << "\n-----------------------" << std::endl;
	std::cout << "CURRENT SIZE OF LIST: " << studentlist.get_size() << std::endl;
	std::cout << "-----------------------" << std::endl;
	if (studentlist.get_head() != nullptr) {
		output(studentlist);
	}
	std::string decision{ "" };
	std::cout << "-----------------------" << std::endl;
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "Append to list (1)\nInsert(2)\nFind by index(3), Find by name(4)\nRemove by index(5), Remove by name(6)\nEnd program(7)" << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cin >> decision;
	//std::cout << std::endl;
	int choice;
	std::stringstream(decision) >> choice;
	return choice;
};
// This loop is the main interaction, it displays the size of the list, the items in the list, and allows for the input of the options.
void control_loop(Studentlist& studentlist) {
	while (true) {
		int choice = decision_process(studentlist);
		switch (choice) {
		case 1:
			Append(studentlist);
			break;
		case 2:
			Insert(studentlist);
			break;
		case 3:
			Find(studentlist, false);
			break;
		case 4:
			Find(studentlist, true);
			break;
		case 5:
			Remove(studentlist, false);
			break;
		case 6:
			Remove(studentlist, true);
			break;
		case 7:
			return;
		default:
			std::cout << "Not a valid option" << std::endl;
			break;
		}

	}

};
/*this function allows you to see all the elements of a the list, displays when list is not empty*/
void Append(Studentlist& studentlist) {
	Student student{ create_student() };
	studentlist.Append(student);
};
/*Checks to see if index is valid first before creating a student and inserting to list*/
void Insert(Studentlist& studentlist) {
	int indexint{ Indexcheck(studentlist) };
	if (indexint == -1) {
		Append(studentlist);
		return;
	}
	if (indexint == 0) {
		return;
	}
	else {
		Student student{ create_student() };
		studentlist.Insert(student, indexint);
	}
};


/*Boolean value is there to check if its by index or by name, either way searches through the linked list*/
void Find(Studentlist& studentlist, bool type) {
	if (type == false) {
		int indexint{ Indexcheck(studentlist) };
		if (indexint == 0) {
			return;
		}
		else {
			Node<Student>* foundstudent{ studentlist.LinkedList<Student>::Find(indexint) };
			std::cout << "First name: " << foundstudent->item.first_name << std::endl;
			std::cout << "Last name: " << foundstudent->item.last_name << std::endl;
			std::cout << "Age: " << foundstudent->item.age << std::endl;
		}
	}
	if (type == true) {
		std::cout << "First name of student: ";
		std::string firstname;
		std::cin >> firstname;
		std::cout << "\nLast name of student: ";
		std::string last;
		std::cin >> last;
		Node<Student>* foundstudent{ studentlist.Find(firstname, last) };

		if (foundstudent == nullptr) {
			std::cout << "\nStudent not in list" << std::endl;
		}
		else {
			std::cout << "-----------------------" << std::endl;
			std::cout << "Found Student at index: " << foundstudent->index << std::endl;
			std::cout << "First name: " << foundstudent->item.first_name << std::endl;
			std::cout << "Last name: " << foundstudent->item.last_name << std::endl;
			std::cout << "Age: " << foundstudent->item.age << std::endl;
		}
	}
};

/*Same idea as find, boolean values decides whether to search by name or by index*/
void Remove(Studentlist& studentlist, bool type) {
	if (type == false) {
		int indexint{ Indexcheck(studentlist) };
		if (indexint == 0 || indexint == -1) {
			std::cout << "Not a valid index, index starts at 1 and max index is: " << studentlist.get_size() << std::endl;
			return;
		}
		else {
			studentlist.LinkedList<Student>::Remove(indexint);
		}
	}
	if (type == true) {
		std::cout << "First name of student: ";
		std::string firstname;
		std::cin >> firstname;
		std::cout << "\nLast name of student: ";
		std::string last;
		std::cin >> last;
		bool success = studentlist.Remove(firstname, last);
		if (success == true) {
			std::cout << "\nStudent removed" << std::endl;
		}
		else {
			std::cout << "\nStudent not in list" << std::endl;
		}

	}
};



/*Outputs every item in the list, from the head to tail, also showing indexes*/
void output(Studentlist& studentlist) {
	Node<Student>* head = studentlist.get_head();
	for (int i = 0; i < studentlist.get_size(); ++i) {
		//std::cout<<"-----------------------"<<std::endl;
		std::cout << "Index: " << i + 1 << std::endl;
		head->index = i + 1;
		std::cout << "First name: " << head->item.first_name << std::endl;
		std::cout << "Last name: " << head->item.last_name << std::endl;
		std::cout << "Age: " << head->item.age << std::endl;
		std::cout << "-----------------------" << std::endl;
		head = head->next;
	}
};
/* THis function checks to see if the index you put in is a valid index, that way we dont have to handle this in the class*/
int Indexcheck(Studentlist& studentlist) {

	std::cout << "Index (int) (can insert onto the end by the List size +1" << std::endl;
	std::string index;
	std::cin >> index;
	int indexint;
	std::stringstream(index) >> indexint;
	if (indexint == 1 && studentlist.get_size() == 0) {
		return -1;
	}
	else if (indexint > studentlist.get_size() + 1 || indexint == 0) {
		std::cout << "Not a valid index, index starts at 1 and max index is: " << studentlist.get_size() << std::endl;
		indexint = 0;
	}
	return indexint;
};

/* For insertions and appending we create a student, so this is the template for that*/
Student create_student() {
	std::cout << "-----------------------" << std::endl;
	std::cout << "First name of student: ";
	std::string first;
	std::cin >> first;
	std::cout << "\nLast name of student: ";
	std::string last;
	std::cin >> last;
	std::cout << "\nDate of birth: ";
	std::string age;
	std::cin >> age;
	std::cout << "-----------------------" << std::endl;
	std::cout << std::endl;
	Student New_student{ first, last, age };
	return New_student;
}
