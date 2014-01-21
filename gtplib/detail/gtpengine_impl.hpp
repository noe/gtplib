// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_engine_detail_header_seen__
#define __gtp_engine_detail_header_seen__

#include "gtplib/gtpcommands.hpp"
#include <boost/variant.hpp>

namespace gtp
{

template<typename ReturnType>
struct Helper
{
  template<typename Engine, typename Cmd>
  void handle (Engine& engine, ProtocolCodec& codec, const Cmd& cmd)
  {
    ReturnType result = engine.handle (cmd);
    codec.writeResponse (result);
  }
};

template<>
struct Helper <void>
{
  template<typename Engine, typename Cmd>
  void handle(Engine& engine, ProtocolCodec& codec, const Cmd& cmd)
  {
    engine.handle (cmd);
  }
};

struct PrintCmd : public boost::static_visitor<void>
{
  template<typename Command>
  void operator()(const Command& cmd) const
  {
    std::cout << "COMMAND: " << cmd << std::endl;
  }
};

template<typename Engine>
class CommandVisitor : public boost::static_visitor<void>
{
  public:

    CommandVisitor (Engine& engine, ProtocolCodec& codec)
      : engine_ (engine), codec_ (codec) { /* do nothing */ }

    template<CommandType t, typename ReturnType, typename... Params>
    void operator()(const Command<t, ReturnType, Params...>& cmd) const
    {
      Helper<ReturnType> helper;
      helper.handle (engine_, codec_, cmd);
    }

  private:
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
  CommandVisitor<Engine> visitor (engine_, codec_);

  while (!stop_)
  {
    try
    {
      WhateverCommand cmd = codec_.readCommand ();
//FIXME: without this like everything blocks
      boost::apply_visitor (PrintCmd(), cmd);
      boost::apply_visitor (visitor, cmd);
    }
    catch (...) //FIXME
    {
      stop_ = true;
    }
  }
}
    
template<typename Engine>
void EngineFrontend<Engine>::stop ()
{
  stop_ = true;
}

}
#endif
