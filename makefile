all: proj4.x

proj4.x: proj4_driver.cpp BET.h BET.hpp
	g++ -std=c++11 proj4_driver.cpp -o proj4.x

