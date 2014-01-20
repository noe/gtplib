#ifndef __gtp_goro_engine_header_seen__
#define __gtp_goro_engine_header_seen__

#include <vector>

#include "gtplib/gtpcommands.hpp"

struct DummyEngine
{
  std::vector<gtp::WhateverCommand> commands_;

  DummyEngine () { /* do nothing */ }

  template<gtp::CommandType t, typename... Params>
  void handle (const gtp::Command<t, void, Params...>& cmd)
  {
    commands_.push_back(cmd);
  }

  template<gtp::CommandType t, typename ReturnType, typename... Params>
  ReturnType handle (const gtp::Command<t, ReturnType, Params...>& cmd)
  {
    commands_.push_back(cmd);
    return ReturnType();
  }
};

#endif
