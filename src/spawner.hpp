#ifndef SPAWNER_HPP
#define SPAWNER_HPP

class State;
class Spawner {
public:
  Spawner();
  void update(State* state, float delta);
  void start();
  void stop();
  int millisBetweenTargets; // Millis between target spawns
  float targetFadeSpeed;
private:
  int targetCounter;        // Cumulative millis from last target spawn
  int prevMillis;
  int running;
};

#endif
