#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "lab_m1/lab1/Tema1.h"
#include "lab_m1/lab1/Tank.h"
// for choosing an icon for the game
#include <stb/stb_image.h>
#include "core/window/window_object.h"
using namespace std;
using namespace m1;
int m1::Tank::widthScreenTank;
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

vector<float> height;
float rotateAngle = 100;
int updateSurface = 0;
int tankWalkChannel2;
int SCORE_TANK0;
int SCORE_TANK1;
int ONCE_PER_RUN = 1;

struct garbage {
	int numberOfTimes;
	int start;
	int end;
};
vector<garbage> garb;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
	Mix_HaltChannel(tanks[0]->tankWalkChannel);
	Mix_HaltChannel(tanks[1]->tankWalkChannel);
	Mix_FreeChunk(tankWalk);
	Mix_FreeChunk(tankWalkDamaged);
	Mix_HaltChannel(tanks[0]->turretRotateChannel);
	Mix_HaltChannel(tanks[1]->turretRotateChannel);
	Mix_FreeChunk(turretRotate);
	Mix_FreeChunk(tankExplosion);
	Mix_FreeChunk(readyFight);
	Mix_HaltMusic();  // Stops any playing music
	Mix_FreeMusic(theme);  // Free the music resource
}

float generateFunction(int x) {
	float fct = 60 * sin(0.005 * x) + 30 * sin(0.03 * x) + 20 * sin(0.02 * x) + 300;
	return fct;
}
void Tema1::createSphere(vector<VertexFormat> &vertices, vector<unsigned int> &indices,int &offset, float centerX, float centerY,float radius) {
	float angleStep = 2 * M_PI / 30;
	int poz = 0;
	for (int i = 0; i < 31; i++) {
		float angle = i * angleStep;
		float x = centerX + radius * cos(angle);
		float y = centerY + radius * sin(angle);
		if (y < 0) {
			continue;
		}
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), glm::vec3(1, 1, 1)));
		if (i != 0) {
			poz++;
			indices.push_back(offset - 1);
			indices.push_back(offset + poz - 1);
			indices.push_back(offset + poz);

		}
	}
	offset += poz + 1;
}
void Tema1::createCloud() {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;

	vertices.push_back(VertexFormat(glm::vec3(16,12.8,0),glm::vec3(1,1,1)));
	int offset = 1;
	createSphere(vertices, indices, offset, 16, 12.8, 16.2);
	vertices.push_back(VertexFormat(glm::vec3(40, 20, 0), glm::vec3(1, 1, 1)));
	offset++;
	createSphere(vertices, indices, offset, 40, 20, 21.3);
	vertices.push_back(VertexFormat(glm::vec3(66.5, 13.5, 0), glm::vec3(1, 1, 1)));
	offset++;
	createSphere(vertices, indices, offset, 66.5, 13.5, 17);
	
	vertices.push_back(VertexFormat(glm::vec3(6, 0, 0), glm::vec3(1, 1, 1))); // I offset
	vertices.push_back(VertexFormat(glm::vec3(6, 5, 0), glm::vec3(1, 1, 1))); // J + 1
	vertices.push_back(VertexFormat(glm::vec3(77, 5, 0), glm::vec3(1, 1, 1))); // H + 2
	vertices.push_back(VertexFormat(glm::vec3(77, 0, 0), glm::vec3(1, 1, 1))); // G + 3

	indices.push_back(offset);
	indices.push_back(offset + 1);
	indices.push_back(offset + 2);

	indices.push_back(offset);
	indices.push_back(offset + 3);
	indices.push_back(offset + 2);


	Mesh* mesh = new Mesh("cloud");
	mesh->InitFromData(vertices, indices);
	AddMeshToList(mesh);

}

