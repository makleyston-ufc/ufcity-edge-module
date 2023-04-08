# Abstract
* [About](#anchor_about)
* [Contributions](#anchor_contributions)
  * [Collaborators](#anchor_colab)
* [Software specs](#anchor_especifications)
  * [Version](#anchor_version)
  * [Minimum requirements](#anchor_minimum_requirements)
  * [Performance and restrictions](#anchor_restrictions)
* [How to use](#anchor_usage)
  * [Embedding the Edge Module in an application](#anchor_include)
  * [Initializing the Edge Module](#anchor_init)
  * [Connecting to Fog Computing](#anchor_connecting_to_fog_computing)
  * [Registering a resource](#anchor_registering_resoruce)
  * [Retrieving all registered resources](#anchor_get_resources)
  * [Removing a resource](#anchor_removing_resource)
  * [Sending resource data to Fog Computing](#anchor_send_resource_data)
  * [Updating location data](#anchor_location_data)
  * [Receiving data from Fog Computing](#anchor_receive_command_data)
  * [Finishing the Edge Module](#anchor_finishing_edge_module)
  * [Errors list](#anchor_error_list)

[//]: # (* [Abordagens e tecnologias utilizadas]&#40;#anchor_enable_tools&#41;)

[//]: # (  * [Semântica]&#40;#anchor_semantic&#41;)

[//]: # (  * [Limpeza de dados]&#40;#anchor_data_cleasing&#41;)

[//]: # (  * [Filtro e agrupamento de dados]&#40;#anchor_aggregation&#41;)

[//]: # (  * [Compressor de mensagens]&#40;#anchor_compression&#41;)

[//]: # (  * [Procolo de comunicação]&#40;#anchor_protocol&#41;)

[//]: # (  * [Políticas de segurança]&#40;#anchor_security&#41;)

[//]: # (* [Licenças]&#40;#anchor_licenses&#41;)

# About <a id="anchor_about"></a>
The Edge Module is a software component that integrates the UFCity smart city solution. This component operates at the edge of the computer network, offering local services that allow the city's resources to obtain, among other aspects, communication with the services of Fog Computing and Cloud Computing, abstracting the communication protocols and allowing the exchange of data both for the sending data from sensors present in intelligent environments and receiving commands to actuate actuators present in physical-cyber spaces.

The Edge Module performs various data processing and treatments to address data heterogeneity, dirty data, and volume issues. For more information, consult the work publications about the advances of this module on the project website.

# Contributions <a id="anchor_contributions"></a>
This software module, as well as the other software elements present throughout the UFCity project, is the result of research carried out within the framework of the Computer Science course of the [Master and Doctorate in Computer Science (MDCC)](http://www.mdcc.ufc.br/) of the [Federal University of Ceará (UFC)](https://www.ufc.br/).

**Collaborators**: <a id="anchor_colab"></a>

* [Danne Makleyston Gomes Pereira](http://lattes.cnpq.br/2002489019346835), UFC.
* [Angelo Roncalli Alencar Brayner](http://lattes.cnpq.br/3895469714548887), UFC.

# Software specs <a id="anchor_especifications"></a>
## Version
Current version: `v0.1`.

## Minimum requirements <a id="anchor_minimum_riquerements"></a>
In development.

## Performance and restrictions <a id="anchor_restrictions"></a>
In development.

# How to use <a id="anchor_usage"></a>
## Embedding the Edge Module in an application <a id="anchor_include"></a>
```
#include "ufcity_interface.h"

using namespace ufcity_interface;
```

## Using the module  
### Initializing the Edge Module <a id="anchor_init"></a>
```
init(std::string location_json);
```
* `location_json` is a JSON with the following structure::<a id="anchor_location_json"></a>
```
{
  "uuid_device":"",
  "location":{
    "lat":"",
    "lng":"",
    "alt":""
  }
}
```
* "**uuid_device**": is the unique ID of the device from which the Edge Module is consumed.
* "**location**": contains the latitude (lat), longitude (lng), and altitude (alt) data of the device. 

### Connecting to Fog Computing <a id="anchor_connecting_to_fog_computing"></a>

```
connect_to_fog(HOST, PORT);
```
* HOST is the IP address of the Fog Computing node, and PORT is the communication port used to connect to the node via MQTT.

### Registering a resource <a id="anchor_registering"></a>
```
register_resource(std::string resource_json);
```
Example of `resource_json`:<a id="anchor_resource_json"></a> 
``` 
{
  "uuid_resource":"",
  "services":[
    {
      "uuid_service":"",
      "data":[
        {
          "tag":"",
          "value":""
        },
        ...
      ]
    },
    ...
  ]
}
```
* "**uuid_resource**" is the ID of the resource to be registered.
* "**services**": is a list of services available by the resource.
  * "**uuid_service**": is the ID of a resource service.
  * "**data**": is the data to be sent. Each piece of data has a tag and a value. For more examples, see the ```samples``` directory.

### Retrieving all registered resources <a id="anchor_get_resources"></a>
```
auto * map = get_resources_map();
    for (auto const &pair: *map) 
        std::cout << "{" << pair.first << ": " << pair.second->get_uuid_resource() << "}" std::endl;
```
Function ```get_resources_map()``` return a ```std::unordered_map<std::string, const ufcity::resource *>```.
* Key: uuid_resource.
* Value: pointer to the resource (resource *).

### Removing a resource <a id="anchor_removing"></a>
```
remove_resource(std::string resource_json);
```
[Click here to view the JSON structure for a resource](#anchor_resource_json).

or
```
remove_resource_by_uuid(std::string uuid_resource);
```
* **uuid_resource**: is the ID of the resource to be removed.
### Sending resource data to Fog Computing <a id="anchor_send_resource_data"></a>
```
send_resource_data(std::string resource_json);
```
[Click here to view the JSON structure for a resource](#anchor_resource_json).

### Updating location data <a id="anchor_location_data"></a>
```
update_location(std::string location_json);
```
[Click here to view the JSON structure for a device](#anchor_init).

### Receiving data from Fog Computing <a id="anchor_receive_command_data"></a>
Implement an observer from ufcity's "observer" class. See the example.

```
class observer_client : public ufcity::observer{
public:
    void update(std::string topic, std::string message) override;
};

void observer_client::update(std::string topic, std::string message) {
    std::cout << "Message: " + message << std::endl;
}
```
After implementing the observer, then register it in the Edge Module.
```
auto * _observer = new observer_client();
register_observer(_observer);
```
To remove an ```observer_client``` use the following function:
```
remove_observer(ufcity::observer *);
```
or
```
remove_observer(int id_observer);
```
### Finishing the Edge Module <a id="anchor_finishing_edge_module"></a>
```
finish();
```
### Errors list <a id="anchor_error_list"></a>
[Click here to access the errors list](error/error_list.h).