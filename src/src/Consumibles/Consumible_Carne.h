#ifndef SRC_CONSUMIBLE_CARNE_H_
#define SRC_CONSUMIBLE_CARNE_H_

#include "Consumible.h"

class Consumible_Carne : public Consumible{
public:
	Consumible_Carne(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Consumible_Carne();

	bool usar() override;
	void render() override;

};

#endif /* SRC_CONSUMIBLE_CARNE_H_ */