#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/lab5/lab_camera.h"
#include "lab_extra/basic_text/basic_text.h"
#include "random"
#include "math.h"
#include "SDL.h"
#include "SDL_mixer.h"

namespace m1
{
    class Lab7 : public gfxc::SimpleScene
    {
     public:
        Lab7();
        ~Lab7();
        struct BoundingBox {
            glm::vec3 max;
            glm::vec3 min;
        };
        struct checkPoint {
            glm::vec3 checkPointPos;
            std::vector<BoundingBox> checkPointsBoxes;
            int state;
        };
        struct ViewPortArea {
            ViewPortArea() : x(0), y(0), width(1), height(1) {}
            ViewPortArea(int x,int y,int width,int height) :
                x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        void Init() override;
        GLuint vertex_height_buffer;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, implemented::Camera* cam, const glm::vec3 &color = glm::vec3(1), int garbage = 0);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void InitTerrain();
        void InitAfter();
        void PrepareBlade(glm::mat4& modelMatrix, float deltaTimeSeconds, float& rotateX, glm::vec3 updatedX);
        void UpdateBlades(glm::mat4 modelMatrix);
        void createRandomPos();
        int intersect(BoundingBox box);
        void createRandomHouses();
        void createRandomCheckPoints();
        void createCheckPoints(glm::vec3 color, char name[100]);
        void RenderScene(float deltaTimeSeconds, implemented::Camera* currentCamera);
        void PrintText();

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        implemented::Camera* camera;
        implemented::Camera* camera_minimap;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float fov = 60.0f;
        float aspectRatio;
        float nearPlane = 0.01f;
        float farPlane = 200.0f;
        
        float orthoLeft = -16.f;
        float orthoRight = 16.f;
        float orthoBottom = -9.f;
        float orthoTop = 9.f;

        float dronePozX = 0;
        float dronePozY = 1.5;
        float dronePozZ = 0;
        float rotationAngle = 0;
        float pitchtAngle = 0;
        float pitchForce = 10.0f;
        float yawForce = 10.0f;
        float yawAngle = 0.0f;
        float rotateOz = 0;
        int weirdVar = 0;
        int lost = 0;
        std::vector<glm::vec3> updatedX{4};
        std::vector<glm::vec3> middleX = {glm::vec3(0.7667, 0.401, 0.7667), glm::vec3(-0.7667,0.401,0.7667), glm::vec3(0.7667,0.401,-0.7667), glm::vec3(-0.7667, 0.401, -0.7667)};
        glm::vec3 forward = glm::vec3(0);
        glm::vec3 right = glm::vec3(0);
        glm::vec3 up = glm::vec3(0);
        glm::vec3 firstPerson = glm::vec3(-1.2, 2.5, 0);
        glm::vec3 firstPersonOrientation = glm::vec3(0, 2.5, 0);
        std::vector<BoundingBox> treeBox;
        std::vector<glm::vec3> treePos;
        std::vector<glm::vec3> treeScale;
        std::vector<glm::vec3> housePos;
        std::vector<glm::vec3> checkPointPos;
        std::vector<std::vector<BoundingBox>> checkPointsBoxes;
        std::vector<checkPoint> points;
        std::vector<BoundingBox> houseBox;
        std::vector<float> rotateRand;
        float rotateOne = 0;
        int checkPopulation[330][330] = { 0 };
        float speed = 12;
        float acceleration = 0.05;
        gfxc::TextRenderer* textRenderer;
        int currentCheckPoint = 0;
        ViewPortArea miniMap;
        Mix_Music* theme;
        Mix_Chunk* passCheck;
        Mix_Chunk* droneFly;
        Mix_Chunk* victory;
        Mix_Chunk* lostS;
        Mix_Chunk* hitTree;
        Mix_Chunk* hitWall;
        Mix_Chunk* hitCheck;

        glm::vec3 thirdPerson = glm::vec3(-4, 3, 0);
        glm::vec3 thirdPersonOrientation = glm::vec3(0, 3, 0);
        int cameraMode = 0;

        bool Perspective = true;
    };
}   // namespace m1
