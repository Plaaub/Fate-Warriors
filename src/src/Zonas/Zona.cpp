#include "Zona.h"

#include "../Interfaz/Motor.h"
#include "../Personajes/Character.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Player.h"
#include "../Datos_Partida.h"
#include "../Interfaz/Motor.h"
#include "../Game.h"
#include "../Tiempo/Time.h"
#include "../Interactuables/Interruptor.h"
#include "../Interactuables/Puerta_Pincho.h"

Zona::Zona(float _i_x, float _i_y, float _i_z, int long_x, int long_y, Enum_Equipo i_equipo){
_reloj=Time::Instance();
    _equipo = i_equipo;
    _rb = Motor::Motor_GetInstance()->crear_rb_ataque();
    Motor::Motor_GetInstance()->posicionar_rotar_y_escalar_rb(_rb,btVector3(_i_x,_i_y,_i_z), btVector3(long_x,10,long_y), 0);
    _conquistando = false;
    _tiempo_inicio_conquista = 0;
    _long_x = long_x;
    _long_y = long_y;
    _pos_x = _i_x;
    _pos_y = _i_z;
    _tiempo_restante_conquista = 10000;

    _npcs_persiguiendome = 0;
}

Zona::~Zona() {
    Motor::Motor_GetInstance()->borrar_rb(_rb);
    _interruptores_asociados.clear();
    std::cout<<"borrado de zona"<<std::endl;
}


/*METODO PARA ACTUALIZAR LA ZONA*/

void Zona::actualizar_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();

    personajes_de_la_zona.clear();
    _num_characters_equipo_A = 0;
    _num_characters_equipo_B = 0;
    bool _conquistando_aux=true;
    bool _pausar_conquista = false;


    for (uint16_t num_character=0; num_character<_num_characters; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            personajes_de_la_zona.push_back(todos_personajes[num_character]);
            //std::cout << this <<  " estoy en la zona \n";

            if(todos_personajes[num_character]->get_equipo() == Enum_Equipo_A){
                _num_characters_equipo_A++;
            }
            else{
                _num_characters_equipo_B++;
            }

            if(todos_personajes[num_character]->get_equipo() == _equipo){
                _conquistando_aux = false;
                _pausar_conquista = true;
            }
       }   
    }

    //Si no hay del bando que toca tambien debe de restaurarse
    if(!hay_personajes_conquistando_esta_zona()){
         _conquistando = false;
      //  _conquistando_aux = false;
        _tiempo_restante_conquista = 10000;
    }

    else{                               //hay personajes conquistando
        if(!_conquistando){             //Es la primera vez que se pone a conquistar el territorio se debe poner el tiempo
            if(_conquistando_aux){
                _conquistando = true;
                iniciar_tiempo_conquista();
            }
        }

        else{                           //No es la primera vez que se conquista, se estaba conquistando de antes
            if(_pausar_conquista){
                _conquistando = false;
                set_tiempo_restante_para_conquistar();
            }

            if(_conquistando){
                //std::cout << _tiempo_restante_conquista - (_reloj->get_current() - _tiempo_inicio_conquista) << " conquistando.... \n";
            }

            //Si se esta conquistando debe comprobar si ha pasado el tiempo necesario de conquista
            if(_reloj->get_current() >_tiempo_inicio_conquista+_tiempo_restante_conquista){
                std::cout<< " conquistado!!!!'------------------------------------------ \n";
                _tiempo_restante_conquista = 0;
                cambiar_bando();
            }
        }


        //Si esta conquistando y de golpe entra un enemigo debe pausar el tiempo de conquista y guardar el tiempo que falta para conquistar el territorio

    }

}

//COMPROBAR SI HAY PERSONAJES CONQUISTANDO
bool Zona::hay_personajes_conquistando_esta_zona(){
    if(_equipo != Enum_Equipo_A && _num_characters_equipo_A==0){
        return false;
    }

    else if(_equipo != Enum_Equipo_B && _num_characters_equipo_B==0){
        return false;
    }
    return true;
}

float Zona::distancia_player_a_zona(){
        Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Player* _player = _datos->get_player();
   return lib_math_distancia_2_puntos(_player->getX(), _player->getZ(), _pos_x, _pos_y);
}


bool Zona::esta_jugador_en_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Player* _player = _datos->get_player();
    Motor* motor = Motor::Motor_GetInstance();

    if(motor->comprobar_colision(_rb, _player->get_objeto_motor()->getRigidBody()) == true){
        return true;
    }
    return false;
}

uint8_t Zona::get_num_npc_en_zona(){
    
    uint8_t num_npc = 0;

    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();


    for (uint16_t num_character=0; num_character<_num_characters-1; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            num_npc++;
       }   
    }
    return num_npc;

}

void Zona::restaurar_vida_enemigos_zona(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();


    for (uint16_t num_character=0; num_character<_num_characters-1; num_character++){
       if(todos_personajes[num_character]->get_vida_actual()>0 && motor->comprobar_colision(_rb, todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
            todos_personajes[num_character]->set_vida(todos_personajes[num_character]->get_vida_maxima());
       }   
    }
}

//Pausa el tiempo que necesita para conquistar un territorio
void Zona::set_tiempo_restante_para_conquistar(){
    _tiempo_restante_conquista = _tiempo_restante_conquista - (_reloj->get_current() - _tiempo_inicio_conquista);
    std::cout << _tiempo_restante_conquista << "Tiempo_que queda" << std::endl;
}

//Cambia de bando el equipo la zona
void Zona::cambiar_bando(){
    _equipo=personajes_de_la_zona[0]->get_equipo();
    _conquistando=false;
}

//Restaura el tiempo de conquista
void Zona::iniciar_tiempo_conquista(){
    _tiempo_inicio_conquista = _reloj->get_current();
}

std::vector <Character*> Zona::get_characters(){
    return personajes_de_la_zona;
}

bool Zona::get_conquistando(){
    return _conquistando;
}


/* ASOCIAR ELEMENTOS A LA ZONA */ 
void Zona::set_interruptor_asociado(Interruptor* _i_interruptor){
    _interruptores_asociados.push_back(_i_interruptor);
}

void Zona::set_puerta_pincho_asociada(Puerta_Pincho* _i_puerta_pincho){
    _puerta_pincho_asociados.push_back(_i_puerta_pincho);
}

std::vector<Interruptor*> Zona::get_interruptores_asociados(){
    return _interruptores_asociados;
}


/* METODOS DE CERRAR/ABRIR ELEMENTOS ASOCIADOS*/ 

void Zona::activar_todas_las_puerta_pincho(){
    uint8_t num_interruptores = _puerta_pincho_asociados.size();
    for (uint8_t cont=0; cont<num_interruptores; cont++){
       _puerta_pincho_asociados[cont]->activar();
    }
}

void Zona::desactivar_todas_las_puerta_pincho(){
    uint8_t num_interruptores = _puerta_pincho_asociados.size();
    for (uint8_t cont=0; cont<num_interruptores; cont++){
       _puerta_pincho_asociados[cont]->desactivar();
    }
}