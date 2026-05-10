#pragma once

#include "Person.h"

class Admin : public Person
{
	friend ostream& operator<<(ostream& out, const Admin& a);
	friend istream& operator>>(istream& in, Admin& a);

public:
	Admin() {}
	Admin(int ID, const char* name, const char* password) : Person(ID, name, password) {}

	void display() const override;
	void input() override;
};
