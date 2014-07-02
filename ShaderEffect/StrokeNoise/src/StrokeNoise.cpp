
#include "StrokeNoise.h"

StrokeNoise::StrokeNoise() {
    fbo.allocate(ofGetWidth(), ofGetHeight());
    noiseFbo.allocate(ofGetWidth(), ofGetHeight());
    noiseShader.load("shaders/strokeNoise/shader.vert", "shaders/strokeNoise/noise.frag");
    renderShader.load("shaders/strokeNoise/shader.vert", "shaders/strokeNoise/render.frag");
    
    // set up gui
    pGroup.add(numSample.set("numSamples", 6, 1, 20));
    pGroup.add(numSteps.set("numSteps", 7, 1, 50));
    pGroup.add(stepDist.set("stepDist", 2.5, 0.1, 6.0));
    pGroup.add(influence.set("influence", 0.9, 0.0, 1.0));
    pGroup.add(edge.set("edge", 0.8, 0.0, 1.0));
    pGroup.add(power.set("power", 4.0, 0.0, 10.0));
    pGroup.add(noise.set("noise", 2.0, -2.0, 2.0));
    pGroup.add(colorNoise.set("colorNoise", 0.0, 0, 1.0));
    pGroup.add(paintColor.set("paintColor", ofColor(0.25 * 255, 0.25 * 255, 0.25 * 255, 1.0 * 255), ofColor(0.0), ofColor(255.0)));
    gui.setup(pGroup);
}

StrokeNoise::~StrokeNoise() {
    
}

void StrokeNoise::begin() {
    
    // update force field
    noiseFbo.begin();
    noiseShader.begin();
    noiseShader.setUniform1f("time", (float) ofGetFrameNum());
    fbo.draw(0, 0);
    noiseFbo.end();
    
    // begin fbo
    fbo.begin();
    ofClear(0,0,255,255);
}

void StrokeNoise::end() {
    // end fbo
    fbo.end();
}

void StrokeNoise::draw() {
    // apply effect to the captured graphics
    renderShader.begin();
    renderShader.setUniform1i("numSample", numSample);
    renderShader.setUniform1i("numSteps", numSteps);
    renderShader.setUniform1f("stepDist", stepDist);
    renderShader.setUniform1f("influence", influence);
    renderShader.setUniform1f("edge", edge);
    renderShader.setUniform1f("power", power);
    renderShader.setUniform1f("noiseLev", noise);
    renderShader.setUniform1f("colorNoise", colorNoise);
    renderShader.setUniform4f("paintColor", (float) paintColor->r / 255, (float) paintColor->g / 255, (float) paintColor->b / 255, 1.0);
    
    renderShader.setUniformTexture("noise", noiseFbo, 1);
    fbo.draw(0,0);
    renderShader.end();
}


void StrokeNoise::drawUI() {
    gui.draw();
}
