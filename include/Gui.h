#ifndef __GUI_H__
#define __GUI_H__


enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {

  // percent to pixels
  const float p2pX(const float perc, const sf::VideoMode& vm);
  const float p2pY(const float perc, const sf::VideoMode& vm);
  const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

  class Button {
  private:

    short unsigned buttonState;
    short unsigned id;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    sf::Color outlineIdleColor;
    sf::Color outlineHoverColor;
    sf::Color outlineActiveColor;


  public:
    Button(float x, float y, float width, float height,
           sf::Font* font, std::string text, unsigned character_size,
           sf::Color text_idle_color,  sf::Color text_hover_color,  sf::Color text_active_color,
           sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
           sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
           short unsigned id = 0);
    virtual ~Button();


    // accessors
    const short unsigned getId() const;
    const bool isPressed() const;
    const std::string getText() const;

    // modifiers
    void setText(const std::string text);
    void setId(const short unsigned id);

    // functions
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& mousePos);
  };

  class DropDownList {
  private:
    float keytime;
    float keytimeMax;

    sf::Font& font;
    gui::Button* activeElement;
    std::vector<gui::Button*> list;
    bool showList;

  public:

    DropDownList(float x, float y,  float width, float height,  sf::Font& font, std::string list[], unsigned numOfElements, unsigned default_index = 0);
    virtual ~DropDownList();

    // accessors
    const unsigned short getActiveElementId() const;
    // functions
    const bool getKeytime();
    void updateKeytime(const float& dt);
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2i& mousePos, const float& dt);

  };

  class TextureSelector {
  private:
    const float keytimeMax;
    float keytime;

    float gridSize;
    bool active;
    bool hidden;
    gui::Button* hide_btn;

    sf::RectangleShape bounds;
    sf::Sprite sheet;
    sf::RectangleShape selector;
    sf::Vector2u mousePosGrid;
    sf::IntRect textureRect;

  public:
    TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
    virtual ~TextureSelector();

    // accessors
    const bool& getActive() const;
    const sf::IntRect& getTextureRect() const;
    // function
    void update(const sf::Vector2i& mousePosWindow, const float& dt);
    void render(sf::RenderTarget& target);
    void updateKeytime(const float& dt);
    const bool getKeytime();
  };

  class ProgressBar {
  private:
    std::string barString;
    float maxWidth;
    int maxValue;
    sf::Text text;
    sf::RectangleShape back;
    sf::RectangleShape inner;


  public:
    ProgressBar(float x, float y, float width, float height, int max_value,  sf::VideoMode& vm, sf::Font* font = nullptr);
    virtual ~ProgressBar();

    // accessors

    // modifiers

    // functions
    void update(const int current_value);
    void render(sf::RenderTarget& target);
  };
}
#endif
