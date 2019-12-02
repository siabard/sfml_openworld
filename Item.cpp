#include "include/stdafx.h"
#include "include/Item.h"

void Item::initVariables() {

}

Item::Item(unsigned value) {
  this->initVariables();

  this->value = value;
  this->type = ItemTypes::IT_DEFAULT;

}

Item::~Item() {

}
