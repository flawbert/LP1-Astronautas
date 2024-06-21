#include "cemiterio.h"

list<Astronauta> Cemiterio::astronautasMortos;

Cemiterio::Cemiterio() {
    astronautasMortos = list<Astronauta>();
}

void Cemiterio::adicionarMorto(const Astronauta& astronauta) {
    astronautasMortos.push_back(astronauta);
}

const list<Astronauta>& Cemiterio::getAstronautasMortos() {
    return astronautasMortos;
}
