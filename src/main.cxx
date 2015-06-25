#include<iostream>
#include<vector>
#include "RPcustomLOFTconfigparser.hxx"
#include "keyvaluepair.hxx"
#include<ctime>
#include<string>

struct loft_config_data
{

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
};

std::vector<std::string> loft_config_param_names;



extern "C" int MUconfig_parse(char *);
extern "C" void MUconfig_parser_help();
extern std::vector<std::string> list_params;
extern std::vector<keyvaluePair<float>*> list_number_params;
extern std::vector<keyvaluePair<std::string>*> list_string_params;




bool compare_datamember_key(std::string &data_member, std::vector<keyvaluePair<float>*>::iterator &it){
    if((data_member)==(*it)->key){
        return 1;
    }else{
        return 0;
    }
}

int match_populate_config(std::vector<keyvaluePair<float>*> &list_number_params,std::vector<keyvaluePair<std::string>*> &list_string_params,loft_config_data &l1,bool show_sstream_out){

    bool valid_match;
    //start populating the config structure...CXX does not have dynamic structures so one has to string match the key with a data member and assign the value
    //this is not fuzzy matching...the parameter is case sensitive and has to be defined as such in the config file...I might add fuzzy matching later
    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
    for(std::vector<keyvaluePair<float>*>::iterator it = list_number_params.begin();it!=list_number_params.end();++it){

        std::string comp;

        comp="IsCar";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.IsCar = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="F_wt";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.F_wt = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_count";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.update_count = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="debug";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.debug = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="angle_thres";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.angle_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_thres";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.update_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_frame_thres";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.update_frame_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="angle";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.angle = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="diff";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.diff = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="update_conf";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.update_conf = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="scenex";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.scenex = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="sceney";
        valid_match=compare_datamember_key(comp,it);
        if(valid_match){
            l1.sceney = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }


    }
    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
}


int main(int argc, char *argv[]){
    loft_config_data *l1 = new loft_config_data;
    std::clock_t start;
    start = std::clock();
    if(argc>=2){

    MUconfig_parse(argv[1]);

    std::cout<<"Time : "<<(std::clock()-start)/(double) (CLOCKS_PER_SEC/1000)<< " ms"<<std::endl;

    for(std::vector<keyvaluePair<float>*>::iterator it = list_number_params.begin();it!=list_number_params.end();++it){
        std::cout<<(*it)->key<<"\t"<<(*it)->value<<std::endl;
    }

    for(std::vector<keyvaluePair<std::string>*>::iterator it = list_string_params.begin();it!=list_string_params.end();++it){
        std::cout<<(*it)->key<<"\t"<<(*it)->value<<std::endl;
    }

    match_populate_config(list_number_params,list_string_params,*l1,1);


    }else{
        MUconfig_parser_help();
    }

}

