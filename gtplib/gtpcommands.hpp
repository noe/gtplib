// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_commands_header_seen__
#define __gtp_commands_header_seen__

#include <tuple>
#include <boost/variant.hpp>

#include "gtplib/gtptypes.hpp"

namespace gtp 
{

////////////////////////////////////////////////////////////////////////////////
// Enumeration of all types of GTP commands in the standard.
//
enum class CommandType
{
  protocol_version,       name,                   version,
  known_command,          list_commands,          quit,
  boardsize,              clear_board,            komi,
  play,                   genmove,                undo,
  fixed_handicap,         place_free_handicap,    set_free_handicap,
  time_settings,          time_left,              final_score,
  final_status_list
};

////////////////////////////////////////////////////////////////////////////////
// Structs for holding a command's metainfo in a typesafe way.
// (see gtp::Command in gtplib/types.hpp).
//
using CmdProtocolVersion = Command<CommandType::protocol_version, int>;
using CmdName = Command<CommandType::name, std::string>;
using CmdVersion = Command<CommandType::version, std::string>;
using CmdKnownCommand = Command<CommandType::known_command, bool, std::string>;
using CmdListCommands = Command<CommandType::list_commands, std::list<CommandType>>;
using CmdQuit = Command<CommandType::quit, void>;
using CmdBoardSize = Command<CommandType::boardsize, void, int>;
using CmdClearBoard = Command<CommandType::clear_board, void>;
using CmdKomi = Command<CommandType::komi, void, int>;
using CmdGenmove = Command<CommandType::genmove, Vertex, Color>;
using CmdPlay = Command<CommandType::play, void, Move>;
using CmdFixedHandicap = Command<CommandType::fixed_handicap, std::list<Vertex>, int>;
using CmdPlaceFreeHandicap = Command<CommandType::place_free_handicap, std::list<Vertex>, int>;
using CmdSetFreeHandicap = Command<CommandType::place_free_handicap, void, std::list<Vertex>>;
using CmdTimeSettings = Command<CommandType::time_settings, void, int, int, int>;
using CmdTimeLeft = Command<CommandType::time_left, void, Color, Color, int, int>;
using CmdFinalScore = Command<CommandType::final_score, void, Score>;
using CmdFinalStatusList = Command<CommandType::final_status_list, std::list<Vertex>, StoneStatus>;


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
