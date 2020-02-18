#include "ofApp.h"

const std::vector<VertexColorPair> meshToVertexColorPair(const ofMesh& mesh){
    std::vector<VertexColorPair> ret;
    for(auto i = 0; i < mesh.getVertices().size(); ++i){
        ret.push_back(std::make_pair(mesh.getVertex(i), mesh.getColor(i)));
    }
    return ret;
}

std::vector<VertexColorPair> vertex{
    { glm::vec3{100, 500,    0.0}, ofColor{232,  52,  34} },
    { glm::vec3{500, 500,    0.0}, ofColor{148, 255,  46} },
    { glm::vec3{100, 100,    0.0}, ofColor{  0, 208,  69} },
    { glm::vec3{500, 100,    0.0}, ofColor{  0, 250, 255} },
    { glm::vec3{100, 500, -400.0}, ofColor{ 56,   0, 231} },
    { glm::vec3{500, 500, -400.0}, ofColor{212,   0, 255} },
    { glm::vec3{100, 100, -400.0}, ofColor{255,   0, 175} },
    { glm::vec3{500, 100, -400.0}, ofColor{231,   0,  13} }
};


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    emphasisPosition = calculation::emphasisPos(vertex);
    cam.lookAt(emphasisPosition);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    ofSetColor(255);
    ofPushStyle();
    ofNoFill();
    ofDrawBox(emphasisPosition, 400);
    ofPopStyle();
    for(auto i = 0; i < vertex.size(); ++i){
        ofSetColor(vertex.at(i).second);
        ofDrawSphere(vertex.at(i).first, 10);
    }

    ofColor targetCol = amako::pos2color(target, vertex);
    ofSetColor(targetCol);
    ofDrawSphere(target, 13);
    
    cam.end();
    
    ofSetColor(targetCol);
    ofDrawRectangle(10, 10, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a'){
        target.x += 10;
    }
    if(key == 's'){
        target.x -= 10;
    }
    if(key == 'd'){
        target.y += 10;
    }
    if(key == 'f'){
        target.y -= 10;
    }
    if(key == 'g'){
        target.z += 10;
    }
    if(key == 'h'){
        target.z -= 10;
    }
    
    if(key == ' '){
        ofColor color = amako::pos2color(glm::vec3{100, 100, 100}, vertex);
        cout << color << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
