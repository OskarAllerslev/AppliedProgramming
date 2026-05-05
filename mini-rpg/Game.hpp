
#ifndef GAME_HPP
#define GAME_HPP


#include <SFML/Graphics.hpp>
#include <string>
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "character.hpp"

enum GameState
{
  PLAYER_TURN,
  ENEMY_TURN,
  GAME_OVER
};


class Game 
{
    public:
        Game();
        void run();


    private:
        void processEvents();
        void update(float dt);
        void render();

        sf::RenderWindow window;
        sf::Font font;
        sf::Texture playerTex, enemyTex;
        sf::Sprite playerSprite, enemySprite;
        sf::Text infoText;

        Player player;
        Vampire enemy;
        GameState currentState;
        std::string actionLog;

        sf::Clock gameClock;
        float enemyDelay;
        float timer;
        sf::Color playerColor;
        sf::Color enemyColor;

        // menu variables 
        int currentMenuIndex;
        sf::RectangleShape menuBox;
        std::vector<sf::Text> menuTexts;
        void setupMenu();

};


#endif