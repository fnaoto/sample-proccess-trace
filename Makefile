.PHONY: run

DCE := docker compose exec gcc
OBJ := $(notdir $(wildcard ./lib/*.c))

run: build
	@$(DCE) sudo ./main.o

build:
	@$(DCE) gcc -o main.o $(OBJ) 

up:
	@docker compose up -d
