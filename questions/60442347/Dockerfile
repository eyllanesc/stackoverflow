FROM ubuntu:18.04

RUN apt-get update && \
    apt-get autoclean

RUN apt-get update && apt-get install \
    -y --no-install-recommends \
    python3-pip \
    python3-setuptools \
    build-essential \
    cmake \
    git \
    ca-certificates \
    libgl1-mesa-dev \
    libxcb-xinerama0 \
    libxcb-shm0 \
    libxcb-xinput0

RUN python3 -m pip install --upgrade pip && python3 -m pip install conan

RUN conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"

RUN conan install qt/5.14.1@bincrafters/stable

RUN git clone https://github.com/eyllanesc/Qt-CMake-HelloWorld.git

RUN cd  Qt-CMake-HelloWorld  && mkdir build && cd build && conan install .. && cmake .. && make

CMD ./Qt-CMake-HelloWorld/build/bin/helloworld