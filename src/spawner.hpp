#ifndef SPAWNER_HPP
#define SPAWNER_HPP

class State;
class Spawner {
public:
  Spawner();
  void update(State* state);
private:
  int millisBetweenTargets; // Millis between target spawns
  int targetCounter;        // Cumulative millis from last target spawn
  int prevMillis;
};

#endif
