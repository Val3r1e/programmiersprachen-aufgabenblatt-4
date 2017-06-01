#define CATCH_CONFIG_RUNNER
#include "../external/catch-1.1/catch.hpp"
#include "List.hpp"
#include "iostream"

TEST_CASE ("List default constructor ", "[Aufg. 4.2]")
{
  List <int> list;
  List <int> list2;
  list2.push_front(4);
  REQUIRE (list.empty() == true);
  REQUIRE (list.size() == 0);
  REQUIRE (list2.empty() == false);
  REQUIRE (list2.size() == 1);
}

TEST_CASE ("add an element with push_front ", "[Aufg. 4.3]")
{
  List <int> list;
  list.push_front(42);
  REQUIRE(42 == list.front());
  list.push_front(3);
  REQUIRE(3 == list.front());
  REQUIRE (list.size() == 2);
}

TEST_CASE ("add an element with push_back ", "[Aufg. 4.3]")
{
  List <int> list;
  list.push_back(42);
  REQUIRE(42 == list.back());
  list.push_back(3);
  REQUIRE(3 == list.back());
}

TEST_CASE ("delete an element with pop_front ", "[Aufg. 4.3]")
{
  List <int> list;
  list.push_back(42);
  list.push_back(3);
  REQUIRE(42 == list.front());
  list.pop_front();
  REQUIRE(3 == list.front());
}

TEST_CASE ("delete an element with pop_back ", "[Aufg. 4.3]")
{
  List <int> list;
  list.push_back(42);
  list.push_back(3);
  REQUIRE(3 == list.back());
  list.pop_back();
  REQUIRE(42 == list.back());
  List <int> list2;
  list2.push_back(2);
  list2.pop_back();
  REQUIRE(0 == list2.size());
}

TEST_CASE (" should be empty after clearing ", "[Aufg. 4.4]")
{
  List <int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.clear();
  REQUIRE(list.empty());
}

TEST_CASE (" should be an empty range after default construction ","[Aufg. 4.6]")
{
  List <int> list;
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b == e);
}

TEST_CASE (" provide acces to the first element with begin ", "[Aufg. 4.6]")
{
  List <int> list;
  list.push_front (42);
  REQUIRE (42 == *list.begin());
}

TEST_CASE (" test == ", "[Aufg. 4.6]")        
{
  List <int> list ;
  list.push_front (42);     //only one element, begin and end still on the same element
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b == e);
}

TEST_CASE (" test != ", "[Aufg. 4.6]")
{
  List <int> list;
  list.push_front (42);   //two elements begin and end are on different elements
  list.push_front (42);
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b != e);
}

TEST_CASE ("default constructor ", "[Aufg. 4.6]")
{
  ListIterator<int> it;
  REQUIRE (it.next() == nullptr);
}

TEST_CASE ("other constructor ", "[Aufg. 4.6]")
{
  ListNode<int> n;
  ListIterator<int> it2(&n);
  REQUIRE (it2.next() == nullptr);
}

TEST_CASE ("pre- and postincrement  ", "[Aufg. 4.6]")
{
  List <int> list;
  list.push_front(8);
  list.push_front(9);
  list.push_front(5);
  list.push_front(6);
  auto b = list.begin();
  auto e = list.end();

  REQUIRE (*b == 6);              //>6 5 9 8  erster Wert
  REQUIRE (*(++b) == 5);          // 6>5 9 8  wird erhöht und neuer Knoten wird ausgegeben
  REQUIRE (*(b++) == 5);          // 6 5>9 8  wird erhöht und alter Wert wird ausgegeben
  REQUIRE (*(++b) == 8);          // 6 5 9>8  wird erhöht und neuer Knoten wird ausgegeben
  REQUIRE ((++b) == nullptr);     // 6 5 9 8> wird erhöht und nullptr wird ausgegeben
  REQUIRE (*e == 8);              // 6 5 9 8< letzter Wert
  REQUIRE (*(e++) == 8);          // 6 5 9 8  < wird erhöht und alter Wert wird ausgegeben 
  REQUIRE (e == nullptr);         // 6 5 9 8  < nullptr wird ausgegeben
}

TEST_CASE (" copy constructor and comparing lists ", "[Aufg. 4.8]")
{
  List <int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List <int> list2(list);
  REQUIRE(list == list2);
  List <int> list3;
  List <int> list4;
  REQUIRE(list != list3);         
  REQUIRE(list3 == list4);        
  list3.push_front(8);
  REQUIRE(list != list3);
}

