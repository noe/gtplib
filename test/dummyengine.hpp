#ifndef __gtp_goro_engine_header_seen__
#define __gtp_goro_engine_header_seen__

#include "gtplib/gtpcommands.hpp"

struct DummyEngine
{
  gtp::CommandType lastCommand_;

  DummyEngine () : lastCommand_ (gtp::CommandType::quit) { /* do nothing */ }

  template<gtp::CommandType t, typename... Params>
  void handle (const gtp::Command<t, void, Params...>& cmd)
  {
    lastCommand_ = t;
  }

  template<gtp::CommandType t, typename ReturnType, typename... Params>
  ReturnType handle (const gtp::Command<t, int, Params...>& cmd)
  {
    lastCommand_ = t;
    return ReturnType();
  }
};

#endif
