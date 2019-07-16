#ifndef __PLAYERGUI_H__
#define __PLAYERGUI_H__

#include "Player.h"

class PlayerGUI {
 private:
  Player* player;

  sf::Font font;

  // Exp bar

  // HP bar
  std::string hpBarString;
  float hpBarMaxWidth;
  sf::Text hpBarText;
  sf::RectangleShape hpBarBack;
  sf::RectangleShape hpBarInner;

  void initFont();
  void initHpBar();

 public:
  PlayerGUI(Player* player);
  virtual ~PlayerGUI();

  // functions
  void updateHpBar();
  void update(const float& dt);

  void renderHpBar(sf::RenderTarget& target);
  void render(sf::RenderTarget& target);
};

#endif
