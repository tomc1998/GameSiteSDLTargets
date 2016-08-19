#include "player.hpp"
#include "vector.hpp"
#include "state.hpp"
#include "input_handler.hpp"
#include <math.h>


void Player::update(State* state, float delta) {
  static const float speed = 15;
  if (A_DOWN) {
    pos.x -= delta*speed*cos(M_PI*rotX/180.f);
    pos.z -= delta*speed*sin(M_PI*rotX/180.f);
  }
  if (D_DOWN) {
    pos.x += delta*speed*cos(M_PI*rotX/180.f);
    pos.z += delta*speed*sin(M_PI*rotX/180.f);
  }
  if (W_DOWN) {
    pos.x += delta*speed*sin(M_PI*rotX/180.f);
    pos.z -= delta*speed*cos(M_PI*rotX/180.f);
  }
  if (S_DOWN) {
    pos.x -= delta*speed*sin(M_PI*rotX/180.f);
    pos.z += delta*speed*cos(M_PI*rotX/180.f);
  }
  //if (Q_DOWN) {
  //  pos.y -= delta*speed;
  //}
  //if (E_DOWN) {
  //  pos.y += delta*speed;
  //}
  if (pos.x+rad > state->rightPos) {
    pos.x = state->rightPos-rad;
  }
  if (pos.x-rad < -state->rightPos) {
    pos.x = -state->rightPos+rad;
  }
  if (pos.z+rad > state->backPos) {
    pos.z = state->backPos-rad;
  }
  if (pos.z-rad < state->frontPos) {
    pos.z = state->frontPos+rad;
  }
}

void Player::init(float _x, float _y, float _z) {
  rotX = 0;
  rotY = 0;
  pos.x = _x;
  pos.y = _y;
  pos.z = _z;
  rad = 3;
}

Player::Player() {
  init(0, 0, 0);
}

Player::Player(float _x, float _y, float _z) {
  init(_x, _y, _z);
}
