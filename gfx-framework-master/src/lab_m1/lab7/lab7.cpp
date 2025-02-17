#include "lab_m1/lab7/lab7.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

std::vector<float> heights(300 * 300, 0.0f);
std::vector<std::vector<float>> matrix(300, std::vector<float>(300));
int waitOne = 0;
int widthStart;
int heightStart;

Lab7::Lab7()
{
}


Lab7::~Lab7()
{
    Mix_HaltMusic();
    Mix_FreeMusic(theme);
}

void Lab7::InitTerrain() {
    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    int width = 300;
    for (int z = 0; z < width; z++) {
        for (int x = 0; x < width; x++) {
            vertices.push_back(VertexFormat(glm::vec3(x, 0, z), glm::vec3(1, 0, 0)));
        }
    }

    for (int z = 0; z < width - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            int currentPoz = (x + z * width);
            indices.push_back(currentPoz);
            indices.push_back(currentPoz + 1);
            indices.push_back(currentPoz + width);

            indices.push_back(currentPoz + width);
            indices.push_back(currentPoz + 1);
            indices.push_back(currentPoz + width + 1);
        }
    }
    Mesh* mesh = new Mesh("terrain");
    mesh->InitFromData(vertices, indices);
    AddMeshToList(mesh);

}

void createCircle(vector<VertexFormat> &vertices, vector<unsigned int> &indices, float r, float nOfPoints, int &startingPoint,float height,glm::vec3 color) {
    float angleStep = 2.5 * M_PI / nOfPoints;
    int offsetY;
    if (height < matrix[0][0]) {
        offsetY = matrix[0][0];
    }
    else {
        offsetY = height;
    }
    vertices.push_back(VertexFormat(glm::vec3(0, offsetY, 0), color)); // center A 0
    for (int i = 0; i < nOfPoints; i++) {
        float angle = i * angleStep;
        float x = r * cos(angle);
        float y = r * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, offsetY, y), color));
        if (i != 0) {
            indices.push_back(startingPoint + 1 + i);
            indices.push_back(startingPoint);
            indices.push_back(startingPoint + 1 + i - 1);
        }
    }
    startingPoint += nOfPoints + 1;
}

void createLeaf(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int &startingPoint,int startPoint,int heightStart,int heightEnd) {
    createCircle(vertices, indices, 2, 30, startingPoint, heightStart, glm::vec3(0.2, 0.36, 0.23));
    vertices.push_back(VertexFormat(glm::vec3(0, heightEnd, 0), glm::vec3(0.13, 0.54, 0.13)));
    for (int i = startPoint; i < startingPoint; i++) {
        indices.push_back(startingPoint);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
}

void Lab7::createRandomHouses() {
    random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 280);
    std::uniform_int_distribution<> dis2(0, 4);
    for (int k = 0; k < 30; k++) {
        int x = dis(gen);
        int z = dis(gen);
        int checkIfFree = 0;
        for (int i = x; i < x + 18; i++) {
            for (int j = z; j < z + 18; j++) {
                if (checkPopulation[i][j]) {
                    checkIfFree = 1;
                }
            }
        }
        int computeMin = matrix[x][z];
        if (!checkIfFree) {
            for (int i = x; i < x + 18; i++) {
                for (int j = z; j < z + 18; j++) {
                    if (matrix[i][j] < computeMin && i < x + 10 && j < z + 10) {
                        computeMin = matrix[i][j];
                    }
                    checkPopulation[i][j] = 1;
                }
            }
        }
        if (!checkIfFree) {
            housePos.push_back(glm::vec3(x, computeMin, z));
            float rotateRandom = dis2(gen) * 90;

            BoundingBox box;
            box.min = glm::vec3(x, computeMin, z);
            box.max = glm::vec3(x + 10, computeMin + 16, z + 10);
            houseBox.push_back(box);

            rotateRand.push_back(rotateRandom);
        }
    }
}

void Lab7::createRandomCheckPoints() {
    random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(50, 260);

    for (int j = 0; j < 10; j++) {
        int x_rand = dis(gen);
        int z_rand = dis(gen);
        int checkAvalability = 0;
        for (int i = 0; i < 7; i++) {
            if (checkPopulation[x_rand + i][z_rand]) {
                checkAvalability = -1;
                break;
            }
        }
        if (checkAvalability != -1) {
            for (int i = 0; i < 7; i++) {
                if (z_rand != 0) {
                    checkPopulation[x_rand + i][z_rand - 1] = 1;
                }
                if (z_rand + 1 < 300) {
                    checkPopulation[x_rand + i][z_rand + 1] = 1;
                }
                checkPopulation[x_rand + i][z_rand] = 1;
            }
            checkPoint check;
            check.checkPointPos = glm::vec3(x_rand,matrix[x_rand][z_rand],z_rand);
            if (j == 0) {
                check.state = 1;
            }
            else {
                check.state = 0;
            }
            BoundingBox box;
            float y_rand = matrix[x_rand][z_rand];
            box.min = glm::vec3(x_rand + 0, y_rand + 0, z_rand - 0.25);
            box.max = glm::vec3(x_rand + 0.25, y_rand + 8, z_rand + 0);
            check.checkPointsBoxes.push_back(box);
            box.min = glm::vec3(x_rand + 2.5, y_rand + 0, z_rand - 0.25);
            box.max = glm::vec3(x_rand + 2.75, y_rand + 8, z_rand);
            check.checkPointsBoxes.push_back(box);
            box.min = glm::vec3(x_rand - 2, y_rand + 8, z_rand - 0.25);
            box.max = glm::vec3(x_rand + 4.75, y_rand + 8.25, z_rand);
            check.checkPointsBoxes.push_back(box);
            box.min = glm::vec3(x_rand + 4.5, y_rand + 8.25, z_rand - 0.25);
            box.max = glm::vec3(x_rand + 4.75, y_rand + 15, z_rand + 0);
            check.checkPointsBoxes.push_back(box);
            box.min = glm::vec3(x_rand - 2, y_rand + 8.25, z_rand - 0.25);
            box.max = glm::vec3(x_rand - 1.75, y_rand + 15, z_rand);
            check.checkPointsBoxes.push_back(box);
            box.min = glm::vec3(x_rand - 1.75, y_rand + 14.75, z_rand - 0.25);
            box.max = glm::vec3(x_rand + 4.5, y_rand + 15, z_rand);
            check.checkPointsBoxes.push_back(box);
            points.push_back(check);
        }
    }
}

void Lab7::createRandomPos() {
    for (int i = 0; i < 100; i++) {
        random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 299);
        std::uniform_real_distribution<> dis2(1, 2);

        int random_number = dis(gen);
        int random_number2 = dis(gen);
        if (checkPopulation[random_number][random_number2]
            + checkPopulation[random_number + 1][random_number2]
            + checkPopulation[random_number - 1][random_number2]
            + checkPopulation[random_number][random_number2 - 1]
            + checkPopulation[random_number + 1][random_number2 + 1]
            + checkPopulation[random_number - 1][random_number2 + 1]
            + checkPopulation[random_number - 1][random_number2 - 1]
            + checkPopulation[random_number + 1][random_number2 - 1]
            + checkPopulation[random_number][random_number2 + 1] == 0) {
            treePos.push_back(glm::vec3(random_number, matrix[random_number][random_number2], random_number2));
            BoundingBox box;
            box.min = glm::vec3(random_number, matrix[random_number][random_number2], random_number2);
            float rXscale = dis2(gen);
            float rYscale = dis2(gen);
            float rZscale = dis2(gen);
            float xScaled = rXscale;
            float yScaled = 4 * rYscale;
            float zScaled = rZscale;
            treeScale.push_back(glm::vec3(rXscale,rYscale,rZscale));
            box.max = glm::vec3(random_number + xScaled, matrix[random_number][random_number2] + yScaled, random_number2 + zScaled);
            treeBox.push_back(box);
            checkPopulation[random_number][random_number2] = 2;
            checkPopulation[random_number + 1][random_number2] = checkPopulation[random_number - 1][random_number2] = 1;
            checkPopulation[random_number][random_number2 + 1] = checkPopulation[random_number][random_number2 - 1] = 1;
            checkPopulation[random_number - 1][random_number2 + 1] = checkPopulation[random_number + 1][random_number2 + 1] = 1;
            checkPopulation[random_number - 1][random_number2 - 1] = checkPopulation[random_number + 1][random_number2 - 1] = 1;
        }
    }
}

