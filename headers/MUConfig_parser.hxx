#ifndef LOFT_CONFIG_PARSER_HXX
#define LOFT_CONFIG_PARSER_HXX

#include<iostream>
#include<vector>
#include "RPcustomLOFTconfigparser.hxx"
#include "keyvaluepair.hxx"
#include<ctime>
#include<cstring>

struct loft_config_data{

    double F_wt;
    double IsCar;
    double update_count;
    double debug;
    double angle_thres;
    double update_thres;
    double update_frame_thres;
    double angle;
    double diff;
    double update_conf;
    double scenex, sceney;
    int search_region_size_multiplier;
    int uniform_search;
};

struct MUTracker_config_data{
    char *inputpath_frames;
    char *wildcard;
    int ULx1,ULy1,width1,height1;
};



class MUConfig_parser{
//one can define a new match and populate config for csurf for instance and simply overload the function as shown
public:
    bool compare_datamember_key(std::string &, std::string &);
    int match_populate_config(std::vector<keyvaluePair<float>*> &,std::vector<keyvaluePair<std::string>*> &,MUTracker_config_data &,bool);
    int match_populate_config(std::vector<keyvaluePair<float>*> &,std::vector<keyvaluePair<std::string>*> &,loft_config_data &,bool);

};




extern "C" int MUconfig_parse(char *);
extern "C" void MUconfig_parser_help();

extern std::vector<keyvaluePair<float>*> loft_list_number_params;
extern std::vector<keyvaluePair<std::string>*> loft_list_string_params;

extern std::vector<keyvaluePair<float>*> MUTracker_list_number_params;
extern std::vector<keyvaluePair<std::string>*> MUTracker_list_string_params;


#endif // LOFT_CONFIG_PARSER_HXX

