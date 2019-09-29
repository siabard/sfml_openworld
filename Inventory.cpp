#include "include/stdafx.h"
#include "include/Inventory.h"

// private functions
void Inventory::initialize() {
  this->nrOfItems = 0;

  this->itemArray = new Item*[this->capacity];

  this->nullify();
}

void Inventory::expand() {}

void Inventory::nullify(const unsigned from) {
  for(size_t i = from; i < this->capaticy; i++) {
    this->itemArray[i] = nullptr;
  }
}

void Inventory::freeMemory() {
  for(size_t i = 0; i < this->nrOfItems; i++) {
    delete this->itemArray[i];
  }

  delete[] this->itemArray;
}


// Constructor && Destructor

Inventory::Inventory(unsigned capacity) {
  this->capacity = capacity;
  this->initialize();

}

Inventory::~Inventory() {
  this->freeMemory();
}

// accessors
const unsigned& Inventory::size() const {
  return this->nrOfItems;
}

const unsigned& Inventory::maxSize() const {
  return this->capacity;
}

// functions
void Inventory::clear() {
  for(size_t i = 0; i < this->nrOfItems; i++) {
    delete this->itemArray[i];
  }
  this->nrOfItems = 0;
  this->nullify();
}

const bool Inventory::empty() const {
  return this->nrOfItems == 0;
}

const bool Inventory::add(Item* item) {

}

const bool Inventory::remove(const unsigned index) {

}

const bool Inventory::saveToFile(const std::string fileName) {}

const bool Inventory::loadFromFile(const std::string fileName) {}
