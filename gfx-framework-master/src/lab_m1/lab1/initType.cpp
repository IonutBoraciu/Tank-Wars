#include "lab_m1/lab1/initType.h"
using namespace std;
using namespace m1;

vector<int> Letters::width;

Letters::Letters() {

}
Letters::~Letters() {

}

void static initP(vector<VertexFormat> &vertices, vector<unsigned int> &indices, int &offset,glm::vec3 color) {

	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(20, 80, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(0, 80, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 50, 1), color)); // G 4
	vertices.push_back(VertexFormat(glm::vec3(20, 70, 1), color)); // L 5
	vertices.push_back(VertexFormat(glm::vec3(40, 80, 1), color)); // H 6
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // I 7	
	vertices.push_back(VertexFormat(glm::vec3(20, 60, 1), color)); // J 8
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // E 9
	vertices.push_back(VertexFormat(glm::vec3(40, 60, 1), color)); // F 10
	vertices.push_back(VertexFormat(glm::vec3(40, 50, 1), color)); // K 11
	vertices.push_back(VertexFormat(glm::vec3(30, 50, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(0, 50, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // S 18

	indices.push_back(0); // A D G
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(3); // D P G
	indices.push_back(15);
	indices.push_back(4);

	indices.push_back(15); // P Q F
	indices.push_back(16);
	indices.push_back(10);

	indices.push_back(15); // P K F
	indices.push_back(11);
	indices.push_back(10);

	indices.push_back(16); // Q O S
	indices.push_back(14);
	indices.push_back(18);

	indices.push_back(16); // Q C S
	indices.push_back(2);
	indices.push_back(18);

	indices.push_back(2); // C R H
	indices.push_back(17);
	indices.push_back(6);

	indices.push_back(17); // R E H
	indices.push_back(9);
	indices.push_back(6);

	indices.push_back(7); // I H K
	indices.push_back(6);
	indices.push_back(11);

	indices.push_back(7); // I M K
	indices.push_back(12);
	indices.push_back(11);
	offset += 18;
}

void static initL(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(60, 80, 1), color)); // offset + 1 T
	vertices.push_back(VertexFormat(glm::vec3(60, 0, 1), color)); // + 2 U
	vertices.push_back(VertexFormat(glm::vec3(70, 0, 1), color)); // + 3 V
	vertices.push_back(VertexFormat(glm::vec3(70, 80, 1), color)); // + 4 W
	vertices.push_back(VertexFormat(glm::vec3(100, 0, 1), color)); // + 5 Z
	vertices.push_back(VertexFormat(glm::vec3(100, 10, 1), color)); // +6 A1
	vertices.push_back(VertexFormat(glm::vec3(70, 10, 1), color)); // +7 B1 
	vertices.push_back(VertexFormat(glm::vec3(60, 10, 1), color)); // +8 C1

	indices.push_back(offset + 1); // T U V
	indices.push_back(offset + 2);
	indices.push_back(offset + 3);

	indices.push_back(offset + 1); // T V W
	indices.push_back(offset + 3);
	indices.push_back(offset + 4);

	indices.push_back(offset + 2); // U C1 A1
	indices.push_back(offset + 8);
	indices.push_back(offset + 6);

	indices.push_back(offset + 2); // U Z A1
	indices.push_back(offset + 5);
	indices.push_back(offset + 6);
	offset += 8;
}

void static initA(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(120, 0, 1), color)); // D1 offset +1
	vertices.push_back(VertexFormat(glm::vec3(130, 0, 1), color)); // F1  + 2
	vertices.push_back(VertexFormat(glm::vec3(130, 70, 1), color)); // G1 + 3
	vertices.push_back(VertexFormat(glm::vec3(160, 0, 1), color)); // H1 + 4
	vertices.push_back(VertexFormat(glm::vec3(150, 0, 1), color)); // I1 + 5
	vertices.push_back(VertexFormat(glm::vec3(150, 70, 1), color)); // J1 + 6
	vertices.push_back(VertexFormat(glm::vec3(120, 70, 1), color)); // L1 + 7
	vertices.push_back(VertexFormat(glm::vec3(160, 70, 1), color)); // M1 + 8
	vertices.push_back(VertexFormat(glm::vec3(130, 50, 1), color)); // N1 + 9
	vertices.push_back(VertexFormat(glm::vec3(150, 50, 1), color)); // O1 + 10
	vertices.push_back(VertexFormat(glm::vec3(150, 40, 1), color)); // P1 + 11
	vertices.push_back(VertexFormat(glm::vec3(130, 40, 1), color)); // Q1 + 12
	vertices.push_back(VertexFormat(glm::vec3(150, 80, 1), color)); // R1 + 13
	vertices.push_back(VertexFormat(glm::vec3(130, 80, 1), color)); // S1 + 14

	indices.push_back(offset + 1); // D1 F1 G1
	indices.push_back(offset + 2);
	indices.push_back(offset + 3);

	indices.push_back(offset + 1); // D1 L1 G1
	indices.push_back(offset + 7);
	indices.push_back(offset + 3);

	indices.push_back(offset + 5); // I1 H1 M1
	indices.push_back(offset + 4);
	indices.push_back(offset + 8);

	indices.push_back(offset + 5); // I1 J1 M1
	indices.push_back(offset + 6);
	indices.push_back(offset + 8);

	indices.push_back(offset + 12); // Q1 N1 O1
	indices.push_back(offset + 9);
	indices.push_back(offset + 10);

	indices.push_back(offset + 12); // Q1 P1 O1
	indices.push_back(offset + 11);
	indices.push_back(offset + 10);

	indices.push_back(offset + 3); // G1 J1 R1
	indices.push_back(offset + 6);
	indices.push_back(offset + 13);

	indices.push_back(offset + 3); // G1 S1 R1
	indices.push_back(offset + 14);
	indices.push_back(offset + 13);

	offset += 14;
}

