#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;

	void set(float _x, float _y) {
		x = _x;
		y = _y;
	}
};

struct ColorRGBA
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	void set(GLubyte _r,GLubyte _g,
			 GLubyte _a,GLubyte _b) 
	{
		r = _r;
		g = _g;
		a = _a;
		b = _b;
	}
};

struct UV {
	float u;
	float v;
	void set(float _u, float _v) {
		u = _u;
		v = _u;
	}

};

struct Vertex
{
	Position position;
	ColorRGBA colorRGBA;
	UV uv;

	void setUV(float u,float v) {
		uv.set(u, v);
	}

	void setPosition(float x, float y) {
		position.set(x, y);
	}

	void setColorRGBA(GLubyte _r, GLubyte _g,
		GLubyte _a, GLubyte _b) {
		colorRGBA.set(_r, _g, _b, _a);
	}
};