TEST_CASE ("add an element with insert ", "[Aufg. 4.9]")
{
  List <int> list;
  list.push_front(4);
  list.push_front(2);
  list.push_front(6);
  
  auto e = list.begin();      //list now: 624
  REQUIRE (*e == 6);  
  REQUIRE (*(++e) == 2);
  REQUIRE (*(++e) == 4);
  REQUIRE (list.size() == 3);

  list.insert(list.begin(),9);        //Add at the front  

  auto h = list.begin();      //list now: 9624
  REQUIRE (*h == 9);  
  REQUIRE (*(++h) == 6);
  REQUIRE (*(++h) == 2);
  REQUIRE (*(++h) == 4);
  REQUIRE (list.size() == 4);

  list.insert(list.end(),1);           //Add at the place of the last node

  auto g = list.begin();      //list now: 96214
  REQUIRE (*g == 9);  
  REQUIRE (*(++g) == 6);
  REQUIRE (*(++g) == 2);
  REQUIRE (*(++g) == 1);      //not 96241 because end() is the last node not behind it
  REQUIRE (*(++g) == 4);
  REQUIRE (list.size() == 5);

  list.insert(list.bend(),3);           //Add behind the last node

  auto j = list.begin();      //list now: 962143
  REQUIRE (*j == 9);  
  REQUIRE (*(++j) == 6);
  REQUIRE (*(++j) == 2);
  REQUIRE (*(++j) == 1);
  REQUIRE (*(++j) == 4);
  REQUIRE (*(++j) == 3);
  REQUIRE (list.size() == 6);

  auto i = list.begin();
  ++i;
  ++i;    //i = 3

  list.insert(i,7);

  auto k = list.begin();      //list now: 9672143
  REQUIRE (*k == 9);  
  REQUIRE (*(++k) == 6);
  REQUIRE (*(++k) == 7);
  REQUIRE (*(++k) == 2);
  REQUIRE (*(++k) == 1);
  REQUIRE (*(++k) == 4);
  REQUIRE (*(++k) == 3);
  REQUIRE (list.size() == 7);
}

TEST_CASE ("reverse ", "[Aufg. 4.10]")
{
  List <int> list;
  list.push_front(8);
  list.push_front(9);
  list.push_front(5);
  list.push_front(6);

  auto b = list.begin();

  REQUIRE (*b == 6);            //list now: 6598
  REQUIRE (*(++b) == 5);
  REQUIRE (*(++b) == 9);
  REQUIRE (*(++b) == 8);

  list.reverse();

  auto e = list.begin();


  REQUIRE (*e == 8);            //list now: 8956
  REQUIRE (*(++e) == 9);
  REQUIRE (*(++e) == 5);
  REQUIRE (*(++e) == 6);
}

TEST_CASE ("free reverse ", "[Aufg. 4.10]")
{
  List <int> list;
  list.push_front(8);              //list now: 6598
  list.push_front(9);
  list.push_front(5);
  list.push_front(6);

  auto r = reverse(list);

  REQUIRE (*r.begin() == 8);      //list now: 8956
  REQUIRE (*r.begin().next() == 9);
  REQUIRE (*r.begin().next().next() == 5);
  REQUIRE (*r.end() == 6);
}

TEST_CASE ("List in Vector ", "[Aufg. 4.11]")
{
  List <int> list;
  list.push_front(8);              //list now: 6598
  list.push_front(9);
  list.push_front(5);
  list.push_front(6);

  std::vector<int> v (list.size());

  std::copy(list.begin(), list.bend(), std::begin(v));

  REQUIRE (v[0] == 6);   
  REQUIRE (v[1] == 5);
  REQUIRE (v[2] == 9);   
  REQUIRE (v[3] == 8);
}

TEST_CASE (" = operator (Zuweisung) ", "[Aufg. 4.12]")
{
  List <int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);

  List <int> list2;

  REQUIRE(list2 != list);

  list2 = list;

  REQUIRE(list2 == list);
  REQUIRE(list2.size() == list.size());
}

TEST_CASE (" move constructor ", "[Aufg. 4.13]")
{
  List <int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);

  List <int> list2 (std::move(list));
  REQUIRE(0 == list.size());
  REQUIRE(list.empty());
  REQUIRE(4 == list2.size());
}

int main(int argc, char* argv[]){

  return Catch::Session().run(argc, argv);
}