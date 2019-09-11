#ifndef PARTICLE
#define PARTICLE

#include <string>
#include <iostream>
#include "vector3d.hpp"

namespace m_engine {

  class Particle {
  public:
    Particle();
    Particle(double mass, double damping = 1, double posX = 0, double posY = 0, double posZ = 0, double velX = 0, double velY = 0, double velZ = 0, double accX = 0, double accY = 0, double accZ = 0);
    Particle(double mass, double damping, const Vector3D& pos, const Vector3D& vel, const Vector3D& acc);
    ~Particle();

    // GETTERS
    double getInversMass() const;

    // SETTERS
    void setMass(double mass);
    void setDamping(double damping);
    inline void setPos(const Vector3D& pos) {m_pos = pos;}
    inline void setVel(const Vector3D& vel) {m_vel = vel;}
    inline void setAcc(const Vector3D& acc) {m_acc = acc;}
    inline void setPos(double x, double y, double z) {m_pos = Vector3D(x,y,z);}
    inline void setVel(double x, double y, double z) {m_vel = Vector3D(x,y,z);}
    inline void setAcc(double x, double y, double z) {m_acc = Vector3D(x,y,z);}

    inline const Vector3D& getPos() const {return m_pos;}
    inline const Vector3D& getVel() const {return m_vel;}
    inline const Vector3D& getAcc() const {return m_acc;}

    // INTEGRATEUR
    void integrate(double time);
    //void renderBash();

  private:
    double m_inversMass;
    double m_damping;
    Vector3D m_pos, m_vel, m_acc;
  };

  inline std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << "[" << "pos: " << p.getPos() << ", vel: " << p.getVel() << ", acc: " << p.getAcc() << "]";
    return os;
  }

}

#endif /* PARTICLE */
