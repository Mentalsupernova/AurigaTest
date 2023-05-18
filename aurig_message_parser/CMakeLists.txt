cmake_minimum_required(VERSION 3.25)
project(aurig_message_parser C)

set(CMAKE_C_STANDARD 23)

add_executable(aurig_message_parser main.c utils.c utils.h Message.c Message.h)
