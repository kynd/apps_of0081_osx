#pragma once

#include "ofMain.h"

class GraphicsPostProcessor {
    
public:
    GraphicsPostProcessor(int w = 0, int h = 0);
    virtual ~GraphicsPostProcessor();
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void draw() = 0;
};
