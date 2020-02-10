#include "include/TextTagSystem.h"

// private functions
void TextTagSystem::initVariables() {}
void TextTagSystem::initTagTemplates() {
  this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "down", 100.f, 100.f, 0.f, -1.f, sf::Color::White, 50, 1000.f, 200.f);
}

void TextTagSystem::initFonts(std::string font_file) {
  if(!this->font.loadFromFile(font_file)) {
    std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font " << font_file << std::endl;
  }

}

// Constructor
TextTagSystem::TextTagSystem(std::string font_file) {

  initFonts(font_file);
  this->initTagTemplates();
  this->initVariables();
}

// Destructor
TextTagSystem::~TextTagSystem() {
  // Clean up tags
  for(auto* tag: this->tags) {
    delete tag;
  }

  // Clean up templates
  for(auto &tag: this->tagTemplates) {
    delete tag.second;
  }
}



// functions
void TextTagSystem::addTextTagString(unsigned tag_type, float pos_x, float pos_y, const std::string str) {
  this->tags.push_back(new TextTag(this->tagTemplates[DEFAULT_TAG], pos_x, pos_y, str));
}

void TextTagSystem::removeTextTag() {

}

void TextTagSystem::update(const float& dt) {
  for(auto* tag: this->tags) {
    tag->update(dt);

    if(tag->canBeRemoved()) {
      delete tag;
    }
  }
}

void TextTagSystem::render(sf::RenderTarget& target) {
  for(auto& tag: this->tags) {
    tag->render(target);
  }
}
