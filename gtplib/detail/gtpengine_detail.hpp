// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_engine_detail_header_seen__
#define __gtp_engine_detail_header_seen__

#include "gtplib/gtpcommands.hpp"

namespace gtp
{

template<typename Engine>
struct CommandVisitor : private boost::static_visitor<>
{
  template<CommandType t, typename... Params>
  void operator()(const Command<t, void, Params...>& cmd)
  {
    engine_.handle (cmd);
  }

  template<CommandType t, typename ReturnType, typename... Params>
  void operator()(const Command<t, void, Params...>& cmd)
  {
    ReturnType result = engine_.handle (cmd);
    codec_.writeResponse (result);
  }

  Engine& engine_;
  ProtocolCodec& codec_;
};

template<typename Engine>
EngineFrontend<Engine>::EngineFrontend (
        std::istream& input,
        std::ostream& output,
        Engine& engine)
  : codec_(input , output), engine_(engine), stop_(false)
{
  /* do nothing */
}

template<typename Engine>
void EngineFrontend<Engine>::start ()
{
  CommandVisitor<Engine> visitor = {engine_, codec_};

  while (!stop_)
  {
    std::unique_ptr<WhateverCommand> cmd = codec_.readCommand ();

    if (!cmd) break;

    boost::apply_visitor (visitor, *cmd);
  }
}
    
template<typename Engine>
void EngineFrontend<Engine>::stop ()
{
  stop_ = true;
}

}
#endif
