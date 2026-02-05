#include "Hexapod.h"
#include "defines.h"

#include <stdio.h>
#include <math.h>

bool Hexapod::init()
{
    // ----- LEG DEFINITIONS -----
    // -- 1) DH matrix
    // DH matrix setup on : 
    // https://tools.glowbuzzer.com/kinviz
    // Link     αi      θi      θ offset  ai      di      d offset    Joint Type  Min. travel Max. travel
    // Link     a_i     angle   alpha_i   length  offset  d_offset    type        min_travel  max_travel
    // 0        -1.57   0       0         38.0    0       0           revolute    -1.57       1.57
    // 1        0.0     0       0         86.25   0       0           revolute    -1.57       1.57
    // 2        0.0     0       1.57      160.0   0       0           revolute    -1.57       1.57

    // 1 - Length
    // 2 - Rotation in the Z axis to reach next joint rotation axis
    // 3 - Angle offset for the 0° position
    // 4 - Default joint rotation
    dh_leg <<
        LIMB_LENGTH_PART1,  -M_PI/2, 0.0,       0,  // Coxia
        LIMB_LENGTH_PART2,  0.0,     0.0,       0,  // Femur
        LIMB_LENGTH_PART3,  0.0,     M_PI/2,    0   // Tibia
    ;

    // -- 2) Link types
    // All revolute joints, servos revolves, duh
    leg_link_types << 
        quik::JOINT_REVOLUTE,
        quik::JOINT_REVOLUTE,
        quik::JOINT_REVOLUTE
    ;

    // -- 3) Joint sign directions
    leg_joint_directions << 
        1,
        1,
        1
    ;

    // -- 4) Tool transform  : position of the tool at the end of the limb, no tool here so empty
    tool_transform = Matrix4d::Identity(4, 4);

    // Identity : https://libeigen.gitlab.io/eigen/docs-nightly/classEigen_1_1MatrixBase.html#acf33ce20ef03ead47cb3dbcd5f416ede
    // Fill the matrix with 0 and put 1s in the diagonal
    // Here it'll fill with : 
    // 1 0 0 0
    // 0 1 0 0
    // 0 0 1 0
    // 0 0 0 1

    // -- 5) Base transforms : starting point of each leg
    // 5.1) Setup matrices
    for (int i = 0; i < LIMB_COUNT; i++)
        base_transforms[i] = Matrix4d::Identity(4, 4);

    // 5.2) Fill matrices with correct positions
    // X+ = forward
    // Y+ = left
    // Z+ = up, all joint are on the same plan so 0
    // Rotation+ = going from X+ to Y+ : counter clockwise related to robot front
    // Leg 0 : Right front
    // X = +101mm   | Y = -57mm     | Z = 0 |   -30°
    fillBaseTransform(0, 57, 101, 0, -30);
    // Leg 1 : Right middle
    // X = 0mm      | Y = -105.5mm  | Z = 0 |   -90°
    fillBaseTransform(1, 105, 0, 0, -90);
    // Leg 2 : Right back
    // X = -101mm   | Y = -57mm     | Z = 0 |   -120°
    fillBaseTransform(2, 57, -101, 0, -120);
    // Leg 3 : Left front
    // X = +101mm   | Y = +57mm     | Z = 0 |   +30°
    fillBaseTransform(3, -57, 101, 0, 30);
    // Leg 4 : Left middle
    // X = 0mm      | Y = +105.5mm  | Z = 0 |   +90°
    fillBaseTransform(4, -105, 0, 0, 90);
    // Leg 5 : Left back
    // X = -101mm   | Y = +57mm     | Z = 0 |   +120°
    fillBaseTransform(5, -57, -101, 0, 120);

    //6) Build the legs using all the datas we setup
    for (int i = 0; i < LIMB_COUNT; i++)
    {
        /* Limb pins : 
            - Board 1 : 0-5  = first joints
            - Board 1 : 8-13 = second joints
            - Board 2 : 0-6  = third joints
        */
        limbs[i].addJoint(BOARD1_PIN_BASE + 0 + i, LIMB_LENGTH_PART1, LIMB_JOINT1_ANGLE, 5.0f, 85.0f);
        limbs[i].addJoint(BOARD1_PIN_BASE + 8 + i, LIMB_LENGTH_PART2, LIMB_JOINT2_ANGLE, 5.0f, 85.0f);
        limbs[i].addJoint(BOARD2_PIN_BASE + 0 + i, LIMB_LENGTH_PART3, LIMB_JOINT3_ANGLE, 5.0f, 85.0f);
        // quik setup
        limbs[i].setupRobot(dh_leg, leg_link_types, leg_joint_directions, base_transforms[i], tool_transform);

        // init servos
        if (!limbs[i].init())
        {
            #ifdef DEBUG
                cout << "[ERROR] - Error while setting up limb " << i << endl;
            #endif
            limbs[i].printAngles();
            return false;
        }
    }

    return true;
}

void Hexapod::fillBaseTransform(int leg_index, double x, double y, double z, double rotation)
{
    if (leg_index < 0 || leg_index >= LIMB_COUNT)
        return;

    // 1) Fill position
    base_transforms[leg_index](0,3) =  x;
    base_transforms[leg_index](1,3) =  y;
    base_transforms[leg_index](2,3) =  z;

    // 2) Fill rotation
    // Rotation about Z (leg mounting angle)
    base_transforms[leg_index].block<3,3>(0,0) = Eigen::AngleAxisd(DEG_TO_RAD(rotation), Eigen::Vector3d::UnitZ()).toRotationMatrix();
}

Limb* Hexapod::getLimb(int index)
{
    if (index < 0 || index >= LIMB_COUNT)
        return NULL;

    return &limbs[index];
}