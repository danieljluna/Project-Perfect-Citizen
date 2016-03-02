#ifndef VERTEX_H
#define VERTEX_H

#include <SFML/Graphics/Sprite.hpp>
#include "PipelineCharacter.h"

namespace ppc {


struct Vertex {

    sf::Color color;

    sf::Vector2f pos;

	PipelineCharacter pipechar;
	
};


};      //End namespace mdg


#endif  //End VERTEX_H
