//
// Created by makleyston on 24/08/22.
//
#include <string>
#include <random>
#include "../../parser/lib/json.hpp"

namespace samples{

std::string json_device = R"JSON(
{
  "uuid_device":"",
  "location":{
    "lat":"123",
    "lng":"321",
    "alt":"0"
  }
}
)JSON";

std::string json_resource = R"JSON(
{
  "uuid_resource":"111",
  "services":[
    {
      "uuid_service":"123",
      "data":[
        {
          "tag":"data_tag_1",
          "value":""
        },
        {
          "tag":"data_tag_2",
          "value":""
        }
      ]
    }
  ]
}
)JSON";

//Se não tiver Location, como os exemplos neste documento, o Edge Module atribuirá o Location do Device.
    std::string json_resource_data = R"JSON(
{
  "uuid_resource":"111",
  "services":[
    {
      "uuid_service":"123",
      "data":[
        {
          "tag":"data_tag_1",
          "value":"333"
        },
        {
          "tag":"data_tag_2",
          "value":"444"
        }
      ]
    }
  ]
}
)JSON";

/* Examples */

/* Light pole
 * service_uuid = switch
 * tag is only for debug */
    std::string json_light_pole = R"JSON(
{
  "uuid_resource":"001.000",
  "services":[
    {
      "uuid_service":"001.001",
      "data":[
        {
          "tag":"light",
          "value":"on"
        }
      ]
    }
  ]
}
)JSON";

    std::string get_light_pole_json(){
        // Seed random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        // Create JSON object and set values
        nlohmann::json j;
        j["uuid_resource"] = "001.000";
        j["services"] = nlohmann::json::array();
        auto& service = j["services"].emplace_back();
        service["uuid_service"] = "001.001";
        service["data"] = nlohmann::json::array();
        auto& data = service["data"].emplace_back();
        data["tag"] = "light";
        data["value"] = (dis(gen) == 0 ? "off" : "on");
        return j.dump();
    }

    std::string get_thermometer_sensor_json(){
        // Seed random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(15, 35);

        // Create JSON object and set values
        nlohmann::json j;
        j["uuid_resource"] = "002.000";
        j["services"] = nlohmann::json::array();
        auto& service = j["services"].emplace_back();
        service["uuid_service"] = "002.001";
        service["data"] = nlohmann::json::array();
        auto& data = service["data"].emplace_back();
        data["tag"] = "measure";
        data["value"] = std::to_string(dis(gen));
        return j.dump();
    }

    std::string get_humidity_sensor_json(){
        // Seed random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(20, 60);

        // Create JSON object and set values
        nlohmann::json j;
        j["uuid_resource"] = "003.000";
        j["services"] = nlohmann::json::array();
        auto& service = j["services"].emplace_back();
        service["uuid_service"] = "003.001";
        service["data"] = nlohmann::json::array();
        auto& data = service["data"].emplace_back();
        data["tag"] = "measure";
        data["value"] = std::to_string(dis(gen));
        return j.dump();
    }

/* Thermometer sensor
 * service_uuid = gathering environment data
 * tag is only for debug */
    std::string json_thermometer_sensor = R"JSON(
{
  "uuid_resource":"002.000",
  "services":[
    {
      "uuid_service":"002.001",
      "data":[
        {
          "tag":"measure",
          "value":"28"
        }
      ]
    }
  ]
}
)JSON";

/* Humidity sensor
 * service_uuid = gathering environment data
 * tag is only for debug */
    std::string json_humidity_sensor = R"JSON(
{
  "uuid_resource":"003.000",
  "services":[
    {
      "uuid_service":"003.001",
      "data":[
        {
          "tag":"measure",
          "value":"78"
        }
      ]
    }
  ]
}
)JSON";


}