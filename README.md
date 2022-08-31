# Sobre
O Edge Module é um componente que compõe a solução para _smart city_ UFCity. 
Este componente atua na borda da rede de computadores oferecendo serviços locais 
que possibilitam aos recursos da cidade obterem, dentre outros aspectos, uma 
comunicação com os serviços da _Fog Computing_ e _Cloud Computing_, abstraindo 
os protocolos de comunicação e permitindo a troca de dados tanto para o envio de dados 
dos sensores presentes nos ambientes inteligentes quanto para o recebimento de 
comandos para atuação dos atuadores presentes em espaços cyber físicos. 

O Edge Module realiza divesos processamentos e tratamentos de dados para resolver 
questões de heterogeneidade dos dados, dados sujos e volume dos dados. Para mais 
informações, consulte as publicações de trabalhos acerca dos avanços deste módulo no 
_website_ do projeto.

# Contribuições
Este módulo de _software_, bem como os demais elementos de _softwares_ presentes 
em todo o projeto da UFCity, é fruto de pesquisas realizadas no âmbido do curso de Ciências da 
Computação do programa de [Mestrado e Doutorado em Ciências da Computação (MDCC)](http://www.mdcc.ufc.br/) 
da [Universidade Federal do Ceará (UFC)](https://www.ufc.br/).

**Colaboradores**: 

Doutorandos: 
* [Danne Makleyston Gomes Pereira](http://lattes.cnpq.br/2002489019346835)

Orientador:
* [Angelo Roncalli Alencar Brayner](http://lattes.cnpq.br/3895469714548887)

# Modo de usar
## Incorporando o Edge Module
```
#include "ufcity_interface.h"

using namespace ufcity_interface;
```

## Utilização 
### Inicializando o Edge Module
```
init(std::string location_json, std::string fog_node_address);
```
Para inicializar o Edge Module é preciso fornecer dois parâmetros: "location_json" e "fog_node_address".
* "fog_node_address": deve ser o endereço lógico do nó da "fog_node_address".
* "location_json": deve ser representado por um json estruturado da seguinte maneira:<a id="anchor_location_json"></a>
```
{
  "device_uuid":"",
  "location":{
    "lat":"",
    "lng":""
  }
}
```
* "**device_uuid**": é a identificação única do dispositivo a qual o Edge Module está sendo consumido.
* "**location**": contém os dados de latitude (lat) e longitude (lng) do dispositivo. 

### Registrando um recurso
```
register_resource(std::string resource_json);
```
O registro de um recurso deve ser realizado mediante json cuja estrutura respeite o
seguinte modelo para um _resource_:<a id="anchor_resource_json"></a> 
``` 
{
  "resource_uuid":"",
  "services":[
    {
      "service_uuid":"",
      "data":[
        {
          "tag":"",
          "value":""
        }
      ]
    }
  ]
}
```
* "resource_uuid" é a identificação do recurso a ser registrado.
* "services": é uma lista de serviços disponíveis pelo recurso.
  * "service_uuid": contém a identificação de cada serviço.
  * "data": possui a identificação (via _tag_) de um determinado dado, bem como o valor que essa _tag_ possui. 
Para mais exemplos consulte o diretório ```samples```.

### Recuperando todos os recursos registrados
```
auto *map = get_resources_map();
for (auto const &pair: *map) {
    std::cout << "resource_uuid:" << pair.first << std::endl;
    std::cout << "resource semantic:" << pair.second << std::endl;
}
```
A função ```get_resources_map()``` retorna um ```std::unordered_map<std::string, std::string>``` onde o 
peimeiro parâmetro ```std::string``` refere-se ao uuid do recurso e o segundo parâmetro, 
também ```std::string```, refere-se ao modelo semântico do recurso.

### Removendo um recurso
```
remove_resource(std::string resource_json);
```
[Este é o modelo JSON para ```resource```](#anchor_resource_json).
### Enviando dados de recursos para a _Fog Computing_
```
send_resource_data(std::string resource_json);
```
[Este é o modelo JSON para ```resource```](#anchor_resource_json).

### Atualizando dados de localização
```
update_location(samples::json_spatial_context_data);
```
[Este é o modelo JSON para o ```location```](#anchor_location_json).

### Recebendo comandos da _Fog Computing_ para atuação
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

### Lista de erros
Cada uma dessas funções podem retornar alguns erros conhecidos. 
Os erros conhecidos pode ser visto nesta [lista](error/error_list.h).