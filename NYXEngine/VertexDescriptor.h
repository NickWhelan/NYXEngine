#pragma once
#include "pch.h"

class VertexDescriptor {
public:
	VertexDescriptor();
	~VertexDescriptor();

	void storeData(float _vertPos, float _color, float _XYZnorm, float _UVCoord);
	void storeDataAndExtra(float _vertPos, float _Color, float _XYZnorm, float _UVCoord, float _ExtraData);
	void retrieveData();
	
private:
	float vertexData[];

};