cmake_minimum_required(VERSION 4.1)
project(Progetto C)

set(CMAKE_C_STANDARD 99)

add_executable(Progetto main.c
        Funzioni.c
        Monopoly.h
        Monopoly.c
        Main.c
)
