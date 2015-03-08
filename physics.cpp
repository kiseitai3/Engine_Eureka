//Now, we include other pieces of code
#include "data_base.h"
#include <string>
#include <SDL.h>
#include <math.h>
#include <cmath>
#include <vector>
#include "conversion.h"
#include "physics.h"
#include "rand_generators.h"

//Engine name space macro
//ENGINE_NAMESPACE


//Let's define some basic physics constants
/*This part is a bit dirty, but such is the world of physics. I normally name my constants with upper case, but the scientist
in me is used to using upper and lower cases for specific physics constants. Sorry if it makes you feel dirty, it makes
me feel dirty. Now, let's heal our wounds and move on! :P
*/
const double Physics::G =6.67*pow(10.0,-11.0);
const double Physics::c =3.00*pow(10.0,8.0);
const double Physics::e =1.60*pow(10.0,-19.0);
const double Physics::pi =3.14159;
const double Physics::epsilon0 =8.85*pow(10.0,-12.0);
const double Physics::mu0 =(4*pi)*pow(10.0,-7.0);
const double Physics::k = 9*pow(10.0,9.0);
/*End of dirty section. */

    bool Physics::Load_Physics(const char* location)// physData is the variable that will contain the name of the tag name in the xml file containing the physics details of especific objects (i.e. The hero's animation would have the tag name <hero>).
{
    unmovable = 0;
    data_base physDOM(location);
    if(physDOM.GetStateOfInternalBuffer())
    {
       mass = physDOM.GetValueFromData("mass");//in kilograms
       C = physDOM.GetValueFromData("charge");//in coulombs
       mu = physDOM.GetValueFromData("mu");//coefficient of friction. Normally we want static and kinetic friction separate, but I'm feeling lazy.
       unmovable = physDOM.GetIntFromData("unmovable");//override for all computations. If this flag is true, this opject can't have its position updated
       B = physDOM.GetStrFromData("B");//Gets magnetic field 2D direction
       magneticFieldMagnitude = physDOM.GetValueFromData("B_magnitude");//Gets magnitude in T of magnetic field.
       elasticity = physDOM.GetValueFromData("elasticity");
       return true;
    }
    else
    {
        return false;
    }
}
//Newtonian block
    double Physics::NewtonianForce(const char axis)
    {
        if(axis == 'x')
        {
            return mass * accelerationX;
        }
        return mass * accelerationY;
    }
    double Physics::Relativity(const char axis)
    {
        if(axis == 'x')
        {
            return sqrt(1-((pow(velocityX, 2)/pow(c, 2))));
        }
        return sqrt(1-((pow(velocityY, 2)/pow(c, 2))));
    }
    double Physics::rel_NewtonianForce(const char axis)// Functions that employ relativity will have a rel_ prefix. These functions will be available in case I do physics calculations on objects moving really fast!
    {
        return Relativity(axis)*NewtonianForce(axis);
    }

     double Physics::rel_CalculateForceB(bool relativity)// Overload of previous function
    {
        if(relativity==true)
        {
            return Relativity()*NewtonianForce();
        }
        else
        {
            return NewtonianForce();
        }
    }
    void Physics::Impulse ( math_VECTOR inputVector)//Basically, I want to take a vector, change its relative direction relative to an imaginary circle in the background, and use the new direction to update the point that describes its new position.
    {
        double tempX = inputVector.endX;
        double tempY = inputVector.endY;
        inputVector.direction = inputVector.direction+2*(360-inputVector.direction);
        if(inputVector.direction>360)
        {
            inputVector.direction= inputVector.direction-360;
        }
        tempX=tempX+cos(inputVector.direction);
        tempY=tempY+sin(inputVector.direction);
        inputVector.endX=(int)tempX;
        inputVector.endY=(int)tempY;
    }
    double Physics::Friction(double targetMU, bool relativity)
    {
        return (rel_CalculateForceB(relativity)*(targetMU));
    }
    //Position math
    void Physics::Update_Velocity(double secondsPassed)
    {
        //Update velocity of this object with change in time!
        velocityX += accelerationX * secondsPassed;
        velocityY += accelerationY * secondsPassed;
    }
    void Physics::Update_Acceleration()
    {
        accelerationX = (ForceCountX)/mass;//Update acceleration with the Net Force!
        accelerationY = (ForceCountY)/mass;//Update acceleration with the Net Force!
    }

