#ifndef __PLAYERGUI_H__
#define __PLAYERGUI_H__

#include "Player.h"
#include "Gui.h"

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
  std::string expBarString;
  float expBarMaxWidth;
  sf::Text expBarText;
  sf::RectangleShape expBarBack;
  sf::RectangleShape expBarInner;

  // HP bar
  /*
  std::string hpBarString;
  float hpBarMaxWidth;
  sf::Text hpBarText;
  sf::RectangleShape hpBarBack;
  sf::RectangleShape hpBarInner;
  */
  gui::ProgressBar* hpBar;

  void initFont();
  void initLevelBar();
  void initEXPBar();
  void initHpBar();

 public:
  PlayerGUI(Player* player, sf::VideoMode& vm);
  virtual ~PlayerGUI();

  // functions
  void updateLevelBar();
  void updateEXPBar();
  void updateHpBar();
  void update(const float& dt);

  void renderLevelBar(sf::RenderTarget& target);
  void renderEXPBar(sf::RenderTarget& target);
  void renderHpBar(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
};

#endif
