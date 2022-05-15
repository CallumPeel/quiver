/// TITLE:  Vector math library
/// AUTHOR: Lane O'Rafferty
/// DATE:   May 2022
///---------------------------------------------------------------------

#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

//----------------------------------------------------------------------

    /// @struct     Vec3
    /// @brief      Defines the attributes of a 3D vector

typedef struct {
    double x, y, z;
} Vec3;

//----------------------------------------------------------------------

    /// @brief      Returns a negated vector
    /// @pre        Vector is initialized
    /// @post       Negated vector is returned
    /// @param      v: pointer to a const Vector. The vector to negate.
    /// @return     Vec3

Vec3 Neg(Vec3 const * v);

    /// @brief      Returns the sum of two vectors
    /// @pre        Vectors are initialized
    /// @post       Vector sum is returned
    /// @param      u: pointer to a const Vector. A vector to sum.
    /// @param      v: pointer to a const Vector. A vector to sum.
    /// @return     Vec3

Vec3 Add(Vec3 const * u, Vec3 const * v);

    /// @brief      Returns the difference of two vectors
    /// @pre        Vectors are initialized
    /// @post       Vector difference is returned
    /// @param      u: pointer to a const Vector. The subtractee.
    /// @param      v: pointer to a const Vector. The subtractor.
    /// @return     Vec3

Vec3 Sub(Vec3 const * u, Vec3 const * v);

    /// @brief      Returns a vector multiplied by some factor
    /// @pre        Vector is initialized
    /// @pre        Factor is a real number
    /// @post       Scaled Vector is returned
    /// @param      u: pointer to a const Vector. The base vector.
    /// @param      fac: the factor to multiply by.
    /// @return     Vec3

Vec3 Mul(Vec3 const * u, double const fac);

    /// @brief      Returns a vector divided by some factor
    /// @pre        Vector is initialized
    /// @pre        Factor is a real number
    /// @post       Scaled Vector is returned
    /// @param      u: pointer to a const Vector. The base vector.
    /// @param      fac: the factor to divide by.
    /// @return     Vec3

Vec3 Div(Vec3 const * u, double const fac);

    /// @brief      Returns the dot product of two vectors
    /// @pre        Vectors are initialized
    /// @post       Vector dot product is returned
    /// @param      u: pointer to a const Vector. A vector to dot.
    /// @param      v: pointer to a const Vector. A vector to dot.
    /// @return     double

double Dot(Vec3 const * u, Vec3 const * v);

    /// @brief      Returns the cross product of two vectors
    /// @pre        Vectors are initialized
    /// @post       Vector cross product is returned
    /// @param      u: pointer to a const Vector. A vector to cross.
    /// @param      v: pointer to a const Vector. A vector to cross.
    /// @return     Vec3

Vec3 Cross(Vec3 const * u, Vec3 const * v);

    /// @brief      Returns the length of a vector
    /// @pre        Vector is initialized
    /// @post       Length is returned
    /// @param      v: pointer to a const Vector. The target vector.
    /// @return     double
double Length(Vec3 const * v);

    /// @brief      Returns the square length of a vector
    /// @pre        Vector is initialized
    /// @post       Square length is returned
    /// @param      v: pointer to a const Vector. The target vector.
    /// @return     double

double Length_squared(Vec3 const * v);

    /// @brief      Returns a normalized vector
    /// @pre        Vector is initialized
    /// @post       Normalized vector is returned
    /// @param      v: pointer to a const Vector. The target vector.
    /// @return     Vec3

Vec3 Normalize(Vec3 const * v);

    /// @brief      Returns a vector reflected about some normal
    /// @pre        Vectors are initialized
    /// @post       Reflected Vector is returned
    /// @param      u: pointer to a const Vector. The incident vector.
    /// @param      n: pointer to a const Vector. The normal vector.
    /// @return     Vec3

Vec3 Reflect(Vec3 const * v, Vec3 const * n);

//----------------------------------------------------------------------

#endif // VECTORS_H_INCLUDED
