#ifndef POSICIONES_RESPAWN_H_
#define POSICIONES_RESPAWN_H_

#include <cstdint>
#include "Utilidades/Vector.h" 
#include "Personajes/Enum_Tipo_Ataque.h"
#include <map>

class Character;
class Nivel;

class Respawn {

public:
	static Respawn* posiciones_instancia();
	~Respawn();

    void crear_zonas_respawn(Nivel* _i_nivel);
    void eliminar_zonas_respawn();
	
    void anyadir_character_y_tiempo_para_reaparecer(Character* _i_character, double _i_tiempo);
    void eliminar_character_a_reaparecer(Character* _i_character);
    void comprobar_si_renace_y_renacer_personaje(Character* _i_personaje);

    void eliminar_datos();
    void eliminar_puntos();
    void vaciar_map();


    Vector2 generar_posicion_al_azar_xz();
    Vector2 generar_posicion_del_bando(Enum_Equipo _i_bando);

private:

    std::map<Character*, double> _character_a_reaparecer;
    Respawn();
	static Respawn* instancia;
   	uint16_t cantidad_de_posiciones;
    float ** posiciones;

};

#endif /* POSICIONES_RESPAWN_H_ */