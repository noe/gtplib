// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_engine_header_seen__
#define __gtp_engine_header_seen__

#include <istream>
#include <ostream>

#include "gtplib/detail/gtpcodec.hpp"

namespace gtp
{

///////////////////////////////////////////////////////////////////////////////
//  Class to assemble the parsing of the input with the actual handling of the
//  GTP commands. It is templatized with Engine, a class that must provide a
//  method called 'handle' for every type of command, receiving as arguments
//  the command's parameters and returning the command's return value. Check
//  header file gtplib/gtpcommands.hpp for the full list of commands.
//
template<typename Engine>
class EngineFrontend
{
  public:

    /* Constructor */
    EngineFrontend (std::istream& input,
                    std::ostream& output,
                    Engine& engine);

    /* Starts processing (blocking) until no more input */
    void start ();

    /* Stops processing */
    void stop ();

  private:

    ProtocolCodec codec_;  // Utility class to read/write the protocol

    Engine& engine_; // Class that actually handles the GTP commands

    bool stop_;  // wheather or not to stop (TODO: use std::atomic)
};

}

#include "gtplib/detail/gtpengine_impl.hpp"
#endif
