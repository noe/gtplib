#include <gtest/gtest.h>

#include "gtplib/gtpfrontend.hpp"
#include "dummyengine.hpp"

#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;
using namespace gtp;

template<typename Command, typename ...Params>
WhateverCommand Cmd(Params... params)
{
  Command c;
  typedef decltype(c.params) Tuple;
  return WhateverCommand(Command{Tuple(params...)});
}

std::map<string, WhateverCommand> buildPairs()
{
  std::map<string, WhateverCommand> result;
  result["protocol_version"] = Cmd<CmdProtocolVersion>();
  result["name"] = Cmd<CmdName>();
  result["known_command"] = Cmd<CmdKnownCommand>();
  result["list_commands"] = Cmd<CmdListCommands>();
  result["boardsize 19"] = Cmd<CmdBoardSize>(19);
  result["clear_board"] = Cmd<CmdClearBoard>();
  result["komi 0.5"] = Cmd<CmdKomi>(0.5);
  result["play b a12"] = Cmd<CmdPlay>(Move{Color::black, Vertex{0, 12}});
  result["genmove w"] = Cmd<CmdGenmove>(Color::white);
  result["fixed_handicap 4"] = Cmd<CmdFixedHandicap>(4);
  result["version"] = Cmd<CmdVersion>();
  return result;
}

TEST(DirectConversion, OneAfterAnother)
{
  std::map<string, WhateverCommand> pairs = buildPairs();

  std::vector<WhateverCommand> expected;
  std::stringstream inputBuffer;

  for (auto pair : pairs)
  {
    inputBuffer << pair.first << "\n";
    expected.push_back (pair.second);
  }

  inputBuffer << "quit\n";
  expected.push_back(CmdQuit{});

  inputBuffer.flush();

  std::stringstream outputDummyBuffer;

  DummyEngine engine;
  gtp::EngineFrontend<DummyEngine> frontend (inputBuffer, outputDummyBuffer, engine);
  frontend.start();

  size_t expectedCommandCount = expected.size();
  size_t parsedCommandCount = engine.commands_.size();
  size_t min = std::min(expectedCommandCount, parsedCommandCount);

  for (size_t k = 0; k < min; ++k)
  {
    EXPECT_EQ(engine.commands_[k], expected[k]);
  }

  EXPECT_EQ(expectedCommandCount, parsedCommandCount);
}

TEST(ReverseConversion, OneAfterAnother)
{
  std::map<string, WhateverCommand> pairs = buildPairs();

  std::vector<WhateverCommand> expected;
  std::stringstream inputBuffer;

  for (auto pair : pairs)
  {
    inputBuffer << pair.first << "\n";
    expected.push_back (pair.second);
  }

  inputBuffer << "quit\n";
  expected.push_back(CmdQuit{});

  inputBuffer.flush();

  std::stringstream outputDummyBuffer;

  DummyEngine engine;
  gtp::EngineFrontend<DummyEngine> frontend (inputBuffer, outputDummyBuffer, engine);
  frontend.start();

  size_t expectedCommandCount = expected.size();
  size_t parsedCommandCount = engine.commands_.size();
  size_t min = std::min(expectedCommandCount, parsedCommandCount);

  for (auto  c : engine.commands_)
  {
    cout << "AGGG: " << c << endl;
  }

  for (size_t k = 0; k < min; ++k)
  {
    cout << "Testing " << expected[k] << "..." << endl;
    EXPECT_EQ(engine.commands_[k], expected[k]);
  }

  EXPECT_EQ(expectedCommandCount, parsedCommandCount);
}
