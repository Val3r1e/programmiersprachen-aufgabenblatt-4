#define CATCH_CONFIG_RUNNER
#include "../external/catch-1.1/catch.hpp"
#include "List.hpp"
#include "iostream"

TEST_CASE ("List_default_constructor ", "[default]")
{
  List <int> list;
  List <int> list2;
  list2.push_front(4);
  REQUIRE (list.empty() == true);
  REQUIRE (list.size() == 0);
  REQUIRE (list2.empty() == false);
  REQUIRE (list2.size() == 1);
}

TEST_CASE ("add an element with push_front ", "[modifiers]")
{
  List <int> list;
  list.push_front(42);
  REQUIRE(42 == list.front());
  list.push_front(3);
  REQUIRE(3 == list.front());
  REQUIRE (list.size() == 2);
}

TEST_CASE ("add an element with push_back ", "[modifiers]")
{
  List <int> list;
  list.push_back(42);
  REQUIRE(42 == list.back());
  list.push_back(3);
  REQUIRE(3 == list.back());
}

TEST_CASE ("delete an element with pop_front ", "[modifiers]")
{
  List <int> list;
  list.push_back(42);
  list.push_back(3);
  REQUIRE(42 == list.front());
  list.pop_front();
  REQUIRE(3 == list.front());
}

TEST_CASE ("delete an element with pop_back ", "[modifiers]")
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

TEST_CASE (" should be empty after clearing ", "[ modifiers ]")
{
  List <int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  //std::cout << "The front is:" << list.front();
  list.clear();
  //std::cout << "The size is: " << list.size();
  //std::cout << "The front is:" << list.front();
  REQUIRE(list.empty());
}

TEST_CASE (" should be an empty range after default construction ","[iterators]")
{
  List <int> list ;
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b == e);
}

TEST_CASE (" provide acces to the first element with begin ", "[iterators]")
{
  List <int> list ;
  list.push_front (42);
  REQUIRE (42 == *list.begin());
}

TEST_CASE (" test == ", "[iterators]")
{
  List <int> list ;
  list.push_front (42);
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b == e);
}

TEST_CASE (" test != ", "[iterators]")
{
  List <int> list;
  list.push_front (42);
  list.push_front (43);
  auto b = list.begin();
  auto e = list.end();
  REQUIRE (b != e);
}

TEST_CASE ("default_constructor ", "[iterators]")
{
  ListIterator<int> it;
  REQUIRE (it.next() == nullptr);
}

TEST_CASE ("other_constructor ", "[iterators]")
{
  ListNode<int> n;
  ListIterator<int> it2(&n);
  REQUIRE (it2.next() == nullptr);
}

TEST_CASE ("operators ", "[iterators]")
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
  //REQUIRE (*(++b) == nullptr);  // 6 5 9 8> vrgl. mit nullptr geht nicht obwohl es drauf zeigt
  REQUIRE (*e == 8);              // 6 5 9 8<
  REQUIRE (*(e++) == 8);          // 6 5 9 8  < wird erhöht und alter Wert wird ausgegeben 
  //REQUIRE (*e == nullptr);      // 6 5 9 8  < vrgl. mit nullptr geht nicht obwohl es drauf zeigt
}

TEST_CASE (" copy constructor ", "[ constructor ]")
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
  //REQUIRE(list != list3);         //list mit Elementen, list3 ohne
  //REQUIRE(list3 == list4);        //list3 ohne Elemente, list4 auch 
  list3.push_front(8);
  REQUIRE(list != list3);
}

/*TEST_CASE (" move constructor ", "[ constructor ]")
{
  List <int> list;
  list.push_front (1);
  list.push_front (2);
  list.push_front (3);
  list.push_front (4);
  List <int> list2 (std::move(list));
  REQUIRE(0 == list.size());
  REQUIRE(list.empty());
  REQUIRE(4 == list2.size());
}*/

/*TEST_CASE ("reverse ", "[reverse]")
{

  List <int> list;
  list.push_front(8);
  list.push_front(9);
  list.push_front(5);
  list.push_front(6);
  auto b = list.begin();

  REQUIRE (*b == 6);  
  REQUIRE (*(++b) == 5);
  REQUIRE (*(++b) == 9);
  REQUIRE (*(++b) == 8);

  list.reverse();
  auto e = list.begin();

  REQUIRE (*e == 8);  
  REQUIRE (*(++e) == 9);
  //REQUIRE (*(++e) == 5);
  //REQUIRE (*(++e) == 6);
}*/

int main(int argc, char* argv[]){

  return Catch::Session().run(argc, argv);
}