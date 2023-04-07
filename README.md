# Sumário
* [Sobre](#anchor_about)
* [Contribuições](#anchor_contributions)
  * [Colaboradores](#anchor_colab)
* [Especificações técnicas](#anchor_especifications)
  * [Versão](#anchor_version)
  * [Requisitos mínimos](#anchor_minimum_requirements)
  * [Perfornamce e restrições](#anchor_restrictions)
* [Modo de usar](#anchor_usage)
  * [Incorporando o Edge Module](#anchor_include)
  * [Inicializando o Edge Module](#anchor_init)
  * [Registrando um recurso](#anchor_registering_resoruce)
  * [Consultando todos os recursos registrados](#anchor_get_resources)
  * [Removendo um recurso](#anchor_removing_resource)
  * [Enviando dados para a _Fog Computing_](#anchor_send_resource_data)
  * [Recebendo comandos para atuação](#anchor_receive_command_data)
  * [Lista de erros conhecidos](#anchor_error_list)
* [Abordagens e tecnologias utilizadas](#anchor_enable_tools)
  * [Semântica](#anchor_semantic)
  * [Limpeza de dados](#anchor_data_cleasing)
  * [Filtro e agrupamento de dados](#anchor_aggregation)
  * [Compressor de mensagens](#anchor_compression)
  * [Procolo de comunicação](#anchor_protocol)
  * [Políticas de segurança](#anchor_security)
* [Licenças](#anchor_licenses)

# About <a id="anchor_about"></a>
The Edge Module is a software component that integrates the UFCity smart city solution. This component operates at the edge of the computer network, offering local services that allow the city's resources to obtain, among other aspects, communication with the services of Fog Computing and Cloud Computing, abstracting the communication protocols and allowing the exchange of data both for the sending data from sensors present in intelligent environments and receiving commands to actuate actuators present in physical-cyber spaces.

The Edge Module performs various data processing and treatments to address data heterogeneity, dirty data, and volume issues. For more information, consult the work publications about the advances of this module on the project website.

# Contributions <a id="anchor_contributions"></a>
This software module, as well as the other software elements present throughout the UFCity project, is the result of research carried out within the framework of the Computer Science course of the [Master and Doctorate in Computer Science (MDCC)](http://www.mdcc.ufc.br/) of the [Federal University of Ceará (UFC)](https://www.ufc.br/).

**Collaborators**: <a id="anchor_colab"></a>

* [Danne Makleyston Gomes Pereira](http://lattes.cnpq.br/2002489019346835), UFC.
* [Angelo Roncalli Alencar Brayner](http://lattes.cnpq.br/3895469714548887), UFC.

# Especificações <a id="anchor_especifications"></a>
## Versão
O Edge Module encontra-se atualmente na versão `v0.1`.

## Requisitos mínimos <a id="anchor_minimum_riquerements"></a>
In development.

## Performance e restrições <a id="anchor_restrictions"></a>
In development.

# Modo de usar <a id="anchor_usage"></a>
## Incorporando o Edge Module <a id="anchor_include"></a>
```
#include "ufcity_interface.h"

using namespace ufcity_interface;
```

## Utilização  
### Inicializando o Edge Module <a id="anchor_init"></a>
```
init(std::string location_json);
```
Para inicializar o Edge Module é preciso fornecer o parâmetro `location_json`.
* `location_json` é um arquivo _json_ com a seguinte estrutura:<a id="anchor_location_json"></a>
```
{
  "uuid_device":"",
  "location":{
    "lat":"",
    "lng":""
  }
}
```
* "**uuid_device**": é a identificação única do dispositivo a qual o Edge Module está sendo consumido.
* "**device**": contém os dados de latitude (lat) e longitude (lng) do dispositivo. 

### Connectando à um nó na Fog Computing
Para realizar uma conexão com um nó da Fog Computing é necessário especificar uma `thread` para executar a função `connect_to_fog` fornecendo o endereço lógico do nó da Fog Computing.

**Atenção 1**: é importante dessasociar a `thread` da linha de execução do Edge Module. Para isso, utilize a função `detach`.

**Atenção 2**: garanta a destruição da `thread` caso o Edge Module seja finalizado. 
```
std::thread connect_thread(&connect_to_fog, "xxx.xxx.xxx.xxx");
connect_thread.detach();
```

### Registrando um recurso <a id="anchor_registering"></a>
```
register_resource(std::string resource_json);
```
Um recurso deve estar representado em formato _json_ com a seguinte estrutura:<a id="anchor_resource_json"></a> 
``` 
{
  "uuid_resource":"",
  "services":[
    {
      "service_uuid":"",
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
* "**uuid_resource**" é a identificação do recurso a ser registrado.
* "**services**": é uma lista de serviços disponíveis pelo recurso.
  * "**service_uuid**": contém a identificação de cada serviço.
  * "**data**": possui a identificação (via _tag_) de um determinado dado, bem como o valor que essa _tag_ possui. 
Para mais exemplos consulte o diretório ```samples```.

### Recuperando todos os recursos registrados <a id="anchor_get_resources"></a>
```
auto *map = get_resources_map();
for (auto const &pair: *map) {
    std::cout << "uuid_resource:" << pair.first << std::endl;
    std::cout << "resource semantic:" << pair.second << std::endl;
}
```
A função ```get_resources_map()``` retorna um ```std::unordered_map<std::string, std::string>``` onde o 
peimeiro parâmetro ```std::string``` refere-se ao uuid do recurso e o segundo parâmetro, 
também ```std::string```, refere-se ao modelo semântico do recurso.

### Removendo um recurso <a id="anchor_removing"></a>
```
remove_by_uuid(std::string resource_json);
```
[Este é o modelo JSON para ```resource_json```](#anchor_resource_json).
### Enviando dados de recursos para a _Fog Computing_ <a id="anchor_send_resource_data"></a>
```
send_resource_data(std::string resource_json);
```
[Este é o modelo JSON para ```resource_json```](#anchor_resource_json).

### Atualizando dados de localização <a id="anchor_update_location"></a>
```
update_location(std::string location_json);
```
[Este é o modelo JSON para o ```location_json```](#anchor_location_json). 

### Recebendo comandos da _Fog Computing_ para atuação <a id="anchor_receive_command_data"></a>
Para receber comandos de atuação da _Fog Computing_ é necessário implementar 
um ```observer``` que será notificado sempre que comandos forem recebidos pelo
Edge Module.

A aplicação cliente deve implementar o ```observer``` da seguinte forma:
```
class observer_client : public ufcity::observer{
public:
    void update(std::string msg) override;
};

void observer_client::update(std::string command) {
    std::cout << "Message: " + command << std::endl;
}
```
Uma vez implementado o ```observer_client``` o mesmo deve ser registrado para 
ser notificado sempre que comandos forem recebidos. O registro deve ser realizado 
da seguinte forma:
```
auto * _observer = new observer_client();
register_observer(_observer);
```
Para remover um ```observer_client``` utiliza-se a seguinte função:
```
remove_observer(_observer);
```

### Lista de erros <a id="anchor_error_list"></a>
Cada uma dessas funções podem retornar alguns erros conhecidos. 
Os erros conhecidos podem ser visto nesta [lista](error/error_list.h).