#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>

Camera::Camera(float fovy, float znear, float zfar)
	:fovy_(fovy), znear_(znear), zfar_(zfar),
	 yaw_(-90.0f), pitch_(0.0f), sensitivity_(0.1f) {

	int width, height;
	GLFWwindow* window = glfwGetCurrentContext();
	glfwGetFramebufferSize(window, &width, &height);
	float aspect = static_cast<float>(width) / height;
	projection_ = glm::perspective(fovy_, aspect, znear_, zfar_);

	position_ = glm::vec3(0.0f, 0.0f, 3.0f);
	forward_ = glm::vec3(0.0f, 0.0f, -1.0f);
	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	view_ = glm::lookAt(position_, position_ + forward_, up_);
}

void Camera::update(float dt) {
    auto window = glfwGetCurrentContext();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    trackMouse(xpos, ypos);

    float speed = 1.0f * (dt * 1.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        move(Direction::FORWARD, speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        move(Direction::LEFT, speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        move(Direction::BACKWARD, speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        move(Direction::RIGHT, speed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        move(Direction::UP, speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        move(Direction::DOWN, speed);
}

void Camera::move(Direction direction, float speed) {
	if (direction == Direction::FORWARD) {
		position_ += forward_ * speed;
	}
	if (direction == Direction::BACKWARD) {
		position_ -= forward_ * speed;
	}
	if (direction == Direction::LEFT) {
		position_ -= glm::normalize(glm::cross(forward_, up_)) * speed;
	}
	if (direction == Direction::RIGHT) {
		position_ += glm::normalize(glm::cross(forward_, up_)) * speed;
	}
	if (direction == Direction::UP) {
		position_ += up_ * speed;
	}
	if (direction == Direction::DOWN) {
		position_ -= up_ * speed;
	}
	view_ = glm::lookAt(position_, position_ + forward_, up_);
}

void Camera::trackMouse(double xpos, double ypos) {
	static double last_xpos = 0;
	static double last_ypos = 0;
	static bool cursor_enabled = true;

	auto window = glfwGetCurrentContext();
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (cursor_enabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cursor_enabled = false;
		}

		double x_offset = xpos - last_xpos;
		double y_offset = last_ypos - ypos;

		x_offset *= sensitivity_;
		y_offset *= sensitivity_;

		yaw_ += x_offset;
		pitch_ += y_offset;

		pitch_ = pitch_ >  89.0f ?  89.0f : pitch_;
		pitch_ = pitch_ < -89.0f ? -89.0f : pitch_;

		forward_ = glm::vec3(
			glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_)),
			glm::sin(glm::radians(pitch_)),
			glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_))
		);
		forward_ = glm::normalize(forward_);

	}
	else {
		if (!cursor_enabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursor_enabled = true;
		}
	}
	last_xpos = xpos;
	last_ypos = ypos;
	view_ = glm::lookAt(position_, position_ + forward_, up_);
}

void Camera::mouseCallback(GLFWwindow* window, double x, double y) {

}