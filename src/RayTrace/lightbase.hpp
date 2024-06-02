#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "../LinAlg/Vector.h"
#include "ray.hpp"
#include "objectbase.hpp"

namespace RT
{
    class LightBase
    {
        public:
            // The default constructor and destructor
            LightBase();
            virtual ~LightBase();

            // Function to compute illumination contribution
            virtual bool ComputeIllumination
            (
                const Vector<double> &intPoint, const Vector<double> &localNormal,
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
                const std::shared_ptr<RT::ObjectBase> &currentObject,
                Vector<double> &color, double &intensity
            );
        
        public:
            Vector<double>  m_color     {3};
            Vector<double>  m_location  {3};
            double          m_intensity;
    };
}

#endif