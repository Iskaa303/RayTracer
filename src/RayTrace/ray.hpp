#ifndef RAY_H
#define RAY_H

#include "../LinAlg/Vector.h"

namespace RT
{
    class Ray
    {
        public:
            Ray();
            Ray(const Vector<double> &point1, const Vector<double> &point2);

            Vector<double> GetPoint1() const;
            Vector<double> GetPoint2() const;

        public:
            Vector<double> m_point1 {3};
            Vector<double> m_point2 {3};
            Vector<double> m_lab    {3};
    };
}

#endif