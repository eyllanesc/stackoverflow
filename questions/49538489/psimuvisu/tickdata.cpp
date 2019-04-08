#include "tickdata.h"
#include "functional"

TickData::TickData() {
  this->enable = false;
  this->startTick = false;
  this->speed = 100;
  this->cbFun = nullptr;

  // Start
  this->enable = true;
  this->start();
}

TickData::~TickData() {}

void TickData::startData() { this->startTick = true; }

void TickData::stopData() { this->startTick = false; }

void TickData::setSpeed(int s) { this->speed = s; }

void TickData::set_callBack_newData(std::function<void(void)> cbFun) {
  this->cbFun = cbFun;
}

void TickData::run() {
  while (this->enable == true) {
    while (this->startTick == true) {
      if (this->cbFun != nullptr) {
        this->cbFun();
      }
      msleep(this->speed);
    }
  }
}
