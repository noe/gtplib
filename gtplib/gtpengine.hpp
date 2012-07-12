// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_engine_header_seen__
#define __gtp_engine_header_seen__

#include <istream>
#include <ostream>

#include "gtplib/gtpcodec.hpp"

namespace gtp
{

template<typename Engine>
class EngineFrontend
{
  public:
    EngineFrontend (std::istream& input,
                    std::ostream& output,
                    Engine& engine);

    /** Starts processing (blocking) until no more input */
    void start ();

    void stop ();

  private:
    ProtocolCodec codec_;
    Engine& engine_;
    bool stop_;
};

}

#include "gtplib/detail/gtpengine_detail.hpp"
#endif
