#include "scene.hpp"

// The constructor
RT::Scene::Scene()
{
    // Configure the camera
    m_camera.SetPosition( Vector<double>{std::vector<double>{0.0, -10.0, -1.0}} );
    m_camera.SetLookAt  ( Vector<double>{std::vector<double>{0.0, 0.0, 0.0}} );
    m_camera.SetUp      ( Vector<double>{std::vector<double>{0.0, 0.0, 1.0}} );
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();
    
    // Construct test spheres
    m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));
    m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));
    m_objectList.push_back(std::make_shared<RT::ObjSphere> (RT::ObjSphere()));

    // Construct a test plane
    m_objectList.push_back(std::make_shared<RT::ObjPlane> (RT::ObjPlane()));
    m_objectList.at(3) -> m_baseColor = Vector<double>{std::vector<double> {0.5, 0.5, 0.5}};

    // Define a transform for the plane
    RT::GTform planeMatrix;
    planeMatrix.SetTransform
    (
        Vector<double>{std::vector<double>{0.0, 0.0, 0.75}},
        Vector<double>{std::vector<double>{0.0, 0.0, 0.0}},
        Vector<double>{std::vector<double>{4.0, 4.0, 1.0}}
    );
    m_objectList.at(3) -> SetTransformMatrix(planeMatrix);

    // Modify the spheres
    RT::GTform testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform
    (
        Vector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.0, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.5, 0.5, 0.75}}
    );
    testMatrix2.SetTransform
    (
        Vector<double>{std::vector<double>{0.0, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.0, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.75, 0.5, 0.5}}
    );
    testMatrix3.SetTransform
    (
        Vector<double>{std::vector<double>{1.5, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.0, 0.0, 0.0}},
        Vector<double>{std::vector<double>{0.75, 0.75, 0.75}}
    );

    m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
    m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
    m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

    m_objectList.at(0) -> m_baseColor = Vector<double>{std::vector<double>{0.25, 0.5, 0.8}};
    m_objectList.at(1) -> m_baseColor = Vector<double>{std::vector<double>{1.0, 0.5, 0.0}};
    m_objectList.at(2) -> m_baseColor = Vector<double>{std::vector<double>{1.0, 0.8, 0.0}};

    // Construct a test light
    m_lightList.push_back(std::make_shared<RT::PointLight> (RT::PointLight()));
    m_lightList.at(0) -> m_location = Vector<double> {std::vector<double> {5.0, -10.0, -5.0}};
    m_lightList.at(0) -> m_color = Vector<double> {std::vector<double> {0.0, 0.0, 1.0}};
    
    m_lightList.push_back(std::make_shared<RT::PointLight> (RT::PointLight()));
    m_lightList.at(1) -> m_location = Vector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
    m_lightList.at(1) -> m_color = Vector<double> {std::vector<double> {1.0, 0.0, 0.0}};

}

// Function to perform the rendering
bool RT::Scene::Render(Image &outputImage)
{
    // Get the dimensions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    RT::Ray cameraRay;
    Vector<double> intPoint     {3};
    Vector<double> localNormal  {3};
    Vector<double> localColor   {3};
    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;

    for (int x = 0; x < xSize; ++x)
    {
        for (int y = 0; y < ySize; ++y)
        {
            // Normalize the x and y coordinates
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate the ray for this pixel
            m_camera.GenerateRay(normX, normY, cameraRay);

            // Test for intersections for all objects on the scene
            std::shared_ptr<RT::ObjectBase> closestObject;
            Vector<double> closestIntPoint      {3};
            Vector<double> closestLocalNormal   {3};
            Vector<double> closestLocalColor    {3};
            double minDist = 1e6;
            bool intersectionFound = false;
            for (auto currentObject : m_objectList)
            {
                bool validInt = currentObject -> TestIntersection(cameraRay, intPoint, localNormal, localColor);

                // If we have a valid intersection, change the pixel color to red
                if (validInt)
                {
                    // Set the flag to indicate that we found an intersection
                    intersectionFound = true;

                    // Compute the distance between the camera and the point of intersection
                    double dist = (intPoint - cameraRay.m_point1).norm();

                    // If this object is closer to the camera than any one that we have seen before, then store a reference to it
					if (dist < minDist)
					{
						minDist = dist;
						closestObject = currentObject;
						closestIntPoint = intPoint;
						closestLocalNormal = localNormal;
						closestLocalColor = localColor;
					}
                }
            }
            // Compute the illumination for the closest object, assuming that there was a valid intersection
			if (intersectionFound)
			{
				// Compute the intensity of illumination
				double intensity;
				Vector<double> color {3};
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool validIllum = false;
				bool illumFound = false;
				for (auto currentLight : m_lightList)
				{
					validIllum = currentLight -> ComputeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObject, color, intensity);
					
					if (validIllum)
					{
						illumFound = true;
						red += color.GetElement(0) * intensity;
						green += color.GetElement(1) * intensity;
						blue += color.GetElement(2) * intensity;
					}
				}
				
				if (illumFound)
				{
					red *= closestLocalColor.GetElement(0);
					green *= closestLocalColor.GetElement(1);
					blue *= closestLocalColor.GetElement(2);
					outputImage.SetPixel(x, y, red, green, blue);
				}
            }
        }
    }

    return true;
}