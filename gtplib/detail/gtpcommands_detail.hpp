// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_command_detail_header_seen__
#define __gtp_command_detail_header_seen__

#include "gtplib/gtpcommands.hpp"

namespace gtp
{

/////////////////////////////////////////////////////////////////////
// boost::variant that can contain all types of GTP commands
//
using WhateverCommand = boost::variant<
  CmdProtocolVersion, 
  CmdName, 
  CmdVersion, 
  CmdKnownCommand, 
  CmdListCommands, 
  CmdQuit, 
  CmdBoardSize, 
  CmdClearBoard, 
  CmdKomi, 
  CmdGenmove, 
  CmdPlay, 
  CmdFixedHandicap, 
  CmdPlaceFreeHandicap, 
  CmdSetFreeHandicap, 
  CmdTimeSettings, 
  CmdTimeLeft, 
  CmdFinalScore, 
  CmdFinalStatusList>;

}

#endif
