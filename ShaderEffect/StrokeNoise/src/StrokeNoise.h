#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class StrokeNoise {
    
public:
    StrokeNoise();
    ~StrokeNoise();
    void begin();
    void end();
    void draw();
    void drawUI();
    
private:
    ofShader renderShader, noiseShader;
    ofFbo fbo, noiseFbo;
    
    ofParameter<int> numSample;
    ofParameter<int> numSteps;
    ofParameter<float> stepDist;
    ofParameter<float> influence;
    ofParameter<float> edge;
    ofParameter<float> power;
    ofParameter<float> noise;
    ofParameter<float> colorNoise;
    ofParameter<ofColor> paintColor;
    ofxPanel gui;
    ofParameterGroup pGroup;
};