int Lab7::intersect(BoundingBox box) {
    float x = max(box.min.x, min(dronePozX, box.max.x));
    float y = max(box.min.y, min((float)(dronePozY + 0.2), box.max.y));
    float z = max(box.min.z, min(dronePozZ, box.max.z));
    float distance = sqrt(
        (double)((x - dronePozX) * (x - dronePozX)) +
        (double)((y - dronePozY + 0.2) * (y - dronePozY + 0.2)) +
        (double)((z - dronePozZ) * (z - dronePozZ))
        );
    return distance < 1;
}


void Lab7::Init()
{
    renderCameraTarget = false;
    glm::ivec2 resolution = window->GetResolution();
    widthStart = resolution.x;
    heightStart = resolution.y;
    theme = Mix_LoadMUS("src/lab_m1/lab7/sounds/nier.mp3");
    passCheck = Mix_LoadWAV("src/lab_m1/lab7/sounds/nier_check.mp3");
    droneFly = Mix_LoadWAV("src/lab_m1/lab7/sounds/drone.mp3");
    victory = Mix_LoadWAV("src/lab_m1/lab7/sounds/victory.mp3");
    lostS = Mix_LoadWAV("src/lab_m1/lab7/sounds/lost.mp3");
    hitTree = Mix_LoadWAV("src/lab_m1/lab7/sounds/hitTree.mp3");
    hitWall = Mix_LoadWAV("src/lab_m1/lab7/sounds/hitWall.mp3");
    hitCheck = Mix_LoadWAV("src/lab_m1/lab7/sounds/hitMetal.mp3");
    Mix_VolumeChunk(droneFly, 25);
    Mix_VolumeMusic(32);
    Mix_VolumeChunk(hitTree, 32);
    Mix_PlayMusic(theme, -1);
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    miniMap = ViewPortArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);
    camera = new implemented::Camera();
    camera_minimap = new implemented::Camera();
    camera->Set(thirdPerson, thirdPersonOrientation, glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, nearPlane, farPlane);

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        vertices.push_back(VertexFormat(glm::vec3(0, 1.25, 0.5), glm::vec3(0, 0, 0))); // A 0
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0.5), glm::vec3(0, 0, 0))); // B 1
        vertices.push_back(VertexFormat(glm::vec3(0, 1.25, 0), glm::vec3(0, 0, 0))); // C 2
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0))); // D 3
        vertices.push_back(VertexFormat(glm::vec3(0, 1.25, -0.5), glm::vec3(0, 0, 0))); // E 4
        vertices.push_back(VertexFormat(glm::vec3(0, 1.25, 1), glm::vec3(0, 0, 0))); // F 5
        vertices.push_back(VertexFormat(glm::vec3(0, 2.25, 0.25), glm::vec3(0, 0, 0))); // G 6

        indices.push_back(0); // A B C
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(3); // D B C
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(6); // G E F
        indices.push_back(4);
        indices.push_back(5);


        Mesh* mesh = new Mesh("arrow");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);

    }

    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        vertices.push_back(VertexFormat(glm::vec3(-0.4, 0, 0.1), glm::vec3(0,0,0))); // A 0
        vertices.push_back(VertexFormat(glm::vec3(0.4, 0, 0.1), glm::vec3(0, 0, 0))); // B 1
        vertices.push_back(VertexFormat(glm::vec3(-0.4, 0, -0.1), glm::vec3(0, 0, 0))); // C 2
        vertices.push_back(VertexFormat(glm::vec3(0.4, 0, -0.1), glm::vec3(0, 0, 0))); // D 3

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(3);

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);

        Mesh* mesh = new Mesh("zoom_zoom");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);
    }

    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        int startingPoint = 0;
        createCircle(vertices, indices, 0.5, 30, startingPoint,0, glm::vec3(0.58, 0.29, 0));
        int saveCopy = startingPoint;
        createCircle(vertices, indices, 0.5, 30, startingPoint,4, glm::vec3(0.58, 0.29, 0));

        for (int i = 0; i < saveCopy; i++) {
            if (i != 0) {
                indices.push_back(i);
                indices.push_back(i + 1);
                indices.push_back(saveCopy + i);

                indices.push_back(saveCopy + i);
                indices.push_back(saveCopy + i + 1);
                indices.push_back(i + 1);
            }
        }
        createLeaf(vertices, indices, startingPoint, startingPoint, 4,7);
        int savePoint = startingPoint;
        startingPoint++;
        createLeaf(vertices, indices, startingPoint, startingPoint, 3,5);
        savePoint = startingPoint;
        startingPoint++;
        createLeaf(vertices, indices, startingPoint, savePoint, 2,4);

        Mesh* mesh = new Mesh("tree");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);
    }

    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        glm::vec3 jinxBlue = glm::vec3(0.10, 0.24, 0.31);
        glm::vec3 powderBlue = glm::vec3(0.69, 0.87, 0.9);
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0, 0.7), jinxBlue)); // A 0
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0, 0.9), powderBlue)); // B 1
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0, -0.7), jinxBlue)); // C 2
        vertices.push_back(VertexFormat(glm::vec3(0.7, 0, -0.9), powderBlue)); // D 3
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0, -0.7), jinxBlue)); // E 4
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0, -0.9), powderBlue)); // F 5
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0, 0.7), powderBlue)); // G 6
        vertices.push_back(VertexFormat(glm::vec3(0.7, 0, 0.9), jinxBlue)); // H 7
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0.2, 0.7), powderBlue)); // I 8
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0.2, -0.7), powderBlue)); // J 9
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0.2, -0.7), powderBlue)); // K 10
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0.2, 0.7), powderBlue)); // L 11
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0.2, 0.9), powderBlue)); // M 12
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0.2, -0.9), powderBlue)); // N 13
        vertices.push_back(VertexFormat(glm::vec3(0.7, 0.2, 0.9), powderBlue)); // O 14
        vertices.push_back(VertexFormat(glm::vec3(0.7, 0.2, -0.9), powderBlue)); // P 15

        // jinx blue

        vertices.push_back(VertexFormat(glm::vec3(0.7, 0.4, 0.9), jinxBlue)); // Q 16
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0.4, 0.7), jinxBlue)); // R 17
        vertices.push_back(VertexFormat(glm::vec3(0.6, 0.4, 0.85), jinxBlue)); // S 18
        vertices.push_back(VertexFormat(glm::vec3(0.85, 0.4, 0.6), jinxBlue)); // T 19
        vertices.push_back(VertexFormat(glm::vec3(0.6, 0.2, 0.85), jinxBlue)); // U 20
        vertices.push_back(VertexFormat(glm::vec3(0.85, 0.2, 0.6), jinxBlue)); // V 21
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0.4, 0.9), jinxBlue)); // Z 22
        vertices.push_back(VertexFormat(glm::vec3(-0.85, 0.4, 0.6), jinxBlue)); // A1 23
        vertices.push_back(VertexFormat(glm::vec3(-0.6, 0.4, 0.85), jinxBlue)); // B1 24
        vertices.push_back(VertexFormat(glm::vec3(-0.85, 0.2, 0.6), jinxBlue)); // C1 25
        vertices.push_back(VertexFormat(glm::vec3(-0.6, 0.2, 0.85), jinxBlue)); // D1 26
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0.4, -0.7), jinxBlue)); // E1 27
        vertices.push_back(VertexFormat(glm::vec3(-0.7, 0.4, -0.9), jinxBlue)); // F1 28
        vertices.push_back(VertexFormat(glm::vec3(-0.85, 0.4, -0.6), jinxBlue)); // G1 29
        vertices.push_back(VertexFormat(glm::vec3(-0.6, 0.4, -0.85), jinxBlue)); // H1 30
        vertices.push_back(VertexFormat(glm::vec3(-0.85, 0.2, -0.6), jinxBlue)); // I1 31
        vertices.push_back(VertexFormat(glm::vec3(-0.6, 0.2, -0.85), jinxBlue)); // J1 32
        vertices.push_back(VertexFormat(glm::vec3(0.9, 0.4, -0.7), jinxBlue)); // K1 33
        vertices.push_back(VertexFormat(glm::vec3(0.7, 0.4, -0.9), jinxBlue)); // L1 34
        vertices.push_back(VertexFormat(glm::vec3(0.85, 0.4, -0.6), jinxBlue)); // M1 35
        vertices.push_back(VertexFormat(glm::vec3(0.6, 0.4, -0.85), jinxBlue)); // N1 36
        vertices.push_back(VertexFormat(glm::vec3(0.85, 0.2, -0.6), jinxBlue)); // O1 37
        vertices.push_back(VertexFormat(glm::vec3(0.6, 0.2, -0.85), jinxBlue)); // P1 38
        vertices.push_back(VertexFormat(glm::vec3(-0.9, 0.4, 0.7), jinxBlue)); // W 39

        indices.push_back(35); // M1 K1 L1
        indices.push_back(33);
        indices.push_back(34);

        indices.push_back(35); // M1 N1 L1
        indices.push_back(36);
        indices.push_back(34);

        indices.push_back(37); // O1 P1 N1
        indices.push_back(38);
        indices.push_back(36);

        indices.push_back(37); // O1 M1 N1
        indices.push_back(35);
        indices.push_back(36);

        indices.push_back(38); // P1 P L1
        indices.push_back(15);
        indices.push_back(34);

        indices.push_back(38); // P1 N1 L1
        indices.push_back(36);
        indices.push_back(34);

        indices.push_back(37); // O1 K K1
        indices.push_back(10);
        indices.push_back(33);

        indices.push_back(37); // O1 M1 K1
        indices.push_back(35);
        indices.push_back(33);

        indices.push_back(10); // K P L1
        indices.push_back(15);
        indices.push_back(34);

        indices.push_back(10); // K K1 L1
        indices.push_back(33);
        indices.push_back(34);

        indices.push_back(30); // H1 F1 E1
        indices.push_back(28);
        indices.push_back(27);

        indices.push_back(30); // H1 G1 E1
        indices.push_back(29);
        indices.push_back(27);

        indices.push_back(32); // J1 I1 G1
        indices.push_back(31);
        indices.push_back(29);

        indices.push_back(32); // J1 H1 G1
        indices.push_back(30);
        indices.push_back(29);

        indices.push_back(9); // J I1 G1
        indices.push_back(31);
        indices.push_back(29);

        indices.push_back(9); // J E1 G1
        indices.push_back(27);
        indices.push_back(29);

        indices.push_back(32); // J1 N F1
        indices.push_back(13);
        indices.push_back(28);

        indices.push_back(32); // J1 H1 F1
        indices.push_back(30);
        indices.push_back(28);

        indices.push_back(13); // N J E1
        indices.push_back(9);
        indices.push_back(27);

        indices.push_back(13); // N F1 E1
        indices.push_back(28);
        indices.push_back(27);

        indices.push_back(23); // A1 W Z
        indices.push_back(39);
        indices.push_back(22);

        indices.push_back(23); // A1 B1 Z
        indices.push_back(24);
        indices.push_back(22);

        indices.push_back(25); // C1 D1 B1
        indices.push_back(26);
        indices.push_back(24);

        indices.push_back(25); // C1 A1 B1
        indices.push_back(23);
        indices.push_back(24);

        indices.push_back(26); // D1 M Z
        indices.push_back(12);
        indices.push_back(22);

        indices.push_back(26); // D1 B1 Z
        indices.push_back(24);
        indices.push_back(22);

        indices.push_back(25); // C1 I W
        indices.push_back(8);
        indices.push_back(39);

        indices.push_back(25); // C1 A1 W
        indices.push_back(23);
        indices.push_back(39);

        indices.push_back(8); // I M Z
        indices.push_back(12);
        indices.push_back(22);

        indices.push_back(8); // I W Z
        indices.push_back(39);
        indices.push_back(22);

        indices.push_back(18); // S Q R
        indices.push_back(16);
        indices.push_back(17);

        indices.push_back(18); // S T R
        indices.push_back(19);
        indices.push_back(17);

        indices.push_back(21); // V L R
        indices.push_back(11);
        indices.push_back(17);

        indices.push_back(21); // V T R
        indices.push_back(19);
        indices.push_back(17);

        indices.push_back(20); // U S T
        indices.push_back(18);
        indices.push_back(19);

        indices.push_back(20); // U V T
        indices.push_back(21);
        indices.push_back(19);

        indices.push_back(20); // U O Q
        indices.push_back(14);
        indices.push_back(16);

        indices.push_back(20); // U S Q
        indices.push_back(18);
        indices.push_back(16);

        indices.push_back(14); // O L R
        indices.push_back(11);
        indices.push_back(17);

        indices.push_back(14); // O Q R
        indices.push_back(16);
        indices.push_back(17);

        indices.push_back(14); // O L N
        indices.push_back(11);
        indices.push_back(13);

        indices.push_back(14); // O J N
        indices.push_back(9);
        indices.push_back(13);

        indices.push_back(7); // H G L
        indices.push_back(6);
        indices.push_back(11);

        indices.push_back(7); // H O L
        indices.push_back(14);
        indices.push_back(11);
         
        indices.push_back(7); // H E J
        indices.push_back(4);
        indices.push_back(9);

        indices.push_back(7); // H O J
        indices.push_back(14);
        indices.push_back(9);

        indices.push_back(4); // E F N
        indices.push_back(5);
        indices.push_back(13);

        indices.push_back(4); // E J N
        indices.push_back(9);
        indices.push_back(13);

        indices.push_back(6); // G L N
        indices.push_back(11);
        indices.push_back(13);

        indices.push_back(6); // G F N
        indices.push_back(5);
        indices.push_back(13);

        indices.push_back(7); // H E F
        indices.push_back(4);
        indices.push_back(5);

        indices.push_back(7); // H G F
        indices.push_back(6);
        indices.push_back(5);

        indices.push_back(0); // A B C
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(0); // A D C
        indices.push_back(3);
        indices.push_back(2);

        indices.push_back(12); // M B C
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(12); // M K C
        indices.push_back(10);
        indices.push_back(2);

        indices.push_back(2); // C D P
        indices.push_back(3);
        indices.push_back(15);

        indices.push_back(2); // C K P
        indices.push_back(10);
        indices.push_back(15);

        indices.push_back(0); // A D P
        indices.push_back(3);
        indices.push_back(15);

        indices.push_back(0); // A I P
        indices.push_back(8);
        indices.push_back(15);

        indices.push_back(0); // A B M
        indices.push_back(1);
        indices.push_back(12);

        indices.push_back(0);// A I M
        indices.push_back(8);
        indices.push_back(12);

        indices.push_back(8); // I M K
        indices.push_back(12);
        indices.push_back(10);

        indices.push_back(8); // I P K
        indices.push_back(15);
        indices.push_back(10);

        Mesh* mesh = new Mesh("drone");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);

    }

    glCreateBuffers(1, &vertex_height_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertex_height_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 300 * 300 * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);

    {
        lightPosition = glm::vec3(0, 1, 1);
        materialShininess = 0;
        materialKd = 0.5;
        materialKs = 0.5;
    }
    InitTerrain();

}

