#include "Points.h"

#include <iostream>

/**
 *	Constructor.
 */
Points::Points() {
	
}

/**
 *	Deconstructor.
 */
Points::~Points() {
	while (!points.empty()) {
		auto it = points.begin();
		delete *it;
		points.erase(it);
	}
}

void Points::init() {
}


void Points::draw() {
}
