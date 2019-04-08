#ifndef GENERATORALEATOR_H
#define GENERATORALEATOR_H

class GeneratorAleator {

public:
  static void init();
  static float getNumber();
  static void setMax(float max);
  static void setMin(float min);

private:
  GeneratorAleator() {} // Disallow creating an instance of this object
  static float max;
  static float min;
};

#endif // GENERATORALEATOR_H
