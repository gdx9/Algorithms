#include <tuple>
#include <memory>

// clipping window positions
constexpr double kWindowMinX = 150;
constexpr double kWindowMaxX = 350;
constexpr double kWindowMinY = 135;
constexpr double kWindowMaxY = 315;

using namespace std;

struct Point{
    explicit Point(const double x , const double y)
    : x(x), y(y){}
    Point() = delete;

    double x, y;
};

struct Line{
    Line(double p1x, double p1y, double p2x, double p2y)
    : p1(p1x, p1y), p2(p2x, p2y){}
    Line() = delete;

    Point p1;
    Point p2;
};



pair<unique_ptr<Point>, unique_ptr<Point>>
    lineClip_LiangBarsky(unique_ptr<Point> pntBegin,
        unique_ptr<Point> pntEnd){

    const double kDx = pntEnd->x - pntBegin->x;
    const double kDy = pntEnd->y - pntBegin->y;
    double p[4] = {-kDx, kDx, -kDy, kDy};
    double q[4] = {-(kWindowMinX - pntBegin->x), kWindowMaxX - pntBegin->x,
            -(kWindowMinY - pntBegin->y), kWindowMaxY - pntBegin->y};

    double tEntry = 0.;
    double tLeaving = 1.;

    // for every edge
    for (int i = 0; i < 4; ++i) {
        if(p[i] == 0 && q[i] < 0){
            // line's parallel to window and completely outside
            return {nullptr, nullptr};
        }

        if(p[i] < 0){
            double t = q[i] / p[i];
            if(t > tLeaving) return {nullptr, nullptr};// don't draw

            tEntry = (t > tEntry) ? t : tEntry;
        }else if(p[i] > 0){
            float t = q[i] / p[i];
            if(t < tEntry) return {nullptr, nullptr};// don't draw

            tLeaving = (t < tLeaving) ? t : tLeaving;
        }
    }

    if(tEntry > tLeaving){
        // maybe input parameters are reversed or something
        return {nullptr, nullptr};
    }

    // update values
    double origX0 = pntBegin->x;
    double origY0 = pntBegin->y;
    if(tEntry > 0.){
        // update
        pntBegin->x = origX0 + tEntry * kDx;
        pntBegin->y = origY0 + tEntry * kDy;
    }
    if(tLeaving < 1.){
        // update
        pntEnd->x = origX0 + tLeaving * kDx;
        pntEnd->y = origY0 + tLeaving * kDy;
    }

    return {move(pntBegin), move(pntEnd)};

}
