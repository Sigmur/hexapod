#ifndef HEXAPOD_H
#define HEXAPOD_H

#include <iostream>
#include <stdlib.h>
#include "Eigen/Dense"
#include "quik/geometry.hpp"
#include "quik/Robot.hpp"
#include "quik/IKSolver.hpp"
#include "Limb.h"
#include "defines.h"

using namespace std;
using namespace Eigen;

class Hexapod
{
    private:
        // quik datas
        Matrix<double, LIMB_DOF, 4> dh_leg;
        Vector<quik::JOINTTYPE_t, LIMB_DOF> leg_link_types;
        Vector<double, 3> leg_joint_directions;
        Matrix4d tool_transform;
        Matrix4d base_transforms[LIMB_COUNT];
        // other
        Limb limbs[6];

        void fillBaseTransform(int leg_index, double x, double y, double z, double rotation);

    public:
        Hexapod() {};
        bool init();
        Limb* getLimb(int index);
};

#endif