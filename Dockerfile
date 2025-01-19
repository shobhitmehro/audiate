FROM ubuntu:latest

WORKDIR /usr/src/app

RUN apt-get update && \
    apt-get install -y build-essential valgrind

COPY . .

CMD ["bash"]
