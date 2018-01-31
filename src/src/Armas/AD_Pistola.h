#ifndef AD_PISTOLA_H_
#define AD_PISTOLA_H_

#include "Arma_distancia.h"

class AD_Pistola : public Arma_distancia{
public:
	AD_Pistola(uint16_t _id, float _i_x, float _i_y, float _i_z);
	virtual ~AD_Pistola();
	void render() override;
	Character* usar(uint16_t _i_direccion) override;

protected: 
		//short Velocidad_bala;
};

#endif /* AD_PISTOLA_H_ */
