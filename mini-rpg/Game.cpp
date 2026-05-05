#include "Game.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>
#include <cmath>

// constructor
Game::Game()
    : window(sf::VideoMode(1000, 800), "MINI-RPG"), player("Oskar", 100, 20),
      enemy("Dracula", 80, 10), currentState(PLAYER_TURN), enemyDelay(0.8f),
      timer(0.f), playerColor(sf::Color::White), enemyColor(sf::Color::White), playerAnimTimer(0.f), enemyAnimTimer(0.f),
      currentMenuIndex(0) {
  if (!font.loadFromFile("Assets/Fonts/font.TTF")) {
    std::cout << "Kunne ikke loade font!\n";
  }
  if (!playerTex.loadFromFile("Assets/Sprites/player.png") ||
      !enemyTex.loadFromFile("Assets/Sprites/vampire.png") ||
      !playerAttackTex.loadFromFile("Assets/Sprites/player_attack.png") ||
      !enemyAttackTex.loadFromFile("Assets/Sprites/vampire_attack.png") 
    ) {
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

  setupMenu();

  // --- OPSÆTNING AF HP BARS ---
  // Player
  playerHpBarBg.setSize(sf::Vector2f(150.f, 15.f));
  playerHpBarBg.setFillColor(sf::Color(100, 0, 0));
  playerHpBarBg.setPosition(150.f, 350.f);

  playerHpBar.setSize(sf::Vector2f(150.f, 15.f));
  playerHpBar.setFillColor(sf::Color::Green);
  playerHpBar.setPosition(150.f, 350.f);

  // Monster
  enemyHpBarBg.setSize(sf::Vector2f(150.f, 15.f));
  enemyHpBarBg.setFillColor(sf::Color(100, 0, 0));
  enemyHpBarBg.setPosition(650.f, 350.f);

  enemyHpBar.setSize(sf::Vector2f(150.f, 15.f));
  enemyHpBar.setFillColor(sf::Color::Green);
  enemyHpBar.setPosition(650.f, 350.f); 
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
      if (event.key.code == sf::Keyboard::Up) {
        currentMenuIndex--;
        if (currentMenuIndex < 0) {
          currentMenuIndex = menuTexts.size() - 1;
        }
      } else if (event.key.code == sf::Keyboard::Down) {
        currentMenuIndex++;
        if (currentMenuIndex >= menuTexts.size()) {
          currentMenuIndex = 0;
        }
      } else if (event.key.code == sf::Keyboard::Space ||
                 event.key.code == sf::Keyboard::Enter) {
        if (currentMenuIndex == 0) {
          // player attacks ------------------------------------
          int oldHp = enemy.GetHealth();
          player.Attack(enemy);
          int damage = oldHp - enemy.GetHealth();

          // Spawn flyvende skade-tal
          FloatingText ft;
          ft.text.setFont(font);
          ft.text.setCharacterSize(35);
          ft.text.setFillColor(sf::Color::Red);
          ft.text.setStyle(sf::Text::Bold);
          ft.text.setString("-" + std::to_string(damage));
          ft.text.setPosition(680.f, 330.f); 
          ft.timer = 1.0f;
          floatingTexts.push_back(ft);

          enemyColor = sf::Color::Red;
          timer = 0.f;
          playerAnimTimer = 0.3f;
          actionLog = "You attacked " + enemy.GetName() + "!";

          if (!enemy.IsAlive()) {
            actionLog += "\nYou defeated the monster!";
            currentState = GAME_OVER;
          } else {
            currentState = ENEMY_TURN;
          }
        } else if (currentMenuIndex == 1) {
            // player heals ------------------------------------
          int oldHp = player.GetHealth();
          player.Heal(25);
          int healed = player.GetHealth() - oldHp;

          // Spawn flyvende heal-tal
          FloatingText ft;
          ft.text.setFont(font);
          ft.text.setCharacterSize(35);
          ft.text.setFillColor(sf::Color::Green);
          ft.text.setStyle(sf::Text::Bold);
          ft.text.setString("+" + std::to_string(healed));
          ft.text.setPosition(180.f, 330.f); 
          ft.timer = 1.0f;
          floatingTexts.push_back(ft);

          actionLog = "You healed yourself!";
          currentState = ENEMY_TURN;
          timer = 0.f;
        }
      }
    }
  }
}

