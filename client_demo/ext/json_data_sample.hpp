//
// Created by makleyston on 24/08/22.
//
#include <string>

namespace samples{

std::string json_device = R"JSON(
{
  "device_uuid":"111",
  "location":{
    "lat":"123",
    "lng":"321"
  }
}
)JSON";

std::string json_resource = R"JSON(
{
  "resource_uuid":"111",
  "services":[
    {
      "service_uuid":"123",
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

    std::string json_resource_data = R"JSON(
{
  "resource_uuid":"111",
  "services":[
    {
      "service_uuid":"123",
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
  "resource_uuid":"001.000",
  "services":[
    {
      "service_uuid":"001.001",
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

/* Thermometer sensor
 * service_uuid = gathering environment data
 * tag is only for debug */
    std::string json_thermometer_sensor = R"JSON(
{
  "resource_uuid":"002.000",
  "services":[
    {
      "service_uuid":"002.001",
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
  "resource_uuid":"003.000",
  "services":[
    {
      "service_uuid":"003.001",
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