void Physics::UpdateForce(Physics* forceProducer, int force_type, bool relativity, char axis)//0 magnetic, 1 contact force, 2 electric force, 3 friction
{
    //vars for physics computations.
    double magneticForce = 0;
    double frictionForce = 0;
    double electricForceX = 0;
    double electricForceY = 0;
    int signX = 0;
    int signY = 0;
    double tempForce = 0;
    double degrees = math_CalculateDirectionDegrees(forceProducer->GetLoc().X, forceProducer->GetLoc().Y);
    //double degreesZ = math_CalculateDirectionDegrees(forceProducer->GetLoc().X, forceProducer->GetLoc().Z);

    if(relativity == true && !unmovable)
    {
        //Calculate Newtonian forces with relativity applied
        if(force_type == 3)
        {
            if(GetForceCount(axis) < 0)
            {
                frictionForce = 1 * Friction(forceProducer->GetMU(), relativity) * Relativity(axis);
            }
            else
            {
                frictionForce = -1 * Friction(forceProducer->GetMU(), relativity) * Relativity(axis);
            }
        }
        if(force_type == 2)
        {
            tempForce = math_CalculateForceFromChargedParticles(forceProducer->GetCharge(), forceProducer->GetLoc());
            signX = math_Sign(forceProducer, true);
            signY = math_Sign(forceProducer, false);
            electricForceX = tempForce * cos(degrees) * signX;
            electricForceY = tempForce * sin(degrees) * signY;
        }
        if(force_type == 1)
        {
            if(forceProducer->NewtonianForce('x') != 0)
            {
                ForceCountX += forceProducer->rel_NewtonianForce('x');
            }
            if(forceProducer->NewtonianForce('y') != 0)
            {
                ForceCountY += forceProducer->rel_NewtonianForce('y');
            }
        }
        if(force_type == 0)
        {
            magneticForce = math_CalculateForceFromMagneticField(forceProducer->GetB2DDirection(), forceProducer->GetBMagnitude());
        }
    }
    else if(!unmovable)
    {
        //Calculate Newtonian forces without relativity applied
        if(force_type == 3)
        {
            if(GetForceCount('x') < 0)
            {
                frictionForce = 1 * Friction(forceProducer->GetMU(), relativity);
            }
            else
            {
                frictionForce = -1 * Friction(forceProducer->GetMU(), relativity);
            }

            if(GetForceCount('y') < 0)
            {
                frictionForce = 1 * Friction(forceProducer->GetMU(), relativity) * Relativity('y');
            }
            else
            {
                frictionForce = -1 * Friction(forceProducer->GetMU(), relativity) * Relativity('y');
            }
        }
        if(force_type == 2)
        {
            tempForce = math_CalculateForceFromChargedParticles(forceProducer->GetCharge(), forceProducer->GetLoc());
            signX = math_Sign(forceProducer, true);
            signY = math_Sign(forceProducer, false);
            electricForceX = tempForce * cos(degrees) * signX;
            electricForceY = tempForce * sin(degrees) * signY;
        }
        if(force_type == 1)
        {
            if(forceProducer->NewtonianForce('x') != 0)
            {
                ForceCountX += forceProducer->NewtonianForce('x');
            }
            if(forceProducer->NewtonianForce('y') != 0)
            {
                ForceCountY += forceProducer->NewtonianForce('y');
            }
        if(force_type == 0)
        {
            magneticForce = math_CalculateForceFromMagneticField(forceProducer->GetB2DDirection(), forceProducer->GetBMagnitude());
        }
    }
    //Update forces based on axis
    if(axis == 'x')
        ForceCountX += frictionForce;
    if(axis == 'y')
        ForceCountY += frictionForce;
    //Update other forces
    ForceCountX += electricForceX;
    ForceCountY += electricForceY + magneticForce + (-1 * g * mass);
    }
}
    void Physics::Update_Position(double secondsPassed)
    {
        /*This method obtains the new position of this physics entity/ object. Remember that this x,y coordinate
        assumes that the object is a point mass so you have to apply the offsets before passing it to the drawing system!
        The drawing system always assumes its x,y coordinate = the top left corner of a rectangle!*/
        Update_Acceleration();
        Update_Velocity(secondsPassed);
        loc.X = loc.X +((int)(secondsPassed * velocityX));//Update position
        loc.Y = loc.Y +((int)(secondsPassed * velocityY));//Update position
    }

    //Some math functions
    double Physics::math_CalculateDirectionDegrees(int sourceX, int sourceY) const
    {
        //Calculates the direction from point A to point B using point A (the class' internal location) as the center of an imaginary Cartician plane.
        return atan((double)((loc.Y-sourceY)/(loc.X-sourceX)));
    }
    int Physics::math_Sign(Physics *forceProducer, bool x) const
    {
        /*This method calculates the degrees in a cartician coorinate system. In other words, if points A & B form a vector with direction towards the
        3rd quadrant, then their degrees are between 180 and 270. This method gets the x or y component of a unit vector bearing the same
        direction. If the component has a negative value, return -1. Return 1 otherwise.*/
        double degrees = math_CalculateDirectionDegrees(forceProducer->GetLoc().X, forceProducer->GetLoc().Y);
        double value = 0.0;
        int sign = 1;
        if(x)
        {
            value = 1 * cos(degrees);
            if(value < 0)
            {
                sign = -1;
            }
            return sign;
        }
        value = 1 * sin(degrees);
        if(value < 0)
        {
            sign = -1;
        }
        return sign;
    }
    int Physics::math_Sign(Physics *forceProducer, const char axis) const
    {
        /*This method calculates the degrees in a cartician coorinate system. In other words, if points A & B form a vector with direction towards the
        3rd quadrant, then their degrees are between 180 and 270. This method gets the x or y component of a unit vector bearing the same
        direction. If the component has a negative value, return -1. Return 1 otherwise.*/
        double degrees = math_CalculateDirectionDegrees(forceProducer->GetLoc().X, forceProducer->GetLoc().Y);
        double value = 0.0;
        int sign = 1;
        if(axis == 'x')
        {
            value = 1 * cos(degrees);
            if(value < 0)
            {
                sign = -1;
            }
            return sign;
        }
        value = 1 * sin(degrees);
        if(value < 0)
        {
            sign = -1;
        }
        return sign;
    }
    double Physics::GetDistance(const math_point& source) const
    {
        return sqrt((pow((double)(loc.Y-source.Y),2))+(pow((double)(loc.X-source.X),2)));
    }
    double Physics::GetBMagnitude() const
    {
        return magneticFieldMagnitude;
    }
    std::string Physics::GetB2DDirection() const
    {
        return B;
    }

    bool Physics::isUnmovable() const
    {
        return unmovable;
    }
    //Electricity
    double Physics::math_CalculateForceFromChargedParticles(double Q2, const math_point& source) const
    {
        int Force=0;
        Force = k*((Q2*C)/pow(GetDistance(source),2));
        return Force;
    }
    double Physics::math_CalculateEField(const math_point& source) const
    {
        return (k*(C))/pow(GetDistance(source), 2);
    }
    double Physics::math_CalculateEField(int ForceCount) const//The difference is that this functions plays on the relationship between force on electric field. This function can only get the electric field produced by a single-point charged particle.
    {
        return ((double)(ForceCount))/C;
    }

    double Physics::math_CalculateForceFromMagneticField(std::string MagneticField, double magnitude) const
    {
        if(MagneticField == "out" )
        {
            return -1 * C * velocityY * magnitude;
        }
        if(MagneticField == "in")
        {
            return C * velocityY * magnitude;
        }
}

    void Physics::math_CalculateMomentum(Physics *actor, Physics *target) const
    {
        double tmpVA, tmpVB = 0;
        //X axis
        tmpVA = actor->GetVelocity('x');
        tmpVB = target->GetVelocity('x');
        actor->SetVelocity(tmpVB, 'x');
        target->SetVelocity(tmpVA, 'x');

        //Y axis
        tmpVA = actor->GetVelocity('y');
        tmpVB = target->GetVelocity('y');
        actor->SetVelocity(tmpVB, 'y');
        target->SetVelocity(tmpVA, 'y');
    }

    //Get & Set functions
    math_point Physics::GetLoc() const
    {
        return loc;
    }

    double Physics::GetVelocity(const char axis) const
    {
        if(axis == 'x')
        {
            return velocityX;
        }
        return velocityY;
    }

    void Physics::SetVelocity(double velocity, const char axis)
    {
        if(axis == 'x')
        {
            velocityX = velocity;
        }
        else
        {
            velocityY = velocity;
        }
    }

    double Physics::GetElasticity() const
    {
        return elasticity;
    }

    double Physics::GetForceCount(const char axis) const
    {
        if(axis == 'x')
        {
            return ForceCountX;
        }
        return ForceCountY;
    }
    void Physics::SetForceCount(int force, const char axis)
    {
        if(axis == 'x')
        {
            ForceCountX = force;
        }
        else if(axis == 'y')
        {
            ForceCountY = force;
        }
        else
        {
            SetForceCount((double)force, axis);
        }
    }
    void Physics::SetForceCount(double force, const char axis)
    {
        if(axis == 'x')
        {
            ForceCountX = (int)force;
        }
        else if(axis == 'y')
        {
            ForceCountY = (int)force;
        }
        else if(axis == 'a')
        {
            //When the axis is a (aka all), I randomly generate the proportions of force assigned to each axis
            float multiplier;
            //This is saying I generate a random number from 0 to 100, which divided by 100 gives me proportionality
            //constant.
            multiplier = randNormal(Range(0, 100)) / 100.0f;
            ForceCountX = (int)(force * multiplier);
            ForceCountY = (int)(force * (1 - multiplier));
        }
    }
    void Physics::AddForce(double force, const char axis)
    {
        if(axis == 'x')
        {
            ForceCountX += force;
        }
        else
        {
            ForceCountY += force;
        }
    }
    double Physics::GetMU() const
    {
        return mu;
    }
    void Physics::ChangePlanetGravitationalConstant(double G)//Although I defined g as Earth gravity, I want to keep the engine as flexible as possible so I want to give a way to redefine g for other worlds :).
    {
        g = G;
    }

    double Physics::GetGravity() const
    {
        return g;
    }

    double Physics::GetCharge() const
    {
        return C;
    }

    double Physics::GetMass() const
    {
        return mass;
    }

    Physics::Physics(const char* location)
    {
         g = 9.80;
         Load_Physics(location);
    }

     void Physics::rel_CalculateForce(const char axis, bool relativity)
    {
        if(relativity==true)
        {
            if(axis == 'x')
            {
                ForceCountX = Relativity(axis)*NewtonianForce(axis);
            }
            ForceCountY = Relativity(axis)*NewtonianForce(axis);
        }
        else
        {
            if(axis == 'x')
            {
                ForceCountX = NewtonianForce(axis);
            }
            ForceCountY = NewtonianForce(axis);
        }
    }

    void Physics::SetLoc(const math_point& pos)
    {
        loc = pos;
    }

    size_t CalculateDistance(const math_point& A, const math_point& B)
    {
        return (size_t)sqrt((pow((double)(A.Y-B.Y),2))+(pow((double)(A.X-B.X),2)));
    }


//End of namespace macro
//ENGINE_NAMESPACE_END