void Lab7::createCheckPoints(glm::vec3 color, char name[100]) {
    vector<VertexFormat> vertices;
    vector<unsigned int> indices;
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color)); // A 0
    vertices.push_back(VertexFormat(glm::vec3(0, 8, 0), color)); // B 1
    vertices.push_back(VertexFormat(glm::vec3(0.25, 0, 0), color)); // C 2
    vertices.push_back(VertexFormat(glm::vec3(0.25, 8, 0), color)); // D 3
    vertices.push_back(VertexFormat(glm::vec3(2.5, 0, 0), color)); // E 4
    vertices.push_back(VertexFormat(glm::vec3(2.75, 0, 0), color)); // F 5
    vertices.push_back(VertexFormat(glm::vec3(2.5, 8, 0), color)); // G 6
    vertices.push_back(VertexFormat(glm::vec3(2.75, 8, 0), color)); // H 7
    vertices.push_back(VertexFormat(glm::vec3(0, 0, -0.25), color)); // I 8
    vertices.push_back(VertexFormat(glm::vec3(0.25, 0, -0.25), color)); // J 9
    vertices.push_back(VertexFormat(glm::vec3(0, 8, -0.25), color)); // K 10
    vertices.push_back(VertexFormat(glm::vec3(0.25, 8, -0.25), color)); // L 11
    vertices.push_back(VertexFormat(glm::vec3(2.5, 0, -0.25), color)); // M 12
    vertices.push_back(VertexFormat(glm::vec3(2.75, 0, -0.25), color)); // N 13
    vertices.push_back(VertexFormat(glm::vec3(2.5, 8, -0.25), color)); // O 14
    vertices.push_back(VertexFormat(glm::vec3(2.75, 8, -0.25), color)); // P 15
    vertices.push_back(VertexFormat(glm::vec3(4.75, 8, 0), color)); // Q 16
    vertices.push_back(VertexFormat(glm::vec3(4.75, 8, -0.25), color)); // R 17
    vertices.push_back(VertexFormat(glm::vec3(-2, 8, 0), color)); // S 18
    vertices.push_back(VertexFormat(glm::vec3(-2, 8, -0.25), color)); // T 19
    vertices.push_back(VertexFormat(glm::vec3(4.75, 8.25, 0), color)); // U 20
    vertices.push_back(VertexFormat(glm::vec3(4.75, 8.25, -0.25), color)); // V 21
    vertices.push_back(VertexFormat(glm::vec3(-2, 8.25, 0), color)); // W 22
    vertices.push_back(VertexFormat(glm::vec3(-2, 8.25, -0.25), color)); // Z 23
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 8.25, 0), color)); // A1 24
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 8.25, -0.25), color)); // B1 25
    vertices.push_back(VertexFormat(glm::vec3(4.5, 8.25, 0), color)); // C1 26
    vertices.push_back(VertexFormat(glm::vec3(4.5, 8.25, -0.25), color)); // D1 27
    vertices.push_back(VertexFormat(glm::vec3(-2, 15, 0), color)); // E1 28
    vertices.push_back(VertexFormat(glm::vec3(-2, 15, -0.25), color)); // F1 29
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 15, -0.25), color)); // G1 30
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 15, 0), color)); // H1 31
    vertices.push_back(VertexFormat(glm::vec3(4.75, 15, 0), color)); // I1 32
    vertices.push_back(VertexFormat(glm::vec3(4.75, 15, -0.25), color)); // J1 33
    vertices.push_back(VertexFormat(glm::vec3(4.5, 15, 0), color)); // K1 34
    vertices.push_back(VertexFormat(glm::vec3(4.5, 15, -0.25), color)); // L1 35
    vertices.push_back(VertexFormat(glm::vec3(4.5, 14.75, 0), color)); // M1 36
    vertices.push_back(VertexFormat(glm::vec3(4.5, 14.75, -0.25), color)); // N1 37
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 14.75, 0), color)); // O1 38
    vertices.push_back(VertexFormat(glm::vec3(-1.75, 14.75, -0.25), color)); // P1 39

    indices.push_back(34); // K1 H1 G1
    indices.push_back(31);
    indices.push_back(30);

    indices.push_back(34); // K1 L1 G1
    indices.push_back(35);
    indices.push_back(30);

    indices.push_back(36); // M1 K1 H1
    indices.push_back(34);
    indices.push_back(31);

    indices.push_back(36); // M1 O1 H1
    indices.push_back(38);
    indices.push_back(31);

    indices.push_back(38); // O1 M1 N1
    indices.push_back(36);
    indices.push_back(37);

    indices.push_back(38); // O1 P1 N1
    indices.push_back(39);
    indices.push_back(37);

    indices.push_back(35); // L1 G1 P1
    indices.push_back(30);
    indices.push_back(39);

    indices.push_back(35); // L1 N1 P1
    indices.push_back(37);
    indices.push_back(39);

    indices.push_back(26); // C1 K1 I1
    indices.push_back(34);
    indices.push_back(32);

    indices.push_back(26); // C1 U I1
    indices.push_back(20);
    indices.push_back(32);

    indices.push_back(26); // C1 K1 L1
    indices.push_back(34);
    indices.push_back(35);

    indices.push_back(26); // C1 D1 L1
    indices.push_back(27);
    indices.push_back(35);

    indices.push_back(27); // D1 L1 J1
    indices.push_back(35);
    indices.push_back(33);

    indices.push_back(27); // D1 V J1
    indices.push_back(21);
    indices.push_back(33);

    indices.push_back(20); // U I1 J1
    indices.push_back(32);
    indices.push_back(33);

    indices.push_back(20); // U V J1
    indices.push_back(21);
    indices.push_back(33);

    indices.push_back(23); // Z F1 G1
    indices.push_back(29);
    indices.push_back(30);

    indices.push_back(23); // Z B1 G1
    indices.push_back(25);
    indices.push_back(30);

    indices.push_back(22); // W Z F1
    indices.push_back(23);
    indices.push_back(29);

    indices.push_back(22); // W E1 F1
    indices.push_back(28);
    indices.push_back(29);

    indices.push_back(22); // W E1 H1
    indices.push_back(28);
    indices.push_back(31);

    indices.push_back(22); // W A1 H1
    indices.push_back(24);
    indices.push_back(31);

    indices.push_back(24); // A1 H1 G1
    indices.push_back(31);
    indices.push_back(30);

    indices.push_back(24); // A1 B1 G1
    indices.push_back(25);
    indices.push_back(30);

    indices.push_back(23); // Z V W
    indices.push_back(21);
    indices.push_back(20);

    indices.push_back(23); // Z W U
    indices.push_back(22);
    indices.push_back(20);

    indices.push_back(23); // Z V R
    indices.push_back(21);
    indices.push_back(17);

    indices.push_back(23); // Z T R
    indices.push_back(19);
    indices.push_back(17);

    indices.push_back(16); // Q R V
    indices.push_back(17);
    indices.push_back(21);

    indices.push_back(16); // Q U V
    indices.push_back(20);
    indices.push_back(21);

    indices.push_back(22); // W S Q
    indices.push_back(18);
    indices.push_back(16);

    indices.push_back(22); // W U Q
    indices.push_back(20);
    indices.push_back(16);

    indices.push_back(19); // T Z W
    indices.push_back(23);
    indices.push_back(22);

    indices.push_back(19); // T S W
    indices.push_back(18);
    indices.push_back(22);

    indices.push_back(18); // S T R
    indices.push_back(19);
    indices.push_back(17);

    indices.push_back(18); // S Q R
    indices.push_back(16);
    indices.push_back(17);

    indices.push_back(6); // G O P
    indices.push_back(14);
    indices.push_back(15);

    indices.push_back(6); // G H P
    indices.push_back(7);
    indices.push_back(15);

    indices.push_back(5); // F H P
    indices.push_back(7);
    indices.push_back(15);

    indices.push_back(5); // F N P
    indices.push_back(13);
    indices.push_back(15);

    indices.push_back(12); // M N P
    indices.push_back(13);
    indices.push_back(15);

    indices.push_back(12); // M O P
    indices.push_back(14);
    indices.push_back(15);

    indices.push_back(4); // E G O
    indices.push_back(6);
    indices.push_back(14);

    indices.push_back(4); // E M O
    indices.push_back(12);
    indices.push_back(14);

    indices.push_back(4); // E F N
    indices.push_back(5);
    indices.push_back(13);

    indices.push_back(4); // E M N
    indices.push_back(12);
    indices.push_back(13);

    indices.push_back(1); // B D L
    indices.push_back(3);
    indices.push_back(11);

    indices.push_back(1); // B K L
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(8); // I J L
    indices.push_back(9);
    indices.push_back(11);

    indices.push_back(8); // I K L
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(0); // A I K
    indices.push_back(8);
    indices.push_back(10);

    indices.push_back(0); // A B K
    indices.push_back(1);
    indices.push_back(10);

    indices.push_back(2); // C J L
    indices.push_back(9);
    indices.push_back(11);

    indices.push_back(2); // C D L
    indices.push_back(3);
    indices.push_back(11);

    indices.push_back(0); // A I J
    indices.push_back(8);
    indices.push_back(9);

    indices.push_back(0); // A C J
    indices.push_back(2);
    indices.push_back(9);

    indices.push_back(4); // E F H
    indices.push_back(5);
    indices.push_back(7);

    indices.push_back(4); // E G H
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(0); // A B D
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(0); // A C D
    indices.push_back(2);
    indices.push_back(3);

    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);
    AddMeshToList(mesh);
}

