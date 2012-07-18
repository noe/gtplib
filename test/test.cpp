#include"gtplib/gtpfrontend.hpp"
#include "dummyengine.hpp"

#include <iostream>

int main(void)
{
//  gtp::ProtocolCodec codec (std::cin, std::cout);
//  gtp::Vertex v = {2, 5};
//  std::list<gtp::Vertex> l; l.push_back(v); l.push_back(v);
//  codec.writeResponse(l);

  DummyEngine engine;
  gtp::EngineFrontend<DummyEngine> frontend (std::cin, std::cout, engine);
   
  return 0;
}



