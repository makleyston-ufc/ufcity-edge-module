//
// Created by makleyston on 24/08/22.
//
#include <string>

namespace samples{

std::string json_spatial_context_data = R"JSON(
{
  "device_uuid":"111",
  "location":{
    "lat":"123",
    "lng":"321"
  }
}
)JSON";

std::string json_resource2 = R"JSON(
{
  "resource_uuid":"222",
  "services_uuid":[
    "uuid_123",
    "uuid_321"
  ]
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

std::string json_resource_data2 = R"JSON(
{
   "resource_uuid":"111",
   "services":[
      {
         "service_uuid":"123",
         "data":{
            "data_tag_1":"999",
            "data_tag_2":"888"
         }
      }
   ]
}
)JSON";

//std::string json_remove_resource = R"JSON(
//{
//	device_uuid:"r_222"
//}
//)JSON";

}