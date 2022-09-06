#pragma once

#include <iostream>
#include <vector>

using namespace std;

//classes for control of objects written in canvas, storage for each object info, use same vector structure on main

class coordinate {
	public:
		float x, y;
};

class Figure {
	public:
		int n_sides = 0;
		Figure(int n) {
			n_sides = n;
		}
};

class Rect : public Figure {
	public:
		vector<coordinate> v_coor;
};

class Trian : public Figure {
public:
	vector<coordinate> v_coor;
};

class Hexag : public Figure {
public:
	vector<coordinate> v_coor;
};