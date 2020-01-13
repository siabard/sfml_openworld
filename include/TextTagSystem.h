#ifndef __TEXT_TAG_SYSTEM_H__
#define __TEXT_TAG_SYSTEM_H__

#include "stdafx.h"

class TextTagSystem {
 private:

  class TextTag {
  public:
  };

 public:
  TextTagSystem();
  virtual ~TextTagSystem();

  // Functions
  void addTextTag(TextTag* text_tag);
  void removeTextTag();

  void update(const float &dt);
  void render(sf::RenderTarget* target);
};

#endif
