#ifndef SRC_TNODO_H_
#define SRC_TNODO_H_

#include "TEntidad.h"

#include <vector>
#include <cstdint>

class TNodo{
    public:
        TNodo(uint16_t entidadID, TNodo* nodo_padre = nullptr);
        ~TNodo();

        TNodo* get_nodo_padre();
        void set_nodo_padre(TNodo* nodo_padre);

        void borrar_nodo();
        bool borrar_hijo(TNodo *hijo);

        void agrega_hijo(TNodo* hijo);
        void agrega_hijo(TEntidad* entidad);

        void draw();

        TEntidad* get_entidad();
        void set_entidad(TEntidad* entidad);

        uint16_t get_entidad_id();

        std::vector<TNodo*>& get_hijos(){return _hijos;}

    private:
        TEntidad *_entidad;
	    TNodo *_padre;
	    std::vector<TNodo*> _hijos;
	    uint16_t _entidadID;
	    bool _visible;
};


#endif /* SRC_TNODO_H_ */