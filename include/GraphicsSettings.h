#ifndef __GRAPHICS_SETTINGS_H__
#define __GRAPHICS_SETTINGS_H__

class GraphicsSettings {
public:
  GraphicsSettings();

  // variables
  std::string title;
  sf::VideoMode resolution;
  bool fullscreen;
  bool verticalSync;
  unsigned frameRateLimit;
  sf::ContextSettings contextSettings;
  std::vector<sf::VideoMode> videoModes;

  // functions
  void saveToFile(const std::string path);;

  void loadFromFile(const std::string path);;
};

#endif
