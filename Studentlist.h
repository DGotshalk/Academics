#pragma once
#include <string>
#include <iostream>
#include "../GenericList/List.h"

/*I am not very creative, its my biggest downfall*/
struct Student {
public:
	Student() : first_name{ "" }, last_name{ "" }, age{ "" } {};
	Student(std::string first, std::string last, std::string a) : first_name{ first }, last_name{ last }, age{ a } {};
	//Student(Student& stud) : first_name{ stud.first_name }, last_name{ stud.last_name }, age{ stud.age } {};
	std::string first_name;
	std::string last_name;

	std::string age;
};

class Studentlist :
	public LinkedList<Student>{
public:
	//StudentOverride() : head{ get_head() }, tail{ get_tail() }, size{ get_size() } {};
	//StudentOverride(const LinkedList<T>& list) : tail{ list.get_tail() }, head{ list.get_head } {};
	Node<Student>* Find(std::string first, std::string last);
	bool Remove(std::string first, std::string last);
	Node<Student>* Index_Before(std::string first, std::string last);
};