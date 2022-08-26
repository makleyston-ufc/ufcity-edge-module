//
// Created by makleyston on 24/08/22.
//
#include <string>

namespace samples{

std::string json_spatial_context_data = R"JSON(
{
    device_uuid:"111",
    location:{
        lat:"lat-123",
        lng:"lng-123"
    }
}
)JSON";

std::string json_resource = R"JSON(
{
	device_uuid:"111",
	resource_uuid:"222",
	services_uuid:{
		"123", "321",
	}
}
)JSON";

std::string json_resource_data = R"JSON(
{
	resource_uuid:"111",
	message_delivery_qos:"0",
	services:{
		{
			service_uuid:"123",
			data:{
				data_tag_1:"999",
				data_tag_2:"888",
			}
		}
	}
}
)JSON";

//std::string json_remove_resource = R"JSON(
//{
//	device_uuid:"r_222"
//}
//)JSON";

}