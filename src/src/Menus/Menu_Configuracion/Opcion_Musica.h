#ifndef SRC_OPCION_MUSICA_H_
#define SRC_OPCION_MUSICA_H_

#include "Opcion_Volumen.h"

class Opcion_Musica : public Opcion_Volumen{
public:
	Opcion_Musica(Input* _i_input);
	~Opcion_Musica();

protected:
	void set_volumen(float _i_vol);
};

#endif /* SRC_OPCION_MUSICA_H_ */