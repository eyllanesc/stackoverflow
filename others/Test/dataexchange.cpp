#include "dataexchange.h"

DataExchange::DataExchange(QObject *parent) : QObject(parent) {
  _serialOn = false;
}

DataExchange::~DataExchange() {}
