//
// Created by makleyston on 02/05/23.
//

#include "service.h"

namespace ufcity {
    service::service(std::string _uuid_service) {
        this->uuid_service = _uuid_service;
    }

    std::string service::get_uuid_service() const {
        return this->uuid_service;
    }

    void service::set_data(std::vector<ufcity::service_data *> _data) {
        this->data = _data;
    }

    void service::add_service_data(ufcity::service_data *_data) {
        this->data.push_back(_data);
    }

    std::vector<ufcity::service_data *> service::get_service_data() {
        return this->data;
    }

    ufcity::service_data * service::get_data_by_tag(std::string _tag) {
        for(auto _service_data : this->data){
            if(_service_data->get_tag() == _tag)
                return _service_data;
        }
        return new ufcity::service_data("","");
    }
} // ufcity