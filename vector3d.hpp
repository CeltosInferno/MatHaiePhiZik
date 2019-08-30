#ifndef VECTOR_3D
#define VECTOR_3D

#include <string>

namespace m_engine {

  class Vector3D {
  public:
    Vector3D(double x=0, double y=0, double z=0);
    ~Vector3D();


	//OPERATORS OVERRIDE
	Vector3D operator+(const Vector3D& u) const;
	Vector3D& operator+=(const Vector3D& u);

	Vector3D operator-(const Vector3D& u) const;
	Vector3D& operator-=(const Vector3D& u);

	Vector3D operator* (double k) const;
	Vector3D& operator*=(double k);

	Vector3D operator* (const Vector3D& u) const;
	Vector3D& operator*=(const Vector3D& u);

	bool operator==(const Vector3D& u) const;
	bool operator!=(const Vector3D& u) const; 

	operator std::string() const;

	//BASIC OPERATIONS ON VECTORS
	double scalar(const Vector3D& u) const;
	double norm() const;
	Vector3D normalize() const;
	Vector3D cross(const Vector3D& u) const;
	double distance(const Vector3D& u) const;
	double tripleProduct(const Vector3D& u, const Vector3D& v) const;


  private:
	  double coord[3];
  };

}

#endif /* VECTOR_3D */
