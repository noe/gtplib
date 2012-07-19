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

  //TODO : replace with cppunit or something alike
  if (expected != engine.commands_)
  {
    std::cout << "noooo" << std::endl;
    for (auto c : engine.commands_) std::cout << int(c) << " ";
    std::cout << std::endl; 
  }
  else
  {
    std::cout << "fuck yead" << std::endl;
  }
}

int main(void)
{
  std::cout << "Hi there!" << std::endl;

  std::vector<gtp::CommandType> cmds {
     gtp::CommandType::quit,
     gtp::CommandType::name,
     gtp::CommandType::quit};

  testTypes ("quit\nname\nquit\n", cmds);

  return 0;
}



