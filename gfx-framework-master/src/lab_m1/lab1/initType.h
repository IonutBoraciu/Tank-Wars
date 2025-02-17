#pragma once
#include "lab_m1/lab1/Tema1.h"
#include "components/simple_scene.h"
#include <vector>

using namespace std;
namespace m1 {
	class Letters : public gfxc::SimpleScene {
	public:
		Letters();
		~Letters();
		friend class Tema1;
	private:
		void static InitLetters(class Tema1 * tema1, glm::vec3 color);
		void static InitNumbers(class Tema1* tema1, glm::vec3 color);
		void static InitScore(class Tema1* tema1, glm::vec3 color, char name[100]);
		void static createNumber(char name[100], int widthVar, char addOn[20], vector<VertexFormat>& vertices, vector<unsigned int>& indices, class Tema1* tema1);
	protected:
		static vector<int> width;
	};

}