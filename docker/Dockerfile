FROM debian:stretch
LABEL maintainer="Adventurecoin Developers <dev@advc.org>"
LABEL description="Dockerised AdventurecoinCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
