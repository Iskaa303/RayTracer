#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace RT
{
    class ObjPlane : public ObjectBase
    {
        public:
            // The default constructor
            ObjPlane();

            // Override the destructor
            virtual ~ObjPlane() override;

            // Override the function to test for intersections
            virtual bool TestIntersection
            (
                const RT::Ray &castRay, Vector<double> &intPoint,
                Vector<double> &localNormal, Vector<double> &localColor
            ) override;
        
        private:
            
    };
}

#endif