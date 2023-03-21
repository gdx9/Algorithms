#include <tuple>
#include <optional>

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

enum class SlopeType{
    UNDEFINED,// vertical line
    ZERO, // horizontal line
    NUMBER
};

enum class LineRelations{
    PERPENDICULAR, PARALLEL, ON_SAME_LINE, INTERSECT, INTERSECT_OUT_OF_SEGMENT, UNKNOWN
};

std::pair<SlopeType, std::optional<double>> calcSlopeOfLine(Line* l){
    double deltaX = l->p2.x - l->p1.x;
    double deltaY = l->p2.y - l->p1.y;

    if(0 == deltaX){
        return {SlopeType::UNDEFINED, std::nullopt};
    }else{
        double slope = deltaY / deltaX;
        if(0 == slope) return {SlopeType::ZERO, slope};
        else return {SlopeType::NUMBER, slope};
    }
}


bool checkLinesPerpendicular(Line* l1, Line* l2){
    std::pair<SlopeType, std::optional<double>> dataL1 = calcSlopeOfLine(l1);
    std::pair<SlopeType, std::optional<double>> dataL2 = calcSlopeOfLine(l2);

    if(SlopeType::UNDEFINED == dataL1.first && SlopeType::ZERO == dataL2.first){
        return true;
    }
    if(SlopeType::UNDEFINED == dataL2.first && SlopeType::ZERO == dataL1.first){
        return true;
    }

    if(std::nullopt != dataL1.second && std::nullopt != dataL2.second){
        // have double value
        return -1. == (dataL1.second.value() * dataL2.second.value());

    }

    return false;
}

std::pair<LineRelations, std::optional<Point>> calcIntesectPoint(Line* l1, Line* l2){
    double numeratorT  = (l1->p1.x - l2->p1.x) * (l2->p1.y - l2->p2.y) - (l1->p1.y - l2->p1.y) * (l2->p1.x - l2->p2.x);
    double numeratorU  = (l1->p1.x - l2->p1.x) * (l1->p1.y - l1->p2.y) - (l1->p1.y - l2->p1.y) * (l1->p1.x - l1->p2.x);
    double denominator = (l1->p1.x - l1->p2.x) * (l2->p1.y - l2->p2.y) - (l1->p1.y - l1->p2.y) * (l2->p1.x - l2->p2.x);

    if (0 == denominator){
        if(0 != numeratorT && 0 != numeratorU){
            return {LineRelations::PARALLEL, std::nullopt};
        }
        if(0 == numeratorT && 0 == numeratorU){
            return {LineRelations::ON_SAME_LINE, std::nullopt};
        }

    }else{
        // denominator != 0 : single solution
        double t = numeratorT / denominator;
        double u = numeratorU / denominator;

        double x = l1->p1.x + t * (l1->p2.x - l1->p1.x);
        double y = l1->p1.y + t * (l1->p2.y - l1->p1.y);

        if((t < 0 || t > 1) || (u < 0 || u > 1)){
            return {LineRelations::INTERSECT_OUT_OF_SEGMENT, Point{x,y}};
        }else{
            return {
                // check if lines perpendicular
                checkLinesPerpendicular(l1, l2) ? (LineRelations::PERPENDICULAR) : LineRelations::INTERSECT,
                Point{x,y}
            };
        }

    }

    return {LineRelations::UNKNOWN, std::nullopt};
}
