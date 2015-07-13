#define INCLUDE_ALL
#include "stdafx.h"
#include "first.hpp"
#define PRINT_ALL
using namespace std;
using namespace mydetails;

int main()
{
  // std::pair<> & std::vector<>
  pair<vector<string>,vector<float>> ar01({"1","2","3","4"},
					 {2.5,3.54,4.23,5.45});
  cout<<"Pair<> & Vector<> :"<<endl;
  cout<<ar01<<endl;
  cout<<endl;

  // C-Array
  string ar02[4] = {"Govind","Sahai","ABVG","dfs"};
  int ar03[] = {6,3,6,3,5,6,0,9};
  int ar04[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
  cout<<"C - arrays : "<<endl;
  cout<<ar02<<endl;
#ifdef PRINT_ALL
  cout<<ar03<<endl;
  cout<<ar04<<endl;
#endif
  cout<<endl;

  // std::array<>
  array<string,4> ar05 = {"Govind","Sahai","ABVG","dfs"};
  array<int, 8> ar06 = {6,3,6,3,5,6,0,9};
  array<int[4], 3> ar07 = {1,2,3,4,5,6,7,8,9,10,11,12};
  cout<<"std::arrays<> : "<<endl;
  cout<<ar05<<endl;
#ifdef PRINT_ALL
  cout<<ar06<<endl;
  cout<<ar07<<endl;
#endif
  cout<<endl;

  // std::unordered_set<>
  unordered_set<string> ar08 = {"Govind", "Sahai"};
  cout<<"std::unordered_set<> : "<<endl;
  cout<<ar08<<endl;
  cout<<endl;

  // std::list<>
  list<int> ar09 = {1,2,3,4};
  cout<<"std::list<> : "<<endl;
  cout<<ar09<<endl;
  cout<<endl;

  // std::map<>
  map<string,int> ar10 = {{"Govind",2}, {"Sahai",4}};
  map<int, string> ar11 = {{2,"Govind"},{4,"Sahai"}};
  map<string, string> ar12 = {{"Govind","dnivoG"},{"Sahai","iahaS"}};
  cout<<"std::map<> : "<<endl;
  cout<<ar10<<endl;
#ifdef PRINT_ALL
  cout<<ar11<<endl;
  cout<<ar12<<endl;
#endif
  cout<<endl;

  // std::tuple<>
  tuple<int,int,int> ar13 = make_tuple(1,2,3);
  tuple<int,int,string,int> ar14 = make_tuple(20,21,"22",23);
  tuple<int,vector<int>,pair<string,float>,int> ar15;
  get<0>(ar15) = 10;
  get<1>(ar15).push_back(11);
  get<1>(ar15).push_back(12);
  get<1>(ar15).push_back(13);
  get<2>(ar15) = make_pair("Govind", 20.5);
  get<3>(ar15) = 100;
  cout<<"std::tuple<> :"<<endl;
  cout<<ar13<<endl;
#ifdef PRINT_ALL
  cout<<ar14<<endl;
  cout<<ar15<<endl;
#endif
  cout<<endl;


  
  return 0;
}
