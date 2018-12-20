cmake_minimum_required(VERSION 2.8.9)
project(mqtt-gateway)

#Add Sources
file(GLOB SOURCES "./*.c")

add_library(lowLayer SHARED ${SOURCES})
