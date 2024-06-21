#ifndef CEMITERIO_H
#define CEMITERIO_H

#include "astronauta.h"
#include <list>

class Cemiterio {
private:
    static list<Astronauta> astronautasMortos;

public:
    Cemiterio();
    static void adicionarMorto(const Astronauta& astronauta);
    static const list<Astronauta>& getAstronautasMortos();
};

#endif