void Lab7::InitAfter() {
    createRandomCheckPoints();
    createRandomHouses();
    createRandomPos();
    createCheckPoints(glm::vec3(1, 0, 0), "checkPoint_red");
    createCheckPoints(glm::vec3(0, 1, 0), "checkPoint_green");
    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        vertices.push_back(VertexFormat(glm::vec3(0, matrix[0][0], 0), glm::vec3(1, 0, 0))); // 0
        vertices.push_back(VertexFormat(glm::vec3(0, matrix[0][1], 1), glm::vec3(1, 0, 0))); // 2
        vertices.push_back(VertexFormat(glm::vec3(1, matrix[1][1], 1), glm::vec3(1, 0, 0))); // 1

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        Mesh* mesh = new Mesh("testing");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);

    }

    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;

        vertices.push_back(VertexFormat(glm::vec3(5, matrix[5][5], 5), glm::vec3(1, 0, 0))); // 0
        vertices.push_back(VertexFormat(glm::vec3(5, matrix[5][6], 6), glm::vec3(1, 0, 0))); // 2
        vertices.push_back(VertexFormat(glm::vec3(6, matrix[6][6], 6), glm::vec3(1, 0, 0))); // 1

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        Mesh* mesh = new Mesh("testing2");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);
    }
    {
        vector<VertexFormat> vertices;
        vector<unsigned int> indices;
        glm::vec3 azure = glm::vec3(0.67, 0.84, 0.9);
        glm::vec3 beige = glm::vec3(0.85, 0.76, 0.63);
        glm::vec3 beige_grey = glm::vec3(0.45, 0.41, 0.36);
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), beige)); // A 0
        vertices.push_back(VertexFormat(glm::vec3(0, 0, 10), beige)); // B 1
        vertices.push_back(VertexFormat(glm::vec3(10, 0, 0), beige)); // C 2
        vertices.push_back(VertexFormat(glm::vec3(10, 0, 10), beige)); // D 3
        vertices.push_back(VertexFormat(glm::vec3(0, 16, 0), beige)); // E 4
        vertices.push_back(VertexFormat(glm::vec3(10, 16, 0), beige)); // F 5
        vertices.push_back(VertexFormat(glm::vec3(0, 16, 10), beige)); // G 6
        vertices.push_back(VertexFormat(glm::vec3(10, 16, 10), beige)); // H 7
        vertices.push_back(VertexFormat(glm::vec3(4.5, 0, 10), beige_grey)); // I 8
        vertices.push_back(VertexFormat(glm::vec3(5.5, 0, 10), beige_grey)); // J 9
        vertices.push_back(VertexFormat(glm::vec3(4.5, 1.5, 10), beige_grey)); // K 10
        vertices.push_back(VertexFormat(glm::vec3(5.5, 1.5, 10), beige_grey)); // L 11
        vertices.push_back(VertexFormat(glm::vec3(6, 5, 10), azure)); // M 12
        vertices.push_back(VertexFormat(glm::vec3(8, 5, 10), azure)); // N 13
        vertices.push_back(VertexFormat(glm::vec3(6, 7, 10), azure)); // O 14
        vertices.push_back(VertexFormat(glm::vec3(8, 7, 10), azure)); // P 15
        vertices.push_back(VertexFormat(glm::vec3(4, 5, 10), azure)); // Q 16
        vertices.push_back(VertexFormat(glm::vec3(4, 7, 10), azure)); // R 17
        vertices.push_back(VertexFormat(glm::vec3(2, 5, 10), azure)); // S 18
        vertices.push_back(VertexFormat(glm::vec3(2, 7, 10), azure)); // T 19
        vertices.push_back(VertexFormat(glm::vec3(6, 10, 10), azure)); // U 20
        vertices.push_back(VertexFormat(glm::vec3(8, 10, 10), azure)); // V 21
        vertices.push_back(VertexFormat(glm::vec3(6, 12, 10), azure)); // W 22
        vertices.push_back(VertexFormat(glm::vec3(8, 12, 10), azure)); // Z 23
        vertices.push_back(VertexFormat(glm::vec3(4, 10, 10), azure)); // A1 24
        vertices.push_back(VertexFormat(glm::vec3(4, 12, 10), azure)); // B1 25
        vertices.push_back(VertexFormat(glm::vec3(2, 12, 10), azure)); // C1 26
        vertices.push_back(VertexFormat(glm::vec3(2, 10, 10), azure)); // D1 27
        vertices.push_back(VertexFormat(glm::vec3(2, 0, 10), beige)); // E1 28
        vertices.push_back(VertexFormat(glm::vec3(2, 16, 10), beige)); // F1 29
        vertices.push_back(VertexFormat(glm::vec3(8, 0, 10), beige)); // G1 30
        vertices.push_back(VertexFormat(glm::vec3(8, 16, 10), beige)); // H1 31
        vertices.push_back(VertexFormat(glm::vec3(0, 5, 10), beige)); // I1 32
        vertices.push_back(VertexFormat(glm::vec3(10, 5, 10), beige)); // J1 33
        vertices.push_back(VertexFormat(glm::vec3(0, 12, 10), beige)); // K1 34
        vertices.push_back(VertexFormat(glm::vec3(10, 12, 10), beige)); // L1 35
        vertices.push_back(VertexFormat(glm::vec3(4.5, 5, 10), beige)); // M1 36
        vertices.push_back(VertexFormat(glm::vec3(5.5, 5, 10), beige)); // N1 37
        vertices.push_back(VertexFormat(glm::vec3(4, 12, 10), beige)); // O1 38
        vertices.push_back(VertexFormat(glm::vec3(6, 12, 10), beige)); // P1 39
        vertices.push_back(VertexFormat(glm::vec3(4, 5, 10), beige)); // Q1 40
        vertices.push_back(VertexFormat(glm::vec3(6, 5, 10), beige)); // R1 41
        vertices.push_back(VertexFormat(glm::vec3(2, 7, 10), beige)); // S1 42
        vertices.push_back(VertexFormat(glm::vec3(2, 10, 10), beige)); // T1 43
        vertices.push_back(VertexFormat(glm::vec3(8, 10, 10), beige)); // U1 44
        vertices.push_back(VertexFormat(glm::vec3(8, 7, 10), beige)); // V1 45
        vertices.push_back(VertexFormat(glm::vec3(4.5, 0, 10), beige)); // W1 46
        vertices.push_back(VertexFormat(glm::vec3(5.5, 0, 10), beige)); // Z1 47
        vertices.push_back(VertexFormat(glm::vec3(4.5, 1.5, 10), beige)); // A2 48
        vertices.push_back(VertexFormat(glm::vec3(5.5, 1.5, 10), beige)); // B2 49

        indices.push_back(48); // A2 B2 N1
        indices.push_back(49);
        indices.push_back(37);

        indices.push_back(48); // A2 M1 N1
        indices.push_back(36);
        indices.push_back(37);

        indices.push_back(47); // Z1 D J1
        indices.push_back(3);
        indices.push_back(33);

        indices.push_back(47); // Z1 N1 J1
        indices.push_back(37);
        indices.push_back(33);

        indices.push_back(1); // B W1 M1
        indices.push_back(46);
        indices.push_back(36);

        indices.push_back(1); // B I1 M1
        indices.push_back(32);
        indices.push_back(36);

        indices.push_back(8); // I J L
        indices.push_back(9);
        indices.push_back(11);

        indices.push_back(8); // I K L
        indices.push_back(10);
        indices.push_back(11);

        indices.push_back(42); // S1 T1 U1
        indices.push_back(43);
        indices.push_back(44);

        indices.push_back(42); // S1 V1 U1
        indices.push_back(45);
        indices.push_back(44);

        indices.push_back(30); // G1 D H
        indices.push_back(3);
        indices.push_back(7);

        indices.push_back(30); // G1 H1 H
        indices.push_back(31);
        indices.push_back(7);

        indices.push_back(39); // P1 R1 Q1
        indices.push_back(40);
        indices.push_back(41);

        indices.push_back(39); // P1 O1 R1
        indices.push_back(38);
        indices.push_back(40);

        indices.push_back(1); // B E1 F1
        indices.push_back(28);
        indices.push_back(29);

        indices.push_back(1); // B G F1
        indices.push_back(6);
        indices.push_back(29);

        indices.push_back(6); // G K1 L1
        indices.push_back(34);
        indices.push_back(35);

        indices.push_back(6); // G H L1
        indices.push_back(7);
        indices.push_back(35);

        indices.push_back(12); // M O P
        indices.push_back(14);
        indices.push_back(15);

        indices.push_back(12); // M N P
        indices.push_back(13);
        indices.push_back(15);

        indices.push_back(18); // S Q R
        indices.push_back(16);
        indices.push_back(17);

        indices.push_back(18); // S T R
        indices.push_back(19);
        indices.push_back(17);

        indices.push_back(20); // U V Z
        indices.push_back(21);
        indices.push_back(23);

        indices.push_back(20); // U W Z
        indices.push_back(22);
        indices.push_back(23);

        indices.push_back(24); // A1 B1 C1
        indices.push_back(25);
        indices.push_back(26);

        indices.push_back(24); // A1 D1 C1
        indices.push_back(27);
        indices.push_back(26);

        indices.push_back(4); // E F H
        indices.push_back(5);
        indices.push_back(7);

        indices.push_back(4); // E G H
        indices.push_back(6);
        indices.push_back(7);

        indices.push_back(3); // D H F
        indices.push_back(7);
        indices.push_back(5);

        indices.push_back(3); // D C F
        indices.push_back(2);
        indices.push_back(5);

        indices.push_back(0); // A C F
        indices.push_back(2);
        indices.push_back(5);

        indices.push_back(0); // A E F
        indices.push_back(4);
        indices.push_back(5);

        indices.push_back(0); // A B G
        indices.push_back(1);
        indices.push_back(6);

        indices.push_back(0); // A E G
        indices.push_back(4);
        indices.push_back(6);


        indices.push_back(0); // A B C
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(1); // B C D
        indices.push_back(2);
        indices.push_back(3);


        Mesh* mesh = new Mesh("house");
        mesh->InitFromData(vertices, indices);
        AddMeshToList(mesh);
    }
}


