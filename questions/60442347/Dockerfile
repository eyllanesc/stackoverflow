FROM ubuntu:18.04

RUN apt-get update && \
    apt-get autoclean

RUN apt-get update && apt-get install \
    -y --no-install-recommends \
    python3-pip \
    python3-setuptools \
    build-essential \
    cmake \
    libegl1-mesa \
    libgl1-mesa-dri \
    x11-xserver-utils \
    libxkbcommon-x11-0 \
    x11-utils \
    libxcb-xinput-dev \
    libxcb-shm0 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-xinerama0 \
    git \
    ca-certificates 

RUN python3 -m pip install --upgrade pip && python3 -m pip install conan

RUN conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"

RUN git clone https://github.com/eyllanesc/Qt-CMake-HelloWorld.git

RUN cd  Qt-CMake-HelloWorld  && mkdir build && cd build && conan install .. && cmake .. && make

CMD ./Qt-CMake-HelloWorld/build/bin/helloworld