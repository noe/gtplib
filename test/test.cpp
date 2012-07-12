#include"gtplib/gtpcodec.hpp"
#include "gtpgoroengine.hpp"

#include <iostream>

int main(void)
{
//  gtp::ProtocolCodec codec (std::cin, std::cout);
//  gtp::Vertex v = {2, 5};
//  std::list<gtp::Vertex> l; l.push_back(v); l.push_back(v);
//  codec.writeResponse(l);

  goro::GtpGoroEngine engine;
  gtp::EngineFrontend<goro::GtpGoroEngine> frontend (std::cin, std::cout, engine);
   
  return 0;
}