//  logic and enemy turn
void Game::update(float dt) {
  if (currentState == ENEMY_TURN) {
    timer += dt;
    if (timer >= enemyDelay) {
      // monster attacks ----------------------------------------
      int oldHp = player.GetHealth();
      enemy.Attack(player);
      int damage = oldHp - player.GetHealth();

      // Spawn flyvende skade-tal for spilleren
      FloatingText ft;
      ft.text.setFont(font);
      ft.text.setCharacterSize(35);
      ft.text.setFillColor(sf::Color::Red);
      ft.text.setStyle(sf::Text::Bold);
      ft.text.setString("-" + std::to_string(damage));
      ft.text.setPosition(180.f, 330.f); 
      ft.timer = 1.0f;
      floatingTexts.push_back(ft);

      playerColor = sf::Color::Red;
      enemyAnimTimer = 0.3f;
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

  // attack animations
  if (playerAnimTimer > 0)
  {
    playerAnimTimer -= dt;
    float fraction = std::max(0.f, playerAnimTimer / 0.3f);
    float offset = std::sin(fraction * 3.14159f) * 50.f;
    playerSprite.setPosition(150.f + offset, 400.f);
    playerSprite.setTexture(playerAttackTex);
  } else 
  {
    playerSprite.setPosition(150.f, 400.f);
    playerSprite.setTexture(playerTex);
  }

  if (enemyAnimTimer > 0)
  {
    enemyAnimTimer -= dt;
    float fraction = std::max(0.f, enemyAnimTimer / 0.3f);
    float offset = std::sin(fraction * 3.14159f) * 50.f;
    enemySprite.setPosition(650.f - offset, 400.f);
    enemySprite.setTexture(enemyAttackTex);
  } else 
  {
    enemySprite.setPosition(650.f, 400.f);
    enemySprite.setTexture(enemyTex);
  }

  // update the menu visually 
  if (currentState == PLAYER_TURN)
  {
    for (size_t i = 0; i < menuTexts.size(); ++i)
    {
      if (i == currentMenuIndex) {
        menuTexts[i].setFillColor(sf::Color::Yellow);
        menuTexts[i].setString(std::string("> ") + (i == 0 ? "Attack" : "Heal"));
      } else {
        menuTexts[i].setFillColor(sf::Color::White);
        menuTexts[i].setString(std::string("  ") + (i == 0 ? "Attack" : "Heal"));
      }
    }
  }

  // --- OPDATER HP BARER ---
  // Udregn procenter (Oskar start HP = 100, Dracula = 80)
  float pHealth = std::max(0.f, (float)player.GetHealth() / 100.f);
  playerHpBar.setSize(sf::Vector2f(150.f * pHealth, 15.f));

  float eHealth = std::max(0.f, (float)enemy.GetHealth() / 80.f); 
  enemyHpBar.setSize(sf::Vector2f(150.f * eHealth, 15.f));

  // --- OPDATER FLYVENDE TAL ---
  for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
      it->timer -= dt;
      it->text.move(0.f, -40.f * dt); // Ryk opad
      
      // Gør teksten gennemsigtig
      sf::Color c = it->text.getFillColor();
      c.a = std::max(0, (int)(255.f * (it->timer / 1.0f)));
      it->text.setFillColor(c);

      if (it->timer <= 0) {
          it = floatingTexts.erase(it); // Slet når tiden er gået
      } else {
          ++it;
      }
  }

  // update text and colors
  std::string uiString = actionLog + "\n\n";
  uiString +=
      player.GetName() + " HP: " + std::to_string(player.GetHealth()) + "\n";
  uiString += enemy.GetName() + " HP: " + std::to_string(enemy.GetHealth());
  infoText.setString(uiString);

  playerSprite.setColor(playerColor);
  enemySprite.setColor(enemyColor);
}

// render
void Game::render() {
  window.clear(sf::Color(30, 30, 30));
  
  // Tegn sprites og tekst
  window.draw(playerSprite);
  window.draw(enemySprite);
  window.draw(infoText);
  
  // Tegn HP Barer
  window.draw(playerHpBarBg);
  window.draw(playerHpBar);
  window.draw(enemyHpBarBg);
  window.draw(enemyHpBar);

  // Tegn menuen hvis det er spillerens tur
  if (currentState == PLAYER_TURN)
  {
    window.draw(menuBox);
    for (auto& text : menuTexts)
    {
        window.draw(text);
    }
  }

  // Tegn alle flyvende tal øverst
  for (auto& ft : floatingTexts) {
      window.draw(ft.text);
  }

  window.display();
}

// setup menu function
void Game::setupMenu() {
  menuBox.setSize(sf::Vector2f(300.f, 150.f));
  menuBox.setFillColor(
      sf::Color(20, 20, 20, 230)); // Mørkegrå, lidt gennemsigtig
  menuBox.setOutlineColor(sf::Color::White);
  menuBox.setOutlineThickness(3.f);
  menuBox.setPosition(50.f, 600.f);

  std::vector<std::string> options = {"Attack", "Heal"};
  for (size_t i = 0; i < options.size(); ++i) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    text.setPosition(80.f, 630.f + i * 50.f);
    menuTexts.push_back(text);
  }
}