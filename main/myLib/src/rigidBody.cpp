#include "rigidBody.hpp"

using namespace m_engine;

void RigidBody::integrate(double time){
    //calcul acceleration
    Vector3D a = m_accumForce * m_inversMass;
    //calcul theta''
    Vector3D theta = m_transformMatrix * m_InversInertialTensor * m_transformMatrix.inverse() * m_accumTorque;
    //update velocity
    m_vel = m_vel * pow(m_linearDamping, time) + a * time;
    //update angular velocity
    //WHAT IS THE OMEGA w
    m_rotation = m_rotation  * pow(m_linearDamping, time)  + time * theta;
}