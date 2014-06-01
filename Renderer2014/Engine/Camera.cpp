#include "Camera.h"

//----------------------------------------------------------------------------

Camera::Camera(void) : needsUpdate(true)
{
	// zAxis should be (0, 0, -1)
	eye = vec3(0, 0, 5);
	lookAt = vec3(0, 0, 4);
	CalculateViewMatrix();
}

//----------------------------------------------------------------------------


Camera::~Camera(void)
{
}

//----------------------------------------------------------------------------

mat4 Camera::GetViewMatrix(void)
{
	//return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -5.f));
	return viewMatrix;
}

//----------------------------------------------------------------------------

void Camera::CalculateViewMatrix(void)
{
	/*
	OpenGL uses Right-Handed World Space Coordinates, and the NDC space will be Left-Handed.
	Right-Handed means that things farther down Z will be a LOWER value, so the zAxis should be (0, 0, -1).

	*/
	zAxis = Normalize(lookAt - eye);
	up = vec3(0, 1, 0);
	right = Cross(zAxis, up);//, zAxis);
	up = -Cross(zAxis, right); 

	viewMatrix = glm::lookAt(eye, eye + zAxis, up);
	/*
	viewMatrix = mat4( 	
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		zAxis.x, zAxis.y, zAxis.z, 0,
		-Dot(right, eye), -Dot(up, eye), -Dot(zAxis, eye), 1
	);
	*/
	needsUpdate = false;
}

//----------------------------------------------------------------------------

void Camera::Update(float dt)
{
	static float st = 0.f;
	st = dt;
	//this->Rotate(0, 0.01f, 0);
	//eye += vec3(0, 0.01, 0);
	//lookAt += vec3(0, 0.01, 0);
	//needsUpdate = true;

	if (needsUpdate)
	{
		CalculateViewMatrix();
	}
}

//----------------------------------------------------------------------------

void Camera::Rotate(float x, float y, float z)
{	
	// We want to move LookAt Point appropriately.

	// First update matrix if eye position or lookAt point have changed
	if (needsUpdate)
	{
		CalculateViewMatrix();
	}
	
	// Calculate rotation matrix for this rotation
	mat4 m = glm::mat4_cast(glm::quat(vec3(x, y, z)));
	Vec4 newZ = m * Vec4(zAxis.x, zAxis.y, zAxis.z, 0.0f);
	zAxis = Vec3(newZ.x, newZ.y, newZ.z) ;
	lookAt = eye + zAxis;
	right = Cross(zAxis, up);

	needsUpdate = true;
}

//----------------------------------------------------------------------------

void Camera::TranslateLocal(float x, float y, float z) 
{
	// Assumes that zAxis is updated.
	// Need to keep zAxis updated.

	eye += zAxis * x;
	lookAt += zAxis * x;

	eye += right * z;
	lookAt += right * z;

	needsUpdate = true;
	//CalculateViewMatrix();

}