void Tema1::initTerrain(char name[100]) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	for (int i = 0; i < height.size(); i++) {
		vertices.push_back(VertexFormat(glm::vec3(i, height[i], 0), glm::vec3(0.54, 0.6, 0.35)));
		vertices.push_back(VertexFormat(glm::vec3(i, 0, 0), glm::vec3(0.54, 0.6, 0.35)));
	}
	for (int i = 0; i < height.size() - 1; i++) {
		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
		indices.push_back(2 * i + 2);
		indices.push_back(2 * i + 1);
		indices.push_back(2 * i + 2);
		indices.push_back(2 * i + 3);
	}

	if (meshes[name] == NULL) {
		Mesh* terrain = new Mesh(name);
		terrain->InitFromData(vertices, indices);
		AddMeshToList(terrain);
	}
	else {
		meshes[name]->InitFromData(vertices, indices);
	}

}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	widthScreen = resolution.x;
	heightScreen = resolution.y;
	Tank::widthScreenTank = widthScreen;
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	for (int i = 0; i < widthScreen + 50; i++) {
		height.push_back(generateFunction(i));
	}
	initTerrain("terrainStrip");
	Tank::CreateLifeBar(this);
	tanks[0] = new Tank(glm::vec3(0.59, 0.52, 0.34), glm::vec3(0.75, 0.6, 0.4), "tank", "cannon", this, 50, 99.5, "projectile1","life1");
	tanks[1] = new Tank(glm::vec3(0, 0.5, 0.5), glm::vec3(0.25, 0.5, 0.42), "tank2", "cannon2", this, widthScreen - 200, 101.75, "projectile2","life2");
	strncpy(tanks[0]->trajName, "traj1",10);
	strncpy(tanks[1]->trajName, "traj2", 10);
	tankWalk = Mix_LoadWAV("src/lab_m1/lab1/assets/tank_walk.mp3");
	tankWalkDamaged = Mix_LoadWAV("src/lab_m1/lab1/assets/tank_walk_damaged.mp3");
	turretRotate = Mix_LoadWAV("src/lab_m1/lab1/assets/turret_rotate.mp3");
	tankExplosion = Mix_LoadWAV("src/lab_m1/lab1/assets/explode.mp3");
	turretFire = Mix_LoadWAV("src/lab_m1/lab1/assets/turret_fire.mp3");
	theme = Mix_LoadMUS("src/lab_m1/lab1/assets/theme.mp3");
	readyFight = Mix_LoadWAV("src/lab_m1/lab1/assets/fight.mp3");
	victory = Mix_LoadWAV("src/lab_m1/lab1/assets/victory.mp3");
	if (!tankWalk || !tankWalkDamaged || !turretRotate || !tankExplosion || !turretFire || !theme) {
		printf("not worked tank walk\n");
	}
	Mix_VolumeChunk(tankWalk, 40);
	Mix_VolumeChunk(tankWalkDamaged, 40);
	Mix_VolumeChunk(turretRotate, 20);
	Mix_VolumeChunk(tankExplosion, 20);
	Mix_VolumeChunk(turretFire, 20);
	Mix_VolumeChunk(readyFight, 50);
	Mix_VolumeMusic(64);
	Mix_PlayMusic(theme, -1);
	Mix_PlayChannel(6, readyFight, 0);
	createCloud();
	cloudXPos.push_back(20.0f); // CLOUD 0 GOING RIGHT
	cloudSpeed.push_back(10);

	cloudXPos.push_back(300.0f); // CLOUD 1 GOING RIGHT
	cloudSpeed.push_back(10);

	cloudXPos.push_back(700.0f); // CLOUD 2 GOING LEFT
	cloudSpeed.push_back(-10);

	cloudXPos.push_back(900.0f); // CLOUD 3 GOING LEFT
	cloudSpeed.push_back(-10);

	cloudXPos.push_back(1100.0f); // CLOUD 4 GOING RIGHT
	cloudSpeed.push_back(10);
	Letters::InitLetters(this,glm::vec3(1,0,0));
	Letters::InitNumbers(this,glm::vec3(1, 0, 0));
	Letters::InitScore(this, glm::vec3(0.59, 0.52, 0.34), "player0");
	Letters::InitScore(this, glm::vec3(0, 0.5, 0.5), "player1");
}

