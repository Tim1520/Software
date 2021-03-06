#pragma once

#include <ros/ros.h>
#include <string>
#include <vector>
#include "thunderbots_msgs/Primitive.h"

/**
 * Defines a Robot Primitive, which is the most basic action / unit of work a robot can
 * do. For example, moving straight to a point, pivoting around a point,
 * or shooting the ball at a target.
 *
 * This is an Abstract, pure-virtual class. It is meant to define the interface that all
 * Primitives must follow.
 * Other classes should inherit from this class and implement the methods to create a
 * useable Primitive class.
 */
class Primitive
{
   public:
    /**
     * Creates a Primitive message from this Primitive
     *
     * @return The Primitive message containing the information from this Primitive
     */
    thunderbots_msgs::Primitive createMsg() const;

    /**
     * Returns the name of the Primitive
     *
     * @return The name of the Primitive as a string
     */
    virtual std::string getPrimitiveName() const = 0;

    /**
     * Returns the ID of the robot that this Primitive corresponds
     * to / is controlling
     *
     * @return The ID of the robot this Primitive is controlling
     */
    virtual unsigned int getRobotId() const = 0;

    /**
     * Returns the generic array of parameters for this Primitive
     *
     * @return A vector of doubles that are the generic parameters for this Primitive
     */
    virtual std::vector<double> getParameterArray() const = 0;

    /**
     * Returns the generic array of Booleans, that represent the extra bits used by
     * the Primitive. These extra bits are typically used to toggle behaviour of the
     * Primitive, such as if the kicker or chipper should be used, or if autokick
     * should be enabled.
     *
     * @return A vector of Booleans that are the extra bits used by the Primitive.
     */
    virtual std::vector<bool> getExtraBitArray() const = 0;

    /**
     * Validates that a primitive message is compatible with the primitive
     * specified by name, and throws an exception if the validation check fails.
     *
     * @param prim_msg The primitive message
     * @param prim_name The name of the primitive
     * @throws //TODO: Add exception
     */
    void validatePrimitiveMessage(const thunderbots_msgs::Primitive& prim_msg,
                                  std::string prim_name) const;

    /**
     * Given a ROS Primitive message, constructs a concrete Primitive object and returns
     * a unique_ptr using the Abstract Primitive interface. This acts like a Primitive
     * factory.
     *
     * @param primitive_msg the Primitive message from which to construct the Primitive
     * @return a unique_ptr to a Primitive object
     */
    static std::unique_ptr<Primitive> createPrimitive(
        const thunderbots_msgs::Primitive& primitive_msg);

    virtual ~Primitive() = default;
};
