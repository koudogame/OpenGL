#pragma once
class Camera
{
private:
	Camera();
	Camera(const Camera&) = delete;
	Camera& operator= (const Camera&) = delete;
public:
	inline static Camera* Get() { static Camera instance; return &instance; }
public:
	~Camera();

public:
	inline const glm::mat4& getProjection() {return projection_;}
	inline const glm::mat4& getView() { return view_; }
	void setView(const glm::vec3& Eye, const glm::vec3& target, glm::vec3 up);
	void setProjection(float ViewRadian, float Aspect, float Near, float Far);
	void editViewEye(const glm::vec3& Eye);
	void editViewTarget(const glm::vec3& Target);
	void editViewUp(const glm::vec3& Up);

private:
	glm::mat4 view_;
	glm::vec3 eye_, target_, up_;
	glm::mat4 projection_;
};
