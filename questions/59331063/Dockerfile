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
  qml-module-qtquick-controls \
  qml-module-qtquick-controls2 \
  qml-module-qtquick-window2  \
  liboscpack-dev

COPY app app

RUN mkdir app/3rdPartyLibs && \
	cd app/3rdPartyLibs && \
	git clone https://github.com/eyllanesc/qml-osc.git

RUN mkdir app/build && \
	cd app/build && \
	qmake .. && \
	make

CMD app/build/59331063