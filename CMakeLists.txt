project(LogicGate LANGUAGES CXX)
cmake_minimum_required(VERSION 3.12)

add_executable(StaticEdition main1.cpp LogicGate.cpp)

add_executable(DynamicEdition main.cpp LogicGateDynamic.cpp)

add_executable(OperatorsEdition main1op.cpp LogicGateOperators.cpp)