void Lab7::FrameStart()
{
    glClearColor(0.16, 0.36, 0.67, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}
const int width = 300;

void getHeight(GLfloat* height_t) {
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            matrix[i][j] = height_t[i + j * 300];
        }
    }
}

void Lab7::UpdateBlades(glm::mat4 modelMatrix) {
    for (int i = 0; i < 4; i++) {
        glm::vec4 updatedPoint = modelMatrix * glm::vec4(middleX[i].x, middleX[i].y, middleX[i].z, 1);
        updatedX[i].x = updatedPoint.x;
        updatedX[i].y = updatedPoint.y;
        updatedX[i].z = updatedPoint.z;
    }
}

void Lab7::PrepareBlade(glm::mat4 &modelMatrix, float deltaTimeSeconds, float &rotateX, glm::vec3 updatedX) {
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(updatedX.x, updatedX.y, updatedX.z));
    if (weirdVar) {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-pitchtAngle), camera->right);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-yawAngle), camera->forward);
        modelMatrix = glm::rotate(modelMatrix, rotateOz, camera->up);
    }
    else {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(pitchtAngle), camera->right);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(yawAngle), camera->forward);
        modelMatrix = glm::rotate(modelMatrix, rotateOz, camera->up);

    }
    if (rotateX != -1) {
        modelMatrix = glm::rotate(modelMatrix, rotateX, glm::vec3(0, 1, 0));
        rotateX += 50 * deltaTimeSeconds;
    }
}

