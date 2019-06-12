#ifndef __EDITOR_STATE_H__
#define __EDITOR_STATE_H__

#include "State.h"
#include "Button.h"

class EditorState
  : public State {
 public:

private:
  // Variables
  sf::Font font;

  std::map<std::string, Button*> buttons;

protected:
  // functions
  void initVariables();
  void initBackground();
  void initFonts();
  void initKeybinds();
  void initButtons();

public:
  EditorState(sf::RenderWindow*,  std::map<std::string, int>*, std::stack<State*>*);
  virtual ~EditorState();

  // fucntions
  void updateButtons();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
  void renderButtons(sf::RenderTarget* target = nullptr);

};

#endif
