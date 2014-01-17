// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_codec_detail_header_seen__
#define __gtp_codec_detail_header_seen__

#include <cassert>
#include <map>
#include <istream>
#include <ostream>
#include <memory>
#include <stdexcept>
#include <boost/tokenizer.hpp>

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
// Dumps a gtp::Vertex to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const Vertex& v)
{
  char column = v.y;
  char row = 'A' + v.x;
  out << row << column << std::endl;
  return out;
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
// Dumps a gtp::Score to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, const Score& score)
{
  bool draw = score.advantage == 0;

  if (draw) out << "0" << std::endl;
  else if (score.winner == Color::white) out << "W+" << score.advantage << std::endl;
  else out << "B+" << score.advantage << std::endl;

  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Dumps a gtp::CommandType to the given output stream
//
inline std::ostream& operator<< (std::ostream& out, CommandType cmd)
{
  static auto command2stringMap (mapCommandToString());
  auto it = command2stringMap.find (cmd);
  assert (it != command2stringMap.end()); // means the map is incomplete!
  out << it->second;
  return out;
}

///////////////////////////////////////////////////////////////////////////////
// Finds out the matching gtp::CommandType for the given stringified command.
//
inline CommandType string2command (const std::string& command)
                            throw (std::exception)
{
  static auto string2commandMap (mapStringToCommand());
  auto it = string2commandMap.find (command);
  if (it == string2commandMap.end()) throw std::exception();
  return it->second;
}

///////////////////////////////////////////////////////////////////////////////
template<size_t index>
struct ParseAux
{
  template<typename Tuple>
  void operator()(std::istream& args, Tuple tuple)
  {
    typename std::tuple_element<std::tuple_size<Tuple>::value - index, Tuple>::type t;
    t << args;
    // TODO: control errors

    std::get<index>(tuple) = std::move(t);

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
  void operator()(std::istream& args, Tuple tuple)
  {
    // do nothing
  }
};


///////////////////////////////////////////////////////////////////////////////
template<typename... Params>
std::tuple<Params...> parseParams(std::istream& args)
{
  typedef typename std::tuple<Params...> Tuple;

  Tuple result;
  ParseAux<std::tuple_size<Tuple>::value> parser;
  parser(args, result);
  return result;
}

///////////////////////////////////////////////////////////////////////////////
template<typename Command>
WhateverCommand processCmd(std::istream& args)
{
  Command cmd;
  return WhateverCommand (cmd);
}

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

  switch (type)
  {
    case CommandType::protocol_version:
      return processCmd<CmdProtocolVersion>(buffer);
    case CommandType::name:
      return processCmd<CmdName>(buffer);
    case CommandType::version:
      return processCmd<CmdVersion>(buffer);
    case CommandType::known_command:
      return processCmd<CmdKnownCommand>(buffer);
    case CommandType::list_commands:
      return processCmd<CmdListCommands>(buffer);
    case CommandType::quit:
      return processCmd<CmdQuit>(buffer);
    case CommandType::boardsize:
      return processCmd<CmdBoardSize>(buffer);
    case CommandType::clear_board:
      return processCmd<CmdClearBoard>(buffer);
    case CommandType::komi:
      return processCmd<CmdKomi>(buffer);
    case CommandType::play:
      return processCmd<CmdPlay>(buffer);
    case CommandType::genmove:
      return processCmd<CmdGenmove>(buffer);
    case CommandType::undo:
      return processCmd<CmdUndo>(buffer);
    case CommandType::fixed_handicap:
      return processCmd<CmdFixedHandicap>(buffer);
    case CommandType::place_free_handicap:
      return processCmd<CmdPlaceFreeHandicap>(buffer);
    case CommandType::set_free_handicap:
      return processCmd<CmdSetFreeHandicap>(buffer);
    case CommandType::time_settings:
      return processCmd<CmdTimeSettings>(buffer);
    case CommandType::time_left:
      return processCmd<CmdTimeLeft>(buffer);
    case CommandType::final_score:
      return processCmd<CmdFinalScore>(buffer);
    case CommandType::final_status_list:
      return processCmd<CmdFinalStatusList>(buffer);

    default: (assert (false)); // this should never happen
  }
 
  CmdQuit quit;
  return WhateverCommand (quit);
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
  void writeResponse ( std::ostream& output, const std::list<T>& listOfElements)
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

    if (failed) throw "end"; //FIXME

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
      continue;  // malformed command
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
