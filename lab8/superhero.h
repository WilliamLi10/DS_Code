#ifndef __SUPERHERO_H__
#define __SUPERHERO_H__
#include<string>
#include<iostream>
class Superhero{
public:
	Superhero(std::string Tname, std::string Ttrue_identity, std::string Tsuperpower)
		:name(Tname), true_identity(Ttrue_identity), superpower(Tsuperpower), good(true) {}
	const std::string& getName() const {return name;}
	const std::string& getPower() const {return superpower;}
	const std::string& getTrueIdentity() const {return true_identity;}
	bool operator==(const std::string& other);
	bool operator!=(const std::string& other);
	void operator-() { this->good = !this->good;}
	bool isGood() {return good;}
	bool operator>(const Superhero& other);
	friend std::ostream& operator<<(std::ostream& ostr, const Superhero& hero);
private:
	std::string name;
	std::string true_identity;
	std::string superpower;
	bool good;

};

std::ostream& operator<<(std::ostream& ostr, const Superhero& hero);
#endif