#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Camera
    {
    public:
        Camera()
        {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            Set(position, center, up);
        }

        ~Camera()
        { }

        // Update camera
        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            // Translates the camera using the `dir` vector computed from
            // `forward`. Movement will always keep the camera at the same
            // height. For example, if you rotate your head up/down, and then
            // walk forward, then you will still keep the same relative
            // distance (height) to the ground!
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            // TODO(student): Translate the camera using the `forward` vector.
            // What's the difference between `TranslateForward()` and
            // `MoveForward()`?
            position += glm::normalize(forward) * distance;

        }

        void TranslateUpward(float distance)
        {
            // TODO(student): Translate the camera using the `up` vector.
            position += glm::normalize(up) * distance;
        }

        void TranslateRight(float distance)
        {
            // TODO(student): See instructions below. Read the entire thing!
            // You need to translate the camera using the `right` vector.
            // Usually, however, translation using camera's `right` vector
            // is not very useful, because if the camera is rotated around the
            // `forward` vector, then the translation on the `right` direction
            // will have an undesired effect, more precisely, the camera will
            // get closer or farther from the ground. The solution is to
            // actually use the projected `right` vector (projected onto the
            // ground plane), which makes more sense because we will keep the
            // same distance from the ground plane.
            // Project the right vector onto the XZ plane to maintain constant height
            glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
            position += dir * distance;

        }

        void RotateFirstPerson_OX(float angle)
        {
            // TODO(student): Compute the new `forward` and `up` vectors.
            // Don't forget to normalize the vectors! Use `glm::rotate()`.
            // Create a rotation matrix that rotates around the local X-axis (right vector)
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, right);

            // Apply the rotation matrix to the forward and up vectors
            forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(forward, 0.0f)));
            up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 0.0f)));
        }

        void RotateFirstPerson_OY(float angle)
        {
            // TODO(student): Compute the new `forward`, `up` and `right`
            // vectors. Use `glm::rotate()`. Don't forget to normalize the
            // vectors!
            // Create a rotation matrix that rotates around the world Y-axis
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));

            // Apply the rotation matrix to the forward and right vectors
            forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(forward, 0.0f)));
            right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(right, 0.0f)));

            // Recalculate the up vector to ensure it remains perpendicular
            up = glm::normalize(glm::cross(right, forward));

        }

        void RotateFirstPerson_OZ(float angle)
        {
            // TODO(student): Compute the new `right` and `up`. This time,
            // `forward` stays the same. Use `glm::rotate()`. Don't forget
            // to normalize the vectors!
            // Create a rotation matrix that rotates around the forward (Z-axis) vector
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, forward);

            // Apply the rotation matrix to the right and up vectors
            right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(right, 0.0f)));
            up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 0.0f)));
        }

        void RotateThirdPerson_OX(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OX axis. Use `distanceToTarget` as translation distance.
            // Step 1: Translate the camera to the origin (around the target point)
            position += forward * distanceToTarget;

            // Step 2: Create a rotation matrix to rotate around the local X-axis (right vector)
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, right);

            // Step 3: Apply the rotation matrix to the forward and up vectors
            forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(forward, 0.0f)));
            up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 0.0f)));

            // Step 4: Update the camera position based on the new forward vector and distance to the target
            position = position - forward * distanceToTarget;
        }

        void RotateThirdPerson_OY(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OY axis.
            // Step 1: Translate the camera to the origin (around the target point)
            position += forward * distanceToTarget;

            // Step 2: Create a rotation matrix to rotate around the global Y-axis
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));

            // Step 3: Apply the rotation matrix to the forward and right vectors
            forward = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(forward, 0.0f)));
            right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(right, 0.0f)));

            // Step 4: Recalculate the up vector to maintain perpendicularity
            up = glm::normalize(glm::cross(right, forward));

            // Step 5: Update the camera position to maintain the distance to the target
            position = position - forward * distanceToTarget;

        }

        void RotateThirdPerson_OZ(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OZ axis.
            // Step 1: Translate the camera to the origin (around the target point)
            position += forward * distanceToTarget;

            // Step 2: Create a rotation matrix to rotate around the local Z-axis
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, forward);

            // Step 3: Apply the rotation matrix to the up and right vectors
            up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(up, 0.0f)));
            right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(right, 0.0f)));

            // Step 4: Update the camera position to maintain the distance to the target
            position = position - forward * distanceToTarget;
        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }
        void Camera::RotateAroundDrone(float deltaYaw, glm ::vec3 dronePosition)
        {
            glm::vec3 relativePosition = position - dronePosition;
            glm::mat4 rotationMatrix = glm::mat4(1.0f);
            rotationMatrix = glm::rotate(rotationMatrix, deltaYaw, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 rotatedPosition = glm::vec3(rotationMatrix * glm::vec4(relativePosition, 1.0f));
            position = dronePosition + rotatedPosition;
            glm::vec3 relativeForward = forward;
            glm::vec3 rotatedForward = glm::vec3(rotationMatrix * glm::vec4(relativeForward, 0.0f));
            forward = rotatedForward;
            right = glm::normalize(glm::cross(up, forward));
            up = glm::normalize(glm::cross(forward, right));
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
        float yaw = 0;
        float pitch = 0;
    };
}   // namespace implemented
