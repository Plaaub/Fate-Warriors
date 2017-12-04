#ifndef SRC_NPC_H_
#define SRC_NPC_H_

#include "Character.h"

class NPC : public Character {
public:
	NPC(float _i_vida, float _i_x, float _i_y);
	virtual ~NPC();

	void move(unsigned long _i_direccion);

private:
};

#endif /* SRC_NPC_H_ */