#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;



class Vertex {
public:
	Vertex(double, double, double);
	Vertex();
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	Vertex operator=(Vertex);
private:
	double x;
	double y;
	double z;
};

Vertex::Vertex(double vx, double vy, double vz) {

	this->x = vx;
	this->y = vy;
	this->z = vz;

}

Vertex::Vertex() {

	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;

}

double Vertex::getX() {
	return this->x;
}

double Vertex::getY() {
	return this->y;
}

double Vertex::getZ() {
	return this->z;
}

void Vertex::setX(double vx) {
	this->x = vx;
}

void Vertex::setY(double vy) {
	this->y = vy;
}

void Vertex::setZ(double vz) {
	this->z = vz;
}

Vertex Vertex::operator=(const Vertex right) {
	this->x = right.x;
	this->y = right.y;
	this->z = right.z;

	return *this;
}

// vetor global de vertices
vector <Vertex> vertices;
vector <Vertex> t_vertices;
vector <Vertex> normais;

vector <Vertex> out_vertices;
vector <Vertex> out_t_vertices;
vector <Vertex> out_normais;
vector <unsigned int> vertexIndices, textureIndices, normalIndices;

GLuint submarine;
float submarinerot;

void loadOBJ(string filename) {

	string type;
	string line;
	ifstream file;
	Vertex aux;
	char ch;
	long double values;
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
		else {

			if (type == "v") {

				l >> values;
				aux.setX(values);
				l >> values;
				aux.setY(values);
				l >> values;
				aux.setZ(values);

				//cout << setprecision(9) << aux.getX() << " " << aux.getY() << " " << aux.getZ() << endl;


				vertices.push_back(aux);

			}
			else if (type == "vt") {

				l >> values;
				aux.setX(values);
				l >> values;
				aux.setY(values);
				l >> values;
				aux.setZ(values);

				//	cout << aux.getX() << " " << aux.getY() << " " << aux.getZ() << endl;

				t_vertices.push_back(aux);

			}
			else if (type == "vn") {

				l >> values;
				aux.setX(values);
				l >> values;
				aux.setY(values);
				l >> values;
				aux.setZ(values);

				//	cout << aux.getX() << " " << aux.getY() << " " << aux.getZ() << endl;

				normais.push_back(aux);

			}
			else if (type == "f") {

				unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];

				for (int i = 0; i < 3; i++) {
					l >> vertexIndex[i];
					l >> ch;
					l >> textureIndex[i];
					l >> ch;
					l >> normalIndex[i];

					//	cout << vertexIndex[i] << " / " << textureIndex[i] << " / " << normalIndex[i] << " ";
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

			}
			else continue;

		}
	}



	file.close();

}


void drawSub() {

	submarine = glGenLists(1);
	glPointSize(2.0);
	glColor3f(1.0, 1.0, 1.0);

	glNewList(submarine, GL_COMPILE);
	{

		glPushMatrix();
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < vertices.size() - 2; i++) {
			glVertex3f(vertices.at(i).getX(), vertices.at(i).getY(), vertices.at(i).getZ());
			glVertex3f(vertices.at(i + 1).getX(), vertices.at(i + 1).getY(), vertices.at(i + 1).getZ());
			glVertex3f(vertices.at(i + 2).getX(), vertices.at(i + 2).getY(), vertices.at(i + 2).getZ());
		}
		glEnd();

	}


	glPopMatrix();
	glEndList();
}


void indexar() {

	Vertex aux;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		unsigned int vertexIndex = vertexIndices[i];
		aux = vertices.at(vertexIndex - 1);
		out_vertices.push_back(aux);

	}

	for (unsigned int i = 0; i < textureIndices.size(); i++) {

		unsigned int vertexIndex = textureIndices[i];
		aux = t_vertices.at(vertexIndex - 1);
		out_t_vertices.push_back(aux);

	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {

		unsigned int vertexIndex = normalIndices[i];
		aux = normais.at(vertexIndex - 1);
		out_normais.push_back(aux);

	}

}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);
	glMatrixMode(GL_MODELVIEW);
}

void drawSubmarine()
{
	glPushMatrix();
	glTranslatef(0, -40.00, -105);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(submarinerot, 0, 1, 0);
	glCallList(submarine);
	drawSub();
	glPopMatrix();
	submarinerot = submarinerot + 0.6;
	if (submarinerot>360)submarinerot = submarinerot - 360;
}
void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawSubmarine();
	glutSwapBuffers(); //swap the buffers
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("ObjLoader");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	loadOBJ("submarine.txt");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
	glutMainLoop();
	return 0;
}

