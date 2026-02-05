#include "Limb.h"
#include "Joint.h"
#include "defines.h"
#include "Eigen/Dense"
#include <math.h>

#include <stdio.h>

using namespace std;
using namespace Eigen;

bool Limb::init()
{
    // 1) Check consistency
    if (!hasJoints())
    {
        #ifdef DEBUG
            cout << "[ERROR] - Error while setting up limb : no joint specified." << endl;
        #endif
        return false; // No joint setup
    }

    // 3) Move servos to base joint orientations
    for (int i = 0; i < joint_count; i++)
    {
        if (!joints[i]->init())
        {
            #ifdef DEBUG
                cout << "[ERROR] - Error while setting up joint " << i << endl;
            #endif
            return false;
        }
    }

    return true;
}

// ------

Joint* Limb::addJoint(int pin, float length, float home_angle, float min_angle, float max_angle)
{
    // 1) Check if we have enough space for more joints
    if (joint_count == LIMB_DOF)
        return NULL; // -1 is invalid joint index, meaning none was added

    // 2) Init the joint
    Joint* joint = new Joint(pin, length, home_angle, min_angle, max_angle);
    if (!joint) // Could not init the joint properly
        return NULL;

    // 3) Add the joint to the limb
    joints[joint_count++] = joint;

    return joint;
}

int Limb::getJointCount()
{
    return joint_count;
}

Joint* Limb::getJoint(int index)
{
    if (!hasJoint(index))
        return NULL;
    return joints[index];
}

bool Limb::hasJoints()
{
    return joint_count > 0;
}

bool Limb::hasJoint(int index)
{
    return (index >= 0 && index < joint_count);
}

bool Limb::setupRobot(Array<double, LIMB_DOF,4> _DH, Vector<quik::JOINTTYPE_t, LIMB_DOF> _linkTypes, Vector<double, LIMB_DOF> _Qsign, Matrix4d _Tbase, Matrix4d _Ttool)
{
    current_angles.setZero();

    robot = std::make_unique<quik::Robot<LIMB_DOF>>(_DH, _linkTypes, _Qsign, _Tbase, _Ttool);
    if (!robot)
        return false;

    inverse_kinematic_solver = std::make_unique<quik::IKSolver<LIMB_DOF>>(robot);
    if (!inverse_kinematic_solver)
        return false;

    return true;
}

bool Limb::setEndTarget(double x, double y, double z)
{ // Set a new target for the end of the limb to be resolved using IK
    // 1) Reset target solving matrix
    Matrix4d target = Matrix4d::Identity();
    target(0,3) = x;
    target(1,3) = y;
    target(2,3) = z;

    // 2) Load current joint angles
    /* TODO
    for (int i = 0; i < LIMB_DOF; i++)
    {
        current_angles(0, i) = (double)DEG_TO_RAD(getJoint(i)->angle);
    }
    */

    // 3) Init other datas for the solver
    Matrix<double, LIMB_DOF, 1> Q0 = current_angles;
    Matrix<double, LIMB_DOF, 1> q_star;
    Matrix<double, 6, 1> e_star;        // Error at solver pose
    int iter;                           // Number of iterations
    quik::BREAKREASON_t br;             // Break out reason
    
    // 4) Compute the inverse kinematics
    inverse_kinematic_solver->IK(target, Q0, q_star, e_star, iter, br);
    if (br != quik::BREAKREASON_TOLERANCE)
        return false; // Failed if not within tolerance

    // 5) Set the newly found angles as target for each servos
    for (int i; i < LIMB_DOF; i++)
    {
        // TODO
        // - use setTarget instead of setAngle
        joints[i]->setAngle((float)RAD_TO_DEG(q_star(i)));
    }

    return true;
}

void Limb::printAngles()
{
    cout << "Print leg angles : " << endl;
    for (int i = 0; i < LIMB_DOF; i++)
        cout << i << " : " << joints[i]->angle << endl;
}
