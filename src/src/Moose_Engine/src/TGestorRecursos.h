#ifndef SRC_TGESTORRECURSOS_H_
#define SRC_TGESTORRECURSOS_H_
#include <cstdint>
#include <glm/ext.hpp>
#include <vector>
#include <cstdint>

class TRecurso;
class TRecursoMalla;
class aiMesh;
class aiScene;
class aiNode;
class TGestorRecursos {

public:
    static TGestorRecursos* get_instancia();
    ~TGestorRecursos();
    TRecurso* getRecursoModelo(char* nombre, std::vector<TRecursoMalla*> &_i_modelos);	
    TRecurso* getRecursoTextura(char* nombre);	
    TRecurso* getRecursoMaterial(char* nombre);
    void cargarModelo(std::string &path, std::vector<TRecursoMalla*> &_i_modelos);
    void cargarNodo(aiNode* nodo, const aiScene* scene, std::vector<TRecursoMalla*> &_i_modelos);
    //std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    //unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
    TRecursoMalla* cargarMalla(aiMesh *mesh, const aiScene *scene);		
private:
    TGestorRecursos();
	std::vector<TRecurso*> _recursos;
    static TGestorRecursos* _instancia;
    TRecurso* getRecurso(char* nombre);
};

#endif /* SRC_TGESTORRECURSOS_H_ */