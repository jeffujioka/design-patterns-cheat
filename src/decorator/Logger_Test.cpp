#include "decorator/Logger.h"
#include <gtest/gtest.h>

using namespace decorator;

TEST(Logger_Test, LoggerOperator)
{
  Logger logger([](){ return "Hallo Welt\n"s; }, "Jeff Test");
  EXPECT_EQ("Entering func Jeff Test\n"s
                 "Hallo Welt\n"s
                 "Exiting func Jeff Test\n"s,
            logger());
}

TEST(Logger_Test, TemplatedLoggerOperator)
{
  auto logger = make_templatedlogger([](){ return "Hallo Welt\n"s; },
                                     "Jeff Test");

  EXPECT_EQ("Entering func Jeff Test\n"s
                 "Hallo Welt\n"s
                 "Exiting func Jeff Test\n"s,
            logger());
}

double add(double a, double b)
{
  return a + b;
}
TEST(Logger_Test, VariadicLoggerIntegrationTest)
{
  auto logger = MakeVariadicLogger(add, "Jeff Test"s);
  EXPECT_EQ(3,logger(1, 2));
}
