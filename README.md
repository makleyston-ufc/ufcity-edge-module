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

# Sobre <a id="anchor_about"></a>
O Edge Module é um componente de _software_ que integra a solução para _smart city_ UFCity. 
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

# Contribuições <a id="anchor_contributions"></a>
Este módulo de _software_, bem como os demais elementos de _softwares_ presentes 
em todo o projeto da UFCity, é fruto de pesquisas realizadas no âmbido do curso de Ciências da 
Computação do programa de [Mestrado e Doutorado em Ciências da Computação (MDCC)](http://www.mdcc.ufc.br/) 
da [Universidade Federal do Ceará (UFC)](https://www.ufc.br/).

**Colaboradores**: <a id="anchor_colab"></a>

* [Danne Makleyston Gomes Pereira](http://lattes.cnpq.br/2002489019346835), UFC.
* [Angelo Roncalli Alencar Brayner](http://lattes.cnpq.br/3895469714548887), UFC.

# Especificações <a id="anchor_especifications"></a>
## Versão
O Edge Module encontra-se atualmente na versão `v0.1`.

## Requisitos mínimos <a id="anchor_minimum_riquerements"></a>
In developement.

## Performance e restrições <a id="anchor_restrictions"></a>
In developement.

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
  "device_uuid":"",
  "location":{
    "lat":"",
    "lng":""
  }
}
```
* "**device_uuid**": é a identificação única do dispositivo a qual o Edge Module está sendo consumido.
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
  "resource_uuid":"",
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
* "**resource_uuid**" é a identificação do recurso a ser registrado.
* "**services**": é uma lista de serviços disponíveis pelo recurso.
  * "**service_uuid**": contém a identificação de cada serviço.
  * "**data**": possui a identificação (via _tag_) de um determinado dado, bem como o valor que essa _tag_ possui. 
Para mais exemplos consulte o diretório ```samples```.

### Recuperando todos os recursos registrados <a id="anchor_get_resources"></a>
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
Os erros conhecidos pode ser visto nesta [lista](error/error_list.h).