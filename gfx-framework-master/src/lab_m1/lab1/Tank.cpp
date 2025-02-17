#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include "lab_m1/lab1/Tank.h"
using namespace std;
using namespace m1;

Tank::Tank(glm::vec3 lower, glm::vec3 upper, char tankName[100], char cannon[100], class Tema1* tema1, int pozTankX, float rotAngle, char projectile[100], char lifeName[100]) {
	tankX = pozTankX;
	tankY = 0;
	domeCenterX = 20;
	domeCenterY = 15;
	angle = 0;
	rotateAngle = rotAngle;
	angleProj = 0;
	heightTank = 0;
	widthTank = 0;
	amplitude = 600;
	color = lower;
	if (tema1->meshes[tankName] == NULL) {
		initVeticesTank(lower, upper);
		initDomeTank(upper);
		initIndicesTank();
		Mesh* tank = new Mesh(tankName);
		tank->InitFromData(verticesT, indicesT);
		tema1->AddMeshToList(tank);
	}
	if (tema1->meshes[cannon] == NULL) {
		initCannon(tema1, cannon);
	}
	if (tema1->meshes[projectile] == NULL) {
		initProjectile(projectile, tema1);
	}
	speed = glm::vec2(0, 0);
	poz = glm::vec2(0, 0);
	life = 100;
	triangleXLife = 10;
	if (tema1->meshes[lifeName] == NULL) {
		CreateLife(tema1, lifeName);
	}
	strncpy(this->lifeName, lifeName,100);
	tankWalkChannel = 0;
	turretRotateChannel = 0;
	tankExplodeChannel = 0;
	speedTank = 100;
}

Tank::~Tank() {

}

void Tank::initProjectile(char projectile[100], class Tema1* tema1) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	int radius = 2;
	int triangleNo = 1;
	int numberOfTriangles = 10;
	float angleStep = 2.5 * M_PI / numberOfTriangles;
	vertices.push_back(VertexFormat(glm::vec3(2, 2, 0), glm::vec3(0, 0, 0)));
	for (int i = 0; i < numberOfTriangles; i++) {
		float angle = i * angleStep;
		float x = 2 + 2 * cos(angle);
		float y = 2 + 2 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), glm::vec3(0, 0, 0)));
		if (i != 0) {
			indices.push_back(0);
			indices.push_back(triangleNo + i - 1);
			indices.push_back(triangleNo + i);
		}
	}
	Mesh* tank = new Mesh(projectile);
	tank->InitFromData(vertices, indices);
	tema1->AddMeshToList(tank);
}

void Tank::initVeticesTank(glm::vec3 lower, glm::vec3 upper) {
	verticesT.push_back(VertexFormat(glm::vec3(-20, 5, 0), upper)); // A
	verticesT.push_back(VertexFormat(glm::vec3(-15, 5, 0), lower)); // B
	verticesT.push_back(VertexFormat(glm::vec3(-15, 15, 0), upper)); // C
	verticesT.push_back(VertexFormat(glm::vec3(15, 15, 0), upper)); // D
	verticesT.push_back(VertexFormat(glm::vec3(20, 5, 0), lower)); // E
	verticesT.push_back(VertexFormat(glm::vec3(15, 5, 0), lower)); // F
	verticesT.push_back(VertexFormat(glm::vec3(10, 0, 0), lower)); // G
	verticesT.push_back(VertexFormat(glm::vec3(-10, 0, 0), lower)); // H
	verticesT.push_back(VertexFormat(glm::vec3(0, 15, 0), upper)); // I
	widthTank = 40 - 0;
	heightTank = 15 - 0;
}

void Tank::initIndicesTank() {
	indicesT.push_back(0);
	indicesT.push_back(2);
	indicesT.push_back(3);

	indicesT.push_back(0);
	indicesT.push_back(3);
	indicesT.push_back(4);

	indicesT.push_back(1);
	indicesT.push_back(7);
	indicesT.push_back(5);

	indicesT.push_back(7);
	indicesT.push_back(5);
	indicesT.push_back(6);
}

void Tank::initDomeTank(glm::vec3 upper) {
	int triangleNo = 9;
	int numberOfTriangles = 30;
	float angleStep = 2 * M_PI / numberOfTriangles;
	for (int i = 0; i < numberOfTriangles; i++) {
		float angle = i * angleStep;
		float x = 0 + 8 * cos(angle);
		float y = 15 + 8 * sin(angle);
		verticesT.push_back(VertexFormat(glm::vec3(x, y, 0), upper)); // I
		if (i != 0) {
			indicesT.push_back(8);
			indicesT.push_back(triangleNo + i - 1);
			indicesT.push_back(triangleNo + i);
		}
	}
}

void Tank::updateTank(vector<float> height) {
	for (int i = 0; i < height.size() - 1; i++) {
		if (tankX >= i && tankX < i + 1) {
			float t = (float)(tankX - i) / (i + 1 - i);
			tankY = height[i] - 0.5 + t * (height[i + 1] - height[i]);
			angle = atan2(height[i + 1] - height[i], i + 1 - i);
			if (tankY < 0) {
				tankY = 0;
				angle = 0;
			}
			break;
		}
	}
}

void Tank::initCannon(class Tema1* tema1, char cannonName[100]) {
	verticesC.push_back(VertexFormat(glm::vec3(0, 7.5, 0), glm::vec3(0, 0, 0))); // A
	verticesC.push_back(VertexFormat(glm::vec3(0, 22.5, 0), glm::vec3(0, 0, 0))); // B
	verticesC.push_back(VertexFormat(glm::vec3(3, 22.5, 0), glm::vec3(0, 0, 0))); // C
	verticesC.push_back(VertexFormat(glm::vec3(3, 7.5, 0), glm::vec3(0, 0, 0))); // D
	indicesC.push_back(0);
	indicesC.push_back(1);
	indicesC.push_back(2);

	indicesC.push_back(0);
	indicesC.push_back(3);
	indicesC.push_back(2);

	Mesh* tank = new Mesh(cannonName);
	tank->InitFromData(verticesC, indicesC);
	tema1->AddMeshToList(tank);
}

