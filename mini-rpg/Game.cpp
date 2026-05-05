#include "Game.hpp"
#include <iostream>

// constructor
Game::Game() 
    : window(sf::VideoMode(1000, 800), "MINI-RPG"),
      player("Oskar", 100, 20),
      enemy("Dracula", 80, 15),
      currentState(PLAYER_TURN),
      enemyDelay(0.8f),
      timer(0.f),
      playerColor(sf::Color::White),
      enemyColor(sf::Color::White)
{
    if (!font.loadFromFile("Assets/Fonts/font.TTF")) {
        std::cout << "Kunne ikke loade font!\n";
    }
    if (!playerTex.loadFromFile("Assets/Sprites/player.png") || 
        !enemyTex.loadFromFile("Assets/Sprites/vampire.png")) {
        std::cout << "Kunne ikke loade sprites!\n";
    }

    playerSprite.setTexture(playerTex);
    playerSprite.setPosition(150.f, 400.f);
    playerSprite.setScale(1.0f, 1.0f);

    enemySprite.setTexture(enemyTex);
    enemySprite.setPosition(650.f, 400.f);
    enemySprite.setScale(1.0f, 1.0f);

    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(20.f, 20.f);

    actionLog = "A wild monster attacks!\nPress space to attack! (H to Heal)";
}

// game loop
void Game::run() {
    while (window.isOpen()) {
        float dt = gameClock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

// input handler 
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (currentState == PLAYER_TURN && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                player.Attack(enemy);
                enemyColor = sf::Color::Red;
                timer = 0.f;
                actionLog = "You attacked " + enemy.GetName() + "!";
                
                if (!enemy.IsAlive()) {
                    actionLog += "\nYou defeated the monster!";
                    currentState = GAME_OVER;
                } else {
                    currentState = ENEMY_TURN;
                }
            }
            else if (event.key.code == sf::Keyboard::H) {
                player.Heal(25);
                actionLog = "You healed yourself!";
                currentState = ENEMY_TURN;
                timer = 0.f;
            }
        }
    }
}

//  logix and enemy turn
void Game::update(float dt) {
    if (currentState == ENEMY_TURN) {
        timer += dt;
        if (timer >= enemyDelay) {
            enemy.Attack(player);
            playerColor = sf::Color::Red;
            actionLog = enemy.GetName() + " attacked you!";
            
            if (!player.IsAlive()) {
                actionLog += "\nYOU DIED";
                currentState = GAME_OVER;
            } else {
                currentState = PLAYER_TURN;
            }
            timer = 0.f;
        }
    }

    // fade back to white 
    if (playerColor.g < 255) {
        int val = std::min(255, (int)(playerColor.g + 10));
        playerColor = sf::Color(255, val, val);
    }
    if (enemyColor.g < 255) {
        int val = std::min(255, (int)(enemyColor.g + 10));
        enemyColor = sf::Color(255, val, val);
    }

    // update text and colors
    std::string uiString = actionLog + "\n\n";
    uiString += player.GetName() + " HP: " + std::to_string(player.GetHealth()) + "\n";
    uiString += enemy.GetName() + " HP: " + std::to_string(enemy.GetHealth());
    infoText.setString(uiString);

    playerSprite.setColor(playerColor);
    enemySprite.setColor(enemyColor);
}

// render
void Game::render() {
    window.clear(sf::Color(30, 30, 30));
    window.draw(playerSprite);
    window.draw(enemySprite);
    window.draw(infoText);
    window.display();
}