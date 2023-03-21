#include <vector>
#include <string>

using namespace std;

struct Point{
    explicit Point(const int32_t x , const int32_t y)
    : x(x), y(y){}
    Point() = delete;

    int32_t x, y;
};

enum class Orientation{
    CLOCKWISE, COUNTER_CLOCKWISE, COLLINEAR
};

Orientation calcOrientation(const Point& p, const Point& q, const Point& r){
    int32_t val = (q.y - p.y) * (r.x - q.x)
        - (q.x - p.x) * (r.y - q.y);

    return (0 == val) ? Orientation::COLLINEAR
            : (val > 0) ? Orientation::CLOCKWISE
            : Orientation::COUNTER_CLOCKWISE;
}

// returns vector of Points than create a convex hull
vector<Point> convexHullJarvis(vector<Point> points){
    vector<Point> hull;
    size_t numPts = points.size();
    if(numPts < 3) return hull;// not enough points

    // get index of most left point
    size_t leftmostPos = 0;
    int32_t minVal = points[leftmostPos].x;
    for(size_t i = 1; i < numPts; ++i){
        if(points[i].x < minVal){
            minVal = points[i].x;
            leftmostPos = i;
        }
    }

    // position of point on the hull
    size_t hullPos = leftmostPos;
    int nextPos = 0;

    while(true){
        hull.push_back(points[hullPos]);

        nextPos = (hullPos + 1) % numPts;

        for(size_t i = 0; i < numPts; ++i){
            if(calcOrientation(points[hullPos], points[i], points[nextPos]) == Orientation::COUNTER_CLOCKWISE){
                nextPos = i;
            }
        }

        hullPos = nextPos;

        if(hullPos == leftmostPos) break;
    }

    return hull;

}
