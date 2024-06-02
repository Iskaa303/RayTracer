#ifndef GTFM_H
#define GTFM_H

#include "../LinAlg/Vector.h"
#include "../LinAlg/Matrix.h"
#include "ray.hpp"

namespace RT
{
    // Define direction flag values
    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTform
    {
        public:
            // The default constructor and destructor
            GTform();
            ~GTform();

            // Construct from a pair of matrices
            GTform(const Matrix2<double> &fwd, const Matrix2<double> &bck);

            // Function to set translation, rotation and scale components
            void SetTransform
            (
                const Vector<double> &translation,
                const Vector<double> &rotation,
                const Vector<double> &scale
            );

            // Functions to return the transform matrices
            Matrix2<double> GetForward();
            Matrix2<double> GetBackward();

            // Function to apply the transform
            RT::Ray Apply(const RT::Ray &inputRay, bool dirFlag);
            Vector<double> Apply(const Vector<double> &inputVector, bool dirFlag);

            // Overload operators
            friend GTform operator* (const RT::GTform &lhs, const RT::GTform &rhs);

            // Overload the assignment operator
            GTform operator= (const GTform &rhs);

            // Function to print matrix to STDOUT
            void PrintMatrix(bool dirFlag);

            // Function to allow printing of vectors
            static void PrintVector(const Vector<double> &vector);
        
        private:
            void Print(const Matrix2<double> &matrix);
        
        private:
            Matrix2<double> m_fwdtfm {4, 4};
            Matrix2<double> m_bcktfm {4, 4};
    };
}

#endif