
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linked_list_collection.h"

using namespace std;

// Test 1
TEST(BasicListTest, CorrectSize) {
  LinkedListCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());
}

// Test 2
TEST(BasicListTest, SimpleFind) {
  LinkedListCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  LinkedListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  LinkedListCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());

  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 5
TEST(BasicListTest, SimpleSort) {
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

// Test 6
TEST(BasicListTest, DiffCorrectSize) {
  LinkedListCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());
  c.add("d", 100.0);
  ASSERT_EQ(4, c.size());
  c.add("e", 2000.0);
  ASSERT_EQ(5, c.size());
  c.add("f", 2500.0);
  ASSERT_EQ(6, c.size());
}

// Test 7
TEST(BasicListTest, DiffRemoveElems) {
  LinkedListCollection<string,int> c;
  int v;
  c.add("k", 10);
  c.add("l", 20);
  ASSERT_EQ(2, c.size());
  c.remove("k");
  c.remove("l"); 

  ASSERT_EQ(0, c.size()); 
  ASSERT_EQ(false, c.find("k", v)); 
  ASSERT_EQ(false, c.find("l", v)); 
}

// Test 8
TEST(BasicListTest, DiffRange) {
  LinkedListCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  c.add(500, "h");
  c.add(1000, "i");
  c.add(300, "g");
  c.add(45000, "l");
  c.add(6000, "j");
  c.add(20000, "k");

  vector<string> vs2;
  c.find(10, 1000, vs2);
  ASSERT_EQ(9, vs2.size());

  vector<string> vs3;
  c.find(10, 45000, vs3);
  ASSERT_EQ(12, vs3.size());
}

// Test 9
TEST(BasicListTest, DiffSort) {
  LinkedListCollection<string,int> c;
  c.add("a", -10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  c.add("h", 500);
  c.add("i", 1000);
  c.add("g", 300);
  c.add("l", 45000);
  c.add("j", 6000);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(10, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

// Test 10
TEST(BasicListTest, Equal){
  LinkedListCollection <string, double> c;
  c.add("de", 40.0);	//test to make sure remove works on 2 char strings
  c.add("t", 67.0);
  double v;
  c.remove("de");
  ASSERT_EQ(c.find("de", v), false);
  c.remove("i"); //test to make sure removing a string that doesnt exist works and doesnt remove anything else instead
  ASSERT_EQ(c.find("t", v), true);
  c.remove("t");
  c.remove("f");
  ASSERT_EQ(c.size(), 0); //test to make sure when empty and remove is used, the size doesnt go below 0 
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

