.PHONY: run

DCE := docker compose exec gcc

run: build
	@${DCE} ./main.o

build:
	@${DCE} gcc -o main.o main.c 
