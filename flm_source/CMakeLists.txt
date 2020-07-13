cmake_minimum_required(VERSION 3.12)
project(Feistel-Lai-Massey LANGUAGES CXX)
include(sources.cmake)
add_executable(flm ${SOURCES})