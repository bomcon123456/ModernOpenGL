#ifndef CAMERA_H
#define CAMERA_H

#include "Core.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera
{
  public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float moveSpeed, float turnSpeed);
	~Camera();

	void KeyControl(bool *keys, float deltaTime);
	void MouseControl(float xChange, float yChange);

	glm::vec3 GetCameraPosition();

	glm::mat4 CalculateViewMatrix();

  private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_movementSpeed;
	float m_turnSpeed;

	void Update();
};

#endif