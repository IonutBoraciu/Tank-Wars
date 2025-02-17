#pragma once
#include "lab_m1/lab1/Tema1.h"
#include "components/simple_scene.h"
#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
using namespace std;
namespace m1 {
	class Tank : public gfxc::SimpleScene {

	public:
		Tank(glm::vec3 lower, glm::vec3 upper, char tankName[100], char cannon[100], class Tema1* tema1, int pozTankX, float rotAngle, char projectile[100], char lifeName[100]);
		~Tank();
		friend class Tema1;
	protected:
		struct projectile {
			glm::vec2 speed;
			glm::vec2 poz;
			float angleProj;
		};
		float tankX;
		float tankY;
		int domeCenterX;
		int domeCenterY;
		float angle;
		vector<VertexFormat> verticesT;
		vector<unsigned int> indicesT;
		vector<VertexFormat> verticesC;
		vector<unsigned int> indicesC;
		float rotateAngle;
		int widthTank;
		int heightTank;
		glm::vec2 speed;
		glm::vec2 poz;
		float angleProj;
		int life;
		int triangleXLife;
		char lifeName[100];
		vector <projectile> projectiles;
		char trajName[100];
		static int widthScreenTank;
		float amplitude;
		float speedTank;

		int tankWalkChannel;
		int turretRotateChannel;
		int tankExplodeChannel;

		glm::vec3 color;

	private:
		void initVeticesTank(glm::vec3 lower, glm::vec3 upper);
		void initIndicesTank();
		void initDomeTank(glm::vec3 upper);
		void updateTank(vector<float> height);
		void initCannon(class Tema1* tema1, char cannonName[100]);
		void initProjectile(char projectile[100], class Tema1* tema1);
		void addProjectile(glm::vec2 speed, glm::vec2 poz, float angle);
		static void CreateLifeBar(class Tema1* tema1);
		void CreateLife(class Tema1* tema1, char name[100]);
		void UpdateLife(class Tema1* tema1);
		void UpdateTrajectory(vector<float> height, class Tema1* tema1);
	};

}

