#include "character.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

// constructor
Character::Character(std::string name, int health, int strength)
{
    this->name = name;
    this->health = health;
    this->strength = strength;
}
std::string Character::GetName() const
{
    return name;
}

void Character::takeDamage(int damage)
{
    health = health - damage;
    if (health <=0)
    {
        health = 0;
    }
}
bool Character::IsAlive() const
{
    if (health > 0)
    {
        return true;
    } 
    else 
    {
        return false;
    }
}
void Character::PrintStatus() const
{
    std::cout << "Status of " << name << "\n";
    std::cout << "Name: " << name  << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Strenght: " << strength << "\n";
}
void Character::PrintHealth() const 
{
    std::cout << "Health: " << health << std::endl;
}

int Character::GetHealth() const 
{
    return health;
}



void Character::Attack(Character &target)
{
    int actualDamage = (rand() % strength) + 1;
    std::cout << name << " Attacks " << target.name << "\n";
    std::cout << "Damage inflicted: " << actualDamage << "\n";
    target.takeDamage(actualDamage);

}

// ---------------------------------------------
// player 
// ---------------------------------------------
Player::Player(std::string name, int health, int strength) : Character(name, health, strength) 
{
}
void Player::Heal(int amount)
{
    // cap vec max health
    int actualHeal = (rand() % amount) +1;
    health = std::min(80, health + actualHeal );
    std::cout << name << " Heals for: " << actualHeal << "HP!\n";
}
// ---------------------------------------------
// vampire
// ---------------------------------------------
Vampire::Vampire(std::string name, int health, int strength) : Character(name, health, strength) 
{
}
void Vampire::Attack(Character &target)
{
   int actualDamage = (rand() % strength) + 1;
   std::cout << name << " bites " << target.GetName()<< " with his fangs!\n";
   std::cout << "Damage inflicted: " << actualDamage << "\n";
   target.takeDamage(actualDamage);
   
   health = health + actualDamage;
   std::cout << name << " lifesteals from " << target.GetName()<< " and gains " << actualDamage << " HP!\n";

}