void Tema1::reInit() {
	for (int i = 0; i < widthScreen + 50; i++) {
		height.push_back(generateFunction(i));
	}
	tanks[0]->tankX = 50;
	tanks[1]->tankX = widthScreen - 200;
	tanks[0]->triangleXLife = 10;
	tanks[1]->triangleXLife = 10;
	tanks[0]->life = tanks[1]->life = 100;
	tanks[0]->UpdateLife(this);
	tanks[1]->UpdateLife(this);
	tanks[0]->rotateAngle = 99.5;
	tanks[1]->rotateAngle = 101.75;
	initTerrain("terrainStrip");
	tanks[0]->projectiles.clear();
	tanks[1]->projectiles.clear();
	cloudXPos.push_back(20.0f); // CLOUD 0 GOING RIGHT
	cloudSpeed.push_back(10);

	cloudXPos.push_back(300.0f); // CLOUD 1 GOING RIGHT
	cloudSpeed.push_back(10);

	cloudXPos.push_back(700.0f); // CLOUD 2 GOING LEFT
	cloudSpeed.push_back(-10);

	cloudXPos.push_back(900.0f); // CLOUD 3 GOING LEFT
	cloudSpeed.push_back(-10);

	cloudXPos.push_back(1100.0f); // CLOUD 4 GOING RIGHT
	cloudSpeed.push_back(10);
	
}


void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.4f, 0.7f, 0.85f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::explodeTerrain(float rotatedX, float rotatedY) {
	double step = 0.001;
	garb.push_back(garbage{ 1000,(int)rotatedX - 50,(int)rotatedX + 50 });
	for (double angle = M_PI; angle < 2 * M_PI; angle += step) {
		int pozCx = rotatedX + (float)20 * cos(angle);
		float pozCy = rotatedY + (float)20 * sin(angle);
		if (pozCx < 0) {
			pozCx = 0;
		}
		if (pozCy < height[pozCx]) {
			height[pozCx] = pozCy;
		}
		if (height[pozCx] < 0) {
			height[pozCx] = 0;
		}
	}
	initTerrain("terrainStrip");
}



void smoothHeights(int start, int end) {
	float blendFactor = 0.1f;
	if (start == 0) start++;
	for (int i = start; i < end; ++i) {
		float neighborAvg = (height[i - 1] + height[i + 1]) / 2.0f;
		height[i] = height[i] * (1.0f - blendFactor) + neighborAvg * blendFactor;
	}
}



void Tema1::updateProjectiles(int tankPoz, float deltaTimeSeconds) {
	glm::mat3 modelMatrix;
	for (auto i = tanks[tankPoz]->projectiles.begin(); i < tanks[tankPoz]->projectiles.end();) {
		modelMatrix = glm::mat3(1);
		i->poz[0] += i->speed[0] * deltaTimeSeconds;
		i->poz[1] += i->speed[1] * deltaTimeSeconds;
		i->speed[1] -= 9.8 * 100 * deltaTimeSeconds;
		modelMatrix *= transform2D::Translate(i->poz[0], i->poz[1]);
		modelMatrix *= transform2D::Rotate(i->angleProj);
		modelMatrix *= transform2D::Translate(0, 15);
		RenderMesh2D(meshes["projectile1"], shaders["VertexColor"], modelMatrix);

		float rotatedX = i->poz[0] + 1 * cos(i->angleProj) - 15 * sin(i->angleProj);
		float rotatedY = i->poz[1] + 1 * sin(i->angleProj) + 15 * cos(i->angleProj);


		int check = 0;
		for (int j = 0; j < height.size() - 1; j++) {
			if (rotatedX >= j && rotatedX <= j + 1) {
				int otherPoz = !tankPoz;
				float tankRealPozX = (float)tanks[otherPoz]->tankX + cos(tanks[otherPoz]->angle) - sin(tanks[otherPoz]->angle);
				float tankRealPozY = (float)tanks[otherPoz]->tankY + sin(tanks[otherPoz]->angle) + cos(tanks[otherPoz]->angle);
				if (tanks[otherPoz]->life > 0) {
					if (rotatedX >= tankRealPozX - 20 && rotatedX <= tankRealPozX + 20) {
						if (rotatedY >= tankRealPozY && rotatedY <= tankRealPozY + 30) {
							tanks[otherPoz]->life -= 20;
							if (!tanks[otherPoz]->life) {
								tanks[otherPoz]->tankExplodeChannel = Mix_PlayChannel(4, tankExplosion, 0);
							}
							tanks[otherPoz]->triangleXLife -= 4;
							tanks[otherPoz]->UpdateLife(this);
							i = tanks[tankPoz]->projectiles.erase(i);
							check = 1;
							break;
						}
					}
				}

				if (rotatedY < height[j]) {
					explodeTerrain(rotatedX, rotatedY);
					i = tanks[tankPoz]->projectiles.erase(i);
					check = 1;
					break;
				}
			}
		}
		if (!check) {
			if (rotatedX < 0) {
				i = tanks[tankPoz]->projectiles.erase(i);
			}
			else if (rotatedX > widthScreen) {
				i = tanks[tankPoz]->projectiles.erase(i);
			}
			else {
				i++;
			}

		}


	}
}

