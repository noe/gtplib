// Copyright (c) 2012, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef __gtp_codec_header_seen__
#define __gtp_codec_header_seen__

#include <iosfwd>
#include "gtplib/gtpcommands.hpp"

namespace gtp
{

class ProtocolCodec
{
  public:

    ProtocolCodec (std::istream& input, std::ostream& output);

    WhateverCommand readCommand ();

    template<typename T> void writeResponse (const T& t);

  private:

    std::istream& input_;
    std::ostream& output_;
};

}

#include "gtplib/detail/gtpcodec_detail.hpp"

#endif
