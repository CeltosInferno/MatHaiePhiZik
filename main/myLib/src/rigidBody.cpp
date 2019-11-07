#include "rigidBody.hpp"

using namespace m_engine;

/*
void setInertialTensorBox(double dx, double dy, double dz);
void setIntertialTensorSphere(double r);
*/

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
