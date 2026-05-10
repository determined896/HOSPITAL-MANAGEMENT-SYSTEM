#pragma once
#include <string>

class Person
{
protected:
	int _id;
	char* name;
	char* password;

public:
	Person();
	Person(int ID, const char* name, const char* password);
	Person(const Person& other);

	void setID(int id) { _id = id; }
	void setName(const char* name);
	void setPassword(const char* password);

	virtual int getID() const { return _id; }
	virtual const char* getName() const { return name; }
	virtual const char* getPassword() const { return password; }

	virtual void display() const = 0;
	virtual void input() = 0;

	Person& operator=(const Person& other);

	virtual ~Person();

};