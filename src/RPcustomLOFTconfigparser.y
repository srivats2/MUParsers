%{
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
//struct that i need for the key-value pair...I had two vectors instead and seems like key-value struct should be better
//boost "any" type would have been awesome here but it adds to a whole new dependency and thats why I need to have two different lists to store different templated types
//in general though, you would be able to use the keyvalue struct to do any generic thing and thats why I have templated it...is this the best way? I doubt it...
#include "keyvaluepair.hxx"
// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern int lineno;
extern FILE *yyin;

keyvaluePair<float> *param_list_numbers;
keyvaluePair<std::string> *param_list_strings;

std::vector<keyvaluePair<std::string>*> list_string_params;
std::vector<keyvaluePair<float>*> list_number_params;
std::string temp;
void yyerror(const char *s);
extern "C" int MUconfig_parse(char*);
extern "C" void MUconfig_parser_help(void);
extern "C" void MUconfig_parser_version(void);
%}





// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
        int ival;
        float fval;
        char *sval;
}

// define the constant-string tokens:
%token COMMENT
%token LOFT
%token START
%token END
%token ENDL
%token DOT
%token EQUAL
%token MY_SEMIC
// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> MY_INT
%token <fval> MY_FLOAT
%token <sval> MY_STRING
%token <sval> MY_FILEPATH
%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "loft config file":

LOFTConfig:
            comment_section LOFTheader body_section LOFTfooter comment_section
            | LOFTheader body_section LOFTfooter comment_section
            | comment_section LOFTheader body_section LOFTfooter
            | LOFTheader body_section LOFTfooter
;
LOFTheader:
START LOFT {std::cout<<"FOUND LOFT CONFIG START"<<std::endl;}
;
LOFTfooter:
END LOFT {std::cout<<"FOUND LOFT CONFIG END"<<std::endl;}
;
body_section:
        body_lines
        ;
body_lines:
        body_lines body_line
        | body_line
        ;
body_line:
    COMMENT {;}
    |string_section DOT_DETECT string_section EQUAL MY_FLOAT MY_SEMIC {param_list_numbers= new keyvaluePair<float>;
    param_list_numbers->key = temp;
    param_list_numbers->value=$5;
    list_number_params.push_back(param_list_numbers);
    }
    |string_section DOT_DETECT string_section EQUAL MY_FILEPATH {param_list_strings=new keyvaluePair<std::string>;
    param_list_strings->key = temp;
    std::string remove_annoying_characters = $5;
    char annoying[] = ";"; //remember to write a for loop if you need to remove multiple characters
    remove_annoying_characters.erase(std::remove(remove_annoying_characters.begin(), remove_annoying_characters.end(), annoying[0]), remove_annoying_characters.end());
    param_list_strings->value= remove_annoying_characters;
    list_string_params.push_back(param_list_strings);
    }
    ;

string_section:
        string_lines
        ;
string_lines:
      string_lines string_line
       |string_line
      ;
string_line:
    MY_STRING {char* param;
    param = (char *)malloc(std::strlen(temp.c_str())+1+std::strlen($1));
    std::strcpy(param, temp.c_str());
    std::strcat(param, $1); temp = param;}
    ;

comment_section:
     comment_lines
       ;

comment_lines:
    comment_lines comment_line
      |comment_line
       ;
comment_line:
    COMMENT
    ;

DOT_DETECT:
    DOT {temp.clear();} //ha! thats a trick to get rid of the structure name...should i be doing this? I dunno..but i could probably fix it later -- RP
    ;
%%
void MUconfig_parser_help(void){
std::cout<<"MU Config Parser is used to parse University of Missouri's tracker config files such as for LOFT & CSURF"<<std::endl;
std::cout<<"Please make sure that the config file has the correct format..Grammar for the file is somewhat strictly enforced"<<std::endl;
std::cout<<"COMMENTS: Any number of lines of comments can be added on top or below the actual config content"<<std::endl;
std::cout<<"COMMENTS (contd.) : Comments need to be prefixed with CXX standard '//' or a '#'..Multiline comments are not supported i.e. CXX '/* */'"<<std::endl;
std::cout<<"CONFIG Params: Config params are always enclosed within 'begin something_config' & 'end something_config'"<<std::endl;
std::cout<<"CONFIG Params (contd.) : This 'something' can be loft or csurf or MUTracker and is case sensitive"<<std::endl;
MUconfig_parser_version();
}

void MUconfig_parser_version(void){
std::cout<<"MUConfig Parser was built with the help of CMake (3.2.3) and GNU GCC (5.1.0)"<<std::endl;
std::cout<<"MUConfig Parser (v1.00.1) was written by Rengarajan Pelapur and built using GNU Flex (2.5.39) & GNU Bison (3.0.4) on ARCH LINUX 4.0.6-1-ARCH"<<std::endl;
}

int MUconfig_parse(char* filename) {
            //int main(int argc, char* argv[]){
                    // open a file handle to a particular file:
                    FILE *myfile = fopen(filename, "r");
                    // make sure it's valid:
                    if (!myfile) {
                            std::cout << "I can't open KW18 file!" << std::endl;
                            return -1;
                    }
                    // set flex to read from it instead of defaulting to STDIN:
                    yyin = myfile;

                    // parse through the input until there is no more:
                    do {
                            yyparse();
                    } while (!feof(yyin));
                    std::cout << "done with a config file (# of lines : "<<lineno<<" )" << std::endl;

}

void yyerror(const char *s) {
        std::cout << "LOFT config parse error! " << s << std::endl;
 }