void static initY(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {


	vertices.push_back(VertexFormat(glm::vec3(190, 80, 1), color)); // K1 + 1
	vertices.push_back(VertexFormat(glm::vec3(200, 0, 1), color)); // D2 + 2
	vertices.push_back(VertexFormat(glm::vec3(210, 0, 1), color)); // E2 + 3
	vertices.push_back(VertexFormat(glm::vec3(180, 80, 1), color)); // E1 + 4
	vertices.push_back(VertexFormat(glm::vec3(180, 70, 1), color)); // T1 + 5
	vertices.push_back(VertexFormat(glm::vec3(180, 60, 1), color)); // V1  + 6
	vertices.push_back(VertexFormat(glm::vec3(190, 60, 1), color)); // W1 + 7
	vertices.push_back(VertexFormat(glm::vec3(190, 70, 1), color)); // Z1 + 8
	vertices.push_back(VertexFormat(glm::vec3(200, 50, 1), color)); // A2 + 9
	vertices.push_back(VertexFormat(glm::vec3(190, 50, 1), color)); // B2 + 10
	vertices.push_back(VertexFormat(glm::vec3(200, 60, 1), color)); // C2 + 11
	vertices.push_back(VertexFormat(glm::vec3(210, 50, 1), color)); // F2 + 12
	vertices.push_back(VertexFormat(glm::vec3(210, 60, 1), color)); // G2 + 13
	vertices.push_back(VertexFormat(glm::vec3(220, 60, 1), color)); // H2 + 14
	vertices.push_back(VertexFormat(glm::vec3(220, 50, 1), color)); // I2 + 15
	vertices.push_back(VertexFormat(glm::vec3(230, 60, 1), color)); // J2 + 16
	vertices.push_back(VertexFormat(glm::vec3(230, 70, 1), color)); // K2 + 17
	vertices.push_back(VertexFormat(glm::vec3(220, 70, 1), color)); // L2 + 18
	vertices.push_back(VertexFormat(glm::vec3(230, 80, 1), color)); // M2 + 19
	vertices.push_back(VertexFormat(glm::vec3(220, 80, 1), color)); // 02 + 20

	indices.push_back(offset + 2); // D2 E2 F2
	indices.push_back(offset + 3);
	indices.push_back(offset + 12);

	indices.push_back(offset + 2); // D2 A2 F2
	indices.push_back(offset + 9);
	indices.push_back(offset + 12);

	indices.push_back(offset + 12); // F2 I2 H2
	indices.push_back(offset + 15);
	indices.push_back(offset + 14);

	indices.push_back(offset + 12); // F2 G2 H2
	indices.push_back(offset + 13);
	indices.push_back(offset + 14);

	indices.push_back(offset + 9); // A2 B2 C2
	indices.push_back(offset + 10);
	indices.push_back(offset + 11);

	indices.push_back(offset + 10); // B2 W1 C2
	indices.push_back(offset + 7);
	indices.push_back(offset + 11);

	indices.push_back(offset + 6); // V1 W1 Z1
	indices.push_back(offset + 7);
	indices.push_back(offset + 8);

	indices.push_back(offset + 6); // V1 T1 Z1
	indices.push_back(offset + 5);
	indices.push_back(offset + 8);

	indices.push_back(offset + 14); // H2 J2 K2
	indices.push_back(offset + 16);
	indices.push_back(offset + 17);

	indices.push_back(offset + 14); // H2 L2 K2
	indices.push_back(offset + 18);
	indices.push_back(offset + 17);

	indices.push_back(offset + 5); // T1 Z1 K1
	indices.push_back(offset + 8);
	indices.push_back(offset + 1);

	indices.push_back(offset + 5); // T1 E1 K1
	indices.push_back(offset + 4);
	indices.push_back(offset + 1);

	indices.push_back(offset + 18); // L2 K2 M2
	indices.push_back(offset + 17);
	indices.push_back(offset + 19);

	indices.push_back(offset + 18); // L2 O2 M2
	indices.push_back(offset + 20);
	indices.push_back(offset + 19);

	offset += 20;
}

void static initE(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {

	vertices.push_back(VertexFormat(glm::vec3(260, 0, 1), color)); // U1 + 1
	vertices.push_back(VertexFormat(glm::vec3(260, 80, 1), color)); // N2 +2
	vertices.push_back(VertexFormat(glm::vec3(300, 80, 1), color)); // P2 + 3
	vertices.push_back(VertexFormat(glm::vec3(300, 0, 1), color)); // Q2 + 4
	vertices.push_back(VertexFormat(glm::vec3(300, 10, 1), color)); // R2 + 5
	vertices.push_back(VertexFormat(glm::vec3(270, 10, 1), color)); // S2 + 6
	vertices.push_back(VertexFormat(glm::vec3(270, 70, 1), color));// T2 + 7
	vertices.push_back(VertexFormat(glm::vec3(300, 70, 1), color)); // U2 + 8
	vertices.push_back(VertexFormat(glm::vec3(300, 45, 1), color)); // V2 + 9
	vertices.push_back(VertexFormat(glm::vec3(300, 35, 1), color)); // W2 + 10
	vertices.push_back(VertexFormat(glm::vec3(270, 45, 1), color)); // Z2 + 11
	vertices.push_back(VertexFormat(glm::vec3(270, 35, 1), color)); // A3 + 12
	vertices.push_back(VertexFormat(glm::vec3(270, 0, 1), color)); // B3 + 13
	vertices.push_back(VertexFormat(glm::vec3(270, 80, 1), color)); // C3 + 14

	indices.push_back(offset + 1); // U1 B3 C3
	indices.push_back(offset + 13);
	indices.push_back(offset + 14);

	indices.push_back(offset + 1); // U1 N2 C3
	indices.push_back(offset + 2);
	indices.push_back(offset + 14);

	indices.push_back(offset + 13); // B3 Q2 R2
	indices.push_back(offset + 4);
	indices.push_back(offset + 5);

	indices.push_back(offset + 13); // B3 S2 R2
	indices.push_back(offset + 6);
	indices.push_back(offset + 5);

	indices.push_back(offset + 12); // A3 W2 V2
	indices.push_back(offset + 10);
	indices.push_back(offset + 9);

	indices.push_back(offset + 12); // A3 Z2 V2
	indices.push_back(offset + 11);
	indices.push_back(offset + 9);

	indices.push_back(offset + 7); // T2 U2 P2
	indices.push_back(offset + 8);
	indices.push_back(offset + 3);

	indices.push_back(offset + 7); // T2 C3 P2
	indices.push_back(offset + 14);
	indices.push_back(offset + 3);

	offset += 14;
}

void static initR(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {

	vertices.push_back(VertexFormat(glm::vec3(320, 0, 1), color)); // D3 + 1
	vertices.push_back(VertexFormat(glm::vec3(320, 80, 1), color)); // E3 + 2
	vertices.push_back(VertexFormat(glm::vec3(330, 80, 1), color)); // F3 + 3
	vertices.push_back(VertexFormat(glm::vec3(330, 0, 1), color)); // G3 + 4
	vertices.push_back(VertexFormat(glm::vec3(360, 80, 1), color)); // H3 + 5
	vertices.push_back(VertexFormat(glm::vec3(360, 50, 1), color)); // I3 + 6
	vertices.push_back(VertexFormat(glm::vec3(350, 50, 1), color)); // J3 + 7
	vertices.push_back(VertexFormat(glm::vec3(350, 40, 1), color)); // K3 + 8
	vertices.push_back(VertexFormat(glm::vec3(360, 40, 1), color)); // L3 + 9
	vertices.push_back(VertexFormat(glm::vec3(360, 0, 1), color)); // M3 + 10
	vertices.push_back(VertexFormat(glm::vec3(350, 0, 1), color)); // N3 + 11
	vertices.push_back(VertexFormat(glm::vec3(330, 40, 1), color)); // O3 + 12
	vertices.push_back(VertexFormat(glm::vec3(330, 50, 1), color)); // P3 + 13
	vertices.push_back(VertexFormat(glm::vec3(350, 80, 1), color)); // Q3 + 14
	vertices.push_back(VertexFormat(glm::vec3(320, 70, 1), color)); // R3 + 15
	vertices.push_back(VertexFormat(glm::vec3(360, 70, 1), color)); // S3 + 16

	indices.push_back(offset + 1); // D3 G3 F3
	indices.push_back(offset + 4);
	indices.push_back(offset + 3);

	indices.push_back(offset + 1); // D3 E3 F3
	indices.push_back(offset + 2);
	indices.push_back(offset + 3);

	indices.push_back(offset + 15); // R3 E3 H3
	indices.push_back(offset + 2);
	indices.push_back(offset + 5);

	indices.push_back(offset + 15); // R3 S3 H3
	indices.push_back(offset + 16);
	indices.push_back(offset + 5);

	indices.push_back(offset + 14); // Q3 J3 I3
	indices.push_back(offset + 7);
	indices.push_back(offset + 6);

	indices.push_back(offset + 14); // Q3 H3 I3
	indices.push_back(offset + 5);
	indices.push_back(offset + 6);

	indices.push_back(offset + 13); // P3 J3 K3
	indices.push_back(offset + 7);
	indices.push_back(offset + 8);

	indices.push_back(offset + 13); // P3 O3 K3
	indices.push_back(offset + 12);
	indices.push_back(offset + 8);

	indices.push_back(offset + 11); // N3 K3 L3
	indices.push_back(offset + 8);
	indices.push_back(offset + 9);

	indices.push_back(offset + 11);// N3 M3 L3
	indices.push_back(offset + 10);
	indices.push_back(offset + 9);

	offset += 16;
}

void initW(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 80, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(60, 10, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(60, 0, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(40, 0, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(70, 10, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(70, 80, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(60, 80, 1), color)); // P 15


	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(1); // B D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(0); // A E G
	indices.push_back(4);
	indices.push_back(6);

	indices.push_back(0); // A F G
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(5); // F I H
	indices.push_back(8);
	indices.push_back(7);

	indices.push_back(5); // F L H
	indices.push_back(11);
	indices.push_back(7);

	indices.push_back(11); // L M J
	indices.push_back(12);
	indices.push_back(9);

	indices.push_back(12); // M K J
	indices.push_back(10);
	indices.push_back(9);

	indices.push_back(9); // J N O
	indices.push_back(13);
	indices.push_back(14);

	indices.push_back(9); // J P O
	indices.push_back(15);
	indices.push_back(14);
	offset = 15;
}

void static initI(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(90, 0, 1), color)); //Q offset + 1
	vertices.push_back(VertexFormat(glm::vec3(90, 60, 1), color)); //R offset + 2
	vertices.push_back(VertexFormat(glm::vec3(100, 60, 1), color)); //S offset + 3
	vertices.push_back(VertexFormat(glm::vec3(100, 0, 1), color)); //T offset + 4
	vertices.push_back(VertexFormat(glm::vec3(100, 70, 1), color)); //U offset + 5
	vertices.push_back(VertexFormat(glm::vec3(100, 80, 1), color)); //V offset + 6
	vertices.push_back(VertexFormat(glm::vec3(90, 80, 1), color)); //W offset + 7
	vertices.push_back(VertexFormat(glm::vec3(90, 70, 1), color)); //Z offset + 8

	indices.push_back(offset + 1); // Q R S
	indices.push_back(offset + 2);
	indices.push_back(offset + 3);

	indices.push_back(offset + 1); // Q T S
	indices.push_back(offset + 4);
	indices.push_back(offset + 3);

	indices.push_back(offset + 8); // Z U V
	indices.push_back(offset + 5);
	indices.push_back(offset + 6);

	indices.push_back(offset + 8); // Z W V
	indices.push_back(offset + 7);
	indices.push_back(offset + 6);
	offset += 8;
}

void initN(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {


	vertices.push_back(VertexFormat(glm::vec3(120, 0, 1), color)); //A1 offset + 1
	vertices.push_back(VertexFormat(glm::vec3(120, 80, 1), color)); //B1 offset + 2
	vertices.push_back(VertexFormat(glm::vec3(130, 0, 1), color)); //C1 offset + 3
	vertices.push_back(VertexFormat(glm::vec3(130, 80, 1), color)); //D1 offset + 4
	vertices.push_back(VertexFormat(glm::vec3(130, 60, 1), color)); //E1 offset + 5
	vertices.push_back(VertexFormat(glm::vec3(140, 60, 1), color)); //F1 offset + 6
	vertices.push_back(VertexFormat(glm::vec3(140, 50, 1), color)); //G1 offset + 7
	vertices.push_back(VertexFormat(glm::vec3(130, 50, 1), color)); //H1 offset + 8
	vertices.push_back(VertexFormat(glm::vec3(140, 40, 1), color)); //I1 offset + 9
	vertices.push_back(VertexFormat(glm::vec3(150, 40, 1), color)); //J1 offset + 10
	vertices.push_back(VertexFormat(glm::vec3(150, 50, 1), color)); //K1 offset + 11
	vertices.push_back(VertexFormat(glm::vec3(160, 0, 1), color)); //L1 offset + 12
	vertices.push_back(VertexFormat(glm::vec3(150, 0, 1), color)); //M1 offset + 13
	vertices.push_back(VertexFormat(glm::vec3(160, 80, 1), color)); //N1 offset + 14
	vertices.push_back(VertexFormat(glm::vec3(150, 80, 1), color)); //O1 offset + 15

	indices.push_back(offset + 1); // A1 C1 D1
	indices.push_back(offset + 3);
	indices.push_back(offset + 4);

	indices.push_back(offset + 1); // A1 B1 D1
	indices.push_back(offset + 2);
	indices.push_back(offset + 4);

	indices.push_back(offset + 5); // E1 H1 G1
	indices.push_back(offset + 8);
	indices.push_back(offset + 7);

	indices.push_back(offset + 5); // E1 F1 G1
	indices.push_back(offset + 6);
	indices.push_back(offset + 7);

	indices.push_back(offset + 7); // G1 I1 J1
	indices.push_back(offset + 9);
	indices.push_back(offset + 10);

	indices.push_back(offset + 7); // G1 K1 J1
	indices.push_back(offset + 11);
	indices.push_back(offset + 10);

	indices.push_back(offset + 13); // M1 L1 N1
	indices.push_back(offset + 12);
	indices.push_back(offset + 14);

	indices.push_back(offset + 13); // M1 O1 N1
	indices.push_back(offset + 15);
	indices.push_back(offset + 14);
	offset += 15;
}

void initS(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(180, 70, 1), color)); //P1 offset + 1
	vertices.push_back(VertexFormat(glm::vec3(180, 40, 1), color)); //R1 offset + 2
	vertices.push_back(VertexFormat(glm::vec3(190, 70, 1), color)); //S1 offset + 3
	vertices.push_back(VertexFormat(glm::vec3(190, 80, 1), color)); //T1 offset + 4
	vertices.push_back(VertexFormat(glm::vec3(210, 80, 1), color)); //U1 offset + 5
	vertices.push_back(VertexFormat(glm::vec3(210, 70, 1), color)); //V1 offset + 6
	vertices.push_back(VertexFormat(glm::vec3(220, 60, 1), color)); //W1 offset + 7
	vertices.push_back(VertexFormat(glm::vec3(220, 70, 1), color)); //Z1 offset + 8
	vertices.push_back(VertexFormat(glm::vec3(210, 60, 1), color)); //A2 offset + 9
	vertices.push_back(VertexFormat(glm::vec3(190, 40, 1), color)); //D2 offset + 10
	vertices.push_back(VertexFormat(glm::vec3(190, 30, 1), color)); //Q1 offset + 11
	vertices.push_back(VertexFormat(glm::vec3(210, 40, 1), color)); //B2 offset + 12
	vertices.push_back(VertexFormat(glm::vec3(210, 30, 1), color)); //C2 offset + 13
	vertices.push_back(VertexFormat(glm::vec3(210, 10, 1), color)); //E2 offset + 14
	vertices.push_back(VertexFormat(glm::vec3(220, 10, 1), color)); //F2 offset + 15
	vertices.push_back(VertexFormat(glm::vec3(220, 30, 1), color)); //G2 offset + 16
	vertices.push_back(VertexFormat(glm::vec3(190, 10, 1), color)); //H2 offset + 17
	vertices.push_back(VertexFormat(glm::vec3(190, 0, 1), color)); //I2 offset + 18
	vertices.push_back(VertexFormat(glm::vec3(210, 0, 1), color)); //J2 offset + 19
	vertices.push_back(VertexFormat(glm::vec3(180, 20, 1), color)); //K2 offset + 20
	vertices.push_back(VertexFormat(glm::vec3(180, 10, 1), color)); //L2 offset + 21
	vertices.push_back(VertexFormat(glm::vec3(190, 20, 1), color)); //M2 offset + 22

	indices.push_back(offset + 2); // R1 D2 S1
	indices.push_back(offset + 10);
	indices.push_back(offset + 3);

	indices.push_back(offset + 2); // R1 P1 S1
	indices.push_back(offset + 1);
	indices.push_back(offset + 3);

	indices.push_back(offset + 3); // S1 V1 U1
	indices.push_back(offset + 6);
	indices.push_back(offset + 5);

	indices.push_back(offset + 3); // S1 T1 U1
	indices.push_back(offset + 4);
	indices.push_back(offset + 5);

	indices.push_back(offset + 6); // V1 Z1 W1
	indices.push_back(offset + 8);
	indices.push_back(offset + 7);

	indices.push_back(offset + 6); // V1 A2 W1
	indices.push_back(offset + 9);
	indices.push_back(offset + 7);

	indices.push_back(offset + 10); // D2 Q1 C2
	indices.push_back(offset + 11);
	indices.push_back(offset + 13);

	indices.push_back(offset + 10); // D2 B2 C2
	indices.push_back(offset + 12);
	indices.push_back(offset + 13);

	indices.push_back(offset + 13); // C2 G2 F2
	indices.push_back(offset + 16);
	indices.push_back(offset + 15);

	indices.push_back(offset + 13); // C2 E2 F2
	indices.push_back(offset + 14);
	indices.push_back(offset + 15);

	indices.push_back(offset + 14); // E2 J2 I2
	indices.push_back(offset + 19);
	indices.push_back(offset + 18);

	indices.push_back(offset + 14); // E2 H2 I2
	indices.push_back(offset + 17);
	indices.push_back(offset + 18);

	indices.push_back(offset + 17); // H2 L2 M2
	indices.push_back(offset + 21);
	indices.push_back(offset + 22);

	indices.push_back(offset + 21); // L2 K2 M2
	indices.push_back(offset + 20);
	indices.push_back(offset + 22);
	offset += 22;
}

void static init1(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(20, 80, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(20, 0, 1), color)); // H 6
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // I 7
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color)); // J 8
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // K 9
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // L 10
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // M 11

	indices.push_back(8); // J M L
	indices.push_back(11);
	indices.push_back(10);

	indices.push_back(8); // J K L
	indices.push_back(9);
	indices.push_back(10);

	indices.push_back(7); // I H F
	indices.push_back(6);
	indices.push_back(5);

	indices.push_back(7); // I E F
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);
	offset += 11;
}

