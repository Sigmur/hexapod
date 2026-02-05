#ifndef LIMB_H
#define LIMB_H

#include <iostream>
#include <memory>
#include "Eigen/Dense"
#include "quik/Robot.hpp"
#include "quik/IKSolver.hpp"
#include "defines.h"
#include "Joint.h"

using namespace Eigen;

class Limb
{
    private:
        int joint_count;
        Joint* joints[LIMB_DOF];

        // This is the quik representation of the limb
        // a "Robot" is quik is a full chain of joint, not multiple chains
        // so we need one robot pert limb to compute the kinematics
        // think of quik::Robot as a robot arm that has a base and a tool, not as a robot dog
        std::shared_ptr<quik::Robot<LIMB_DOF>> robot;
        // This solves the inverse kinematics for our loaded robot object
        std::unique_ptr<quik::IKSolver<LIMB_DOF>> inverse_kinematic_solver;
        // Current joint angles
        Matrix<double, LIMB_DOF, 1> current_angles;

    public:
        Limb() {};
        bool init();

        // ----- Joint
        Joint* addJoint(int pin = DEFAULT_JOINT_PIN, float length = 0.0f, float home_angle = 90.0f, float min_angle = 0.0f, float max_angle = 180.0f);
        Joint* addJoint(int pin = DEFAULT_JOINT_PIN);
        Joint* getJoint(int index);
        int getJointCount();
        bool hasJoints();
        bool hasJoint(int index);

        // ----- Geometry
        bool setupRobot(Array<double,LIMB_DOF,4> _DH, Vector<quik::JOINTTYPE_t,LIMB_DOF> _linkTypes, Vector<double,LIMB_DOF> _Qsign, Matrix4d _Tbase, Matrix4d _Ttool);
        bool setEndTarget(double x, double y, double z);
        void printAngles();
};

#endif