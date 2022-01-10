#include "geometry.hpp"

Geometry::Geometry()
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
}

Geometry::~Geometry()
{
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ibo);
    glDeleteVertexArrays(1, &this->vao);
}

Triangle::Triangle(const glm::vec3 p[3], const glm::vec3 n[3])
{
    this->dim = 3;
    this->n_vertices = 3;
    this->n_indices = 3;
    this->n_attributes = 2;

    std::vector<float> data;
    std::vector<unsigned int> indices;

    for(int i = 0; i < this->n_vertices; i++)
    {
        data.push_back(p[i].x);
        data.push_back(p[i].y);
        data.push_back(p[i].z);
        data.push_back(n[i].x);
        data.push_back(n[i].y);
        data.push_back(n[i].z);

        indices.push_back(i);
    }

    glBufferData(GL_ARRAY_BUFFER, this->dim*this->n_vertices*this->n_attributes*sizeof(float), data.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->n_indices*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Triangle::Draw() const
{
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->n_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Sphere::Sphere(unsigned int n_theta_divs, unsigned int n_phi_divs)
{
    this->dim = 3;
    this->n_vertices = 2+(n_theta_divs-2)*n_phi_divs;
    this->n_indices = (n_theta_divs-3)*n_phi_divs*6 + 2*n_phi_divs*3;
    this->n_attributes = 2;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    for(int i = 1; i < n_theta_divs-1; i++)
    {
        float theta = glm::radians(180.0f/n_theta_divs*i);
        for(int j = 0; j < n_phi_divs; j++)
        {
            float phi = glm::radians(360.0f/n_phi_divs*j);
            vertices.push_back(glm::vec3(sinf(theta)*cosf(phi), cosf(theta), -sinf(theta)*sinf(phi)));
        }
    }
    vertices.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

    for(int j = 0; j < n_phi_divs; j++)
    {
        indices.push_back(0);
        indices.push_back(1+j);
        indices.push_back(1+(j+1)%n_phi_divs);
    }
    for(int i = 1; i < n_theta_divs-1; i++)
    {
        for(int j = 0; j < n_phi_divs; j++)
        {
            indices.push_back(1+(i-1)*n_phi_divs+j);
            indices.push_back(1+i*n_phi_divs+j);
            indices.push_back(1+(j+1)%n_phi_divs+i*n_phi_divs);
            indices.push_back(1+(i-1)*n_phi_divs+j);
            indices.push_back(1+(j+1)%n_phi_divs+i*n_phi_divs);
            indices.push_back(1+(j+1)%n_phi_divs+(i-1)*n_phi_divs);
        }
    }
    for(int j = 0; j < n_phi_divs; j++)
    {
        indices.push_back(1+j+(n_theta_divs-3)*n_phi_divs);
        indices.push_back(this->n_vertices-1);
        indices.push_back(1+(j+1)%n_phi_divs+(n_theta_divs-3)*n_phi_divs);
    }

    std::vector<float> data;
    for(int i = 0; i < vertices.size(); i++)
    {
        data.push_back(vertices[i].x);
        data.push_back(vertices[i].y);
        data.push_back(vertices[i].z);
        data.push_back(vertices[i].x);
        data.push_back(vertices[i].y);
        data.push_back(vertices[i].z);
    }

    glBufferData(GL_ARRAY_BUFFER, this->dim*this->n_vertices*this->n_attributes*sizeof(float), data.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->n_indices*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Sphere::Draw() const
{
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->n_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Grid::Grid(glm::vec3 min_cord, glm::vec3 max_cord, unsigned int n_divs)
{
    this->dim = 3;
    this->n_attributes = 2;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 gap = (max_cord - min_cord) / (float)n_divs;

    for(unsigned int x = 0; x <= n_divs; x++) for(unsigned int y = 0; y <= n_divs; y++) for(unsigned int z = 0; z <= n_divs; z++)
    {
        vertices.push_back(min_cord + glm::vec3(x, y, z)*gap);
    }

    this->n_vertices = vertices.size();

    for(unsigned int x = 0; x <= n_divs; x++) for(unsigned int y = 0; y <= n_divs; y++) for(unsigned int z = 0; z < n_divs; z++)
    {
        indices.push_back(x*(n_divs+1)*(n_divs+1)+y*(n_divs+1)+z);
        indices.push_back(x*(n_divs+1)*(n_divs+1)+y*(n_divs+1)+z+1);
    }
    for(unsigned int x = 0; x <= n_divs; x++) for(unsigned int y = 0; y < n_divs; y++) for(unsigned int z = 0; z <= n_divs; z++)
    {
        indices.push_back(x*(n_divs+1)*(n_divs+1)+y*(n_divs+1)+z);
        indices.push_back(x*(n_divs+1)*(n_divs+1)+(y+1)*(n_divs+1)+z);
    }
    for(unsigned int x = 0; x < n_divs; x++) for(unsigned int y = 0; y <= n_divs; y++) for(unsigned int z = 0; z <= n_divs; z++)
    {
        indices.push_back(x*(n_divs+1)*(n_divs+1)+y*(n_divs+1)+z);
        indices.push_back((x+1)*(n_divs+1)*(n_divs+1)+y*(n_divs+1)+z);
    }

    this->n_indices = indices.size();

    std::vector<float> data;
    for(int i = 0; i < vertices.size(); i++)
    {
        data.push_back(vertices[i].x);
        data.push_back(vertices[i].y);
        data.push_back(vertices[i].z);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
    }

    glBufferData(GL_ARRAY_BUFFER, this->dim*this->n_vertices*this->n_attributes*sizeof(float), data.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->n_indices*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Grid::Draw() const
{
    glBindVertexArray(this->vao);
    glDrawElements(GL_LINES, this->n_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Metaball::Metaball(const glm::vec3& min_cord, const glm::vec3& max_cord, int n_divs, double isolevel, const ImplicitFunction& imp)
{
    this->dim = 3;
    this->n_attributes = 2;

    glm::vec3 gap = (max_cord - min_cord) / (float)n_divs;

    std::vector<std::vector<std::vector<glm::vec3>>>p(n_divs+1, std::vector<std::vector<glm::vec3>>(n_divs+1, std::vector<glm::vec3>(n_divs+1)));
    std::vector<std::vector<std::vector<double>>>val(n_divs+1, std::vector<std::vector<double>>(n_divs+1, std::vector<double>(n_divs+1)));
    for(int x = 0; x <= n_divs; x++) for(int y = 0; y <= n_divs; y++) for(int z = 0; z <= n_divs; z++)
    {
        p[x][y][z] = min_cord + glm::vec3(x, y, z)*gap;
        val[x][y][z] = imp.f(p[x][y][z]);
    }

    std::vector<float> data;
    for(int x = 0; x < n_divs; x++) for(int y = 0; y < n_divs; y++) for(int z = 0; z < n_divs; z++)
    {
        int cubeindex = 0;
        if(val[x  ][y  ][z  ] < isolevel) cubeindex |=   1;
        if(val[x+1][y  ][z  ] < isolevel) cubeindex |=   2;
        if(val[x+1][y  ][z+1] < isolevel) cubeindex |=   4;
        if(val[x  ][y  ][z+1] < isolevel) cubeindex |=   8;
        if(val[x  ][y+1][z  ] < isolevel) cubeindex |=  16;
        if(val[x+1][y+1][z  ] < isolevel) cubeindex |=  32;
        if(val[x+1][y+1][z+1] < isolevel) cubeindex |=  64;
        if(val[x  ][y+1][z+1] < isolevel) cubeindex |= 128;

        if(edgeTable[cubeindex] ==    0) continue;

        glm::vec3 vertlist[12];
        if (edgeTable[cubeindex] &    1) vertlist[ 0] = VertexInterp(isolevel, p[x  ][y  ][z  ], p[x+1][y  ][z  ], val[x  ][y  ][z  ], val[x+1][y  ][z  ]);
        if (edgeTable[cubeindex] &    2) vertlist[ 1] = VertexInterp(isolevel, p[x+1][y  ][z  ], p[x+1][y  ][z+1], val[x+1][y  ][z  ], val[x+1][y  ][z+1]);
        if (edgeTable[cubeindex] &    4) vertlist[ 2] = VertexInterp(isolevel, p[x+1][y  ][z+1], p[x  ][y  ][z+1], val[x+1][y  ][z+1], val[x  ][y  ][z+1]);
        if (edgeTable[cubeindex] &    8) vertlist[ 3] = VertexInterp(isolevel, p[x  ][y  ][z+1], p[x  ][y  ][z  ], val[x  ][y  ][z+1], val[x  ][y  ][z  ]);
        if (edgeTable[cubeindex] &   16) vertlist[ 4] = VertexInterp(isolevel, p[x  ][y+1][z  ], p[x+1][y+1][z  ], val[x  ][y+1][z  ], val[x+1][y+1][z  ]);
        if (edgeTable[cubeindex] &   32) vertlist[ 5] = VertexInterp(isolevel, p[x+1][y+1][z  ], p[x+1][y+1][z+1], val[x+1][y+1][z  ], val[x+1][y+1][z+1]);
        if (edgeTable[cubeindex] &   64) vertlist[ 6] = VertexInterp(isolevel, p[x+1][y+1][z+1], p[x  ][y+1][z+1], val[x+1][y+1][z+1], val[x  ][y+1][z+1]);
        if (edgeTable[cubeindex] &  128) vertlist[ 7] = VertexInterp(isolevel, p[x  ][y+1][z+1], p[x  ][y+1][z  ], val[x  ][y+1][z+1], val[x  ][y+1][z  ]);
        if (edgeTable[cubeindex] &  256) vertlist[ 8] = VertexInterp(isolevel, p[x  ][y  ][z  ], p[x  ][y+1][z  ], val[x  ][y  ][z  ], val[x  ][y+1][z  ]);
        if (edgeTable[cubeindex] &  512) vertlist[ 9] = VertexInterp(isolevel, p[x+1][y  ][z  ], p[x+1][y+1][z  ], val[x+1][y  ][z  ], val[x+1][y+1][z  ]);
        if (edgeTable[cubeindex] & 1024) vertlist[10] = VertexInterp(isolevel, p[x+1][y  ][z+1], p[x+1][y+1][z+1], val[x+1][y  ][z+1], val[x+1][y+1][z+1]);
        if (edgeTable[cubeindex] & 2048) vertlist[11] = VertexInterp(isolevel, p[x  ][y  ][z+1], p[x  ][y+1][z+1], val[x  ][y  ][z+1], val[x  ][y+1][z+1]);

        for(int i = 0; triTable[cubeindex][i] != -1; i += 3) 
        {
            for(int j = 0; j < 3; j++)
            {
                glm::vec3 n = imp.getNormal(vertlist[triTable[cubeindex][i+j]]);
                data.push_back(vertlist[triTable[cubeindex][i+j]].x);
                data.push_back(vertlist[triTable[cubeindex][i+j]].y);
                data.push_back(vertlist[triTable[cubeindex][i+j]].z);
                data.push_back(n.x);
                data.push_back(n.y);
                data.push_back(n.z);
            }
        }
    }

    this->n_data = data.size();

    glBufferData(GL_ARRAY_BUFFER, this->n_data*sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->dim*this->n_attributes*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Metaball::Draw() const
{
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->n_data);
    glBindVertexArray(0);
}

glm::vec3 Metaball::VertexInterp(double isolevel, const glm::vec3& p1, const glm::vec3& p2, double valp1, double valp2)
{
    double mu;
    glm::vec3 p;

    if (abs(isolevel-valp1) < 0.00001) return(p1);
    if (abs(isolevel-valp2) < 0.00001) return(p2);
    if (abs(valp1-valp2) < 0.00001) return(p1);
    mu = (isolevel - valp1) / (valp2 - valp1);
    p.x = p1.x + mu * (p2.x - p1.x);
    p.y = p1.y + mu * (p2.y - p1.y);
    p.z = p1.z + mu * (p2.z - p1.z);

    return(p);
}


