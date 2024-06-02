#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

namespace RT
{
    class PointLight : public LightBase
    {
        public:
            // The default constructor
            PointLight();

            // Override the default destructor
            virtual ~PointLight() override;

            // Function to compute illumination contribution
            virtual bool ComputeIllumination
            (
                const Vector<double> &intPoint, const Vector<double> &localNormal,
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
                const std::shared_ptr<RT::ObjectBase> &currentObject,
                Vector<double> &color, double &intensity
            ) override;
    };
}

#endif