void static init2(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {

	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // J 7
	vertices.push_back(VertexFormat(glm::vec3(30, 50, 1), color)); // K 8
	vertices.push_back(VertexFormat(glm::vec3(40, 50, 1), color)); // L 9
	vertices.push_back(VertexFormat(glm::vec3(20, 50, 1), color)); // M 10
	vertices.push_back(VertexFormat(glm::vec3(20, 40, 1), color)); // N 11
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // O 12
	vertices.push_back(VertexFormat(glm::vec3(10, 30, 1), color)); // P 13
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // Q 14
	vertices.push_back(VertexFormat(glm::vec3(20, 30, 1), color)); // R 15
	vertices.push_back(VertexFormat(glm::vec3(0, 30, 1), color)); // U 16
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // W 17
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // Z 18
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color)); // A1 19
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // C1 20
	vertices.push_back(VertexFormat(glm::vec3(40, 0, 1), color)); // D1 21

	indices.push_back(19); // A1 D1 C1
	indices.push_back(21);
	indices.push_back(20);

	indices.push_back(19); // A1 W C1
	indices.push_back(17);
	indices.push_back(20);

	indices.push_back(19); // A1 U P
	indices.push_back(16);
	indices.push_back(13);

	indices.push_back(19); // A1 Z P
	indices.push_back(18);
	indices.push_back(13);

	indices.push_back(13); // P R N
	indices.push_back(15);
	indices.push_back(11);

	indices.push_back(13); // P Q N
	indices.push_back(14);
	indices.push_back(11);

	indices.push_back(11); // N O K
	indices.push_back(12);
	indices.push_back(8);

	indices.push_back(11); // N M K
	indices.push_back(10);
	indices.push_back(8);

	indices.push_back(8); // K L J
	indices.push_back(9);
	indices.push_back(7);

	indices.push_back(8); // K G J
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(6); // G F E
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(6); // G B E
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);
	offset += 21;
}

