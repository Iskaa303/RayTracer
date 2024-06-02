#include "ray.hpp"

RT::Ray::Ray()
{
    m_point1 = Vector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    m_point2 = Vector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    m_lab = m_point2 - m_point1;
}

RT::Ray::Ray(const Vector<double> &point1, const Vector<double> &point2)
{
    m_point1 = point1;
    m_point2 = point2;
    m_lab = m_point2 - m_point1;
}

Vector<double> RT::Ray::GetPoint1() const
{
    return m_point1;
}

Vector<double> RT::Ray::GetPoint2() const
{
    return m_point2;
}