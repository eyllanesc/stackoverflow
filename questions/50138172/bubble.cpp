#include "bubble.hh"

Bubble::Bubble(int x, int y, Color c) : x_(x), y_(y), color_(c) {}

int Bubble::getX() const { return x_; }

int Bubble::getY() const { return y_; }

Color Bubble::getColor() const { return color_; }
