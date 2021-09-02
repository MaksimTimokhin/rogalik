FROM ubuntu:21.04

COPY docker/install_deps.sh /

RUN sh install_deps.sh

ENV CXX="/usr/bin/clang++-12"
ENV CC="/usr/bin/clang-12"

ADD . /rogalik

WORKDIR /rogalik/build

RUN cmake .. && cmake --build .

# RUN useradd -ms /bin/bash xterm
# USER xterm
# ENTRYPOINT ["xterm", "-e", "bin/rogue"]
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENTRYPOINT bin/rogue