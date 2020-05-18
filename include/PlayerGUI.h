#ifndef __PLAYERGUI_H__
#define __PLAYERGUI_H__

#include "Player.h"
#include "Gui.h"
#include "PlayerGUITabs.h"

class PlayerGUI {
 private:
  Player* player;

  sf::Font font;
  sf::VideoMode& vm;

  // Level Bar
  std::string levelBarString;
  sf::Text levelBarText;
  sf::RectangleShape levelBarBack;

  // Exp bar
  gui::ProgressBar* expBar;

  // HP bar
  gui::ProgressBar* hpBar;

  // tabs
  PlayerGUITabs* playerTabs;

  void initFont();
  void initLevelBar();
  void initEXPBar();
  void initHpBar();
  void initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player);

 public:
  PlayerGUI(Player* player, sf::VideoMode& vm);
  virtual ~PlayerGUI();

  // functions
  void updateLevelBar();
  void updateEXPBar();
  void updateHpBar();
  void update(const float& dt);
  void updatePlayerTabs();

  void renderLevelBar(sf::RenderTarget& target);
  void renderEXPBar(sf::RenderTarget& target);
  void renderHpBar(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
  void renderPlayerTabs(sf::RenderTarget& target);
};

#endif
