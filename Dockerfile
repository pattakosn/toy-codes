FROM ubuntu:latest
LABEL Description="C++ build environment"

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get upgrade -y && apt-get install -y software-properties-common && add-apt-repository ppa:oibaf/graphics-drivers
RUN apt-get update && apt-get upgrade -y && apt-get install -y --reinstall ca-certificates
RUN apt-get -y --no-install-recommends install \
    git \
    pkg-config \
    wget \
    curl \
    zip \
    unzip \
    tar \
    build-essential \
    clang \
    g++ \
    gdb \
    libboost-dev \
    libeigen3-dev \
    libvulkan1 \
    libvulkan-dev \
    mesa-vulkan-drivers \
    nvidia-cuda-toolkit

RUN mkdir /opt/vcpkg && \
    git clone https://github.com/microsoft/vcpkg /opt/vcpkg && \
    /opt/vcpkg/bootstrap-vcpkg.sh && \
    ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg && \
    vcpkg install benchmark intel-mkl

RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.sh -O cmake.sh && \
    sh cmake.sh --prefix=/usr/local/ --exclude-subdir && \
    rm cmake.sh

RUN mkdir /src
