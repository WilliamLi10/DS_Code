#include"superhero.h"
#include<string>
#include<iostream>
bool Superhero::operator==(const std::string& guess)
{
	return this->true_identity == guess;
}
bool Superhero::operator!=(const std::string& guess)
{
	return this->true_identity != guess;
}

bool Superhero::operator>(const Superhero& other)
{
	if( this->superpower == "Fire" && other.superpower == "Wood")
	{
		return true;
	}
	else if( this->superpower == "Wood" && other.superpower == "Water")
	{
		return true;
	}
	else if( this->superpower == "Water" && other.superpower == "Fire")
	{
		return true;
	}
	else
	{
		return this->superpower.size() > other.superpower.size();
	}
}

std::ostream& operator<<(std::ostream& ostr, const Superhero& hero)
{
	if(hero.good)
		ostr <<"Super hero " << hero.getName() << " with super power " << hero.getPower() << std::endl;
	else
		ostr <<"Super villan " << hero.getName() << " with super power " << hero.getPower() << std::endl;
	return ostr;
}