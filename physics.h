#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "data_base.h"
#include "typedefs.h"
#include <string>
#include <SDL.h>
#include <vector>

 class Physics
{

    public:
    //methods
    double NewtonianForce(char axis = 'x');
    double Relativity(char axis = 'x');
    double rel_NewtonianForce(char axis = 'x');// Functions that employ relativity will have a rel_ prefix. These functions will be available in case I do physics calculations on objects moving really fast!
    double rel_CalculateForceB(bool relativity);// Overload of previous function
    void Impulse (math_VECTOR inputVector);//Basically, I want to take a vector, change its relative direction relative to an imaginary circle in the background, and use the new direction to update the point that describes its new position.
    double Friction(double targetMU, bool relativity);
    void Update_Velocity(double secondsPassed);
    void UpdateForce(Physics* forceProducer, int force_type, bool relativity = false, char axis = 'x');//IndexSize should be simple to get.
    void Update_Acceleration();
    double math_CalculateDirectionDegrees(int sourceX, int sourceY) const;
    double GetDistance(const math_point& source) const;
    math_point GetLoc() const;
    double GetMU() const;
    double GetMass() const;
    std::string GetB2DDirection() const;
    double GetBMagnitude() const;
    double GetGravity() const;
    double GetVelocity(char axis) const;
    double GetElasticity() const;
    double math_CalculateForceFromChargedParticles(double Q2, const math_point& source) const;
    double math_CalculateEField(const math_point& source) const;
    double math_CalculateEField(int ForceCount) const;
    int math_Sign(Physics *forceProducer, bool x) const;
    int math_Sign(Physics *forceProducer, char axis) const;
    void math_CalculateMomentum(Physics *actor, Physics *target) const;
    double math_CalculateForceFromMagneticField(std::string MagneticField, double magnitude) const;
    //math_VECTOR GetInternalVector();
    double GetForceCount(char axis) const;
    bool isUnmovable() const;
    void SetForceCount(int force, char axis);
    void SetForceCount(double force, char axis);
    void SetLoc(const math_point& pos);
    void SetVelocity(double velocity, char axis);
    void AddForce(double force, char axis = 'x');
    Physics(const char* location = "");
    void Update_Position(double secondsPassed);//Since physics differ for a ship in space vs. a man walking on a rock with a strong gravitational pull, I need the spaceType flag to update the position of the object in an appropriate manner. True= space; False= rock!
    void ChangePlanetGravitationalConstant(double g);//Although I defined g as Earth gravity, I want to keep the engine as flexible as possible so I want to give a way to redefine g for other worlds :).
    bool Load_Physics(const char* physData);
    double GetCharge() const;


    private:
    double mass;
    double ForceCountX;//I will separate forces by axis
    double ForceCountY;
    int unmovable;
    double mu;
    double accelerationX;
    double accelerationY;
    double velocityX;
    double velocityY;
    double magneticFieldMagnitude;
    double C;
    double elasticity;
    double g;
    math_point loc;
    std::string B;
    //Let's define some basic physics constants
    static const double G;
    static const double c;
    static const double e;
    static const double pi;
    static const double epsilon0;
    static const double mu0;
    static const double k;
    //methods
    void rel_CalculateForce(char axis = 'x', bool relativity = false);
};

size_t CalculateDistance(const math_point& A, const math_point& B);
#endif // PHYSICS_H_INCLUDED
