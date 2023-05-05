//
// Created by makleyston on 04/05/23.
//

#ifndef UFCITY_EXAMPLE3_JSON_H
#define UFCITY_EXAMPLE3_JSON_H

#include <string>
#include <random>
#include <uv/unix.h>
#include "../../parser/lib/json.hpp"

namespace ex3 {

    std::vector<std::string> split(std::string _value);
    std::string uuid_generator();

    static std::unordered_map<std::string, std::string> _resources;
    static std::unordered_map<std::string, std::string> _services;

    std::string get_resource_json(std::string sensor_data) {
        auto _data = split(sensor_data);
        auto _sensor = _data.at(0);
        auto _value = _data.at(1);


        if (_resources[_sensor].empty())
            _resources[_sensor] = uuid_generator();

        if (_services[_sensor].empty())
            _services[_sensor] = uuid_generator();

        // Create JSON object and set values
        nlohmann::json j;
        j["uuid_resource"] = _resources[_sensor];
        j["services"] = nlohmann::json::array();
        auto &service = j["services"].emplace_back();
        service["uuid_service"] = _services[_sensor];
        service["data"] = nlohmann::json::array();
        auto &data = service["data"].emplace_back();
        data["tag"] = "measure";
        data["value"] = _value;
        return j.dump();
    }

    std::vector<std::string> split(std::string _value) {
        std::vector<std::string> output;
        size_t pos = 0, prev_pos = 0;
        while ((pos = _value.find(":", prev_pos)) != std::string::npos) {
            output.push_back(_value.substr(prev_pos, pos - prev_pos));
            prev_pos = pos + 1;
        }
        output.push_back(_value.substr(prev_pos));
        return output;
    }

    std::string uuid_generator() {
        static std::random_device dev;
        static std::mt19937 rng(dev());

        std::uniform_int_distribution<int> dist(0, 15);

        const char *v = "0123456789abcdef";
        const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

        std::string res;
        for (int i = 0; i < 16; i++) {
            if (dash[i]) res += "-";
            res += v[dist(rng)];
            res += v[dist(rng)];
        }
        return res;
    }

}
#endif //UFCITY_EXAMPLE3_JSON_H
