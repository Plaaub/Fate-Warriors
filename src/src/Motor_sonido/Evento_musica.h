#ifndef SRC_EVENTO_MUSICA_H_
#define SRC_EVENTO_MUSICA_H_
#include "Evento_sonido.h"
class Evento_musica: public Evento_sonido{
    public:
        Evento_musica(std::string _i_ruta, FMOD::Studio::System *sys);
        ~Evento_musica();
        void start() override;
        void stop();
        void pause();
        void quit_pause();
};
#endif 