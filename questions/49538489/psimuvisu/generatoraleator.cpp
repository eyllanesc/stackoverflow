#include "generatoraleator.h"
#include "time.h"
#include <QTime>
#include <stdio.h>
#include <stdlib.h>

float GeneratorAleator::max = 10;
float GeneratorAleator::min = -10;

void GeneratorAleator::init() { qsrand(QTime::currentTime().msec()); }

float GeneratorAleator::getNumber() {
  float a = GeneratorAleator::min;
  float b = GeneratorAleator::max;
  return (qrand() / (double)RAND_MAX) * (b - a) + a;
}

void GeneratorAleator::setMax(float max) { GeneratorAleator::max = max; }

void GeneratorAleator::setMin(float min) { GeneratorAleator::min = min; }
