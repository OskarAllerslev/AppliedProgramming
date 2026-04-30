
#include "character.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


int main() {
  srand(time(NULL));

  // set hero stength from input
  int hero_strength;
  std::cout << "Set hero strength: " << "\n";
  std::cin >> hero_strength;

  // create the characters25
  Player hero("Oskar", 25, hero_strength);
  Vampire monster("Dracula", 15, 3);

  std::cout << "------------------------------\n";
  hero.PrintStatus();
  monster.PrintStatus();

  std::cout << "------------------------------\n";

  while (hero.IsAlive() && monster.IsAlive()) {
    std::cout << "\n*** Your turn ***\n";
    std::cout << "Choose an action:\n";
    std::cout << "[1] Attack\n";
    std::cout << "[2] Heal\n";
    std::cout << "Your choice: ";
    
    int choice;
    std::cin >> choice;
    std::cout << "\n";
    
    if (choice == 1)
    {
        hero.Attack(monster);
    } 
    else if (choice == 2)
    {
        hero.Heal(10);
    } 
    else 
    {
        std::cout << "You dozed away and you lose your chance!\n";
    }

    
    if (monster.IsAlive()) 
    { 
        std::cout << "\n*** Monster turn ***\n";
        monster.Attack(hero);
    }
    std::cout << "------------------------------\n";
    hero.PrintHealth();
    monster.PrintHealth();
    std::cout << "------------------------------\n";
  }
  if (hero.IsAlive())
  {
    std::cout << "You won!\n";
  } 
  else 
  {
    std::cout << "You lost...\n";
  }
}