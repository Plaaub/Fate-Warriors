#ifndef SRC_ENUM_TIPO_ATAQUE_H_
#define SRC_ENUM_TIPO_ATAQUE_H_

enum Enum_Tipo_Ataque{
	Ataque_Ninguno,	// NIngun ataque
	Ataque_Normal,		// Ataque normal
	Ataque_Fuerte,		// Ataque fuerte
	Ataque_Agarre,		// Agarre que lanza
	Ataque_Especial,	// Ataque especial solo para el personaje
	Ataque_Desconocido	// Eliminar, se gestiona con tipo accion
};
#endif /* SRC_ENUM_TIPO_ATAQUE_H_ */