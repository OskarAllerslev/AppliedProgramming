#include "Game.hpp"

int main() 
{
  Game game;
  game.run();
  return 0;
}





/*
to compile 
clang++ main.cpp character.cpp Game.cpp -I SFML/include -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -o game.exe
*/