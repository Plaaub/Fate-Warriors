#include "TCamara.h"
#include <iostream>

TCamara::TCamara(){
      
}
TCamara::~TCamara(){}
void TCamara::beginDraw(Shader* _i_shader){
}
void TCamara::endDraw(){
}

void TCamara::setActiva(bool activa){
    _activa = activa;
}

void TCamara::calculaView(){
    
}
glm::mat4 TCamara::getPerspectiva(){
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)720, 0.1f, 100.0f);
    return projection;
}