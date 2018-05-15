#ifndef SRC_TMOOSEENGINE_H_
#define SRC_TMOOSEENGINE_H_

#include <vector>
#include <cstdint>
#include <glm/ext.hpp>
class TNodo;
class TGestorRecursos;
class TEntidad;
class TTransform;
class TCamara;
class TLuz;
class TModelado;
class TModeladoEscenario;
class TAnimacion;
class Mapeado;
class Shader;
class GLFWwindow;
class Skybox;
class UI;
class ParticleGenerator;

class TMooseEngine{

    public:
        ~TMooseEngine();
        static TMooseEngine* get_instancia();

        void        borrarNodo(uint16_t nodo);
        TNodo*      crearNodo(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoCamara(TNodo *padre, TEntidad *ent);
        TNodo*      crearNodoLuz(TNodo *padre, TEntidad *ent);
        TTransform* crearTransform();
        TCamara*    crearCamara(bool activa);
        TLuz*       crearLuz(glm::vec3 ambiente, glm::vec3 especular, glm::vec3 difusa);
        TModelado*  crearModelado(const char* _i_path);
        TModeladoEscenario* crearModeladoEscenario(const char* _i_paht);
        TAnimacion* crearAnimacion(const char* _i_path);


        inline GLFWwindow* getWindow(){ return window;}

        void        drawLuces();
        void        drawCamaras();

        inline TNodo* nodoRaiz(){
            return _escena;
        }

        void draw();
        void drawSombras();
        void initUI();
        void render_estado_Partida();
        void renderUIMenu(uint16_t opcion, uint16_t opcion2, bool config_abierta);
        void renderUIMenuPausa(uint16_t opcion, uint16_t opcion2, bool config_abierta);
        void renderUIMenuConfig(uint16_t opcion);
        void renderUIHUD();
        void renderUIMenuWin(uint16_t opcion);
        void renderUIMenuLose(uint16_t opcion);

        bool ventana_abierta();
	    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
 //       void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        float getMouseOffsetX();
        float getMouseOffsetY();

        void apagar();

        inline UI* getUI(){ return _ui; }
        ParticleGenerator* get_gestor_particulas();

        void resize_window(int _i_width, int _i_height);

    private:

        void setMouseOffsetX(float offset);
        void setMouseOffsetY(float offset);

        float _offsetX, _offsetY;

        TMooseEngine();
        static TMooseEngine* _instancia;
        std::vector<Mapeado*> _mapping_camaras;
        std::vector<Mapeado*> _mapping_luces;
        TNodo* _escena;
        TGestorRecursos* _gestorRecursos;
        uint16_t _contadorIDEntidad;
        uint8_t  _n_c_actual;
        uint8_t  _n_l_actual;

        glm::mat4 matriz_luz = glm::mat4(1.0f);
        glm::mat4 matriz_view = glm::mat4(1.0f);
        
        GLFWwindow* window;
        Shader *_shader;        


        void init_opengl(uint16_t width, uint16_t height);
        void PreparacionSombras();
        void ConfigurarSombrasMapeado();
        void ConfigurarSombrasProyectadas();
        void clear();
        
        //GLFW mouse input
	    float _lastX, _lastY, _xpos, _ypos;
	    bool _firstMouse;

        //atributos para camaras, luces y demás
        unsigned int depthMapFBO;
        unsigned int depthMap;
        unsigned int SHADOW_WIDTH,SHADOW_HEIGHT;

        //reproductor animaciones
        std::vector<TAnimacion*> _animaciones;
        UI* _ui;
        Skybox* _skybox;
        ParticleGenerator* _particulas;
};


#endif /* SRC_TMOOSEENGINE_H_ */