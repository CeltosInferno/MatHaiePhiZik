#include "rigidBody.hpp"

using namespace m_engine;

//Constructor
RigidBody::RigidBody(double r, double mass, double linearDamping = 1, double angularDamping = 1, Vector3D pos = Vector3D(0,0,0), Vector3D vel = Vector3D(0,0,0),Quaternion orientation = Quaternion(0,0,0,0) ,Vector3D rotation = Vector3D(0,0,0)):
    m_inversMass(1/mass), m_linearDamping(linearDamping), m_angularDamping(angularDamping), m_pos(pos), m_vel(vel),m_orientation(orientation),m_rotation(rotation)
{
    setInertialTensorSphere(r);
};

RigidBody::RigidBody(double dx, double dy, double dz, double mass, double linearDamping = 1, double angularDamping = 1, Vector3D pos = Vector3D(0,0,0), Vector3D vel = Vector3D(0,0,0),Quaternion orientation = Quaternion(0,0,0,0) ,Vector3D rotation = Vector3D(0,0,0)):
    m_inversMass(1/mass), m_linearDamping(linearDamping), m_angularDamping(angularDamping), m_pos(pos), m_vel(vel),m_orientation(orientation),m_rotation(rotation)
{
    setInertialTensorBox(dx,dy,dz);
};
             

//update object
void RigidBody::integrate(double time){
    //calcul acceleration
    Vector3D a = m_accumForce * m_inversMass;
    //calcul theta''
    Vector3D theta = m_globalInversInertialTensor * m_accumTorque;
    //update linear velocity
    m_vel = m_vel * pow(m_linearDamping, time) + a * time;
    //update angular velocity
    m_rotation = m_rotation  * pow(m_linearDamping, time)  + time * theta;
    //update position
    m_pos += m_vel * time;
    //update rotation
    m_orientation.rotateByVector(m_rotation);
    //Update transformMatrix and InertialTensor for this object
    Matrix3 m_transformMatrixInv =m_orientation.toMatrix();

    m_transformMatrix = m_transformMatrixInv.inverse();
    m_globalInversInertialTensor = m_transformMatrixInv * m_localInversInterialTensor * m_transformMatrix;

    //clear accum
    cleanAccum();
    
}


//clean both accumulators
void RigidBody::cleanAccum(){
    cleanForceAccum();
    cleanTorqueAccum();
};

//clean Force accumulator
void RigidBody::cleanForceAccum(){
    m_accumForce=Vector3D(0,0,0);
};

//clean torque accumulator
void RigidBody::cleanTorqueAccum(){
    m_accumTorque=Vector3D(0,0,0);
};


//add a Force applied to a point of the object in local referentiel
void RigidBody::addForceAtPoint(const Vector3D& F, const Vector3D& point){
    //Convert point to relative coordinates
    Vector3D local_point = m_orientation.toMatrix() * (point - m_pos);
    //update accumForce
    m_accumForce += F;
    //update accumTorque
    m_accumTorque += cross(local_point,F);
};
//add a Force applied to an object as an entity
void RigidBody::addForceAtBodyPoint(const Vector3D& F){
    //addForce
    m_accumForce += F;
};

//add a Torque on object
void RigidBody::addTorque(const Vector3D& torque){
    m_accumTorque += torque;
};

void RigidBody::setInertialTensorBox(double dx, double dy, double dz){
    double k = 1/12 /m_inversMass;
    m_localInversInterialTensor = Matrix3(k*(dy*dy + dz*dz),0,0, 0,k*(dx*dx + dz*dz),0  ,0,0,k*(dx*dx + dy*dy)).inverse();
};
void RigidBody::setInertialTensorSphere(double r){
    m_localInversInterialTensor =  Matrix3() * 2/5 / m_inversMass * r*r;
};
