#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "character.hpp"


enum GameState
{
  PLAYER_TURN,
  ENEMY_TURN,
  GAME_OVER
};

int main()
{
  // spilvindue navn
  sf::RenderWindow window(sf::VideoMode(1000,800), "MINI-RPG");

  // set font 
    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/font.TTF")) return -1;

    sf::Texture playerTex, enemyTex;
    if (!playerTex.loadFromFile("Assets/Sprites/player.png")) return -1;
    if (!enemyTex.loadFromFile("Assets/Sprites/vampire.png")) return -1;

  // create sprites

  sf::Sprite playerSprite(playerTex);
  playerSprite.setPosition(150.f, 400.f);
  playerSprite.setScale(1.0f,1.0f);

  sf::Sprite enemySprite(enemyTex);
  enemySprite.setPosition(650.f, 400.f);
  enemySprite.setScale(1.0f, 1.0f);

  // create characters
  Player player("Oskar", 100, 20);
  Vampire enemy("Dracula", 80, 15);

  sf::Text infoText;
  infoText.setFont(font);
  infoText.setCharacterSize(24);
  infoText.setFillColor(sf::Color::White);
  infoText.setPosition(20.f, 20.f);


  GameState currentState = PLAYER_TURN;

  std::string actionLog = "A wild monster attacks!\nPress space to attack!.";

  sf::Clock gameClock;
  float enemyDelay = 0.8f;
  float timer = 0.f;


  sf::Color playerColor = sf::Color::White;
  sf::Color enemyColor = sf::Color::White;


  while(window.isOpen())
  {
    float dt = gameClock.restart().asSeconds();
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();

      if (currentState == PLAYER_TURN && event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Space) 
        {
          player.Attack(enemy);
          enemyColor = sf::Color::Red; 
          timer = 0.f;
          actionLog = "You attacked " + enemy.GetName() + "!";
          if (!enemy.IsAlive()) {
              actionLog += "\nYou defeated the monster!";
              currentState = GAME_OVER;
          }
          else currentState = ENEMY_TURN;
        }
        else if (event.key.code == sf::Keyboard::H)
        {
          player.Heal(25);
          actionLog = "You healed yourself!";
          currentState = ENEMY_TURN;
          timer = 0.f;
        }
      }
    }

    // MONSTER TURN 
    if (currentState == ENEMY_TURN)
    {
      timer += dt;
      if (timer >= enemyDelay)
      {
        enemy.Attack(player);
        playerColor = sf::Color::Red;
        actionLog = enemy.GetName() + " attacked you!";
        
        if (!player.IsAlive())
        {
            actionLog += "\nYOU DIED";
            currentState = GAME_OVER;
        }
        else 
        {
          currentState = PLAYER_TURN;
        }
        timer = 0.f;
      }
    }

    if (playerColor.g < 255) {
        int val = std::min(255, (int)(playerColor.g + 10));
        playerColor = sf::Color(255, val, val);
    }
    if (enemyColor.g < 255) {
        int val = std::min(255, (int)(enemyColor.g + 10));
        enemyColor = sf::Color(255, val, val);
    }

    std::string uiString = actionLog + "\n\n";
    uiString += player.GetName() + " HP: " + std::to_string(player.GetHealth()) + "\n";
    uiString += enemy.GetName() + " HP: " + std::to_string(enemy.GetHealth());
    infoText.setString(uiString);

    playerSprite.setColor(playerColor);
    enemySprite.setColor(enemyColor);

    // RENDER
    window.clear(sf::Color(30, 30, 30));
    window.draw(playerSprite);
    window.draw(enemySprite);
    window.draw(infoText);
    window.display();
  }


  return 0;
}





/*
to compile 
clang++ main.cpp character.cpp -I SFML/include -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -o game.exe
*/