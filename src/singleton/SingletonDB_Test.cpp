#include "singleton/SingletonDB.h"

#include <gtest/gtest.h>

#include <fstream>

 using namespace std;

 class DBTest : public ::testing::Test
 {
  void SetUp()
  {
    ofstream ofs("capitals.txt");

    ofs << "Paris" << endl << 2'241'346 << endl;
    ofs << "Brasília" << endl << 2'648'532 << endl;
    ofs << "Rome" << endl << 2'868'104 << endl;
    ofs << "Berlin" << endl << 3'748'148 << endl;
    ofs << "London" << endl << 8'908'081 << endl;
    ofs << "Tokyo" << endl << 13'929'286 << endl;
    ofs << "Beijing" << endl << 21'542'000 << endl;
    ofs.close();
  }
 };

TEST_F(DBTest, IntegrationTest)
{
  EXPECT_EQ(2'241'346, SingletonDB::GetInstance().population("Paris"));
  EXPECT_EQ(2'648'532, SingletonDB::GetInstance().population("Brasília"));
  EXPECT_EQ(2'868'104, SingletonDB::GetInstance().population("Rome"));
  EXPECT_EQ(3'748'148, SingletonDB::GetInstance().population("Berlin"));
  EXPECT_EQ(8'908'081, SingletonDB::GetInstance().population("London"));
  EXPECT_EQ(13'929'286, SingletonDB::GetInstance().population("Tokyo"));
  EXPECT_EQ(21'542'000, SingletonDB::GetInstance().population("Beijing"));
}
