#include "MUConfig_parser.hxx"

int main(int argc, char *argv[]){
    loft_config_data *l1 = new loft_config_data;
    MUTracker_config_data *m1 = new MUTracker_config_data;
    MUConfig_parser *config_parser = new MUConfig_parser;
    std::clock_t start;
    start = std::clock();
    if(argc>=2){

    MUconfig_parse(argv[1]);

    std::cout<<"Time : "<<(std::clock()-start)/(double) (CLOCKS_PER_SEC/1000)<< " ms"<<std::endl;

    config_parser->match_populate_config(loft_list_number_params,loft_list_string_params,*l1,1);
    config_parser->match_populate_config(MUTracker_list_number_params,MUTracker_list_string_params,*m1,1);


    }else{
        MUconfig_parser_help();
    }

}
