#pragma once

#include "stdafx.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

	mat4 GetViewMatrix();
	
	// Called Per Frame
	void Update(float dt);
		
	void Translate(vec3 offset) { eye += offset; needsUpdate = true; }
	void Translate(float x, float y, float z) { eye += vec3(x, y, z); needsUpdate = true; }
	
	void TranslateLocal(float x, float y, float z) ;
	void TranslateTo(vec3 position) { eye = position; needsUpdate = true; }
	void TranslateTo(float x, float y, float z) { eye = vec3(x, y, z); needsUpdate = true; }

	// Eulers
	void Rotate(float x, float y, float z);
	
	void LookAt(vec3 position) { lookAt = position; needsUpdate = true; }


private:
	//quat rot;	
	mat4 viewMatrix;

	vec3 eye;
	vec3 lookAt;

	vec3 right;
	vec3 up;
	vec3 zAxis;

	bool needsUpdate;

	// Builds the Matrix
	void CalculateViewMatrix(void);
	

};

