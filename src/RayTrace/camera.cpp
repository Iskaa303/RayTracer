#include "camera.hpp"
#include "ray.hpp"
#include <math.h>

RT::Camera::Camera()
{
    // The default constructor
    m_cameraPosition = Vector<double>   {std::vector<double> {0.0, -10.0, 0.0}};
    m_cameraLookAt = Vector<double>     {std::vector<double> {0.0, 0.0, 0.0}};
    m_cameraUp = Vector<double>         {std::vector<double> {0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;
}

void RT::Camera::SetPosition(const Vector<double> &newPosition)
{
    m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const Vector<double> &newLookAt)
{
    m_cameraLookAt = newLookAt;
}

void RT::Camera::SetUp(const Vector<double> &upVector)
{
    m_cameraUp = upVector;
}

void RT::Camera::SetLength(double newLength)
{
    m_cameraLength = newLength;
}

void RT::Camera::SetHorzSize(double newHorzSize)
{
    m_cameraHorzSize = newHorzSize;
}

void RT::Camera::SetAspect(double newAspect)
{
    m_cameraAspectRatio = newAspect;
}

// Method to return the position of the camera
Vector<double> RT::Camera::GetPosition()
{
    return m_cameraPosition;
}

// Method to return the LookAt of the camera
Vector<double> RT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}

// Method to return the up vector of the camera
Vector<double> RT::Camera::GetUp()
{
    return m_cameraUp;
}

// Method to return the length of the camera
double RT::Camera::GetLength()
{
    return m_cameraLength;
}

// Method to return the horizontal size of the camera
double RT::Camera::GetHorzSize()
{
    return m_cameraHorzSize;
}

// Method to return the camera aspect ratio
double RT::Camera::GetAspect()
{
    return m_cameraAspectRatio;
}

// Method to return the U vector of the camera
Vector<double> RT::Camera::GetU()
{
    return m_projectionScreenU;
}

// Method to return the V vector of the camera
Vector<double> RT::Camera::GetV()
{
    return m_projectionScreenV;
}

// Method to return the projection screen centre of the camera
Vector<double> RT::Camera::GetScreenCentre()
{
    return m_projectionScreenCentre;
}

// Function to compute camera geometry
void RT::Camera::UpdateCameraGeometry()
{
    // First, compute the vector from the camera position to LookAt position
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // Second, compute the U and V vectors
    m_projectionScreenU = Vector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = Vector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_alignmentVector.Normalize();

    // Third, compute the position of the centre point of the screen
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    // Modify the U and V vectors to match the size and aspect ratio
    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

// Function to generate the ray
bool RT::Camera::GenerateRay(float proScreenX, float proScreenY, RT::Ray &cameraRay)
{
    // Compute the location of the screen point in the world coordinates
    Vector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    Vector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

    // Use this point along with the camera position to compute the ray
    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point2 = screenWorldCoordinate;
    cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
    
    return true;
}