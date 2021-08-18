#!/bin/sh

docker context use default
docker stop (docker ps -a -q)
docker rm (docker ps -a -q)

docker run -it --name ex1A.1 game ./ex1A.sh > output.ex1A.1.txt
docker run -it --name ex1A.2 game ./ex1A.sh > output.ex1A.2.txt
docker run -it --name ex1B.1 game ./ex1B.sh > output.ex1B.1.txt
docker run -it --name ex1B.2 game ./ex1B.sh > output.ex1B.2.txt
docker run -it --name ex2.1 game ./ex2.sh > output.ex2.1.txt
docker run -it --name ex2.2 game ./ex2.sh > output.ex2.2.txt
docker run -it --name ex3.1 game ./ex3.sh > output.ex3.1.txt

docker context use bntu
docker stop (docker ps -a -q)
docker rm (docker ps -a -q)

docker run -it --name ex3.2 game ./ex3.sh > output.ex3.2.txt
docker run -it --name ex4.1 game ./ex4.sh > output.ex4.1.txt
docker run -it --name ex4.2 game ./ex4.sh > output.ex4.2.txt