#include "MUConfig_parser.hxx"

const struct loft_config_data loft_config_default={0,1,0,0,5,0.57,5,-1,0,0,200,200,5,1};



bool MUConfig_parser::compare_datamember_key(std::string &data_member, std::string &key){
    if((data_member)==key){
        return 1;
    }else{
        return 0;
    }
}

int MUConfig_parser::match_populate_config(std::vector<keyvaluePair<float>*> &list_number_params,std::vector<keyvaluePair<std::string>*> &list_string_params,MUTracker_config_data &m1,bool show_sstream_out){

    bool valid_match=0;
    //start populating the config structure...CXX does not have dynamic structures so one has to string match the key with a data member and assign the value
    //this is not fuzzy matching...the parameter is case sensitive and has to be defined as such in the config file...I might add fuzzy matching later
    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    std::cout<<"MUTracker Config:"<<std::endl;
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
    for(std::vector<keyvaluePair<std::string>*>::iterator it = list_string_params.begin();it!=list_string_params.end();++it){

        std::string comp;

        comp="inputpath_frames";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
                char* paramval;
                paramval = (char *)malloc(std::strlen((*it)->key.c_str())+1);
                std::strcpy(paramval, (*it)->key.c_str());
                m1.inputpath_frames = paramval;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="wildcard";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
                char* paramval;
                paramval = (char *)malloc(std::strlen((*it)->key.c_str())+1);
                std::strcpy(paramval, (*it)->key.c_str());
                m1.wildcard = paramval;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

    }

    for(std::vector<keyvaluePair<float>*>::iterator it = list_number_params.begin();it!=list_number_params.end();++it){

        std::string comp;

        comp="ULx1";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            m1.ULx1 = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="ULy1";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            m1.ULy1 = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="width1";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            m1.width1 = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="height1";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            m1.height1 = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

    }

    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
    return 0;
}

int MUConfig_parser::match_populate_config(std::vector<keyvaluePair<float>*> &list_number_params,std::vector<keyvaluePair<std::string>*> &list_string_params,loft_config_data &l1,bool show_sstream_out){

    bool valid_match=0;
    //start populating the config structure...CXX does not have dynamic structures so one has to string match the key with a data member and assign the value
    //this is not fuzzy matching...the parameter is case sensitive and has to be defined as such in the config file...I might add fuzzy matching later
    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    std::cout<<"LOFT Config:"<<std::endl;
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
    for(std::vector<keyvaluePair<float>*>::iterator it = list_number_params.begin();it!=list_number_params.end();++it){

        std::string comp;

        comp="IsCar";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.IsCar = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="F_wt";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.F_wt = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_count";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.update_count = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="debug";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.debug = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="angle_thres";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.angle_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_thres";
         valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.update_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="update_frame_thres";
         valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.update_frame_thres = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="angle";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.angle = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="diff";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.diff = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="update_conf";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.update_conf = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="scenex";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.scenex = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }

        comp="sceney";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.sceney = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="search_region_size_multiplier";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.search_region_size_multiplier = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }
        comp="uniform_search";
        valid_match=this->compare_datamember_key(comp,(*it)->key);
        if(valid_match){
            l1.uniform_search = (*it)->value;
            if(show_sstream_out){
                std::cout<<"Parameter "<<comp<<" was set as "<<(*it)->value<<std::endl;
            }
            continue;
        }


    }
    if(show_sstream_out){
    std::cout<<"---------------------------------------------------------"<<std::endl;
    }
    return 0;
}




