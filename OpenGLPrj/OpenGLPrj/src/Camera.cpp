#include "Camera.h"

Camera::Camera() :
	m_position(glm::vec3(0)), m_worldUp(glm::vec3(0)), m_yaw(0), m_pitch(0), m_movementSpeed(0), m_turnSpeed(0)
{
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float moveSpeed, float turnSpeed) :
	m_position(pos), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_movementSpeed(moveSpeed), m_turnSpeed(turnSpeed)
{
	m_front = glm::vec3(0.f, 0.f, -1.f);

	Update();
}

Camera::~Camera()
{
}

void Camera::KeyControl(bool *keys, float deltaTime)
{

	float speed = m_movementSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		m_position += m_front * speed;
		std::cout << m_position.x << " " << m_position.y << " "<< m_position.z << std::endl;
	}
	if (keys[GLFW_KEY_S])
	{
		m_position -= m_front * speed;
	}
	if (keys[GLFW_KEY_D])
	{
		m_position += m_right * speed;
	}
	if (keys[GLFW_KEY_A])
	{
		m_position -= m_right * speed;
	}
	if (keys[GLFW_KEY_E])
	{
		m_position += m_worldUp * speed;
	}
	if (keys[GLFW_KEY_Q])
	{
		m_position -= m_worldUp * speed;
	}
}

void Camera::MouseControl(float xChange, float yChange)
{
	xChange *= m_turnSpeed;
	yChange *= m_turnSpeed;

	m_yaw += xChange;
	m_pitch += yChange;
	if (m_pitch > 89.f)
	{
		m_pitch = 89.f;
	}
	else if (m_pitch < -89.f)
	{
		m_pitch = -89.f;
	}

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::vec3 Camera::GetCameraPosition()
{
	return m_position;
}

glm::vec3 Camera::GetCameraDirection()
{
	return glm::normalize(m_front);
}

void Camera::Update()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

