// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef gtp_types_header_seen__
#define gtp_types_header_seen__

namespace gtp 
{

// Player color, either white or black
enum class Color { white, black };

// A position in the board
enum class VertexOrPassType { VERTEX, PASS };

struct Vertex { unsigned x,y; };

struct VertexOrPass { 
  VertexOrPassType type; Vertex vertex;
  VertexOrPass() : type(VertexOrPassType::PASS), vertex{0, 0} {}
  VertexOrPass(const Vertex& v) : type(VertexOrPassType::VERTEX), vertex(v) {}
  VertexOrPass(unsigned x, unsigned y) : type(VertexOrPassType::VERTEX), vertex{x, y} {}
  operator Vertex() { return vertex; }
};

VertexOrPass Pass() { return VertexOrPass{}; }

// A player's move
struct Move { Color color; VertexOrPass vertex; };

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
