
#include "TMooseEngine.h"
#include "TGestorRecursos.h"
#include "TRecurso.h"
#include "TRecursoMalla.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TMalla.h"
#include "TLuz.h"
#include <iostream>
#include <glm/ext.hpp>
#include <iostream>
#include "TNodo.h"

//OPEN GL 
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void recorrerArbol(){
    //TGestorRecursos* resurseManajer = new TGestorRecursos();
    //resurseManajer->getRecursoMalla("Enemigo.obj");
    TMooseEngine* motor=new TMooseEngine();
	
    TTransform* trans1=motor->crearTransform();
	TTransform* trans2=motor->crearTransform();
	TTransform* trans3=motor->crearTransform();

	TLuz* luz =motor->crearLuz();
    TCamara* camara=motor->crearCamara();
    char cstr[50] = "Enemigo.obj";
    char* cstr2  = cstr;
    TMalla* malla1 = motor->crearMalla(cstr2);

    trans1->escalar(0.5,0.25,0.5);
    trans1->trasladar(0,0,-300);
    trans3->trasladar(10,10,0);


    TNodo* nodoTrans1 = motor->crearNodo(motor->nodoRaiz(),trans1);
    TNodo* nodoTrans2 = motor->crearNodo(motor->nodoRaiz(),trans2);
    TNodo* nodoTrans3 = motor->crearNodo(nodoTrans2, trans3);

    TNodo* nodoMalla  = motor->crearNodo(nodoTrans2, malla1);
    TNodo* nodoLuz    = motor->crearNodo(nodoTrans1, luz);
    TNodo* nodoCamara = motor->crearNodo(nodoTrans3, camara);
   
    TNodo* Escena=motor->nodoRaiz();
    /*TNodo *RotaLuz= new TNodo();
    TNodo *RotaCam= new TNodo();
    TNodo* RotaCoche = new TNodo();
    Escena->agrega_hijo(RotaLuz);
    Escena->agrega_hijo(RotaCam);
    Escena->agrega_hijo(RotaCoche);
    TNodo* TraslaLuz=motor->crearNodo(motor->nodoRaiz(),trans1);
    TNodo* TraslaCam=motor->crearNodo(motor->nodoRaiz(),trans2);
    TNodo* TraslaCoche=motor->crearNodo(motor->nodoRaiz(),trans3);
    RotaLuz->agrega_hijo(TraslaLuz);
    RotaCam->agrega_hijo(TraslaCam);
    RotaCoche->agrega_hijo(TraslaCoche);

    TTransform *TransfRotaLuz=new TTransform();
    TTransform* TransfRotaCam=new TTransform();
    TTransform *TransfRotaCoche=new TTransform();

    RotaLuz->set_entidad(TransfRotaLuz);
    RotaCam->set_entidad(TransfRotaCam);
    RotaCoche->set_entidad(TransfRotaCoche);
    
    
    NLuz->set_entidad(EntLuz);
    NCam->set_entidad(EntCam);
    NChasis->set_entidad(MallaChasis);*/


    Escena->draw();
    glm::mat4 algo=glm::mat4();
    algo[0]=glm::vec4( 3.0, 4.0, 0.0, 1.0 );
    glm::mat4 algo2=glm::mat4();
    algo2[1]=glm::vec4( 3.0, 7.0, 0.0, 1.0 );
    glm::mat4 algo3=algo*algo2;//a nivel de papel es algo2 * algo1
    std::cout<<algo[0][0]<<std::endl;
    /*int nViewport =motor->registrarViewport(x,y,alto,ancho);
    motor->setViewportActivoActivo(nViewport);
    int nCamara=motor->registrarCamara(nodoCamara);
    motor->setCamaraActiva(nCamara);
    int nLuz=motor->registrarLuz(nodoLuz);
    motor->setLuzActiva(nLuz);*/

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

int dibujarOpenGL(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MooseEngine", NULL, NULL);
    
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        //input
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //cosicas chulas
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

int main(){
    dibujarOpenGL();
    return 0;
}