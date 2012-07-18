// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_engine_header_seen__
#define __gtp_engine_header_seen__

#include "gtplib/gtpcommands.hpp"

namespace gtp
{

struct IEngine
{
  virtual int handle (const CmdProtocolVersion& cmd) = 0;
  virtual std::string handle (const CmdName& cmd) = 0;
  virtual std::string handle (const CmdVersion& cmd) = 0;
  virtual bool handle (const CmdKnownCommand& cmd) = 0;
  virtual std::list<CommandType> handle (const CmdListCommands& cmd) = 0;
  virtual void handle (const CmdQuit& cmd) = 0;
  virtual void handle (const CmdBoardSize& cmd) = 0;
  virtual void handle (const CmdClearBoard& cmd) = 0;
  virtual void handle (const CmdKomi& cmd) = 0;
  virtual Vertex handle (const CmdGenmove& cmd) = 0;
  virtual void handle (const CmdPlay& cmd) = 0;
  virtual std::list<Vertex> handle (const CmdFixedHandicap& cmd) = 0;
  virtual std::list<Vertex> handle (const CmdPlaceFreeHandicap& cmd) = 0;
  virtual void handle (const CmdSetFreeHandicap& cmd) = 0;
  virtual void handle (const CmdTimeSettings& cmd) = 0;
  virtual void handle (const CmdTimeLeft& cmd) = 0;
  virtual void handle (const CmdFinalScore& cmd) = 0;
  virtual std::list<Vertex> handle (const CmdFinalStatusList& cmd) = 0;

  virtual ~IEngine () { /* do nothing */ }
};

}
#endif
