FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        gcc \
        gdb \
        valgrind \
        make \
        vim \
        git \
        libcriterion-dev \
        libreadline-dev \
        libx11-dev \
        libxext-dev \
        libxrender-dev \
        libxrandr-dev \
        libxft-dev \
        libbsd-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app
