#include "Snake.h"


Snake::Snake(float l, float w, int _dl, int _dw) {
    length = l;
    width = w;
    dl = _dl;
    dw = _dw;
    shader.load("shaders/phong/shader.vert", "shaders/phong/shader.frag");
    
    // center points
    for (int i = 0; i < dl; i ++) {
        points.push_back(ofVec3f(i * 30, 0,0));
    }
    
    // ball
    head = ofMesh::sphere(w);
    
    // tube
    for (int i = 0; i < dl; i ++) {
        for (int j = 0; j < dw; j ++) {
            int p0 = (i - 1) * dw + j - 1;
            int p1 = (i - 1) * dw + j - 0;
            int p2 = (i - 1) * dw + j + 1;
            int p3 = i * dw + j - 1;
            int p4 = i * dw + j - 0;
            int p5 = i * dw + j + 1;
            
            mesh.addVertex(ofVec3f());
            mesh.addNormal(ofVec3f());
            if (i > 0) {
                if (j < dw - 1) {
                    mesh.addIndex(p4);
                    mesh.addIndex(p2);
                    mesh.addIndex(p1);
                }
                if (j > 0) {
                    mesh.addIndex(p4);
                    mesh.addIndex(p1);
                    mesh.addIndex(p3);
                }
                if (j == dw -1) {
                    mesh.addIndex(p4);
                    mesh.addIndex((i - 1) * dw);
                    mesh.addIndex(p1);
                    mesh.addIndex(i * dw);
                    mesh.addIndex((i - 1) * dw);
                    mesh.addIndex(p4);
                }
            }
        }
    }
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

Snake::~Snake() {}
void Snake::update(float x, float y) {
    x -= ofGetWidth() / 2;
    y -= ofGetHeight() / 2;
    x *= -1;
    float dist = headPos.distance(ofVec3f(x,y,0));
    headPos.x += (x - headPos.x) / 2;
    headPos.y += (y - headPos.y) / 2;
    headPos *= 0.99;
    
    //center points
    points[0] += (headPos - points[0]) * 0.4;
    for (int i = 1; i < dl; i ++) {
        points[i] += (points[i - 1] - points[i]) * 0.5;
    }
    
    // tube
    for (int i = 0; i < dl; i ++) {
        ofVec3f direc = ((i == 0) ? points[i] - points [i + 1] : points[i - 1] - points[i]).normalize();
        ofVec3f rad = direc.getCrossed(ofVec3f(0,0,1));
        float dist = (i == 0) ? points[i].distance(points [i + 1]) : points[i].distance(points[i - 1] - points[i]);
        float ratio = pow(abs((float) i / (dl - 1) - 0.5) + 0.5, 3.5);
        for (int j = 0; j < dw; j ++) {
            mesh.getVertices()[i * dw + j].set(points[i] + rad * width * ratio);
            mesh.getNormals()[i * dw + j].set(rad);
            rad.rotate(360.f / dw, direc);
        }
    }
    
}

void Snake::draw() {
    ofClear(0,0,255);
    glEnable(GL_DEPTH_TEST);
    
    shader.begin();
    shader.setUniform3f("lightDir", 1,1,1);
    shader.setUniform3f("ambientColor", 0.5, 0.5, 0.5);
    shader.setUniform4f("diffuseColor", 1,1,1,1);
    shader.setUniform4f("specularColor", 1,1,1,1);
    
    mesh.draw();
    
    ofPushMatrix();
    ofTranslate(points[0]);head.draw();
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(points[points.size() - 1]);head.draw();
    ofPopMatrix();
    
    shader.end();
    glDisable(GL_DEPTH_TEST);
    
}