void static init0(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // L 11

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(5); // F A H
	indices.push_back(0);
	indices.push_back(7);

	indices.push_back(5); // F G H
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(1); // B I J
	indices.push_back(8);
	indices.push_back(9);

	indices.push_back(1); // B E J
	indices.push_back(4);
	indices.push_back(9);

	indices.push_back(7); // H L K
	indices.push_back(11);
	indices.push_back(10);

	indices.push_back(7); // H I K
	indices.push_back(8);
	indices.push_back(10);
}
void static init3(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(30, 50, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(40, 50, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(20, 50, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(20, 30, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(30, 30, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(40, 30, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // S 18
	vertices.push_back(VertexFormat(glm::vec3(10, 20, 1), color)); // T 19
	vertices.push_back(VertexFormat(glm::vec3(0, 20, 1), color)); // U 20
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // V 21

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(4); // E B G
	indices.push_back(1);
	indices.push_back(6);

	indices.push_back(4); // E F G
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(6); // G J I
	indices.push_back(9);
	indices.push_back(8);

	indices.push_back(6); // G H I
	indices.push_back(7);
	indices.push_back(8);

	indices.push_back(10); // K L M
	indices.push_back(11);
	indices.push_back(12);

	indices.push_back(10); // K H M
	indices.push_back(7);
	indices.push_back(12);

	indices.push_back(12); // M N O
	indices.push_back(13);
	indices.push_back(14);

	indices.push_back(12); // M P O
	indices.push_back(15);
	indices.push_back(14);

	indices.push_back(13); // N S R
	indices.push_back(18);
	indices.push_back(17);

	indices.push_back(13); // N Q R
	indices.push_back(16);
	indices.push_back(17);

	indices.push_back(20); // U T Q
	indices.push_back(19);
	indices.push_back(16);

	indices.push_back(20); // U V Q
	indices.push_back(21);
	indices.push_back(16);
}

void static init4(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(0, 40, 1), color)); // D 2
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // E 3
	vertices.push_back(VertexFormat(glm::vec3(20, 70, 1), color)); // F 4
	vertices.push_back(VertexFormat(glm::vec3(20, 60, 1), color)); // G 5
	vertices.push_back(VertexFormat(glm::vec3(20, 80, 1), color)); // H 6
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // I 7
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // J 8
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // K 9
	vertices.push_back(VertexFormat(glm::vec3(40, 80, 1), color)); // L 10
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // M 11
	vertices.push_back(VertexFormat(glm::vec3(40, 0, 1), color)); // N 12
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // O 13
	vertices.push_back(VertexFormat(glm::vec3(40, 50, 1), color)); // P 14
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // Q 15
	vertices.push_back(VertexFormat(glm::vec3(0, 50, 1), color)); // R 16

	indices.push_back(2); // D Q B
	indices.push_back(15);
	indices.push_back(1);

	indices.push_back(2); // D A B
	indices.push_back(0);
	indices.push_back(1);
	
	indices.push_back(1); // B G F
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(1); // B E F
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(4); // F K L
	indices.push_back(9);
	indices.push_back(10);

	indices.push_back(4); // F H L
	indices.push_back(6);
	indices.push_back(10);

	indices.push_back(11); // M N L
	indices.push_back(12);
	indices.push_back(10);

	indices.push_back(11); // M I L
	indices.push_back(7);
	indices.push_back(10);

	indices.push_back(16); // R D O
	indices.push_back(2);
	indices.push_back(13);

	indices.push_back(16); // R P O
	indices.push_back(14);
	indices.push_back(13);
}

void static init5(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(40, 80, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(0, 80, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(0, 40, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(0, 60, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(10, 50, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(30, 50, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(10, 20, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // S 18
	vertices.push_back(VertexFormat(glm::vec3(0, 20, 1), color)); // T 19
	vertices.push_back(VertexFormat(glm::vec3(0, 50, 1), color)); // U 20

	indices.push_back(0); // A B D 
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(0); // A C D
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(6); // G F E
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(6); // G C E
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(6); // G K J
	indices.push_back(10);
	indices.push_back(9);

	indices.push_back(6); // G U J
	indices.push_back(20);
	indices.push_back(9);

	indices.push_back(10); // K L M
	indices.push_back(11);
	indices.push_back(12);

	indices.push_back(10); // K N M
	indices.push_back(13);
	indices.push_back(12);

	indices.push_back(13); // N Q P
	indices.push_back(16);
	indices.push_back(15);

	indices.push_back(15); // P O N
	indices.push_back(14);
	indices.push_back(13);

	indices.push_back(19); // T R O
	indices.push_back(17);
	indices.push_back(14);

	indices.push_back(19); // T S O
	indices.push_back(18);
	indices.push_back(14);

}

void static init6(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(40, 80, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(20, 60, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(20, 70, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(30, 60, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(20, 50, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(10, 50, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(10, 60, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(0, 50, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(0, 40, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(30, 50, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // S 18
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // T 19
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // U 20
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // V 21

	indices.push_back(0); // A B D
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(0); // A C D
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(3); // D G E
	indices.push_back(6);
	indices.push_back(4);

	indices.push_back(3); // D F E
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(9); // J E H
	indices.push_back(4);
	indices.push_back(7);

	indices.push_back(9); // J I H
	indices.push_back(8);
	indices.push_back(7);

	indices.push_back(10); // K L M
	indices.push_back(11);
	indices.push_back(12);

	indices.push_back(10); // K N M
	indices.push_back(13);
	indices.push_back(12);

	indices.push_back(12); // M O P
	indices.push_back(14);
	indices.push_back(15);

	indices.push_back(12); // M Q P
	indices.push_back(16);
	indices.push_back(15);

	indices.push_back(16); // Q T S
	indices.push_back(19);
	indices.push_back(18);

	indices.push_back(16); // Q R S
	indices.push_back(17);
	indices.push_back(18);

	indices.push_back(20); // U R V
	indices.push_back(17);
	indices.push_back(21);

	indices.push_back(20); // U L V
	indices.push_back(11);
	indices.push_back(21);
}

void static init7(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(0, 80, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(40, 80, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(30, 60, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(40, 60, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(20, 60, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(20, 40, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(10, 20, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(20, 20, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(0, 20, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color)); // P 15

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(5); // F D G
	indices.push_back(3);
	indices.push_back(6);

	indices.push_back(5); // F E G
	indices.push_back(4);
	indices.push_back(6);

	indices.push_back(7); // H E J
	indices.push_back(4);
	indices.push_back(9);

	indices.push_back(7); // H I J
	indices.push_back(8);
	indices.push_back(9);

	indices.push_back(10); // K I M
	indices.push_back(8);
	indices.push_back(12);

	indices.push_back(10); // K L M
	indices.push_back(11);
	indices.push_back(12);

	indices.push_back(14);// O L N
	indices.push_back(11);
	indices.push_back(13);

	indices.push_back(14); // O P N
	indices.push_back(15);
	indices.push_back(13);

}

void static init8(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(0, 40, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(10, 30, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(30, 30, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(30, 10, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(40, 10, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(40, 30, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(0, 30, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // S 18
	vertices.push_back(VertexFormat(glm::vec3(30, 0, 1), color)); // T 19

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(6); // G B F
	indices.push_back(1);
	indices.push_back(5);

	indices.push_back(6); // G E F
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(5); // F H L
	indices.push_back(7);
	indices.push_back(11);

	indices.push_back(5); // F K L
	indices.push_back(10);
	indices.push_back(11);

	indices.push_back(2); // C J I
	indices.push_back(9);
	indices.push_back(8);

	indices.push_back(2); // C H I
	indices.push_back(7);
	indices.push_back(8);

	indices.push_back(11); // L O N
	indices.push_back(14);
	indices.push_back(13);

	indices.push_back(11); // L M N
	indices.push_back(12);
	indices.push_back(13);

	indices.push_back(15); // P M T
	indices.push_back(12);
	indices.push_back(19);

	indices.push_back(15); // P S T
	indices.push_back(18);
	indices.push_back(19);

	indices.push_back(17); // R K P
	indices.push_back(10);
	indices.push_back(15);

	indices.push_back(17); // R Q P
	indices.push_back(16);
	indices.push_back(15);
}

void static init9(vector<VertexFormat>& vertices, vector<unsigned int>& indices, int& offset, glm::vec3 color) {
	vertices.push_back(VertexFormat(glm::vec3(10, 10, 1), color)); // A 0
	vertices.push_back(VertexFormat(glm::vec3(10, 0, 1), color)); // B 1
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color)); // C 2
	vertices.push_back(VertexFormat(glm::vec3(0, 10, 1), color)); // D 3
	vertices.push_back(VertexFormat(glm::vec3(10, 20, 1), color)); // E 4
	vertices.push_back(VertexFormat(glm::vec3(20, 20, 1), color)); // F 5
	vertices.push_back(VertexFormat(glm::vec3(20, 10, 1), color)); // G 6
	vertices.push_back(VertexFormat(glm::vec3(30, 20, 1), color)); // H 7
	vertices.push_back(VertexFormat(glm::vec3(30, 30, 1), color)); // I 8
	vertices.push_back(VertexFormat(glm::vec3(20, 30, 1), color)); // J 9
	vertices.push_back(VertexFormat(glm::vec3(40, 30, 1), color)); // K 10
	vertices.push_back(VertexFormat(glm::vec3(40, 40, 1), color)); // L 11
	vertices.push_back(VertexFormat(glm::vec3(30, 40, 1), color)); // M 12
	vertices.push_back(VertexFormat(glm::vec3(10, 40, 1), color)); // N 13
	vertices.push_back(VertexFormat(glm::vec3(10, 30, 1), color)); // O 14
	vertices.push_back(VertexFormat(glm::vec3(0, 70, 1), color)); // P 15
	vertices.push_back(VertexFormat(glm::vec3(0, 40, 1), color)); // Q 16
	vertices.push_back(VertexFormat(glm::vec3(10, 70, 1), color)); // R 17
	vertices.push_back(VertexFormat(glm::vec3(30, 70, 1), color)); // S 18
	vertices.push_back(VertexFormat(glm::vec3(40, 70, 1), color)); // T 19
	vertices.push_back(VertexFormat(glm::vec3(30, 80, 1), color)); // U 20
	vertices.push_back(VertexFormat(glm::vec3(10, 80, 1), color)); // V 21

	indices.push_back(0); // A B C
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0); // A D C
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(0); // A G F
	indices.push_back(6);
	indices.push_back(5);

	indices.push_back(0); // A E F
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(5); // F H I
	indices.push_back(7);
	indices.push_back(8);

	indices.push_back(5); // F J I
	indices.push_back(9);
	indices.push_back(8);

	indices.push_back(10);// K O N
	indices.push_back(14);
	indices.push_back(13);

	indices.push_back(10); // K L N
	indices.push_back(11);
	indices.push_back(13);

	indices.push_back(12); // M L T
	indices.push_back(11);
	indices.push_back(19);

	indices.push_back(12); // M S T
	indices.push_back(18);
	indices.push_back(19);

	indices.push_back(18); // S U V
	indices.push_back(20);
	indices.push_back(21);

	indices.push_back(18); // S R V
	indices.push_back(17);
	indices.push_back(21);

	indices.push_back(15); // P R N
	indices.push_back(17);
	indices.push_back(13);

	indices.push_back(15); // P Q N
	indices.push_back(16);
	indices.push_back(13);
}


void Letters::InitLetters(class Tema1* tema1, glm::vec3 color) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	int offset = 0;
	initP(vertices, indices, offset, color);
	initL(vertices, indices, offset, color);
	initA(vertices, indices, offset, color);
	initY(vertices, indices, offset, color);
	initE(vertices, indices, offset, color);
	initR(vertices, indices, offset, color);

	if (tema1->meshes["P"] == NULL) {
		Mesh* player = new Mesh("P");
		player->InitFromData(vertices, indices);
		tema1->AddMeshToList(player);
	}
	else {
		tema1->meshes["P"]->InitFromData(vertices, indices);
	}

	vertices.clear();
	indices.clear();
	offset = 0;

	initW(vertices, indices, offset, color);
	initI(vertices, indices, offset, color);
	initN(vertices, indices, offset, color);
	initS(vertices, indices, offset, color);

	if (tema1->meshes["WINS"] == NULL) {
		Mesh* win = new Mesh("WINS");
		win->InitFromData(vertices, indices);
		tema1->AddMeshToList(win);
	}
	else {
		tema1->meshes["WINS"]->InitFromData(vertices, indices);
	}
}

void Letters::InitNumbers(class Tema1* tema1, glm::vec3 color) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	int offset = 0;
	init1(vertices, indices, offset, color);

	if (tema1->meshes["1"] == NULL) {
		Mesh* player = new Mesh("1");
		player->InitFromData(vertices, indices);
		tema1->AddMeshToList(player);
	}
	else {
		tema1->meshes["1"]->InitFromData(vertices, indices);
	}

	vertices.clear();
	indices.clear();
	offset = 0;

	init2(vertices, indices, offset, color);
	if (tema1->meshes["2"] == NULL) {
		Mesh* player2 = new Mesh("2");
		player2->InitFromData(vertices, indices);
		tema1->AddMeshToList(player2);
	}
	else {
		tema1->meshes["2"]->InitFromData(vertices, indices);
	}
}

void Letters::createNumber(char name[100],int widthVar, char addOn[20], vector<VertexFormat> &vertices, vector<unsigned int> &indices, class Tema1 *tema1) {
	char copyName[100];
	strcpy(copyName, name);
	strcat(copyName, addOn);
	Mesh* player_0 = new Mesh(copyName);
	player_0->InitFromData(vertices, indices);
	tema1->AddMeshToList(player_0);
	width.push_back(widthVar);
	vertices.clear();
	indices.clear();
}

void Letters::InitScore(class Tema1* tema1, glm::vec3 color,char name[100]) {
	vector<VertexFormat> vertices;
	vector<unsigned int> indices;
	char copyName[100];
	int offset = 0;
	init0(vertices, indices, offset, color);
	createNumber(name, 40, "_0", vertices, indices, tema1);

	init1(vertices, indices, offset, color);
	createNumber(name, 30, "_1", vertices, indices, tema1);
	
	init2(vertices, indices, offset, color);
	createNumber(name, 40, "_2", vertices, indices, tema1);

	init3(vertices, indices, offset, color);
	createNumber(name, 40, "_3", vertices, indices, tema1);

	init4(vertices, indices, offset, color);
	createNumber(name, 40, "_4", vertices, indices, tema1);

	init5(vertices, indices, offset, color);
	createNumber(name, 40, "_5", vertices, indices, tema1);

	init6(vertices, indices, offset, color);
	createNumber(name, 40, "_6", vertices, indices, tema1);

	init7(vertices, indices, offset, color);
	createNumber(name, 40, "_7", vertices, indices, tema1);

	init8(vertices, indices, offset, color);
	createNumber(name, 40, "_8", vertices, indices, tema1);

	init9(vertices, indices, offset, color);
	createNumber(name, 40, "_9", vertices, indices, tema1);

}