#include "include/stdafx.h"
#include "include/State.h"

State::State(StateData* state_data) {
  this->stateData = state_data;
  this->window = state_data->window;
  this->supportedKeys = state_data->supportedKeys;
  this->states = state_data->states;
  this->quit = false;
  this->paused = false;
  this->keytime = 0.f;
  this->keytimeMax = 10.f;
  this->gridSize = state_data->gridSize;
}

State::~State() {
}


const bool State::getQuit() const {
  return this->quit;
}

void State::updateMousePositions(sf::View* view) {
  this->mousePosScreen = sf::Mouse::getPosition();
  this->mousePosWindow = sf::Mouse::getPosition(*this->window);

  if(view) {
    this->window->setView(*view);
  }

  this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
  this->mousePosGrid =
    sf::Vector2i(static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
                 static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
                 );

  this->window->setView(this->window->getDefaultView());
}

/**
 * Converts a percentage value to pixels relative to the current resolution in the x-axis
 * @param perc the percentage value
 * @return the calculated pixel value
 */
const float State::p2pX(const float perc) const {
  return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.width * (perc / 100.f)));
}

/**
 * Converts a percentage value to pixels relative to the current resolution in the y-axis
 *
 * @param perc the percentage value
 * @return the calculated pixel value
 */
const float State::p2pY(const float perc) const {
  return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.height * (perc / 100.f)));
}


/**
 * Converts a percentage value to size relative to the current resolution
 *
 * @return the calculated font size
 */
const unsigned State::calcCharSize() const {
  return
    static_cast<unsigned>(this->stateData->gfxSettings->resolution.width + this->stateData->gfxSettings->resolution.height)
    / 60
    ;
}

void State::endState() {
  this->quit = true;
}

void State::pauseState() {
  this->paused = true;
}

void State::unpauseState() {
  this->paused = false;
}


void State::updateKeytime(const float& dt) {
  if(this->keytime < this->keytimeMax)
    this->keytime += 100.f * dt;
}

const bool State::getKeytime() {
  if (this->keytime >= this->keytimeMax) {
    this->keytime = 0.f;
    return true;
  }
  return false;
}
