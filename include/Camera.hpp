
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MY_CAMERA
{

    constexpr glm::vec3 FRONT = glm::vec3(1,0,0);
    constexpr glm::vec3 UP = glm::vec3(0,1,0);
    constexpr glm::vec3 RIGHT = glm::vec3(0,0,1);

    class Camera
    {
        private:
            typedef glm::vec3 vec;
            vec cameraPos;
            vec cameraFront;
            vec cameraUp;
            vec cameraRight;
            vec worldUp;
            float yaw;
            float pitch;
            /**
             * @brief 
             * update camera vectors
             */
            void updateCameraVectors()
            {
                vec front;
                front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                front.y = sin(glm::radians(pitch));
                front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraFront = glm::normalize(front);
                cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
                cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
            }
        public:
            Camera(vec position = vec(0,0,0))
            {
                worldUp = vec(0,1,0);
                cameraPos = position;
                yaw = -90.0f;
                pitch = 0.0f;
                updateCameraVectors();
            }
            glm::mat4 getLookAt()const
            {
                return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            }
            void ProcessKeyBorad(vec localDirection ,float speed)
            {
                localDirection*=speed;
                //从局部坐标转换为世界坐标
                cameraPos = cameraPos+localDirection.x*cameraFront+localDirection.y*worldUp+localDirection.z*cameraRight;
                updateCameraVectors();
            }

            void ProcessMouse(glm::vec2 offset)
            {
                yaw +=offset.x;
                pitch +=offset.y;

                if(pitch>89.0f)pitch = 89.0f;
                if(pitch< -89.0f)pitch = -89.0f;
                updateCameraVectors();
            }
    };
}