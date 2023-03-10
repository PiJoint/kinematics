#ifndef UTILS_HPP
#define UTILS_HPP


#include <Eigen/Dense>

typedef Eigen::Matrix<double, 4, 4> SE3;
typedef Eigen::Matrix<double, 3, 3> SO3;
typedef Eigen::Matrix<double, 2, 1> VEC2;
typedef Eigen::Matrix<double, 3, 1> VEC3;
typedef Eigen::Matrix<double, 6, 1> VEC6;
typedef Eigen::Matrix<double, 9, 1> VEC9;
typedef Eigen::Matrix<double, 2, 2> MAT2;
typedef Eigen::Matrix<double, 6, 6> MAT6;
typedef Eigen::Matrix<double, 3, 6> MAT36;
typedef Eigen::Matrix<double, 6, 3> MAT63;

MAT2 rotMatrix2D(double th);

class SE3Operations{
    public:
        static SE3 Rx(double th);
        static SE3 Ry(double th);
        static SE3 Rz(double th);
        static SE3 Tx(double d);
        static SE3 Ty(double d);
        static SE3 Tz(double d);
        static SO3 ro(SE3 T);
        static VEC3 tau(SE3 T);
        static VEC3 rotmToAngleAxis(SO3 R);
        static VEC6 to6D(SE3 v);
         /**
         * @brief Get the Gripper Pose object 
         * 
         * @param pose 
         * @param yaw 
         * @return SE3 
         */
        static SE3 getGripperPose(VEC3 pose, double yaw);
};

class LM{
    public:
        /**
         * @brief Parameters for the Levenberg-Marquardt algorithm.
        */

        static constexpr double lambda = 0.01;
        static constexpr int maxIterations = 500;
        static constexpr double errTresh = 0.001;

        /**
         * @brief Computes the error vector between the desired and
         * current end-effector poses.
         * @param T_curr the current end-effector pose.
         * @param T_des The desired end-effector pose
        */
        static VEC6 error(SE3 &T_curr, SE3 &T_des);

        /**
         * @brief Computes the gk term, which represents the direction
         * of the update for the joint configuration.
         * @param J the jacobian matrix of the robot.
         * @param e the current error between the desired and current
         * end-effector poses.
        */
        static VEC6 gk(Eigen::Matrix<double, 6, 6> &J, VEC6 &e);

        /**
         * @brief Computes the Ak matrix, which drives the update of
         * the joint configuration.
         * @param robot The robot.
         * @param E the current error between the desired and current
         * end-effector poses.
        */
        static Eigen::Matrix<double, 6, 6> Ak(Eigen::Matrix<double, 6, 6> &J, double E);

};

#endif