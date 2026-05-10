#include <iostream>
#include <cstring>
using namespace std;

#include "Person.h"

Person::Person()
{
	_id = 0;

	name = nullptr;
	password = nullptr;
}
Person::Person(int ID, const char* name, const char* password)
{
	_id = ID;

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);

	this->password = new char[strlen(password) + 1];
	strcpy_s(this->password, strlen(password) + 1, password);
}

Person::~Person()
{
	delete[] name;
	delete[] password;
}

void Person::setPassword(const char* password)
{
	if (!password) 
		return;
	delete[] this->password;

	this->password = new char[strlen(password) + 1];
	strcpy_s(this->password, strlen(password) + 1, password);
}

void Person::setName(const char* name)
{
	if (!name) 
		return;
	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

Person::Person(const Person& other)
{
	_id = other._id;

	name = new char[strlen(other.name) + 1];
	strcpy_s(name, strlen(other.name) + 1, other.name);

	password = new char[strlen(other.password) + 1];
	strcpy_s(password, strlen(other.password) + 1, other.password);
}

Person& Person::operator=(const Person& other)
{
	if (this == &other) return *this;

	delete[] name;
	delete[] password;

	_id = other._id;

	name = new char[strlen(other.name) + 1];
	strcpy_s(name, strlen(other.name) + 1, other.name);

	password = new char[strlen(other.password) + 1];
	strcpy_s(password, strlen(other.password) + 1, other.password);

	return *this;
}