#ifndef __STATE_HPP_
#define __STATE_HPP_

#include "Entity.h"
#include <stack>
#include "GraphicsSettings.h"

class State;
class Player;
class GraphicsSettings;

class StateData {
public:
  StateData() {}

  // Variables
  float gridSize;
  sf::RenderWindow* window;
  GraphicsSettings* gfxSettings;
  std::map<std::string, int>* supportedKeys;
  std::stack<State*>* states;
};


class State {
private:

protected:
  StateData* stateData;
  std::stack<State*>* states;
  sf::RenderWindow* window;
  std::map<std::string, int>* supportedKeys;
  std::map<std::string, int> keybinds;

  bool quit;
  bool paused;
  float keytime;
  float keytimeMax;
  float gridSize;

  sf::Vector2i mousePosScreen;
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;
  sf::Vector2i mousePosGrid;

  // Resources
  std::map<std::string, sf::Texture> textures;

  // FUNCTIONS
  virtual void initKeybinds() = 0;



public:
  State(StateData* state_data);
  virtual ~State();

  // Accessors
  const bool getQuit() const;
  const bool getKeytime();

  // functions
  // percent to pixels
  const float p2pX(const float perc) const;
  const float p2pY(const float perc) const;
  const unsigned calcCharSize() const;

  void endState();
  void pauseState();
  void unpauseState();

  virtual void updateMousePositions(sf::View* view = nullptr);
  virtual void updateKeytime(const float& dt);
  /* pure virtual */
  /* make sure when inheritence, inherited class must implement pure virtual function */
  /* end state function */
  virtual void updateInput(const float& dt) = 0;
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
