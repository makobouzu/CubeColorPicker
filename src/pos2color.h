//
//  pos2color.h
//  ColorStudy_day5
//
//  Created by Makoto Amano on 2020/02/18.
//

#ifndef pos2color_h
#define pos2color_h
#include "calculation.h"

using VertexColorPair = std::pair<glm::vec3, ofColor>;
namespace colorPick {

inline ofColor pos2color(const glm::vec3& target, const std::vector<VertexColorPair>& vertex){
    glm::vec3 emphasisPosition = calculation::emphasisPos(vertex);
    ofColor emphasisColor = calculation::emphasisCol(vertex);
    
    //targetから近い4つの頂点
    std::vector<VertexColorPair> planeNeighbor = calculation::neighborVertex(target, vertex, 4);
    
    //平面と、重心とtargetを結ぶ線の交点(平面でいうtargetにあたる)
    glm::vec3 interTarget = calculation::planeIntersection(target, planeNeighbor, emphasisPosition);
    
    //平面上の交点と近い2頂点を結んだ線分
    std::vector<VertexColorPair> lineNeighbor = calculation::neighborVertex(interTarget, planeNeighbor, 3);
    
    //平面の重心と色
    glm::vec3 lineEmphasisPosition = calculation::emphasisPos(planeNeighbor);
    ofColor lineEmphasisCol = calculation::emphasisCol(planeNeighbor);
    
    //lineと、重心とintertargetを結ぶ線の交点の色と位置
    glm::vec3 lineInterPos = calculation::lineIntersection(interTarget, lineEmphasisPosition, lineNeighbor.at(0).first, lineNeighbor.at(1).first);
    if(!calculation::detail::dividingPoint(interTarget, lineNeighbor.at(0).first, lineNeighbor.at(1).first)){
        lineInterPos = calculation::lineIntersection(interTarget, lineEmphasisPosition, lineNeighbor.at(0).first, lineNeighbor.at(2).first);
    }
    ofColor   lineInterCol = calculation::intersectionColor(lineInterPos, planeNeighbor, lineNeighbor);
    
    ofColor intertargetCol = calculation::targetColor(interTarget, lineInterPos, lineInterCol, lineEmphasisPosition, lineEmphasisCol);
    
    ofColor targetCol      = calculation::targetColor(target, interTarget, intertargetCol, emphasisPosition, emphasisColor);
    
//    ofSetColor(0, 255, 0);
//    ofDrawLine(planeNeighbor.at(0).first, planeNeighbor.at(1).first);
//    ofDrawLine(planeNeighbor.at(1).first, planeNeighbor.at(2).first);
//    ofDrawLine(planeNeighbor.at(2).first, planeNeighbor.at(3).first);
//    ofDrawLine(planeNeighbor.at(3).first, planeNeighbor.at(0).first);
//    ofSetColor(255, 0, 0);
//    ofDrawLine(lineNeighbor.at(0).first, lineNeighbor.at(1).first);
//    ofDrawLine(lineNeighbor.at(1).first, lineNeighbor.at(0).first);
//    ofSetColor(lineEmphasisCol);
//    ofDrawSphere(lineEmphasisPosition, 10);
//    ofSetColor(lineInterCol);
//    ofDrawSphere(lineInterPos, 10);
//    ofSetColor(intertargetCol);
//    ofDrawSphere(interTarget, 10);
    
    return targetCol;
}

}// pos2color

#endif /* pos2color_h */
