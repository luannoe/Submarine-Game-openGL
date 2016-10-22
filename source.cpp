#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



struct vertex {

	double x;
	double y;
	double z;

};

struct texture_vertex {

	double x;
	double y;

};

struct index {

	int a;
	int b;
	int c;

};

// vetor global de vertices
vector <vertex> vertices;
vector <texture_vertex> t_vertices;
vector <vertex> normais;
vector <unsigned int> vertexIndices, textureIndices, normalIndices;
//vetores usados para criar a face



void criaVetores(string filename) {

	string type;
	string line;
	ifstream file;
	vertex aux;
	texture_vertex aux2;
	
	//index aux3;
	file.open(filename);

	if (!file) {

		cerr << "Erro ao abrir o arquivo... Abortando.";
		return;
	} 


	while (!file.eof()) {
		getline(file, line);
		
		istringstream l(line);
		l >> type;

		//cout << type << endl;
		//file >> line;
		//cout << line << endl;

		if (line[0] == '#' || line == "")
			continue;
		else{
			
			 if (type == "v") {

				l >> aux.x;
				l >> aux.y;
				l >> aux.z;

				//cout << aux.x << " " << aux.y << " " << aux.z << endl;

				vertices.push_back(aux);

			}else if (type == "vt") {
				
				l >> aux2.x;
				l >> aux2.y;

			//	cout << aux2.x << " " << aux2.y << endl;

				t_vertices.push_back(aux2);

			}else if (type == "vn") {
			
				l >> aux.x;
				l >> aux.y;
				l >> aux.z;

				//cout << aux.x << " " << aux.y << " " << aux.z << endl;

				normais.push_back(aux);

			}else if (type == "f") {
				
				unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];

				for (int i = 0; i < 3; i++) {
					l >> vertexIndex[i];
					l >> textureIndex[i];
					l >> normalIndex[i];

					cout << vertexIndex[i] <<" " << textureIndex[i] << " " << normalIndex[i] << endl;
				}

				

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				textureIndices.push_back(textureIndex[0]);
				textureIndices.push_back(textureIndex[1]);
				textureIndices.push_back(textureIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);


				//	faces.push_back(aux);
				//cout << "face" << endl;
			}

		}
	}


	file.close();

}


int main() {


	string arquivo = "submarine.txt";

	criaVetores(arquivo);

	system("PAUSE");

	return 0;
}