//
//  calculation.h
//  ColorStudy_day5
//
//  Created by Makoto Amano on 2020/02/17.
//

#ifndef calculation_h
#define calculation_h

using VertexColorPair = std::pair<glm::vec3, ofColor>;

namespace calculation {
namespace detail {
inline bool comparePair(const std::pair<glm::vec3, float>& a, const std::pair<glm::vec3, float>& b) {
    if(a.second != b.second){
        return a.second < b.second;
    }
}

inline ofColor findColor(const std::vector<VertexColorPair>& vertex, const glm::vec3& pos){
    ofColor color;
    auto findPos = std::find_if(vertex.begin(), vertex.end(), [&pos](const VertexColorPair& element){ return element.first == pos;});
    color = (*findPos).second;
    return color;
}

inline glm::vec3 vectorMinus(const glm::vec3& v1, const glm::vec3& v2){
    glm::vec3 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}



}

//--------------------------------------------------------------

inline glm::vec3 emphasisPos(const std::vector<VertexColorPair>& vertex){
    glm::vec3 sum, emphasis;
    for(auto&& v: vertex){
        sum += v.first;
    }
    emphasis = sum / vertex.size();
    return emphasis;
}

inline ofColor emphasisCol(const std::vector<VertexColorPair>& vertex){
    float sumR, sumG, sumB;
    for(auto&& v: vertex){
        sumR += v.second.r;
        sumG += v.second.g;
        sumB += v.second.b;
    }
    sumR = int(sumR / vertex.size());
    sumG = int(sumG / vertex.size());
    sumB = int(sumB / vertex.size());
    ofColor emphasis = {sumR, sumG, sumB};
    return emphasis;
}

//find nearest num vertex
inline std::vector<VertexColorPair> neighborVertex(const glm::vec3& target, const std::vector<VertexColorPair>& vertex, int num){
    std::vector<std::pair<glm::vec3, float>> vertexDistance;
    for(auto i = 0; i < vertex.size(); ++i){
        float tar2pos = sqrt(pow(target.x - vertex.at(i).first.x, 2.0) + pow(target.y - vertex.at(i).first.y, 2.0) + pow(target.z - vertex.at(i).first.z, 2.0));
        vertexDistance.push_back(std::make_pair(vertex.at(i).first, tar2pos));
    }
    
    std::stable_sort(vertexDistance.begin(), vertexDistance.end(), detail::comparePair);
    int size = int(vertexDistance.size())- num;
    for(auto i = 0; i < size; ++i){
        vertexDistance.pop_back();
    }
    std::vector<glm::vec3> neighbor;
    for(auto&& v : vertexDistance){
        neighbor.push_back(v.first);
    }
    
    std::vector<VertexColorPair> neighborVertex;
    for(auto i = 0; i < neighbor.size(); ++i){
        neighborVertex.push_back(std::make_pair(neighbor.at(i), detail::findColor(vertex, neighbor.at(i))));
    }
    return neighborVertex;
}

//find 3D point plane and line(through emphasis & target)
inline glm::vec3 planeIntersection(const glm::vec3& target, const std::vector<VertexColorPair>& neighbor, const glm::vec3& emphasis){
    glm::vec3 pos0, pos1, pos2;
    pos0  = neighbor.at(0).first;
    pos1  = neighbor.at(1).first;
    pos2  = neighbor.at(2).first;
    
//  ax+by+cz+d=0 plane
    float a, b, c, d;
    a = (pos1.y - pos0.y)*(pos2.z - pos0.z)-(pos2.y - pos0.y)*(pos1.z - pos0.z);
    b = (pos1.z - pos0.z)*(pos2.x - pos0.x)-(pos2.z - pos0.z)*(pos1.x - pos0.x);
    c = (pos1.x - pos0.x)*(pos2.y - pos0.y)-(pos2.x - pos0.x)*(pos1.y - pos0.y);
    d = -1*(a*pos0.x + b*pos0.y + c*pos0.z);
    
//  line
    glm::vec3 v = detail::vectorMinus(emphasis, target);
    
    glm::vec3 intersection;
    intersection.x = ((b*v.y + c*v.z)*emphasis.x - v.x*(b*emphasis.y + c*emphasis.z + d)) / (a*v.x + b*v.y + c*v.z);
    intersection.y = ((c*v.z + a*v.x)*emphasis.y - v.y*(c*emphasis.z + a*emphasis.x + d)) / (a*v.x + b*v.y + c*v.z);
    intersection.z = ((a*v.x + b*v.y)*emphasis.z - v.z*(a*emphasis.x + b*emphasis.y + d)) / (a*v.x + b*v.y + c*v.z);
    
    return intersection;

}

//find 2D point line and line(through emphasis & target)
inline glm::vec3 lineIntersection(const glm::vec3& target, const std::vector<VertexColorPair>& neighbor, const glm::vec3& emphasis){
    glm::vec3 pos1, pos2;
    pos1  = neighbor.at(0).first;
    pos2  = neighbor.at(1).first;
    
    glm::vec3 intersection;
    if(target.z == pos1.z){
        //  y = ax + b or y = b
        float a, b;
        if(pos1.x != pos2.x){
            a = (pos2.y - pos1.y)/(pos2.x - pos1.x);
            b = -1*(pos2.y - pos1.y)/(pos2.x - pos1.x) * pos1.x + pos1.y;
        }else{
            a = pos2.y - pos1.y;
            b = -1*(pos2.y - pos1.y) * pos1.x + pos1.y;
        }
                
        //  y = cx + d
        float c, d;
        if(target.x != emphasis.x){
            c = (target.y - emphasis.y)/(target.x - emphasis.x);
            d = -1*(target.y - emphasis.y)/(target.x - emphasis.x) * emphasis.x + emphasis.y;
        }else{
            c = target.y - emphasis.y;
            d = -1*(target.y - emphasis.y) * emphasis.x + emphasis.y;
        }
            
        intersection.x = (d - b)/(a - c);
        intersection.y = (a*d - b*c)/(a - c);
        intersection.z = pos2.z;
    }else if(target.y == pos1.y){
        // x = az + b of x = b
        float a, b;
        if(pos1.z != pos2.z){
            a = (pos2.x - pos1.x)/(pos2.z - pos1.z);
            b = -1*(pos2.x - pos1.x)/(pos2.z - pos1.z) * pos1.z + pos1.x;
        }else{
            a = pos2.x - pos1.x;
            b = -1*(pos2.x - pos1.x) * pos1.z + pos1.x;
        }
                
        //  x = cz + d
        float c, d;
        if(target.z != emphasis.z){
            c = (target.x - emphasis.x)/(target.z - emphasis.z);
            d = -1*(target.x - emphasis.x)/(target.z - emphasis.z) * emphasis.z + emphasis.x;
        }else{
            c = target.x - emphasis.x;
            d = -1*(target.x - emphasis.x) * emphasis.z + emphasis.x;
        }
            
        intersection.x = (a*d - b*c)/(a - c);
        intersection.y = pos2.y;
        intersection.z = (d - b)/(a - c);
        
    }else if(target.x == pos1.x){
        // z = ay + b of z = b
        float a, b;
        if(pos1.y != pos2.y){
            a = (pos2.z - pos1.z)/(pos2.y - pos1.y);
            b = -1*(pos2.z - pos1.z)/(pos2.y - pos1.y) * pos1.y + pos1.z;
        }else{
            a = pos2.z - pos1.z;
            b = -1*(pos2.z - pos1.z) * pos1.y + pos1.z;
        }
                
        //  z = cy + d
        float c, d;
        if(target.y != emphasis.y){
            c = (target.z - emphasis.z)/(target.y - emphasis.y);
            d = -1*(target.z - emphasis.z)/(target.y - emphasis.y) * emphasis.y + emphasis.z;
        }else{
            c = target.z - emphasis.z;
            d = -1*(target.z - emphasis.z) * emphasis.y + emphasis.z;
        }
            
        intersection.x = pos2.x;
        intersection.y = (d - b)/(a - c);
        intersection.z = (a*d - b*c)/(a - c);
    }
    return intersection;
}

//find color  pos1-----intersection-----pos2
inline ofColor intersectionColor(const glm::vec3& intersection, const std::vector<VertexColorPair>& vertex, const std::vector<VertexColorPair>& neighborVertex){
    
    glm::vec3 pos1  = neighborVertex.at(0).first;
    glm::vec3 pos2  = neighborVertex.at(1).first;
    ofColor pos1Col = neighborVertex.at(0).second;
    ofColor pos2Col = neighborVertex.at(1).second;

    ofColor color;
    float disLine = sqrt(pow(pos2.x - pos1.x, 2.0) + pow(pos2.y - pos1.y, 2.0) + pow(pos2.z - pos1.z, 2.0));
    float pos1inter = sqrt(pow(pos1.x - intersection.x, 2.0) + pow(pos1.y - intersection.y, 2.0) + pow(pos1.z - intersection.z, 2.0));
    float ratio = pos1inter / disLine;

    if(ratio > 1){
        color = pos2Col;
    }else{
        color = pos1Col.getLerped(pos2Col, ratio);
    }
    return color;
}

//find color  intersection-----target-----point
inline ofColor targetColor(const glm::vec3& target, const glm::vec3& intersection, const ofColor& interCol, const glm::vec3& point, const ofColor& pointCol){
    
    ofColor color;
    float distance = sqrt(pow(intersection.x - point.x, 2.0) + pow(intersection.y - point.y, 2.0) + pow(intersection.z - point.z, 2.0));
    float point2target = sqrt(pow(point.x - target.x, 2.0) + pow(point.y - target.y, 2.0) + pow(point.z - target.z, 2.0));
    float ratio = point2target / distance;
    
    if(target == point){
        return pointCol;
    }else{
        if(ratio > 1){
            color = interCol;
        }else{
            color = pointCol.getLerped(interCol, ratio);
        }
        return color;
    }
}

}//namespace calculation

#endif /* calculation_h */
