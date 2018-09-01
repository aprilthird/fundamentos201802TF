#include <cstddef>

#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite()
{
	vboID = 0;
}

void Sprite::init(float _x, float _y, int _width, int _height) {
	x = _x;
	y = _y;
	height = _height;
	witdh = _width;

	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	Vertex vertexData[6];

	vertexData[0].setPosition(x + witdh, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + witdh, y);
	vertexData[5].setPosition(x + witdh, y + height);


	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)offsetof(Vertex, position)
	);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE,
		GL_TRUE,
		sizeof(Vertex),
		(void*)offsetof(Vertex, colorRGBA)
	);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Sprite::~Sprite()
{

	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}