void Lab7::RenderScene(float deltaTimeSeconds, implemented::Camera *currentCamera) {
    static int x = 0;
    if (!x)
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vertex_height_buffer);

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["terrain"], shaders["LabShader"], modelMatrix, currentCamera,glm::vec3(0, 0, 0.69), 1);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(dronePozX, dronePozY, dronePozZ));
        if (weirdVar) {
            modelMatrix = glm::rotate(modelMatrix, glm::radians(-pitchtAngle), currentCamera->right);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(-yawAngle), currentCamera->forward);
            modelMatrix = glm::rotate(modelMatrix, rotateOz, currentCamera->up);
            UpdateBlades(modelMatrix);
        }
        else {
            modelMatrix = glm::rotate(modelMatrix, glm::radians(pitchtAngle), currentCamera->right);
            modelMatrix = glm::rotate(modelMatrix, glm::radians(yawAngle), currentCamera->forward);
            modelMatrix = glm::rotate(modelMatrix, rotateOz, currentCamera->up);
            UpdateBlades(modelMatrix);
        }
        if(currentCamera != camera)
            modelMatrix = glm::scale(modelMatrix, glm::vec3(5,5,5));
        RenderSimpleMesh(meshes["drone"], shaders["LabShader"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
    }

    {
        for (int i = 0; i < 4; i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            PrepareBlade(modelMatrix, deltaTimeSeconds, rotateOne, updatedX[i]);
            RenderSimpleMesh(meshes["zoom_zoom"], shaders["LabShader"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
        }
    }

    {
        for (int i = 0; i < treePos.size(); i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, treePos[i]);
            modelMatrix = glm::scale(modelMatrix, treeScale[i]);
            RenderSimpleMesh(meshes["tree"], shaders["LabShader"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
        }
    }

    if (waitOne)
    {
        for (int i = 0; i < housePos.size(); i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, housePos[i]);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 8, 5));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateRand[i]), glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -8, -5));
            RenderSimpleMesh(meshes["house"], shaders["LabShader"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
        }
        for (int i = 0; i < points.size(); i++) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(points[i].checkPointPos.x, points[i].checkPointPos.y, points[i].checkPointPos.z));
            if (currentCamera != camera) {
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 15));
            }
            if (points[i].state != 1)
                RenderSimpleMesh(meshes["checkPoint_red"], shaders["VertexColor"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
            else
                RenderSimpleMesh(meshes["checkPoint_green"], shaders["VertexColor"], modelMatrix, currentCamera, glm::vec3(0.69, 0.87, 0.9));
        }
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(dronePozX, dronePozY, dronePozZ));
        glm::vec3 targetPos = glm::vec3(0);
        for (int i = 0; i < points.size(); i++) {
            if (points[i].state) {
                targetPos = points[i].checkPointPos;
                break;
            }
        }

        glm::vec3 direction = glm::normalize(targetPos - glm::vec3(dronePozX, dronePozY, dronePozZ));
        float angle = acos(glm::dot(glm::normalize(camera->forward), direction));
        if (targetPos.x == 0 && targetPos.y == 0 && targetPos.z == 0) {
            angle = 0;
        }
        float side = glm::dot(camera->right, direction);
        if (side > 0) {
            angle *= -1.0f;
        }

        if (weirdVar) {
            modelMatrix = glm::rotate(modelMatrix, rotateOz, camera->up);
        }
        else {
            modelMatrix = glm::rotate(modelMatrix, rotateOz, camera->up);
        }
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 9, -11));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.625, -0.125));
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.625, 0.125));
        RenderSimpleMesh(meshes["arrow"], shaders["LabShader"], modelMatrix, currentCamera, glm::vec3(0.69f, 0.87f, 0.9f));

    }

    if (!x) {
        GLfloat* height_t = (GLfloat*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 300 * 300 * sizeof(GLfloat), GL_MAP_READ_BIT);
        for (int i = 0; i < 300; i++) {
            heights[i] = height_t[i];
        }
        vector<std::vector<float>> heightMap(300, std::vector<float>(300));
        getHeight(height_t);
        InitAfter();
        waitOne = 1;
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    }
    x++;
}


