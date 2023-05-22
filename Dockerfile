FROM ubuntu:18.04
LABEL Description="C++ build environment"

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    g++ \
    cmake \
    gdb \
    wget
