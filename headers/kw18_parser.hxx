#ifndef __KW18_PARSER_INCLUDED__
#define __KW18_PARSER_INCLUDED__ 1
#include<iostream>
#include<vector>
#include "RPcustomLOFTconfigparser.hxx"
#include<ctime>
#include<string>
#include<cstring>


extern std::vector<int> my_kw18_data_x;
extern std::vector<int> my_kw18_data_y;
extern std::vector<int> my_kw18_data_frno;
extern std::vector<int> my_kw18_data_oid;

extern "C" int kw18_parse(char*);

extern "C" void KW18_parser_help(void);
#endif
