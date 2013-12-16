#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include "data_base.h"
#include <string>
#include <SDL.h>
#include <vector>

 struct math_VECTOR// The math prefix will remind me this is a basic math unit
    {
         public:
        int endX;
        int endY;
        double direction; //I'm gonna use the degrees in a circle as the general direction in the screen
        int magnitude;
    };

  struct math_point
  {
      int X;
      int Y;
  };

 class Physics
{

    public:
    //methods
    double NewtonianForce(const char axis = 'x');
    double Relativity(const char axis = 'x');
    double rel_NewtonianForce(const char axis = 'x');// Functions that employ relativity will have a rel_ prefix. These functions will be available in case I do physics calculations on objects moving really fast!
    double rel_CalculateForceB(bool relativity);// Overload of previous function
    void Impulse (math_VECTOR inputVector);//Basically, I want to take a vector, change its relative direction relative to an imaginary circle in the background, and use the new direction to update the point that describes its new position.
    double Friction(double targetMU, bool relativity);
    void Update_Velocity(double secondsPassed);
    void UpdateForce(Physics* forceProducers, int force_type, bool relativity = false);//IndexSize should be simple to get.
    void Update_Acceleration();
    double math_CalculateDirectionDegrees(int sourceX, int sourceY);
    double GetDistance(math_point source);
    math_point GetLoc();
    double GetMU();
    double GetMass();
    std::string GetB2DDirection();
    double GetBMagnitude();
    double GetGravity();
    double GetVelocity(const char axis);
    double GetElasticity();
    double math_CalculateForceFromChargedParticles(double Q2, math_point source);
    double math_CalculateEField(math_point source);
    double math_CalculateEField(int ForceCount);
    int math_Sign(Physics *forceProducer, bool x);
    int math_Sign(Physics *forceProducer, const char axis);
    void math_CalculateMomentum(Physics *actor, Physics *target);
    double math_CalculateForceFromMagneticField(std::string MagneticField, double magnitude);
    //math_VECTOR GetInternalVector();
    double GetForceCount(const char axis);
    bool isUnmovable();
    void SetForceCount(int force, const char axis);
    void SetForceCount(double force, const char axis);
    void SetVelocity(double velocity, const char axis);
    void AddForce(double force, const char axis = 'x');
    Physics(const char* location = "");
    void Update_Position(double secondsPassed);//Since physics differ for a ship in space vs. a man walking on a rock with a strong gravitational pull, I need the spaceType flag to update the position of the object in an appropriate manner. True= space; False= rock!
    void ChangePlanetGravitationalConstant(double g);//Although I defined g as Earth gravity, I want to keep the engine as flexible as possible so I want to give a way to redefine g for other worlds :).
    bool Load_Physics(const char* physData);
    double GetCharge();


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
    data_base physDOM;
    math_point loc;
    std::string B;
    //Let's define some basic physics constants
    double g;
    double G;
    double c;
    double e;
    double pi;
    double epsilon0;
    double mu0;
    double k;
    //methods
    void rel_CalculateForce(const char axis = 'x', bool relativity = false);
};

int CalculateDistance(math_point A, math_point B);
#endif // PHYSICS_H_INCLUDED
