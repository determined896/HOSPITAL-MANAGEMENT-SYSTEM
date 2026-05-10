#pragma once
#include <string>

#include "Person.h"

class Patient : public Person
{
	friend ostream& operator<<(ostream& out, const Patient&);
	friend istream& operator>>(istream& in, Patient& p);
private:
	int age;
	char gender;
	char contact[12];
	float balance;
public:
	Patient();
	Patient(int id, const char* name, int age, char gender, const char* contact, const char* password, float balance);

	void setAge(int age) { this->age = age; }
	void setGender(char gender) { this->gender = gender; }
	void setContact(const char* contact) { strcpy_s(this->contact, 12, contact); }
	void setBalance(float balance) { this->balance = balance; }

	float getBalance() const { return balance; }
	int getAge() const { return age; }
	char getGender() const { return gender; }
	const char* getContact() const { return contact; }

	Patient& operator+=(int amount);
	Patient& operator-=(int amount);
	bool operator==(const Patient& p) const;

	void display() const override;
	void input() override;
};

