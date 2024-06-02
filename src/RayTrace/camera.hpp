#ifndef CAMERA_H
#define CAMERA_H

#include "../LinAlg/Vector.h"
#include "ray.hpp"

namespace RT
{
    class Camera
    {
        public:
            // The default constructor
            Camera();

            // Functions to set camera parameters
            void SetPosition    (const Vector<double> &newPosition);
            void SetLookAt      (const Vector<double> &newLookAt);
            void SetUp          (const Vector<double> &upVector);
            void SetLength      (double newLength);
            void SetHorzSize    (double newSize);
            void SetAspect      (double newAspect);

            // Functions to return camera parameters
            Vector<double>      GetPosition();
            Vector<double>      GetLookAt();
            Vector<double>      GetUp();
            Vector<double>      GetU();
            Vector<double>      GetV();
            Vector<double>      GetScreenCentre();
            double              GetLength();
            double              GetHorzSize();
            double              GetAspect();

            // Function to generate a ray
            bool GenerateRay(float proScreenX, float proScreenY, RT::Ray &cameraRay);

            // Function to update the camera geometry
            void UpdateCameraGeometry();
        
        private:
            Vector<double> m_cameraPosition {3};
            Vector<double> m_cameraLookAt   {3};
            Vector<double> m_cameraUp       {3};
            double m_cameraLength;
            double m_cameraHorzSize;
            double m_cameraAspectRatio;

            Vector<double> m_alignmentVector        {3};
            Vector<double> m_projectionScreenU      {3};
            Vector<double> m_projectionScreenV      {3};
            Vector<double> m_projectionScreenCentre {3};

    };
}

#endif