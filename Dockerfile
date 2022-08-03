FROM digicatapult/morello-sdk:latest

USER cheri
WORKDIR /home/cheri/morello-examples
COPY --chown=cheri:cheri . /home/cheri/morello-examples/

ENV MORELLO_SDK=/home/cheri/morello-sdk
CMD ["make", "all"]
