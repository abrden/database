FROM ubuntu:14.04

RUN apt-get update -qq
RUN apt-get install -y \
    build-essential \
    wget \
    valgrind
RUN wget https://cmake.org/files/v3.5/cmake-3.5.1-Linux-x86_64.sh
RUN sh cmake-3.5.1-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir
RUN mkdir /app
COPY . /app
WORKDIR /app
RUN chmod a+x build.sh
RUN chmod a+x run.sh
RUN sh build.sh
CMD ["./run.sh"]