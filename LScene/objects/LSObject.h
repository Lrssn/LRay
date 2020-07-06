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


private:
	vec3 pos;
};