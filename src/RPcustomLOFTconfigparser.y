%define api.prefix{MUConfig}
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
/*************************************************************/
//for the loft section
keyvaluePair<float> *loft_param_list_numbers;
keyvaluePair<std::string> *loft_param_list_strings;

std::vector<keyvaluePair<std::string>*> loft_list_string_params;
std::vector<keyvaluePair<float>*> loft_list_number_params;

std::string loft_temp_string;
/*************************************************************/

/*************************************************************/
//for the MUTracker section
keyvaluePair<float> *MUTracker_param_list_numbers;
keyvaluePair<std::string> *MUTracker_param_list_strings;

std::vector<keyvaluePair<std::string>*> MUTracker_list_string_params;
std::vector<keyvaluePair<float>*> MUTracker_list_number_params;

std::string MUTracker_temp_string;
/*************************************************************/
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
%token MUTracker
// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> MY_INT
%token <fval> MY_FLOAT
%token <sval> MY_STRING
%token <sval> MY_FILEPATH
//we can expect one shift reduce warning because of MUConfig_lines...the section of
//grammar that contains MUTrackerConfig or LOFTConfig or both or with comments
//has been denoted with non-terminal symbols...this is perfectly fine and can be
//ignored without consequence
//this is mainly to provide total flexibility to the user while writting a config file
//MUTracker section maybe at the beginning or at the end and any combinations in between
//One can also entirely skip either section which is something i will need to think about
%expect 1

%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "config file":


MUConfig_lines:
               MUConfig_lines MUConfig_line
               | MUConfig_line
;

MUConfig_line:
        comment_section
        | MUTrackerConfig
        | LOFTConfig

;

MUTrackerConfig:
                MUTrackerheader MUTracker_body_section MUTrackerfooter

;

MUTracker_body_section:
        MUTracker_body_lines
        ;
MUTracker_body_lines:
        MUTracker_body_lines MUTracker_body_line
        | MUTracker_body_line
        ;
MUTracker_body_line:
    COMMENT {;}
    |string_section DOT_DETECT string_section EQUAL MY_FLOAT MY_SEMIC {MUTracker_param_list_numbers= new keyvaluePair<float>;
    MUTracker_param_list_numbers->key = MUTracker_temp_string;
    MUTracker_param_list_numbers->value=$5;
    MUTracker_list_number_params.push_back(MUTracker_param_list_numbers);
    }
    |string_section DOT_DETECT string_section EQUAL MY_FILEPATH {MUTracker_param_list_strings=new keyvaluePair<std::string>;
    MUTracker_param_list_strings->key = MUTracker_temp_string;
    std::string remove_annoying_characters_MUTracker = $5;
    char annoying[] = ";"; //remember to write a for loop if you need to remove multiple characters
    remove_annoying_characters_MUTracker.erase(std::remove(remove_annoying_characters_MUTracker.begin(), remove_annoying_characters_MUTracker.end(), annoying[0]), remove_annoying_characters_MUTracker.end());
    MUTracker_param_list_strings->value= remove_annoying_characters_MUTracker;
    MUTracker_list_string_params.push_back(MUTracker_param_list_strings);
    }
    |string_section DOT_DETECT string_section EQUAL MY_STRING MY_SEMIC {MUTracker_param_list_strings=new keyvaluePair<std::string>;
    MUTracker_param_list_strings->key = MUTracker_temp_string;
    MUTracker_param_list_strings->value = $5;
    MUTracker_list_string_params.push_back(MUTracker_param_list_strings);
    }

    ;


MUTrackerheader:
START MUTracker {std::cout<<"FOUND MUTracker START"<<std::endl;}
;
MUTrackerfooter:
END MUTracker {std::cout<<"FOUND MUTracker END"<<std::endl;}
;

LOFTConfig:
            LOFTheader loft_body_section LOFTfooter
;
LOFTheader:
START LOFT {;}
;
LOFTfooter:
END LOFT {;}
;
loft_body_section:
        loft_body_lines
        ;
loft_body_lines:
        loft_body_lines loft_body_line
        | loft_body_line
        ;
loft_body_line:
    COMMENT {;}
    |string_section DOT_DETECT string_section EQUAL MY_FLOAT MY_SEMIC {loft_param_list_numbers= new keyvaluePair<float>;
    loft_param_list_numbers->key = loft_temp_string;
    loft_param_list_numbers->value=$5;
    loft_list_number_params.push_back(loft_param_list_numbers);
    }
    |string_section DOT_DETECT string_section EQUAL MY_FILEPATH {loft_param_list_strings=new keyvaluePair<std::string>;
    loft_param_list_strings->key = loft_temp_string;
    std::string remove_annoying_characters_loft = $5;
    char annoying[] = ";"; //remember to write a for loop if you need to remove multiple characters
    remove_annoying_characters_loft.erase(std::remove(remove_annoying_characters_loft.begin(), remove_annoying_characters_loft.end(), annoying[0]), remove_annoying_characters_loft.end());
    loft_param_list_strings->value= remove_annoying_characters_loft;
    loft_list_string_params.push_back(loft_param_list_strings);
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
    param = (char *)malloc(std::strlen(loft_temp_string.c_str())+1+std::strlen($1));
    std::strcpy(param, loft_temp_string.c_str());
    std::strcat(param, $1); loft_temp_string = param; MUTracker_temp_string=param;}
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
    DOT {loft_temp_string.clear(); MUTracker_temp_string.clear();} //ha! thats a trick to get rid of the structure name...should i be doing this? I dunno..but i could probably fix it later -- RP
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
std::cout<<"MUConfig Parser (v1.00.1) was written by Rengarajan Pelapur and built using GNU Flex (2.5.39) & GNU Bison (3.0.4) on ARCH LINUX 4.0.7-2-ARCH"<<std::endl;
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
        std::cout << "Config parse error! " << s << std::endl;
        std::cout<< "Line #"<<lineno<<" in the cfg file does not match any known grammar"<<std::endl;
        exit(-1);
 }


