#pragma once
struct vec3 {
	float x; 
	float y; 
	float z;
};
enum OBJECTTYPE {
	IMPLICIT_OBJECT, MESH_OBJECT
};

class LSObject {
public:
	LSObject();
	~LSObject();

	void setPos(vec3 _pos);
	vec3 getPos();

private:
	vec3 mPos;
};