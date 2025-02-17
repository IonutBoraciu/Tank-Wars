#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab1/Tank.h"
#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
#include "lab_m1/lab1/initType.h"

namespace m1
{
 class Tema1 : public gfxc::SimpleScene
 {
 public:
  Tema1();
  ~Tema1();

  void Init() override;
  friend class Tank;
  friend class Letters;

 private:
  void FrameStart() override;
  void Update(float deltaTimeSeconds) override;
  void FrameEnd() override;

  void OnInputUpdate(float deltaTime, int mods) override;
  void OnKeyPress(int key, int mods) override;
  void OnKeyRelease(int key, int mods) override;
  void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
  void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
  void OnWindowResize(int width, int height) override;

  void initTerrain(char name[100]);
  bool checkIntersection();
  void updateProjectiles(int tankPoz, float deltaTimeSeconds);
  void updateTerrain(float deltaTimeSeconds);
  void explodeTerrain(float rotatedX, float rotatedY);
  void updateMesh(char name[100], std::vector<VertexFormat> vertices, std::vector<unsigned int> indices);
  int checkUpdateTerrain();
  void playTankWalk(int tankPoz);
  void playTurret(int tankPoz);
  void createCloud();
  void updateClouds(float deltaTimeSeconds);
  void createSphere(std::vector<VertexFormat>& vertices, std::vector<unsigned int>& indices, int &offset, float centerX, float centerY, float radius);
  void reInit();
  void updateScore();
  void displayNumber(int width, int number,int mode);
 protected:
	 int widthScreen;
	 int heightScreen;
	 Tank* tanks[10] = { nullptr };

	 Mix_Chunk* tankWalk;
	 Mix_Chunk* tankWalkDamaged;
	 Mix_Chunk* turretRotate;
	 Mix_Chunk* tankExplosion;
	 Mix_Chunk* turretFire;
	 Mix_Chunk* readyFight;
	 Mix_Chunk* victory;
	 Mix_Music* theme;
	 std::vector<float> cloudXPos;
	 std::vector<float> cloudSpeed;
  // TODO(student): If you need any other class variables, define them here.

 };
}   // namespace m1
#pragma once
