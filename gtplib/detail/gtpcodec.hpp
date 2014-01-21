// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_codec_header_seen__
#define __gtp_codec_header_seen__

#include <iosfwd>
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
  CmdUndo,
  CmdPlay, 
  CmdFixedHandicap, 
  CmdPlaceFreeHandicap, 
  CmdSetFreeHandicap, 
  CmdTimeSettings, 
  CmdTimeLeft, 
  CmdFinalScore, 
  CmdFinalStatusList,
  CmdError>;

///////////////////////////////////////////////////////////////////////////////
// Class to read GTP commands from an input stream and to write
// responses to them in an output stream.
//
class ProtocolCodec
{
  public:

    // Constructor.
    ProtocolCodec (std::istream& input, std::ostream& output);

    // Reads a command from the input provided in the constructor.
    WhateverCommand readCommand ();

    // Writes a response to the output provided in the constructor.
    template<typename T> void writeResponse (const T& t);

  private:

    std::istream& input_;  // input from where the commands are parsed.

    std::ostream& output_;  // output to where responses are written.
};

}

#include "gtplib/detail/gtpcodec_impl.hpp"

#endif
