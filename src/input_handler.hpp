#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP
#include "state.hpp"

extern int W_DOWN;
extern int A_DOWN;
extern int S_DOWN;
extern int D_DOWN;
extern int Q_DOWN;
extern int E_DOWN;


extern float xSens, ySens;

void handleInput(State& state, float delta);

#endif
