#ifndef RIGIDBODY
#define RIGIDBODY

#include "vector3d.hpp"
#include "quaternion.hpp"
#include "matrix3.hpp"

namespace m_engine {

	class RigidBody {
	public:
		// CONSTRUCTORS
		//generate a circle of radius r
		RigidBody(double r, double mass, double linearDamping = 1, 
				double angularDamping = 1, Vector3D pos = Vector3D(0, 0, 0), 
				Vector3D vel = Vector3D(0, 0, 0), 
				Quaternion orientation = Quaternion(0, 0, 0, 0), 
				Vector3D rotation = Vector3D(0, 0, 0));
		//generates a rectangle of length (dx,dy,dz) in global space
		RigidBody(double dx, double dy, double dz, 
				double mass, double linearDamping, double angularDamping, 
				Vector3D pos, Vector3D vel, 
				Quaternion orientation, Vector3D rotation);
		~RigidBody();

		//values used by the graphic renderer to draw renctangles
		const double dx;
		const double dy;
		const double dz;

		// GETTERS
		double getInversMass() const { return m_inversMass; };

		inline const Vector3D& getPos() const { return m_pos; }
		inline const Vector3D& getVel() const { return m_vel; }
		inline const Quaternion& getOrientation() const { return m_orientation;}
		inline const Matrix3& getTransform() const { return m_transformMatrix; }
        // SETTERS
        inline void setMass(double mass) {m_inversMass = 1.0/mass;};
        inline void setLinearDamping(double damping) {m_linearDamping = damping;};
        inline void setAngularDampung(double damping) {m_angularDamping = damping;};
        inline void setPos(const Vector3D& pos) {m_pos = pos;}
        inline void setVel(const Vector3D& vel) {m_vel = vel;}
        inline void setPos(double x, double y, double z) {m_pos = Vector3D(x,y,z);}
        inline void setVel(double x, double y, double z) {m_vel = Vector3D(x,y,z);}
        inline void setOrientation(const Quaternion& orientation) {m_orientation = orientation;}
        void setInertialTensorBox(double dx, double dy, double dz);
        void setInertialTensorSphere(double r);

        //update object characteristics
        void integrate(double time);
        //clean both accumulators
        void cleanAccum();
        //clean Force accumulator
        void cleanForceAccum();
        //clean torque accumulator
        void cleanTorqueAccum();
        //add a Force applied to a point of the object in global referentiel
        void addForceAtGlobalPoint(const Vector3D& F, const Vector3D& point);
		//add a Force applied to a point of the object in local referentiel
		void addForceAtLocalPoint(const Vector3D& F, const Vector3D& point);
        //add a Force applied to an object as an entity
        void addForceAtBodyPoint(const Vector3D& F);
        //add a Torque on object
        void addTorque(const Vector3D& torque);
		//convert a point into local reference to global reference
		Vector3D localToGlobal(const Vector3D& localPoint);
    private:
        double m_inversMass;
        double m_linearDamping;
        double m_angularDamping;
        Vector3D m_pos;
        Vector3D m_vel;
        Quaternion m_orientation;
        Vector3D m_rotation;
		//Matrix local --> global
        Matrix3 m_transformMatrix;
        Matrix3 m_globalInversInertialTensor;
        Matrix3 m_localInversInterialTensor;

        Vector3D m_accumForce;
        Vector3D m_accumTorque;
    };
}


#endif /* RIGIDBODY */