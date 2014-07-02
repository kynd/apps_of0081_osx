#pragma once

#include "ofMain.h"


class Snake {
    
public:
    Snake(float l = 200, float w = 50, int _dl = 40, int _dw = 10);
    ~Snake();
    void update(float x, float y);
    void draw();
    
private:
    ofShader shader;
    ofVec3f headPos;
    vector<ofVec3f> points;
    ofMesh mesh;
    ofMesh head;
    float length, width;
    int dl, dw;
};
