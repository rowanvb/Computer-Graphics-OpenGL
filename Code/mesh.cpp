#include "mesh.h"
#include <algorithm>
#include <vector>       // std::vector


/**
 * @brief Mesh::init
 * Intializes a mesh object by determining its vertices based on the .obj file.
 */
void Mesh::init(QString filename){
    Model model = Model(filename);

    QVector<QVector3D> pos = model.getVertices();
    QVector<QVector3D> norm = model.getNormals();
    QVector<QVector2D> texCoords = model.getTextureCoords();

    if (texCoords.size() < pos.size()){
        texCoords.resize(pos.size());
        //std::fill(texCoords.end(), texCoords.end() + pos.size() - texCoords.size(), QVector2D());
    }

    for(int i = 0 ; i < pos.size(); i++){
        QVector3D normalized = pos[i];
        _bufferObject.push_back({normalized.x(), normalized.y(), normalized.z(),
                                 norm[i].x(), norm[i].y(), norm[i].z(),
                                 texCoords[i].x(), texCoords[i].y()});
    }
}

Mesh::Mesh (QString filename, const GLuint &VAO, const GLuint &VBO, const GLuint &texture) : Object(VAO, VBO, texture)
{
    init(filename);
}

