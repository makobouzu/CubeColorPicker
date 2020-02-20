#pragma once

#include "ofMain.h"
#include "calculation.h"
#include "pos2color.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
private:
    glm::vec3 emphasisPosition;
    glm::vec3 target = {250, 300, -100};
    ofVboMesh vboMesh;
    ofEasyCam cam;
};