void Tema1::updateTerrain(float deltaTimeSeconds) {
	// old function, not working properly
	int checkTerrain = 0;
	for (int i = 0; i < height.size() - 4; i++) {
		if (fabs(height[i] - height[i + 1]) >= 3) {
			if (height[i] > height[i + 1]) {
				height[i] -= 50 * deltaTimeSeconds;
				height[i + 1] += 50 * deltaTimeSeconds;
				checkTerrain = 1;
			}
			else {
				height[i] += 50 * deltaTimeSeconds;
				height[i + 1] -= 50 * deltaTimeSeconds;
				checkTerrain = 1;
			}
		}
	}

	if (checkTerrain) {
		initTerrain("terrainStrip");
	}
}

int Tema1::checkUpdateTerrain() {
	int check = 0;
	for (auto i = garb.begin(); i < garb.end();) {
		if (i->start < 0) {
			i->start = 0;
		}
		if (i->end > widthScreen) {
			i->end = widthScreen;
		}
		smoothHeights(i->start, i->end);
		i->numberOfTimes--;
		check = 1;
		if (i->numberOfTimes == 0) {
			i = garb.erase(i);
		}
		else {
			i++;
		}
	}
	if (check) {
		initTerrain("terrainStrip");
	}
	return check;
}

void Tema1::playTankWalk(int tankPoz) {
	if (!Mix_Playing(tanks[tankPoz]->tankWalkChannel))
		if (tanks[tankPoz]->life > 40) {
			tanks[tankPoz]->tankWalkChannel = Mix_PlayChannel(3, tankWalk, 0);
		}
		else {
			tanks[tankPoz]->tankWalkChannel = Mix_PlayChannel(2, tankWalkDamaged, 0);
		}
}

void Tema1::playTurret(int tankPoz) {
	if (!Mix_Playing(tanks[tankPoz]->turretRotateChannel)) {
		tanks[tankPoz]->turretRotateChannel = Mix_PlayChannel(1, turretRotate, 0);
	}
}

void Tema1::updateClouds(float deltaTimeSeconds) {
	for (int i = 0; i < cloudXPos.size(); i++) {
		cloudXPos[i] += cloudSpeed[i] * 5 * deltaTimeSeconds;
		if (cloudXPos[i] + 30 <= 0  && cloudSpeed[i] < 0 || cloudXPos[i] + 30 >= widthScreen && cloudSpeed[i] > 0) {
			cloudSpeed[i] *= -1;
		}
	}
}

void Tema1::displayNumber(int width,int number,int mode) {
	glm::mat3  modelMatrix = glm::mat3(1);
	char num = (char)(48 + number);
	char name[100];
	if(!mode)
		strcpy(name, "player0_");
	else
		strcpy(name, "player1_");
	name[8] = num;
	name[9] = '\0';;
	modelMatrix *= transform2D::Translate(10 + width, heightScreen - 100);
	RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
}

void Tema1::updateScore() {
	if (SCORE_TANK0 > 99) {
		SCORE_TANK0 = 0;
	}
	int firstNum = SCORE_TANK0 / 10;
	int secondNum = SCORE_TANK0 % 10;
	if (firstNum != 0) {
		displayNumber(0, firstNum,0);
		displayNumber(Letters::width[firstNum] + 10, secondNum,0);
	}
	else {
		displayNumber(0, secondNum,0);
	}

	if (SCORE_TANK1 > 99) {
		SCORE_TANK1 = 0;
	}
	firstNum = SCORE_TANK1 / 10;
	secondNum = SCORE_TANK1 % 10;
	if (firstNum != 0) {
		displayNumber(widthScreen - Letters::width[secondNum] - 20 - Letters::width[firstNum] - 10, firstNum,1);
		displayNumber(widthScreen - Letters::width[secondNum] - 20, secondNum,1);
	}
	else {
		displayNumber(widthScreen - Letters::width[secondNum] - 20, secondNum,1);
	}


}

