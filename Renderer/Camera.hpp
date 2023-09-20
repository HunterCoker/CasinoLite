#pragma once

#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
	explicit Camera(float fovy = 45.0f, float znear = 0.01f, float zfar = 100.0f);
	Camera(const Camera&) = delete;
	~Camera() = default;

	enum class Direction {
		FORWARD = 0,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

    void update(float dt);

	[[nodiscard]] glm::mat4 getProjectionView() const { return projection_ * view_; }

    void move(Direction direction, float speed);
    void trackMouse(double xpos, double ypos);
	void mouseCallback(GLFWwindow* window, double x, double y);
private:
	glm::mat4 view_{}, projection_{};
	glm::vec3 position_{}, forward_{}, up_{};
	float fovy_, znear_, zfar_;
	double sensitivity_, yaw_, pitch_;
};