#include "Camera2D.h"


Camera2D::Camera2D() :
	position(0, 0),
	cameraMatrix(1.0f),
	scale(1.0f),
	updateCameraMatrix(true),
	orthoMatrix(1.0f),
	screenWidth(500), screenHeight(500)
{

}

void Camera2D::init(int screenWidth, int screenHeight) {
	screenWidth = screenWidth;
	screenHeight = screenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}

void Camera2D::update() {
	if (updateCameraMatrix) {
		/*glm::vec3 translate(-_position.x, -_position.y, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(_cameraMatrix,scale);
		*/

		glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);

		glm::vec3 scale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;

		updateCameraMatrix = false;
	}
}

Camera2D::~Camera2D()
{
}