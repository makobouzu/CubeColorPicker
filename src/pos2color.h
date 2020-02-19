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
namespace amako {

inline ofColor pos2color(const glm::vec3& target, const std::vector<VertexColorPair>& vertex){
    glm::vec3 emphasisPosition = calculation::emphasisPos(vertex);
    ofColor emphasisColor = calculation::emphasisCol(vertex);
    
    //targetから近い4つの頂点
    std::vector<VertexColorPair> planeNeighbor = calculation::neighborVertex(target, vertex, 4);
    
    //平面と、重心とtargetを結ぶ線の交点(平面でいうtargetにあたる)
    glm::vec3 interTarget = calculation::planeIntersection(target, planeNeighbor, emphasisPosition);
    
    //平面上の交点と近い2頂点を結んだ線分
    std::vector<VertexColorPair> lineNeighbor = calculation::neighborVertex(interTarget, planeNeighbor, 2);
    
    //平面の重心と色
    glm::vec3 lineEmphasisPosition = calculation::emphasisPos(planeNeighbor);
    ofColor lineEmphasisCol = calculation::emphasisCol(planeNeighbor);
    
    //lineと、重心とintertargetを結ぶ線の交点の色と位置
    glm::vec3 lineInterPos = calculation::lineIntersection(interTarget, lineNeighbor, lineEmphasisPosition);
    ofColor   lineInterCol = calculation::intersectionColor(lineInterPos, planeNeighbor, lineNeighbor);
    
    ofColor intertargetCol = calculation::targetColor(interTarget, lineInterPos, lineInterCol, lineEmphasisPosition, lineEmphasisCol);
    
    ofColor targetCol      = calculation::targetColor(target, interTarget, intertargetCol, emphasisPosition, emphasisColor);
    
    return targetCol;
}

}// pos2color

#endif /* pos2color_h */
