#pragma once
#include <string>

#include "Validator.h"
#include "Person.h"

class Doctor : public Person
{
	friend ostream& operator<<(ostream& out, const Doctor&);
	friend istream& operator>>(istream& in, Doctor& d);
private:
	string specialization;
	char contact[12];
	float fee;
public:
	Doctor();
	Doctor(int id, const char* name, const char* password, string specialization, const char* contact, float fee);

	void setSpecialization(const string& spec) { specialization = spec; }
	void setContact(const char* contact) { strcpy_s(this->contact, 12, contact); }
	void setFee(float fee) { this->fee = fee; }

	float getFee() const { return fee; }
	string getSpecialization() const { return specialization; }
	const char* getContact() const { return contact; }

	bool operator==(const Doctor& d);

	void display() const override;
	void input() override;
};