FROM ubuntu:18.04

MAINTAINER eyllanesc <e.yllanescucho@gmail.com>

RUN apt-get update && \
    apt-get autoclean

RUN apt-get update && apt-get install \
  -y --no-install-recommends \
  git \
  ca-certificates \
  build-essential \ 
  qt5-default \
  qtdeclarative5-dev \
  liboscpack-dev

COPY app app
RUN mkdir app/3rdPartyLibs

RUN cd app/3rdPartyLibs && git clone https://github.com/eyllanesc/qml-osc.git
RUN mkdir app/build && cd app/build && qmake .. && make

RUN apt-get update && apt-get install \
  -y --no-install-recommends \
  qml-module-qtquick-controls \
  qml-module-qtquick-controls2 \
  qml-module-qtquick-window2 

CMD app/build/59331063