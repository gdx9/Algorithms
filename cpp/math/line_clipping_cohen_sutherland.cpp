#include <tuple>
#include <memory>

constexpr uint8_t kAreaInside = 0b00000000;
constexpr uint8_t kAreaLeft   = 0b00000001;
constexpr uint8_t kAreaRight  = 0b00000010;
constexpr uint8_t kAreaBottom = 0b00000100;
constexpr uint8_t kAreaTop    = 0b00001000;

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

uint8_t calcRegionCode(double x, double y){
    uint8_t code = kAreaInside;
    if(x < kWindowMinX)
        code |= kAreaLeft;// left of window
    else if(x > kWindowMaxX)
        code |= kAreaRight;// right of window

    if(y < kWindowMinY)
        code |= kAreaBottom;// under window
    else if(y > kWindowMaxY)
        code |= kAreaTop;// above window

    return code;
}

pair<unique_ptr<Point>, unique_ptr<Point>>
    lineClip_CohenSutherland(unique_ptr<Point> pntBegin,
            unique_ptr<Point> pntEnd){

    uint8_t pntBeginCode = calcRegionCode(pntBegin->x, pntBegin->y);
    uint8_t pntEndCode   = calcRegionCode(pntEnd->x,   pntEnd->y);

    // while both points are not in the same region
    while(pntBeginCode | pntEndCode){
        if(pntBeginCode & pntEndCode){
            // both points are in the same region
            return {nullptr, nullptr};
        }else{
            // one of part of line is in rectangle
            Point* procPnt;
            int code;

            // pick up one point which is out of window
            if(kAreaInside != pntBeginCode){
                procPnt = pntBegin.get();
                code = pntBeginCode;
            }else{
                procPnt = pntEnd.get();
                code = pntEndCode;
            }

            // get window area
            if (code & kAreaLeft) {
                // move point to x_min
                procPnt->y = pntBegin->y + (pntEnd->y - pntBegin->y)
                        * (kWindowMinX - pntBegin->x) / (pntEnd->x - pntBegin->x);
                procPnt->x = kWindowMinX;
            } else if (code & kAreaRight) {
                // move point to x_max
                procPnt->y = pntBegin->y + (pntEnd->y - pntBegin->y)
                        * (kWindowMaxX - pntBegin->x) / (pntEnd->x - pntBegin->x);
                procPnt->x = kWindowMaxX;
            }
            else if (code & kAreaTop) {//
                // move point to y_min
                procPnt->x = pntBegin->x + (pntEnd->x - pntBegin->x)
                        * (kWindowMaxY - pntBegin->y) / (pntEnd->y - pntBegin->y);
                procPnt->y = kWindowMaxY;
            } else if (code & kAreaBottom) {//
                // move point to y_max
                procPnt->x = pntBegin->x + (pntEnd->x - pntBegin->x)
                        * (kWindowMinY - pntBegin->y) / (pntEnd->y - pntBegin->y);
                procPnt->y = kWindowMinY;
            }

            if(code == pntBeginCode){
                pntBeginCode = calcRegionCode(pntBegin->x, pntBegin->y);
            }else{
                pntEndCode = calcRegionCode(pntEnd->x, pntEnd->y);
            }
        }
    }

    return {move(pntBegin), move(pntEnd)};
}
