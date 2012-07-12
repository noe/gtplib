// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_types_header_seen__
#define __gtp_types_header_seen__

#include <list>
#include <string>

namespace gtp 
{

// Player color, either white or black
enum class Color { white, black };

// A position in the board
struct Vertex { unsigned x,y; };

// A player's move
struct Move { Color color; Vertex vertex; };

// Result of a game
struct Score { Color winner; unsigned advantage; };

// Posible statuses for a stone
enum class StoneStatus {  dead, alive, seki };

// Forward declaration of the command type enumeration
enum class CommandType;

// Structure of a GTP command
template<CommandType t, typename ReturnType, typename... Params>
struct Command
{
  static const CommandType type = t;
  typedef ReturnType return_type;
  typename std::tuple<Params...> params;
};

}
#endif
