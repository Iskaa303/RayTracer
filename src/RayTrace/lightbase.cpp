#include "lightbase.hpp"

// Constructor
RT::LightBase::LightBase()
{

}

// Destructor
RT::LightBase::~LightBase()
{

}

// Function to compute illumination contribution
bool RT::LightBase::ComputeIllumination
(
    const Vector<double> &intPoint, const Vector<double> &localNormal,
    const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
    const std::shared_ptr<RT::ObjectBase> &currentObject,
    Vector<double> &color, double &intensity
) {
    return false;   
}