void Tank::addProjectile(glm::vec2 speed, glm::vec2 poz, float angle) {
	projectiles.push_back(projectile{ speed,poz,angle });
}

void Tank::CreateLifeBar(class Tema1* tema1) {
	{
		vector<VertexFormat> vertices;
		vector<unsigned int> indices;
		vertices.push_back(VertexFormat(glm::vec3(-10, 0, 1), glm::vec3(0, 0, 0))); // A 0
		vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), glm::vec3(0, 0, 0))); // B 1
		vertices.push_back(VertexFormat(glm::vec3(10, 1, 1), glm::vec3(0, 0, 0))); // C 2
		vertices.push_back(VertexFormat(glm::vec3(-10, 1, 1), glm::vec3(0, 0, 0))); // D 3
		vertices.push_back(VertexFormat(glm::vec3(10, 8, 1), glm::vec3(0, 0, 0))); // E 4
		vertices.push_back(VertexFormat(glm::vec3(-10, 8, 1), glm::vec3(0, 0, 0))); // F 5
		vertices.push_back(VertexFormat(glm::vec3(10, 7, 1), glm::vec3(0, 0, 0))); // G 6
		vertices.push_back(VertexFormat(glm::vec3(-10, 7, 1), glm::vec3(0, 0, 0))); // H 7
		vertices.push_back(VertexFormat(glm::vec3(11, 1, 1), glm::vec3(0, 0, 0))); // I 8
		vertices.push_back(VertexFormat(glm::vec3(11, 7, 1), glm::vec3(0, 0, 0))); // J 9
		vertices.push_back(VertexFormat(glm::vec3(-11, 1, 1), glm::vec3(0, 0, 0))); // K 10
		vertices.push_back(VertexFormat(glm::vec3(-11, 7, 1), glm::vec3(0, 0, 0))); // L 11

		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(2);

		indices.push_back(10);
		indices.push_back(3);
		indices.push_back(7);

		indices.push_back(10);
		indices.push_back(11);
		indices.push_back(7);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(2);
		indices.push_back(8);
		indices.push_back(9);

		indices.push_back(2);
		indices.push_back(6);
		indices.push_back(9);

		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(4);

		indices.push_back(7);
		indices.push_back(5);
		indices.push_back(4);


		Mesh* tank = new Mesh("lifeBar");
		tank->InitFromData(vertices, indices);
		tema1->AddMeshToList(tank);
	}
}
void Tank::CreateLife(class Tema1* tema1, char name[100]) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	vertices.push_back(VertexFormat(glm::vec3(-10, 1, 1), color)); // D 0
	vertices.push_back(VertexFormat(glm::vec3(10, 1, 1), color)); // C 1
	vertices.push_back(VertexFormat(glm::vec3(10, 7, 1), color)); // G 2
	vertices.push_back(VertexFormat(glm::vec3(-10, 7, 1), color)); // H 3

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);

	Mesh* tank = new Mesh(name);
	tank->InitFromData(vertices, indices);
	tema1->AddMeshToList(tank);
}

void Tank::UpdateLife(class Tema1* tema1) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	vertices.push_back(VertexFormat(glm::vec3(-10, 1, 1), color)); // D 0
	vertices.push_back(VertexFormat(glm::vec3(triangleXLife, 1, 1), color)); // C 1
	vertices.push_back(VertexFormat(glm::vec3(triangleXLife, 7, 1), color)); // G 2
	vertices.push_back(VertexFormat(glm::vec3(-10, 7, 1), color)); // H 3

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);
	tema1->updateMesh(lifeName, vertices, indices);
}

void Tank::UpdateTrajectory(vector<float> height, class Tema1* tema1) {
	glm::vec2 speed = glm::vec2((float)cos(rotateAngle + angle + M_PI / 2) * amplitude, (float)sin(rotateAngle + angle + M_PI / 2) * amplitude);
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	double epsilon = 0.0001;
	float rotatedX = tankX + 1 * cos(angle) - 15 * sin(angle);
	float rotatedY = tankY + 1 * sin(angle) + 15 * cos(angle);
	glm::vec2 poz = glm::vec2(rotatedX, rotatedY);
	int realPoz = 0;
	for (;;) {
		if (poz[0] > 0 && poz[1] > 0) {
			vertices.push_back(VertexFormat(glm::vec3(poz[0], poz[1], 0), glm::vec3(0, 0, 0)));
			indices.push_back(realPoz);
			realPoz++;
			
		}
		poz[0] += speed[0] * epsilon;
		poz[1] += speed[1] * epsilon;
		speed[1] -= 9.8 * 100 * epsilon;
		if (poz[1] < height[(int)poz[0]] || poz[0] < 0 || poz[0] > widthScreenTank) {
			break;
		}

	}
	if (tema1->meshes[trajName] == NULL) {
		Mesh* tank = new Mesh(trajName);
		tank->InitFromData(vertices, indices);
		tank->SetDrawMode(GL_LINE_STRIP);
		tema1->AddMeshToList(tank);
	}
	else {
		tema1->meshes[trajName]->InitFromData(vertices, indices);
		tema1->meshes[trajName]->SetDrawMode(GL_LINE_STRIP);
	}

}