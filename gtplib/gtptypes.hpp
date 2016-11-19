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

static inline VertexOrPass Pass() { return VertexOrPass{}; }

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

// equality operator for commands
template<CommandType t, typename ReturnType, typename... Params>
static inline bool operator==(const Command<t, ReturnType, Params...>& c1,
                const Command<t, ReturnType, Params...>& c2)
{
  return c1.params == c2.params;
}

// equality operator for Vertex
static inline bool operator==(const Vertex& v1, const Vertex& v2)
{
  return v1.x == v2.x && v1.y == v2.y;
}

// equality operator for VertexOrPass
static inline bool operator==(const VertexOrPass& v1, const VertexOrPass& v2)
{
  return v1.type == v2.type && v1.vertex == v2.vertex;
}

// equality operator for Move
static inline bool operator==(const Move& m1, const Move& m2)
{
  return m1.color == m2.color;
}

// equality operator for Score
static inline bool operator==(const Score& s1, const Score& s2)
{
  return (s1.advantage == 0 && s2.advantage == 0)
         || (s1.advantage == s2.advantage && s1.winner == s2.winner);
}


}
#endif