void Lab7::Update(float deltaTimeSeconds)
{
    glm::ivec2 res = window->GetResolution();
    glViewport(0, 0, res.x, res.y);
    if (res.x == 0 || res.y == 0) {
        res.x = 1;
        res.y = 1;
    }
    projectionMatrix = glm::perspective(glm::radians(fov), (float)res.x/res.y, nearPlane, farPlane);
    RenderScene(deltaTimeSeconds, camera);
    PrintText();

    glClear(GL_DEPTH_BUFFER_BIT);
    miniMap = ViewPortArea(50, 50, res.x / 5.f, res.y / 5.f);
    glViewport(miniMap.x, miniMap.y, miniMap.width, miniMap.height);
    orthoLeft = -150;
    orthoRight = 150;
    orthoBottom = -150;
    orthoTop = 150;
    projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, nearPlane, farPlane);
    glm::vec3 cameraPosition = glm::vec3(150, 100.0f, 150);
    glm::vec3 cameraTarget = glm::vec3(150, 0, 150);
    glm::vec3 upVector = glm::vec3(0.0f,0.0f, -1.0f);
    camera_minimap->Set(cameraPosition, cameraTarget, upVector);
    RenderScene(deltaTimeSeconds, camera_minimap);
}

void Lab7::PrintText() {
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    static int minutes = 1;
    static int seconds = 59;
    const float kTopY = 10.f;
    const float kRowHeight = 25.f;
    int rowIndex = 0;
    static int playOnce = 0;
    const glm::vec3 kTextColor = NormalizedRGB(0, 0, 0);
    glm::ivec2 resolution = window->GetResolution();
    if (resolution.x != widthStart || resolution.y != heightStart) {
        textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
        textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);
        widthStart = resolution.x;
        heightStart = resolution.y;
    }

    if (currentTime - lastTime >= 1000 && currentCheckPoint != points.size()) {
        lastTime = currentTime;
        if (seconds != 0)
            seconds--;
        if (seconds == 0 && minutes != 0) {
            seconds = 59;
            minutes--;
        }
    }
    if (seconds == 0 && minutes == 0) {
        lost = 1;
    }
    string time = to_string(minutes) + ":" + to_string(seconds);
    string score = to_string(currentCheckPoint) + "/" + to_string(points.size());
    textRenderer->RenderText(time, resolution.x - 220, kTopY + kRowHeight * rowIndex++, 4, kTextColor);
    textRenderer->RenderText(score, resolution.x - 220, kTopY + kRowHeight * rowIndex++ + 40, 4, kTextColor);
    if (currentCheckPoint == points.size()) {
        textRenderer->RenderText("VICTORY", resolution.x / 2 - 300, resolution.y / 2, 8, kTextColor);
        if (!playOnce) {
            Mix_PlayChannel(3, victory, 0);
            playOnce = 1;
        }
    }
    else if (lost) {
        textRenderer->RenderText("LOST", resolution.x / 2 - 180, resolution.y / 2, 8, kTextColor);
        if (!playOnce) {
            Mix_PlayChannel(3, lostS, 0);
            playOnce = 1;
        }
    }
   
}


void Lab7::FrameEnd()
{
    
}

