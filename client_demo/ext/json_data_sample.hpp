//
// Created by makleyston on 24/08/22.
//
#include <string>

namespace samples{

std::string json_device = R"JSON(
{
  "uuid_device":"111",
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