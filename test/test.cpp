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
  result["known_commands"] = Cmd<CmdKnownCommand>();
  result["list_commands"] = Cmd<CmdListCommands>();
  result["quit"] = Cmd<CmdQuit>();
  result["boardsize 19"] = Cmd<CmdBoardSize>(19);
  result["clear_board"] = Cmd<CmdClearBoard>();
  result["komi 0.5"] = Cmd<CmdKomi>(0.5);
  result["play b a12"] = Cmd<CmdPlay>(Move{Color::black, Vertex{0, 12}});
  result["genmove w"] = Cmd<CmdGenmove>(Color::white);
  result["fixed_handicap 4"] = Cmd<CmdFixedHandicap>(4);
  result["version"] = Cmd<CmdVersion>();
  return result;
}

void testTypes (const std::string& input, std::vector<gtp::CommandType>& expected)
{
  std::stringstream inputBuffer(input);
  std::stringstream outputBuffer;

  DummyEngine engine;
  gtp::EngineFrontend<DummyEngine> frontend (inputBuffer, outputBuffer, engine);
  frontend.start();

  size_t expectedCommandCount = expected.size();
  size_t parsedCommandCount = engine.commands_.size();
  size_t min = std::min(expectedCommandCount, parsedCommandCount);

  for (size_t k = 0; k < min; ++k)
  {
    EXPECT_EQ(engine.commands_[k], expected[k]);
  }

  EXPECT_EQ(expectedCommandCount, parsedCommandCount);

  //TODO : replace with cppunit or something alike
  if (expected != engine.commands_)
  {
    std::cout << "noooo" << std::endl;
    std::cout << std::endl; 
  }
  else
  {
    std::cout << "fuck yeah" << std::endl;
  }
}

TEST(whatever1, whatever2)
{
  std::cout << "Hi there!" << std::endl;

  std::vector<gtp::CommandType> cmds {
     gtp::CommandType::quit,
     gtp::CommandType::name,
     gtp::CommandType::quit,
     gtp::CommandType::fixed_handicap,
     };

  testTypes ("quit\nname\nquit\nfixed_handicap 4\n", cmds);
}



