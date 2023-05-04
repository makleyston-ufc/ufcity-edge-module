//
// Created by makleyston on 29/04/23.
//

#include "buffer.h"
#include "../../orchestrator/orchestrator.h"
#include "../../model/config/methods.h"
#include "../../processing/missing_data.h"

namespace ufcity_db {
    buffer::buffer() = default;
    buffer* buffer::instance = nullptr;

    buffer *buffer::get_instance() {
        if (instance == nullptr){
            instance = new buffer();
        }
        return instance;
    }

    int buffer::get_index_by_uuid_resource(std::string uuid_resource){
        for(int i = 0; i < this->selected_resources.size(); i++){
            auto resource_list = this->selected_resources.at(i);
            if((resource_list.front()) != nullptr && (resource_list.front()->get_uuid_resource() == uuid_resource))
                return i;
        }
        return -1; //O recurso não existe na lista
    }

    void buffer::add_resource(ufcity::resource * _resource) {
        auto config = ufcity::orchestrator::get_instance()->get_config();
        int index = get_index_by_uuid_resource(_resource->get_uuid_resource());
        if(index != -1)
            this->selected_resources.at(index).push_back(_resource);
        else{
            std::vector<ufcity::resource *> resource_list = {};
            resource_list.push_back(_resource);
            this->selected_resources.push_back(resource_list);
            this->times.push_back(std::chrono::system_clock::now()); /* register the time of sign */
        }
    }

    long buffer::number_items_in_buffer(std::string uuid_resource) {
        int index = get_index_by_uuid_resource(uuid_resource);
        if(index != -1)
            return this->selected_resources.at(index).size();
        return -1;
    }

    std::vector<std::vector<ufcity::resource *>> buffer::get_resource_buffer() {
        auto config = ufcity::orchestrator::get_instance()->get_config();
        const auto _size = config->get_data_grouping_config()->get_size();
        const auto _time = config->get_data_grouping_config()->get_time();

        switch (config->get_data_grouping_config()->get_method_char()){
            case methods::AT_LEAST_TIME_GROUPING:
                return at_least_time_function(_time);
            case methods::AT_LEAST_TIME_AND_SIZE_GROUPING:
                return al_least_time_and_size_function(_time, _size);
            case methods::FIXED_SIZE_GROUPING:
                return fixed_size_function(_size);
            case methods::HAPPENS_FIRST_GROUPING:
                return happens_first_function(_time, _size);
        }

        std::vector<std::vector<ufcity::resource *>> result;
        return result;
    }

    std::vector<std::vector<ufcity::resource *>> buffer::fixed_size_function(long size) {
//        std::cout << "@@ " << size << std::endl;
        std::vector<std::vector<ufcity::resource *>> result;
        auto it = this->selected_resources.begin();
        auto it_times = this->times.begin();
        while (it != this->selected_resources.end()) {
            auto resource_list = *it;
            if (resource_list.size() >= size) {
                std::cout << "SIZE: " << size << ". Result.size: " << result.size() <<". Selected.size: " << this->selected_resources.size() << std::endl;
                result.push_back(resource_list);
                it = this->selected_resources.erase(it);
                std::cout << "SIZE: " << size << ". Result.size: " << result.size() <<". Selected.size: " << this->selected_resources.size() << std::endl;
                it_times = this->times.erase(it_times); /* erase the vector of times used in 'at least time' */
            } else {
                ++it;
                ++it_times;
            }
        }
        return result;
    }

    std::vector<std::vector<ufcity::resource *>> buffer::at_least_time_function(long time) {
        std::vector<std::vector<ufcity::resource *>> result;
        auto it = this->selected_resources.begin();
        auto it_times = this->times.begin();
        while (it_times != this->times.end()) {
            auto _t = *it_times;
            if ((_t + std::chrono::seconds(time)) <= std::chrono::system_clock::now()) {
                auto resource_list = *it;
                result.push_back(resource_list);
                it = this->selected_resources.erase(it);
                it_times = this->times.erase(it_times); /* erase the vector of times used in 'at least time' */
            } else {
                ++it;
                ++it_times;
            }
        }
        return result;
    }

    std::vector<std::vector<ufcity::resource *>> buffer::al_least_time_and_size_function(long time, long size) {
        std::vector<std::vector<ufcity::resource *>> result;
        auto it = this->selected_resources.begin();
        auto it_times = this->times.begin();
        while (it != this->selected_resources.end()) {
            auto resource_list = *it;
            auto _t = *it_times;
            if ((resource_list.size() >= size) && ((_t + std::chrono::seconds(time)) <= std::chrono::system_clock::now())) {
                result.push_back(resource_list);
                it = this->selected_resources.erase(it);
                it_times = this->times.erase(it_times); /* erase the vector of times used in 'at least time' */
            } else {
                ++it;
                ++it_times;
            }
        }
        return result;
    }

    std::vector<std::vector<ufcity::resource *>> buffer::happens_first_function(long time, long size) {
        auto _s = fixed_size_function(size);
        auto _t = at_least_time_function(time);
        _s.insert(_s.end(), _t.begin(), _t.end());
        return _s;
    }
} // ufcity_db