#include <gtest/gtest.h>

#include "gtplib/gtpfrontend.hpp"
#include "dummyengine.hpp"

#include <iostream>
#include <sstream>


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



