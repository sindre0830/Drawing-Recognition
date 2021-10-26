#include "Paintbrush.h"

#include <iostream>

/**
 *	Constructor.
 */
Paintbrush::Paintbrush() {
	
}

/**
 *	Deconstructor.
 */
Paintbrush::~Paintbrush() {
	while (!points.empty()) {
		auto it = points.begin();
		delete *it;
		points.erase(it);
	}
}

void Paintbrush::init() {
}


void Paintbrush::draw() {
}
