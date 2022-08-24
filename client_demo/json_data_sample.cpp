//
// Created by makleyston on 24/08/22.
//
#include <string>

namespace samples{

std::string json_spatial_data = R"JSON(
{
    device_uuid:"111",
    location:{
        latitude:"lat-123",
        longitude:"lng-123"
    }
}
)JSON";

std::string json_discovered_resource = R"JSON(
{
	device_uuid:"111",
	resource_uuid:"222",
	services_uuid:{
		"123", "321",
	}
}
)JSON";

}