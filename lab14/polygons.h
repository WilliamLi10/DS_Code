

#ifndef __POLYGONS_H__
#define __POLYGONS_H__
#include "utilities.h"
#include <string>
#include <vector>

class Polygon {
public:
    // Constructors
    Polygon(const std::string& n, const std::vector<Point>& p) {
        m_name = n;
        m_points = p;
    }
    virtual ~Polygon() {}

    // Accessor and help function
    std::string getName() const { return m_name; }

    virtual bool HasAllEqualSides() const {
        std::vector<double> lengths;
        for (unsigned int i = 1; i < m_points.size(); ++i)
            lengths.push_back(DistanceBetween(m_points[i - 1],m_points[i]));
        for (unsigned int i = 0; i < lengths.size() - 1; ++i)
            for (unsigned int j = 1; j < lengths.size(); ++j)
                if (!EqualSides(lengths[i], lengths[j])) return false;
        return true;
    }

    virtual bool HasAllEqualAngles() const {
        std::vector<double> angles;
        for (unsigned int i = 0; i < m_points.size(); ++i) {
            if (i == 0) angles.push_back(Angle(m_points[m_points.size() - 1],m_points[i],m_points[i + 1]));
            else if (i == m_points.size() - 1) angles.push_back(Angle(m_points[i - 1],m_points[i],m_points[0]));
            else angles.push_back(Angle(m_points[i - 1],m_points[i],m_points[i + 1]));
        }
        for (unsigned int i = 0; i < angles.size() - 1; ++i)
            for (unsigned int j = 1; j < angles.size(); ++j)
                if (!EqualAngles(angles[i], angles[j])) return false;
        return true;
    }

    virtual bool HasARightAngle() const {
        std::vector<double> angles;
        for (unsigned int i = 0; i < m_points.size(); ++i) {
            if (i == 0) angles.push_back(Angle(m_points[m_points.size() - 1],m_points[i],m_points[i + 1]));
            else if (i == m_points.size() - 1)
                angles.push_back(Angle(m_points[i - 1],m_points[i],m_points[0]));
            else angles.push_back(Angle(m_points[i - 1],m_points[i],m_points[i + 1]));
        }
        for (unsigned int i = 0; i < angles.size() - 1; ++i)
            if (RightAngle(angles[i])) return true;
        return false;
    }

protected:
    std::string m_name;
    std::vector<Point> m_points;
};

class Triangle : public Polygon {
public:
    Triangle(const std::string& n, const std::vector<Point>& p)
            : Polygon(n, p) { if (p.size() != 3) throw 1; }
};

class IsoscelesTriangle : virtual public Triangle {
public:
    IsoscelesTriangle(const std::string& n, const std::vector<Point>& p)
            : Triangle(n, p) {
        double side1_length = DistanceBetween(m_points[0],m_points[1]);
        double side2_length = DistanceBetween(m_points[1],m_points[2]);
        double side3_length = DistanceBetween(m_points[2],m_points[0]);
        if (!EqualSides(side1_length, side2_length) &&
            !EqualSides(side1_length, side3_length) &&
            !EqualSides(side2_length, side3_length)) throw 1;
    }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string& n, const std::vector<Point>& p)
            : Triangle(n, p), IsoscelesTriangle(n, p) {
            if (!HasAllEqualSides()) throw 1;
    }
};

class RightTriangle : virtual public Triangle {
public:
    RightTriangle(const std::string& n, const std::vector<Point>& p)
            : Triangle(n, p) { if (!HasARightAngle()) throw 1; }
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
    IsoscelesRightTriangle(const std::string& n, const std::vector<Point>& p)
            : Triangle(n, p), IsoscelesTriangle(n, p), RightTriangle(n, p) {}
};

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const std::string& n, const std::vector<Point>& p)
            : Polygon(n, p) { if (p.size() != 4) throw 1; }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(const std::string& n, const std::vector<Point>& p): Quadrilateral(n, p) {
        if (!HasAllEqualAngles()) throw 1;
    }
};

class Square : public Rectangle {
public:
    Square(const std::string& n, const std::vector<Point>& p)
            : Rectangle(n, p) {
        if (!HasAllEqualSides()) throw 1;
    }
};

//class Kite : virtual public Quadrilateral {
//public:
//    Kite(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n, p) {
//
//    }
//};

//class Parallelogram : virtual public Quadrilateral {
//public:
//    Parallelogram(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n, p) {
//        Vector a(p[0],p[1]);
//        Vector b(p[2],p[3]);
//        Vector c(p[0],p[3]);
//        Vector d(p[1],p[2]);
//        if (!Parallel(a,b) && !Parallel(c,d)) throw 1;
//    }
//};
//
//class Trapezoid : public Quadrilateral {
//public:
//    Trapezoid(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n, p) {
//        Vector a(p[0],p[1]);
//        Vector b(p[2],p[3]);
//        if (!Parallel(a,b)) throw 1;
//    }
//};

//class Rhombus : virtual public Parallelogram, public Kite {
//public:
//    Rhombus(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n,p), Parallelogram(n, p), Kite(n,p) {}
//};

//class Rectangle : virtual public Parallelogram {
//public:
//    Rectangle(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n,p), Parallelogram(n, p) {
//      if(!HasAllEqualAngles()) throw 1;
//    }
//};
//
//class Square : public Rhombus, public Rectangle {
//public:
//    Square(const std::string& n, const std::vector<Point>& p)
//            : Quadrilateral(n,p), Parallelogram(n, p), Rhombus(n,p), Rectangle(n,p) {
//        if (!HasAllEqualSides()) throw 1;
//    }
//};

#endif //LAB14_POLYGONS_H