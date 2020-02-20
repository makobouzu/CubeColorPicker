#include "ofApp.h"

const std::vector<VertexColorPair> mesh2VertexColorPair(const ofMesh& mesh){
    std::vector<VertexColorPair> ret;
    for(auto i = 0; i < mesh.getVertices().size(); ++i){
        ret.push_back(std::make_pair(mesh.getVertex(i), mesh.getColor(i)));
    }
    return ret;
}
//std::vector<VertexColorPair> vertex = mesh2VertexColorPair(mesh);

//width 400, height 500, depth 400
std::vector<VertexColorPair> vertex{
    { glm::vec3{100, 500,    0.0}, ofColor{232,  52,  34} },
    { glm::vec3{500, 500,    0.0}, ofColor{148, 255,  46} },
    { glm::vec3{100,  0,    0.0}, ofColor{  0, 208,  69} },
    { glm::vec3{500,  0,    0.0}, ofColor{  0, 250, 255} },
    { glm::vec3{100, 500, -400.0}, ofColor{ 56,   0, 231} },
    { glm::vec3{500, 500, -400.0}, ofColor{212,   0, 255} },
    { glm::vec3{100,  0, -400.0}, ofColor{255,   0, 175} },
    { glm::vec3{500,  0, -400.0}, ofColor{231,   0,  13} }
};


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    emphasisPosition = calculation::emphasisPos(vertex);
    cam.lookAt(emphasisPosition);
    
    //guide
    for(auto i = 100; i <= 500; i += 10){
        for(auto j = 0; j <= 500; j += 10){
            for(auto k = 0; k  >= -400; k -= 10){
                glm::vec3 pos = {i, j, k};
                ofColor color = colorPick::pos2color(pos, vertex);
                vboMesh.addVertex(pos);
                vboMesh.addColor(color);
            }
        }
    }
    
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
    ofDrawBox(emphasisPosition, 400, 500, 400);
    ofPopStyle();
    vboMesh.draw(OF_MESH_POINTS);
    for(auto i = 0; i < vertex.size(); ++i){
        ofSetColor(vertex.at(i).second);
        ofDrawSphere(vertex.at(i).first, 10);
    }
    

    ofColor targetCol = colorPick::pos2color(target, vertex);
    ofSetColor(targetCol);
    ofDrawSphere(target, 10);
    
    cam.end();
    
    //picked color
    ofSetColor(targetCol);
    ofDrawRectangle(10, 10, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a') target.x += 10;
    if(key == 's') target.x -= 10;
    if(key == 'd') target.y += 10;
    if(key == 'f') target.y -= 10;
    if(key == 'g') target.z += 10;
    if(key == 'h') target.z -= 10;
    
    if(key == ' '){
        ofColor color = colorPick::pos2color(target, vertex);
        cout << color << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