Uint32 lastColorChangeTime = 0;
Uint32 colorChangeInterval = 500;

void Tema1::Update(float deltaTimeSeconds)
{
	static float scale = 1;
	static float speed = 0.25;
	Uint32 currentTime = SDL_GetTicks();
	int check = checkUpdateTerrain();
	updateClouds(deltaTimeSeconds);
	glm::mat3 modelMatrix = glm::mat3(1);
	RenderMesh2D(meshes["terrainStrip"], shaders["VertexColor"], modelMatrix);
	if (tanks[0]->life && !tanks[1]->life && ONCE_PER_RUN) {
		SCORE_TANK0++;
		ONCE_PER_RUN = 0;
		Mix_PlayChannel(7, victory, 0);
	}
	else if (!tanks[0]->life && tanks[1]->life && ONCE_PER_RUN) {
		SCORE_TANK1++;
		ONCE_PER_RUN = 0;
		Mix_PlayChannel(7, victory, 0);
	}
	if (tanks[0]->life) {
		tanks[0]->updateTank(height);
		modelMatrix *= transform2D::Translate(tanks[0]->tankX, tanks[0]->tankY);
		modelMatrix *= transform2D::Rotate(tanks[0]->angle);
		RenderMesh2D(meshes["tank"], shaders["VertexColor"], modelMatrix);

		modelMatrix *= transform2D::Translate(0, 15);
		modelMatrix *= transform2D::Rotate(tanks[0]->rotateAngle);
		RenderMesh2D(meshes["cannon"], shaders["VertexColor"], modelMatrix);

		updateProjectiles(0, deltaTimeSeconds);

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(tanks[0]->tankX, tanks[0]->tankY + 50);
		RenderMesh2D(meshes["lifeBar"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);;
		tanks[0]->UpdateTrajectory(height, this);
		RenderMesh2D(meshes[tanks[0]->trajName], shaders["VertexColor"], modelMatrix);
	}

	if (tanks[1]->life) {
		modelMatrix = glm::mat3(1);
		tanks[1]->updateTank(height);
		modelMatrix *= transform2D::Translate(tanks[1]->tankX, tanks[1]->tankY);
		modelMatrix *= transform2D::Rotate(tanks[1]->angle);
		RenderMesh2D(meshes["tank2"], shaders["VertexColor"], modelMatrix);

		modelMatrix *= transform2D::Translate(0, 15);
		modelMatrix *= transform2D::Rotate(tanks[1]->rotateAngle);
		RenderMesh2D(meshes["cannon2"], shaders["VertexColor"], modelMatrix);

		updateProjectiles(1, deltaTimeSeconds);

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(tanks[1]->tankX, tanks[1]->tankY + 50);
		RenderMesh2D(meshes["lifeBar"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		tanks[1]->UpdateTrajectory(height, this);
		RenderMesh2D(meshes[tanks[1]->trajName], shaders["VertexColor"], modelMatrix);
	}
	for (int i = 0; i < cloudXPos.size();i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(cloudXPos[i], 620);
		RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
	}
	if (tanks[0]->life * tanks[1]->life == 0) {
 		if (currentTime - lastColorChangeTime >= colorChangeInterval) {
			lastColorChangeTime = currentTime;
			glm::vec3 color = glm::vec3(
				static_cast<float>(rand()) / RAND_MAX,
				static_cast<float>(rand()) / RAND_MAX,
				static_cast<float>(rand()) / RAND_MAX
			);
			Letters::InitLetters(this, color);
			Letters::InitNumbers(this,	color);;

		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(widthScreen / 2 - 180, 620);
		modelMatrix *= transform2D::Translate(180, 40);
		modelMatrix *= transform2D::Scale(scale, scale);
		modelMatrix *= transform2D::Translate(-180, -40);
		RenderMesh2D(meshes["P"], shaders["VertexColor"], modelMatrix);
		int halfX = 20;
		if (tanks[0]->life == 0) {
			halfX = 15;
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(widthScreen / 2 - 20, 500);
		modelMatrix *= transform2D::Translate(halfX, 40);
		modelMatrix *= transform2D::Scale(scale, scale);
		modelMatrix *= transform2D::Translate(-halfX, -40);
		if (tanks[0]->life == 0) {
			RenderMesh2D(meshes["2"], shaders["VertexColor"], modelMatrix);
		}
		else {
			RenderMesh2D(meshes["1"], shaders["VertexColor"], modelMatrix);
		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(widthScreen / 2 - 110, 380);
		modelMatrix *= transform2D::Translate(110, 40);
		modelMatrix *= transform2D::Scale(scale, scale);
		modelMatrix *= transform2D::Translate(-110, -40);
		RenderMesh2D(meshes["WINS"], shaders["VertexColor"], modelMatrix);


		scale += (float)speed * deltaTimeSeconds;
		if (scale > 1.2 && speed > 0) {
			speed *= -1;
		}
		if (scale < 0.9 && speed < 0) {
			speed *= -1;
		}
	}
	updateScore();
}

void Tema1::FrameEnd()
{
}

bool Tema1::checkIntersection() {
	bool check = true;
	float angle0 = tanks[0]->angle * M_PI / 180.0f;
	float angle1 = tanks[1]->angle * M_PI / 180.0f;
	float xOffset0 = (float)tanks[0]->tankX * cos(angle0) - (float)tanks[0]->tankY * sin(angle0);
	float yOffset0 = (float)tanks[0]->tankX * sin(angle0) + (float)tanks[0]->tankY * cos(angle0);

	float xOffset1 = (float)tanks[1]->tankX * cos(angle1) - (float)tanks[1]->tankY * sin(angle1);
	float yOffset1 = (float)tanks[1]->tankX * sin(angle1) + (float)tanks[1]->tankY * cos(angle1);
	float x = pow((xOffset0 - xOffset1), 2);
	float y = pow((yOffset0 - yOffset1), 2);
	float val = sqrt(x + y);
	int offset = tanks[0]->widthTank;
	if (val + 2 >= 20 + offset) {
		check = false;
	}

	return check;
}

void Tema1::updateMesh(char name[100],vector<VertexFormat> vertices, vector<unsigned int> indices) {
	if (meshes[name] != NULL) {
		meshes[name]->InitFromData(vertices, indices);
	}
	else {
		Mesh* mesh = new Mesh(name);
		mesh->InitFromData(vertices, indices);
		AddMeshToList(mesh);
	}
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	double limitLeft = 102.010933;
	double limitRight = 99.357399;
	if (tanks[0]->life <= 40 && tanks[0]->speedTank >= 99) {
		tanks[0]->speedTank *= 0.7;
	}
	if (tanks[1]->life <= 40 && tanks[1]->speedTank >= 99) {
		tanks[1]->speedTank *= 0.7;
	}
	if (tanks[0]->life) {
		if (window->KeyHold(GLFW_KEY_A)) {
			if (tanks[0]->tankX - 30 > 0) {
				playTankWalk(0);
				tanks[0]->tankX -= tanks[0]->speedTank * deltaTime;
			}
		}
		else if (window->KeyHold(GLFW_KEY_D)) {
			if (tanks[0]->tankX + 20 < widthScreen) {
				bool check = checkIntersection();
				if (!check) {
					playTankWalk(0);
					tanks[0]->tankX += tanks[0]->speedTank * deltaTime;
				}
				else if (tanks[1]->life <= 0) {
					playTankWalk(0);
					tanks[0]->tankX += tanks[0]->speedTank * deltaTime;
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_W)) {
			if (tanks[0]->rotateAngle <= limitLeft) {
				playTurret(0);
				tanks[0]->rotateAngle += deltaTime;
			}
		}
		else if (window->KeyHold(GLFW_KEY_S)) {
			if (tanks[0]->rotateAngle >= limitRight) {
				playTurret(0);
				tanks[0]->rotateAngle -= deltaTime;
			}
		}
	}
	if (tanks[1]->life) {
		if (window->KeyHold(GLFW_KEY_LEFT)) {
			if (tanks[1]->tankX - 10 > 0) {
				bool check = checkIntersection();
				if (!check) {
					playTankWalk(1);
					tanks[1]->tankX -= tanks[1]->speedTank * deltaTime;
				}
				else if (tanks[0]->life <= 0) {
					playTankWalk(1);
					tanks[1]->tankX -= tanks[1]->speedTank * deltaTime;
				}
			}
		}
		else if (window->KeyHold(GLFW_KEY_RIGHT)) {
			if (tanks[1]->tankX + 20 < widthScreen) {
				playTankWalk(1);
				tanks[1]->tankX += tanks[1]->speedTank * deltaTime;
			}
		}

		if (window->KeyHold(GLFW_KEY_UP)) {
			if (tanks[1]->rotateAngle <= limitLeft) {
				tanks[1]->rotateAngle += deltaTime;
				playTurret(1);
			}
		}
		else if (window->KeyHold(GLFW_KEY_DOWN)) {
			if (tanks[1]->rotateAngle >= limitRight) {
				tanks[1]->rotateAngle -= deltaTime;
				playTurret(1);
			}
		}
	}
}


void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_SPACE && tanks[0]->life > 0) {
		glm::vec2 speed = glm::vec2((float)cos(tanks[0]->rotateAngle + tanks[0]->angle + M_PI / 2) * tanks[0]->amplitude, (float)sin(tanks[0]->rotateAngle + tanks[0]->angle + M_PI / 2) * tanks[0]->amplitude);
		if (tanks[0]->projectiles.size() <= 2) {
			tanks[0]->addProjectile(speed, glm::vec2(tanks[0]->tankX, tanks[0]->tankY), tanks[0]->angle);
			Mix_PlayChannel(5, turretFire, 0);
		}
	}

	if (key == GLFW_KEY_ENTER && tanks[1]->life > 1) {
		glm::vec2 speed = glm::vec2((float)cos(tanks[1]->rotateAngle + tanks[1]->angle + M_PI / 2) * tanks[1]->amplitude, (float)sin(tanks[1]->rotateAngle + tanks[1]->angle + M_PI / 2) * tanks[1]->amplitude);
		if (tanks[1]->projectiles.size() <= 2) {
			tanks[1]->addProjectile(speed, glm::vec2(tanks[1]->tankX, tanks[1]->tankY), tanks[1]->angle);
			Mix_PlayChannel(6, turretFire, 0);
		}
	}

	if (key == GLFW_KEY_R) {
		height.clear();
		cloudSpeed.clear();
		cloudXPos.clear();
		garb.clear();
		reInit();
		Mix_HaltMusic();
		Mix_PlayMusic(theme,-1);
		Mix_PlayChannel(6, readyFight, 0);
		ONCE_PER_RUN = 1;
		Mix_HaltChannel(7);
		tanks[0]->speedTank = 100;
		tanks[1]->speedTank = 100;
	}
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
	if (key == GLFW_KEY_D) {
		Mix_HaltChannel(tanks[0]->tankWalkChannel);
	}
	if (key == GLFW_KEY_A) {
		Mix_HaltChannel(tanks[0]->tankWalkChannel);
	}
	if (key == GLFW_KEY_RIGHT) {
		Mix_HaltChannel(tanks[1]->tankWalkChannel);
	}
	if (key == GLFW_KEY_LEFT) {
		Mix_HaltChannel(tanks[1]->tankWalkChannel);
	}
	if (key == GLFW_KEY_W) {
		Mix_HaltChannel(tanks[0]->turretRotateChannel);
	}
	if (key == GLFW_KEY_S) {
		Mix_HaltChannel(tanks[0]->turretRotateChannel);
	}
	if (key == GLFW_KEY_UP) {
		Mix_HaltChannel(tanks[1]->turretRotateChannel);
	}
	if (key == GLFW_KEY_DOWN) {
		Mix_HaltChannel(tanks[1]->turretRotateChannel);
	}
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