void Lab7::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera* cam, const glm::vec3& color, int garbage)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;
    int type = 0;
    glUseProgram(shader->program);

    if (garbage == 1) {
        type = 1;
    }
    GLint material_shininess_loc = glGetUniformLocation(shader->program, "type");
    glUniform1i(material_shininess_loc, type);

    GLint material_kd_loc = glGetUniformLocation(shader->program, "maxDrone");
    materialKd = dronePozY;
    glUniform1f(material_kd_loc, materialKd);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glm::mat4 viewMatrix = cam->GetViewMatrix();

    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);

    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Lab7::OnInputUpdate(float deltaTime, int mods)
{
        static int boom = 0;
        static float saveRotate = 0;
        static int direction = 1;
        glm::vec3 forwardDir = glm::vec3(cos(glm::radians(pitchtAngle)), sin(glm::radians(pitchtAngle)), 0);
        glm::vec3 leftDir = glm::vec3(cos(glm::radians(yawAngle)), sin(glm::radians(yawAngle)), 0);
        static int invertAscend = 0;
        static int block = 0;
        if (!block) {
            if (!Mix_Playing(2)) {
                Mix_PlayChannel(2,droneFly,0);
            }
        }
        else {
            Mix_HaltChannel(2);
        }

        if (dronePozX >= 0 && dronePozZ >= 0 && dronePozX < 300 && dronePozZ < 300) {
            if (matrix[dronePozX][dronePozZ] >= dronePozY) {
                block = 1;
            }
        }
        if (block) {
            if (rotateOne != -1) {
                saveRotate = rotateOne;
                rotateOne = -1;
            }
        }
        for (int i = 0; i < points.size(); i++) {
            int var = 0;
            int xPoz = points[i].checkPointPos.x;
            int yPoz = points[i].checkPointPos.y;
            int zPoz = points[i].checkPointPos.z;
            if (points[i].state) {
                if (dronePozX >= xPoz - 1.75 && dronePozX <= xPoz + 4.5) {
                    if (dronePozY >= yPoz + 8.25 && dronePozY <= yPoz + 14.75) {
                        if (dronePozZ >= zPoz - 0.25 && dronePozZ <= zPoz) {
                            points[i].state = 0;
                            if (i + 1 < points.size()) {
                                points[i + 1].state = 1;
                                if (!lost) {
                                    currentCheckPoint++;
                                    Mix_PlayChannel(1, passCheck, 0);
                                }
                            }
                            else {
                                if (!lost) {
                                    currentCheckPoint++;
                                    Mix_PlayChannel(1, passCheck, 0);
                                }
                            }
                        }
                    }
                }
                if (lost) {
                    points[i].state = 0;
                }
            }
            for (int j = 0; j < points[i].checkPointsBoxes.size(); j++) {

                var += intersect(points[i].checkPointsBoxes[j]);
                if (var) {
                    Mix_PlayChannel(6, hitCheck, 0);
                }
            }
            if (var) {
                speed = 12;
                if (forwardDir.y < 0) {
                    direction = -1;
                }
                else {
                    direction = 1;
                }
                boom = deltaTime * 10000 * 2;
            }
        }
        for (int i = 0; i < treePos.size(); i++) {
            int var = intersect(treeBox[i]);
            if (var) {
                speed = 12;
                Mix_PlayChannel(4, hitTree, 0);
                if (forwardDir.y < 0) {
                    direction = -1;
                }
                else {
                    direction = 1;
                }
                boom = deltaTime * 10000 * 2;
            }
        }
        for (int i = 0; i < housePos.size(); i++) {
            int var = intersect(houseBox[i]);
            if (var) {
                Mix_PlayChannel(5, hitWall, 0);
                speed = 12;
                if (forwardDir.y < 0) {
                    direction = -1;
                }
                else {
                    direction = 1;
                }
                boom = deltaTime * 10000 * 2;
            }
        }

        glm::vec3 movement = glm::vec3(0.0f);
        int incrementSpeed = 0;
        if (window->KeyHold(GLFW_KEY_LEFT_SHIFT)) {
            if (!invertAscend) {
                if (block) {
                    rotateOne = saveRotate;
                }
                block = 0;
            }
        }

        if (boom == 0 && !block) {
            if (pitchtAngle >= 0 + FLT_EPSILON || pitchtAngle < 0) {

                if (fabs(forwardDir.y) > 0.05) {
                    if (forwardDir.y < 0 + FLT_EPSILON) {
                        camera->TranslateForward(speed * deltaTime);
                        movement += camera->forward;
                    }
                    else if (forwardDir.y > 0 + FLT_EPSILON) {
                        camera->TranslateForward(-speed * deltaTime);
                        movement -= camera->forward;
                    }
                }
            }
            if (yawAngle >= 0 + FLT_EPSILON || yawAngle < 0) {
                if (fabs(leftDir.y) > 0.05) {
                    if (leftDir.y < 0 + FLT_EPSILON) {
                        camera->TranslateRight(-speed * deltaTime);
                        movement -= camera->right;
                    }
                    else if (leftDir.y > 0 + FLT_EPSILON) {
                        camera->TranslateRight(speed * deltaTime);
                        movement += camera->right;
                    }
                }
            }
        }
        else if(!block) {
            boom--;
            if (pitchtAngle >= 0 + FLT_EPSILON || pitchtAngle < 0) {
                if (fabs(forwardDir.y) > 0.05) {
                    if (direction < 0) {
                        camera->TranslateForward(-speed * deltaTime);
                        movement -= camera->forward;
                    }
                    else if (forwardDir.y > 0) {
                        camera->TranslateForward(speed * deltaTime);
                        movement += camera->forward;
                    }
                }
            }
        }
        if (window->KeyHold(GLFW_KEY_LEFT_SHIFT) && boom == 0) {
            if (!invertAscend) {
                block = 0;
                camera->TranslateUpward(speed * deltaTime);
                movement += camera->up;
            }
            else if(dronePozY > 0 && !block) {
                camera->TranslateUpward(-speed * deltaTime);
                movement -= camera->up;
            }
            incrementSpeed = 1;
        } else if (dronePozY > 1) {
            if (boom == 0 && !block) {
                camera->TranslateUpward(-speed * deltaTime);
                movement -= camera->up;
            }
        }
        if (window->KeyHold(GLFW_KEY_W)) {
            pitchtAngle += 1;
 
        }
        else if (window->KeyHold(GLFW_KEY_S)) {
            pitchtAngle -= 1;
 
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            if (!weirdVar) {
                yawAngle -= 1;
            }
            else {
                yawAngle += 1;
            }
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            if (!weirdVar) {
                yawAngle += 1;
            }
            else {
                yawAngle -= 1;
            }
        }
        dronePozX += movement.x * speed * deltaTime;
        dronePozY += movement.y * speed * deltaTime;
        dronePozZ += movement.z * speed * deltaTime;
        if (window->KeyHold(GLFW_KEY_LEFT)) {
            rotateOz += deltaTime * 5;
            weirdVar = 1;
            camera->RotateAroundDrone(deltaTime * 5, glm::vec3(dronePozX, dronePozY, dronePozZ));
        }
        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            rotateOz -= deltaTime * 5;
            weirdVar = 1;
            camera->RotateAroundDrone(-deltaTime * 5, glm::vec3(dronePozX, dronePozY, dronePozZ));
        }
        if (fabs(pitchtAngle) == 360) {
            pitchtAngle = 0;
        }
        if (fabs(yawAngle) == 360) {
            yawAngle = 0;
        }
        float checkInvertedAngle = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchtAngle));
        if (checkInvertedAngle < 0) {
            invertAscend = 1;
        }
        else {
            invertAscend = 0;
        }
        if (incrementSpeed) {
            if (speed < 15) {
                speed += acceleration * deltaTime * 50;
            }
        }
        else {
            if (speed > 12) {
                speed -= acceleration * deltaTime * 50;
            }
        }
}


void Lab7::OnKeyPress(int key, int mods)
{


}


void Lab7::OnKeyRelease(int key, int mods)
{

}




void Lab7::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   
}


void Lab7::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab7::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab7::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab7::OnWindowResize(int width, int height)
{
}
