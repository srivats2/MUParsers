#include "MUConfig_parser.hxx"
#include "kw18_parser.hxx"



int extension_check(std::string &filename){

std::string::size_type idx;
idx = filename.rfind('.');

if(idx != std::string::npos)
{
    std::string extension = filename.substr(idx+1);

    if (extension=="kw18"){
    std::cout<<"File appears to have a KW18 extension...trying the KW18 reader"<<std::endl;
    return 0;
    }else if(extension=="cfg"){
        std::cout<<"File appears to have a config file extension..trying the MUConfig file reader"<<std::endl;
        return 1;
    }else{
        std::cerr<<"(ERROR) Extension not recognized...MUParsers can only read cfg or KW18 file formats..make sure the extension and format match"<<std::endl;
        return -1;
    }

}
else
{
 return -1;
}

}

int main(int argc, char *argv[]){
    loft_config_data *l1 = new loft_config_data;
    MUTracker_config_data *m1 = new MUTracker_config_data;
    MUConfig_parser *config_parser = new MUConfig_parser;
    std::clock_t start;
    if(argc>=2){
    //extension check
    std::string filename = argv[1];

    int check_case = extension_check(filename);
    start = std::clock();

switch(check_case){

case 1:{
        try{
            MUconfig_parse(argv[1]);

            std::cout<<"Time : "<<(std::clock()-start)/(double) (CLOCKS_PER_SEC/1000)<< " ms"<<std::endl;

            config_parser->match_populate_config(loft_list_number_params,loft_list_string_params,*l1,1);
            config_parser->match_populate_config(MUTracker_list_number_params,MUTracker_list_string_params,*m1,1);
            }catch(std::exception e){
            std::cout<<e.what()<<std::endl;
            }
    break;

}
case 0:{
        try{
        kw18_parse(argv[1]);
        std::cout<<"Time : "<<(std::clock()-start)/(double) (CLOCKS_PER_SEC/1000)<< " ms"<<std::endl;

    }catch(std::exception e){
        std::cout<<e.what()<<std::endl;
    }
  break;
}

default:{
    MUconfig_parser_help();
    KW18_parser_help();

}

}

    }else{
        MUconfig_parser_help();
        KW18_parser_help();
    }

}
/*
#include<iostream>
#include<vector>
#include"RPcustomKW18parser.hxx"
#include<ctime>

extern "C" int kw18_parse(char *);


int main(int argc, char *argv[]){
    std::clock_t start;
    start = std::clock();

    kw18_parse(argv[1]);

    std::cout<<"Time : "<<(std::clock()-start)/(double) (CLOCKS_PER_SEC/1000)<< " ms"<<std::endl;

}

*/
