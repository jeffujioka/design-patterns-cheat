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

TEST_F(DBTest, IntegrationTotalPopulation)
{
  vector<string> capitals = {
      "Paris", "Brasília", "Rome", "Berlin", "London", "Tokyo", "Beijing"};
  RecordFinder finder(SingletonDB::GetInstance());

  EXPECT_EQ(55'885'497, finder.total_population(capitals));
}

// TODO replace this for gmock class
struct DummyDB : public Database
{
  map<string, int> populations;

  DummyDB()
  {
    populations["cap_a"] = 10;
    populations["cap_b"] = 20;
    populations["cap_c"] = 30;
    populations["cap_d"] = 40;
  }

  int population(const string& name) override { return populations[name]; }
};

TEST(SingletonDB_Test, PopulationDummy)
{
  DummyDB db;
  RecordFinder finder(db);

  // TODO replace by EXPEC_CALL + Return
  EXPECT_EQ(10, finder.population("cap_a"));
  EXPECT_EQ(20, finder.population("cap_b"));
  EXPECT_EQ(30, finder.population("cap_c"));
  EXPECT_EQ(40, finder.population("cap_d"));
}

TEST(SingletonDB_Test, TotalPopulation)
{
  vector<string> capitals = {
      "cap_a", "cap_b", "cap_c", "cap_d"};
  DummyDB db;
  RecordFinder finder(db);

  EXPECT_EQ(100, finder.total_population(capitals));
}