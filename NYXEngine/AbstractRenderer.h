#pragma once
#include "OpenGL\include\glew.h"
#include "pch.h"

class AbstractRenderer {
public:
	AbstractRenderer() {}
	virtual ~AbstractRenderer() {}

	enum PRIMITIVETYPE {
		NONE,
		POINT,
		TRIANGLE,
		RECT
	};

	virtual void renderPrimitive(PRIMITIVETYPE prim) = 0;
};