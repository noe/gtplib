#ifndef __gtp_goro_engine_header_seen__
#define __gtp_goro_engine_header_seen__

#include "gtplib/gtpengine.hpp"

namespace goro
{

struct GtpGoroEngine
{
  template<gtp::CommandType t, typename... Params>
  void handle (const gtp::Command<t, void, Params...>& cmd)
  {
    std::cout << "int!" << std::endl;
  }

  template<gtp::CommandType t, typename... Params>
  int handle (const gtp::Command<t, int, Params...>& cmd)
  {
    std::cout << "int!" << std::endl;
    return 0;
  }

  template<gtp::CommandType t, typename... Params>
  std::string handle (const gtp::Command<t, std::string, Params...>& cmd)
  {
    std::cout << "int!" << std::endl;
    return "hey";
  }

  template<gtp::CommandType t, typename... Params>
  bool handle (const gtp::Command<t, bool, Params...>& cmd)
  {
    std::cout << "bool!" << std::endl;
    return false;
  }

  template<gtp::CommandType t, typename... Params>
  std::list<gtp::CommandType> handle (const gtp::Command<t, std::list<gtp::CommandType>, Params...>& cmd)
  {
    std::cout << "list of commands!" << std::endl;
    return std::list<gtp::CommandType>();;
  }

  template<gtp::CommandType t, typename... Params>
  gtp::Vertex handle (const gtp::Command<t, gtp::Vertex, Params...>& cmd)
  {
    std::cout << "vertex!" << std::endl;
    gtp::Vertex v = {0, 1};
    return v;
  }

  template<gtp::CommandType t, typename... Params>
  std::list<gtp::Vertex> handle (const gtp::Command<t, std::list<gtp::Vertex>, Params...>& cmd)
  {
    std::cout << "list of vertices!" << std::endl;
    return std::list<gtp::Vertex>();
  }

};

}
#endif
