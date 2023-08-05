#include <cassert>
#include "superhero.h"
#include "team.h"
#include<iostream>
#include<list>
bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}
Team operator+(const Team &a, const Team &b)
{
  Team retTeam = a;
  for(std::list<Superhero>::const_iterator i = b.superheroes.begin(); i != b.superheroes.end(); ++i)
  {
    retTeam.superheroes.push_back(*i);
  }
  return retTeam;
}


Team operator+(const Team &a, const Superhero &b)
{
  Team retTeam = a;
  retTeam.superheroes.push_back(b);
  return retTeam;
}

Team operator+(const Superhero &a, const Superhero &b)
{
  Team retTeam;
  retTeam += a;
  retTeam += b;
  return retTeam;
}

void Team::operator-=(const Superhero &a)
{ 
  for(std::list<Superhero>::const_iterator i = this->superheroes.begin(); i != this->superheroes.end();++i )
  {
    if(i->getName() == a.getName())
    {
      i = this->superheroes.erase(i);
      break;
    }
  }
}

