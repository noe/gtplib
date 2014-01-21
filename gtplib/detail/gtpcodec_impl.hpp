// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_codec_detail_header_seen__
#define __gtp_codec_detail_header_seen__

#include <cassert>
#include <map>
#include <string>
#include <istream>
#include <ostream>
#include <memory>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <boost/mpl/for_each.hpp>

namespace gtp
{

///////////////////////////////////////////////////////////////////////////////
// Creates a map that associates every GTP command with its
// associated gtp::CommandType.
//
inline std::map<std::string, CommandType> mapStringToCommand ()
{
  std::map<std::string, CommandType> result;

  result.insert(std::make_pair("protocol_version", CommandType::protocol_version));
  result.insert(std::make_pair("name", CommandType::name));
  result.insert(std::make_pair("version", CommandType::version));
  result.insert(std::make_pair("known_command", CommandType::known_command));
  result.insert(std::make_pair("list_commands", CommandType::list_commands));
  result.insert(std::make_pair("quit", CommandType::quit));
  result.insert(std::make_pair("boardsize", CommandType::boardsize));
  result.insert(std::make_pair("clear_board", CommandType::clear_board));
  result.insert(std::make_pair("komi", CommandType::komi));
  result.insert(std::make_pair("play", CommandType::play));
  result.insert(std::make_pair("genmove", CommandType::genmove));
  result.insert(std::make_pair("undo", CommandType::undo));
  result.insert(std::make_pair("fixed_handicap", CommandType::fixed_handicap));
  result.insert(std::make_pair("place_free_handicap", CommandType::place_free_handicap));
  result.insert(std::make_pair("set_free_handicap", CommandType::set_free_handicap));
  result.insert(std::make_pair("time_settings", CommandType::time_settings));
  result.insert(std::make_pair("time_left", CommandType::time_left));
  result.insert(std::make_pair("final_score", CommandType::final_score));
  result.insert(std::make_pair("final_status_list", CommandType::final_status_list));

  return result;
}

///////////////////////////////////////////////////////////////////////////////
// Creates a map that associates every gtp::CommandType with its
// associated string.
//
inline std::map<CommandType, std::string> mapCommandToString ()
{
  std::map<CommandType, std::string> result;
  for (auto entry : mapStringToCommand())
  {
    result.insert(std::make_pair(entry.second, entry.first));
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////
// Finds out the matching gtp::CommandType for the given stringified command.
//
inline CommandType string2command (const std::string& command)
{
  static auto string2commandMap (mapStringToCommand());
  auto it = string2commandMap.find (command);
  if (it == string2commandMap.end())
  {
    throw std::logic_error("No command for " + command);
  }
  return it->second;
}

///////////////////////////////////////////////////////////////////////////////
// Finds out the matching string for the given CommandType.
//
inline std::string command2string (CommandType type)
{
  static auto commandMap (mapCommandToString());
  auto it = commandMap.find (type);
  if (it == commandMap.end())
  {
    throw std::logic_error("No command string associated");
  }
  return it->second;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::Vertex to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const Vertex& v)
{
  unsigned column = v.y;
  char row = 'A' + v.x;
  out << row << column;
  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::Vertex from the given input stream
//
inline std::istream& operator>>(std::istream& in, Vertex& vertex)
{
  std::string v;
  in >> v;
  boost::to_upper(v);
  if (v.size() < 2 || v.size() > 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  vertex.x = v.at(0) - 'A';
  vertex.y = atoi(&v.c_str()[1]);

  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::VertexOrPass from the given input stream
//
inline std::istream& operator>>(std::istream& in, VertexOrPass& vertexOrPass)
{
  std::string s;
  in >> s;
  if (s == "pass")
  {
    vertexOrPass = Pass();
  }
  else
  {
    vertexOrPass.type = VertexOrPassType::VERTEX;
    std::stringstream buffer (s);
    buffer >> vertexOrPass.vertex;
  }

  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::VertexOrPassType to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const VertexOrPass& v)
{
  if (v.type == VertexOrPassType::PASS)
  {
    out << "pass";
  }
  else
  {
    out << v.vertex;
  }
  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::Color from the given input stream
//
inline std::istream& operator>>(std::istream& in, Color& color)
{
  char colorChar;
  in >> colorChar;
  if (in.fail()) return in;
  color = colorChar == 'W' || colorChar == 'w'? Color::white : Color::black;
  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::Move to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const Move& move)
{
  char color = move.color == Color::white ? 'W' : 'B';
  out << color << " " << move.vertex;
  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::Move from the given input stream
//
inline std::istream& operator>>(std::istream& in, Move& move)
{
  in >> move.color;
  if (!in.fail()) in >> move.vertex;
  return in;
}


///////////////////////////////////////////////////////////////////////////////
// Parses a std::list<gtp::Vertex> from the given input stream
//
inline std::istream& operator>>(std::istream& in, std::list<Vertex>& list)
{
  Vertex vertex;
  while(in >> vertex) list.push_back(vertex);
  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a std::list<gtp::Vertex> to the given output stream
//
inline std::ostream& operator<< (std::ostream& out,
                                 const std::list<Vertex>& vertices)
{
  for (auto vertex : vertices)
  {
    out << vertex;
  }

  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::Score from the given input stream
//
inline std::istream& operator>>(std::istream& in, Score& score)
{
  std::string s;
  in >> s;
  if (s == "0")
  {
    score.winner = Color::white;
    score.advantage = 0;
  }
  else
  {
    std::stringstream buffer (s);
    buffer >> score.winner;
    if (!buffer.fail()) buffer >> score.advantage;
  }

  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Parses a gtp::StoneStatus from the given input stream
//
inline std::istream& operator>>(std::istream& in, StoneStatus& stoneStatus)
{
  std::string s;
  in >> s;
  boost::to_upper(s);
  
  if (s == "DEAD") stoneStatus = StoneStatus::dead;
  else if (s == "ALIVE") stoneStatus = StoneStatus::alive;
  else if (s == "SEKI") stoneStatus = StoneStatus::seki;
  else in.setstate(std::ios::failbit);

  return in;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::Score to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const Score& score)
{
  bool draw = score.advantage == 0;

  if (draw) out << "0";
  else if (score.winner == Color::white) out << "W+" << score.advantage;
  else out << "B+" << score.advantage;

  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::CommandType to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const CommandType& cmd)
{
  out << command2string(cmd);
  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a std::list<gtp::CommandType> to the given output stream
//
inline std::ostream& operator<< (std::ostream& out,
                                 const std::list<CommandType>& cmdTypes)
{
  for (auto cmdType : cmdTypes) out << cmdType;
  return out;
}


///////////////////////////////////////////////////////////////////////////////
// Dumps a Command<?> to the given output stream
//
template<CommandType t, typename ReturnType, typename... Params>
std::ostream& operator<< (std::ostream& out,
                          const Command<t, ReturnType, Params...>& cmd)
{
  out << t;
  return out;
 //TODO: improve this 
}

///////////////////////////////////////////////////////////////////////////////
template<size_t index>
struct ParseAux
{
  template<typename Tuple>
  void operator()(std::istream& args, Tuple& tuple)
  {
    enum aux { TUPLE_INDEX = std::tuple_size<Tuple>::value - index};
    typename std::tuple_element<TUPLE_INDEX, Tuple>::type t;
    args >> t;

    if (args.fail()) return;

    std::get<TUPLE_INDEX>(tuple) = std::move(t);

    // keep parsing
    ParseAux<index - 1> aux;
    aux(args, tuple);
  }
};

///////////////////////////////////////////////////////////////////////////////
template<>
struct ParseAux<0>
{
  template<typename Tuple>
  void operator()(std::istream& args, Tuple& tuple)
  {
    // do nothing
  }
};

///////////////////////////////////////////////////////////////////////////////
struct ProcessCommand
{
  CommandType commandType;;
  std::istream& args;
  WhateverCommand& result;

  template<typename Command>
  void operator()(Command)
  {
    if (commandType != Command::type) return;
     
    Command cmd;
    typedef decltype(Command::params) Tuple;
    ParseAux<std::tuple_size<Tuple>::value> parser;
    parser(args, cmd.params);
    cmd.params;
    result = WhateverCommand (cmd);
  }
};

///////////////////////////////////////////////////////////////////////////////
// Actual method for parsing a GTP command.
//
inline WhateverCommand commandFromLine (const std::string& line)
                                 throw (std::exception)
{
  std::stringstream buffer(line);

  std::string command;
  buffer >> command;
 
  CommandType type = string2command (command);

  CmdError error;
  WhateverCommand result(error);
  ProcessCommand processor{type, buffer, result};
  
  boost::mpl::for_each<WhateverCommand::types>(processor);
  return result;
}

///////////////////////////////////////////////////////////////////////////////
// Writes anything to the given output stream by means of its operator<<
// (so T needs to have an operator<< defined).
//
template<typename T>
struct WriteHelper
{
  void writeResponse (std::ostream& output, const T& t)
  {
    output << t;
  }
};

///////////////////////////////////////////////////////////////////////////////
// Dumps a list of things to an output stream.
//
template<typename T>
struct WriteHelper<std::list<T>>
{
  void writeResponse (std::ostream& output, const std::list<T>& listOfElements)
  {
    WriteHelper<T> helper;

    for (const T& t : listOfElements)
    {
      helper.writeResponse(output, t);
      output << " ";
    }
  }
}; 

///////////////////////////////////////////////////////////////////////////////
// Constructor
//
ProtocolCodec::ProtocolCodec (std::istream& input, std::ostream& output)
  : input_ (input), output_(output)
{
  // do nothing
} 

///////////////////////////////////////////////////////////////////////////////
// Member function that reads a command. If the input stream has an error
// or finishes, it returns a QUIT command.
//
WhateverCommand ProtocolCodec::readCommand ()
{
  CmdQuit quit;
  WhateverCommand nullCmd (quit);

  std::string line;
  bool keepReading = true;

  while (keepReading)
  {
    keepReading = false;

    bool failed = !std::getline(input_, line);

    if (failed) return WhateverCommand(CmdError{}); 

    if (line.empty())
    {
      keepReading = true;
      continue;
    }

    try
    {
      return commandFromLine (line);
    }
    catch (std::exception& ex)
    {
      return WhateverCommand(CmdError{}); 
    }
  }

  return nullCmd;
} 

///////////////////////////////////////////////////////////////////////////////
// Member function that writes generically a response (it makes use of
// nonmember method templates also called 'writeResponse').
//
template<typename T> void ProtocolCodec::writeResponse (const T& t)
{
  WriteHelper<T> helper;
  helper.writeResponse (output_, t);
  output_ << std::endl;
}

}
#endif
