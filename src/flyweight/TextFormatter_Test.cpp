#include "flyweight/TextFormatter.h"

#include <gtest/gtest.h>

using namespace flyweight;

TEST(TextFormatter_Test, HeavyCapitalization)
{
  HeavyweightTextFormatter fmt("This is a such awesome thing!");

  fmt.Capitalize(15, 21);

  auto is_equal = fmt.Capitalize() == "This is a such AWESOME thing!";
  EXPECT_TRUE(is_equal);
}

TEST(TextFormatter_Test, LightCapitalization)
{
  LightweightTextFormatter fmt("This is a such awesome thing!");

  EXPECT_FALSE(fmt.Range(15, 21).capitalize);
  fmt.Range(15, 21).capitalize = true;
  EXPECT_TRUE(fmt.Range(15, 21).capitalize);
  EXPECT_FALSE(fmt.Range(15, 21).bold);
  EXPECT_FALSE(fmt.Range(15, 21).italic);
}

TEST(TextFormatter_Test, LightCapitalizationText)
{
  LightweightTextFormatter fmt("This is a such awesome thing!");

  fmt.Range(15, 21).capitalize = true;
  auto is_equal = fmt.Capitalize() == "This is a such AWESOME thing!";
  EXPECT_TRUE(is_equal);
}

TEST(TextFormatter_Test, LightCapitalizationTwice)
{
  LightweightTextFormatter fmt("This is a such awesome thing!");

  EXPECT_EQ(0u, fmt.fmt_ranges.size());
  fmt.Range(15, 21).capitalize = true;
  fmt.Range(15, 21).capitalize = true;
  EXPECT_EQ(1u, fmt.fmt_ranges.size());
}
