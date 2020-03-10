FROM ubuntu:18.04

RUN apt-get update && \
  apt-get autoclean

RUN apt-get update && apt-get install \
    -y --no-install-recommends \
    build-essential \ 
    qt5-default \
    qtdeclarative5-dev \
    qml-module-qtlocation \
    qml-module-qtpositioning \
    qml-module-qtquick-controls \
    libqt5opengl5-dev \
    qtdeclarative5-private-dev \
    qtbase5-private-dev \
    git \
    ca-certificates

RUN git clone https://code.qt.io/qt/qtlocation.git && cd qtlocation && git checkout 5.9

COPY update-HERE-Qt5.9.patch qtlocation

RUN cd qtlocation && \
	git config --global user.email "you@example.com" && \
	git am < update-HERE-Qt5.9.patch && \
	qmake . && \
	make && \
	make install

COPY app app

RUN mkdir app/build && cd app/build && qmake .. && make 
