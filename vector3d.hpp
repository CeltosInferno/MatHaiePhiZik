#ifndef VECTOR_3D
#define VECTOR_3D

#include <string>
#include <iostream>

namespace m_engine {
	
  class Vector3D {
  public:
    Vector3D(double x=0, double y=0, double z=0);
    ~Vector3D();
    
    //GETTER
    //Access coordinate 'i' by writing vector[i]
    //Return 0 if i outbounded
    double operator[] (int i) const;

    //SETTER
    //Writing coordinate 'i' by writing vector[i]
    //Return vector[0] if i outbounded
    double& operator[] (int i);

    //OPERATORS OVERRIDE
    //Additions operators
    inline Vector3D operator+(const Vector3D& u) const {
      return Vector3D(x+u.x, y + u.y, z + u.z);
    }
    Vector3D& operator+=(const Vector3D& u);

    //Substraction operators
    inline Vector3D operator-() const {return Vector3D(-x,-y,-z);}
    inline Vector3D operator-(const Vector3D& u) const {
      return Vector3D(x - u.x, y - u.y, z - u.z);
    }
    Vector3D& operator-=(const Vector3D& u);

    //Multiplication with a scalar operators
    inline Vector3D operator*(double k) const {
      return Vector3D(x*k, y*k, z*k);
    }
    Vector3D& operator*=(double k);

    //Multiplication of each coordinate of two vectors operators
    inline Vector3D operator*(const Vector3D& u) const {
      return Vector3D(x * u.x, y * u.y, z * u.z);
    }
    Vector3D& operator*=(const Vector3D& u);

    //Division by a scalar operators
    inline Vector3D operator/(double k) const {
      return Vector3D(x / k, y / k, z / k);
    }
    Vector3D& operator/=(double k);

    //Equality operators
    inline bool operator==(const Vector3D& u) const {
      return (x == u.x && y == u.y && z == u.z);
    }
    inline bool operator!=(const Vector3D& u) const {
      return !(*this == u);
    }

    //BASIC OPERATIONS ON VECTORS
    //Return the scalar product
    double scalar(const Vector3D& u) const;
    //Return the norm
    double norm() const;
    //Return the square of the norm
    double sqrNorm() const;
    //Return the vector normalized
    Vector3D normalize() const;
    //Return the cross product
    Vector3D cross(const Vector3D& u) const;
    //Return the distance between the two points represented by vectors
    double distance(const Vector3D& u) const;
    //Return the triple product, ie the volume of the parallelepiped defined by three vectors
    double tripleProduct(const Vector3D& u, const Vector3D& v) const;

  public:
    double x, y, z;
  };

  //STATIC OPERATORS
  //Return the result of multiplication of a scalar and a vector
  inline Vector3D operator* (double k, const Vector3D& v) {
    return v*k;
  }

  //Overiding << for printing
  inline std::ostream& operator<<(std::ostream& os, const Vector3D& u) {
    os << "(" << u.x << ", " << u.y << ", " << u.z << ")";
    return os;
  }
  
  //Return scalar product of two vectors
  inline double scalar(const Vector3D& v, const Vector3D& u) {
    return v.scalar(u);
  }
  
  //Return norm of a vector
  inline double norm(const Vector3D& v) {
    return v.norm();
  }
  
  //Return the square of the norm of a vector
  inline double sqrNorm(const Vector3D& v) {
    return v.sqrNorm();
  }

  //Return the normalized vector
  inline Vector3D normalize(const Vector3D& v) {
    return v.normalize();
  }
  
  //Return cross product of two vectors
  inline Vector3D cross(const Vector3D& v, const Vector3D& u) {
    return v.cross(u);
  }
  
  //Return distance between two points
  inline double distance(const Vector3D& v, const Vector3D& u) {
    return v.distance(u);
  }
  
  //Return triple product of three vectors, ie the volume of the parallelepiped defined by three vectors
  inline double tripleProduct(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
    return v1.tripleProduct(v2,v3);
  }

}

#endif /* VECTOR_3D */
