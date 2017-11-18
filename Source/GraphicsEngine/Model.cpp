#include "Model.h"
#include "Vertex.h"

Model::Model():
	m_ID(0),
	m_VboID(0),
	m_IboID(0),
	m_NumVertices(0),
	m_NumIndices(0)
{

}

Model::Model(int ID):
	m_ID(ID),
	m_VboID(0),
	m_IboID(0),
	m_NumVertices(0),
	m_NumIndices(0)
{

}

Model::~Model()
{
	
}

int index = 0;
const int numIndices = 36;
const int numVertices = 36;
int cubeIndices[numIndices];

float cubeVertices[numVertices][6] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float textureCoords[6][2] = {
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

void quad(int a, int b, int c, int d)
{
	cubeIndices[index] = a; index++;
	cubeIndices[index] = b; index++;
	cubeIndices[index] = d; index++;
	cubeIndices[index] = b; index++;
	cubeIndices[index] = c; index++;
	cubeIndices[index] = d; index++;
}

void colorcube()
{
	quad(0, 1, 2, 3);
	quad(1, 5, 6, 2);
	quad(5, 6, 7, 4);
	quad(4, 0, 3, 7);
	quad(4, 5, 1, 0);
	quad(7, 6, 2, 3);
}

void Model::LoadModel(const char* filePath)
{
	//tmp for cube. later read from a formated file.
	const int n = 8;
	Vertex vertices[numVertices];
	m_NumIndices = numIndices;
	m_NumVertices = numVertices;

	for (int i=0; i<numVertices; i++)
	{
		vertices[i].pos = glm::vec3(cubeVertices[i][0], cubeVertices[i][1], cubeVertices[i][2]);
		vertices[i].nor = glm::vec3(cubeVertices[i][3], cubeVertices[i][4], cubeVertices[i][5]);
		vertices[i].uv  = glm::vec2(textureCoords[i%6][0], textureCoords[i%6][1]);
	}

	//colorcube();

	//Gen buffers and push data to the GPU
	glGenBuffers(1, &m_VboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	glGenBuffers(1, &m_IboID);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboID);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint Model::GetVboID() const
{
	return m_VboID;
}

GLuint Model::GetIboID() const
{
	return m_IboID;
}

GLuint Model::GetNumVertices() const
{
	return m_NumVertices;
}

GLuint Model::GetNumIndices() const
{
	return m_NumIndices;
}

//	vertices[0].pos = glm::vec3(-0.5,  0.5,  0.5);
//	vertices[1].pos = glm::vec3( 0.5,  0.5,  0.5);
//	vertices[2].pos = glm::vec3( 0.5, -0.5,  0.5);
//	vertices[3].pos = glm::vec3(-0.5, -0.5,  0.5);
//	vertices[4].pos = glm::vec3(-0.5,  0.5, -0.5);
//	vertices[5].pos = glm::vec3( 0.5,  0.5, -0.5);
//	vertices[6].pos = glm::vec3( 0.5, -0.5, -0.5);
//	vertices[7].pos = glm::vec3(-0.5, -0.5, -0.5);

//	vertices[0].color = glm::vec4(0.0, 0.0, 1.0, 1.0);
//	vertices[1].color = glm::vec4(0.0, 1.0, 0.0, 1.0);
//	vertices[2].color = glm::vec4(1.0, 0.0, 0.0, 1.0);
//	vertices[3].color = glm::vec4(0.0, 1.0, 1.0, 1.0);
//	vertices[4].color = glm::vec4(1.0, 0.0, 1.0, 1.0);
//	vertices[5].color = glm::vec4(1.0, 1.0, 0.0, 1.0);
//	vertices[6].color = glm::vec4(1.0, 1.0, 1.0, 1.0);
//	vertices[7].color = glm::vec4(0.0, 0.0, 0.0, 1.0);
//
//	vertices[0].uv = glm::vec2(0.0, 0.0);
//	vertices[1].uv = glm::vec2(1.0, 0.0);
//	vertices[2].uv = glm::vec2(1.0, 1.0);
//	vertices[3].uv = glm::vec2(0.0, 1.0);
//	vertices[4].uv = glm::vec2(0.0, 0.0);
//	vertices[5].uv = glm::vec2(1.0, 0.0);
//	vertices[6].uv = glm::vec2(1.0, 1.0);
//	vertices[7].uv = glm::vec2(0.0, 1.0);
