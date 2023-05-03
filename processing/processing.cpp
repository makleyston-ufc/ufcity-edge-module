//
// Created by makleyston on 26/08/22.
//

#include "processing.h"
namespace proc {

    double convert_to_double(std::string _value){
        try {
            double value = std::stod(_value);
            return value;
            std::cout << "Conversion successful. Value is: " << value << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Conversion failed. Error message: " << e.what() << std::endl;
        }
        return -1;
    }

    bool can_convert_to_double(const std::string& str) {
        try {
            std::size_t pos;
            double result = std::stod(str, &pos);

            // Check if the entire string was converted
            if (pos == str.size()) {
                return true;
            }
        } catch (const std::invalid_argument& e) {
            // The conversion failed due to an invalid argument
        } catch (const std::out_of_range& e) {
            // The conversion failed due to the value being out of range
        }

        return false;
    }


    /* ### Hoje o código está implementado considerando que os serviços de sensoriamento são lidos sempre igualmente. É necssário fazer alterações no código
     * para permitir o missing data e a remove outliers por serviço, pois um recurso pode ter vários serviços e esses serviços pdoem oferecer sensoriamentos
     * em tempos distintos. Logo, uma amostragem de um resource pode ter um determinado serviço, enquanto que outra amostragem pode não ter e isso não necessariamente
     * é um missing data, mas sim à possibilidade do recurso ainda não ter realizado a leitura.
     * ### Um outro ponto que deve conter em futuras atualizações é a consideração de vários dados para um mesmo serviço, e.g., location que possui lat, long e alt. Ćomo
     * está codificado hoje é como se cada serviço possui no máximo um dado. */

    std::vector<ufcity::resource *> handler(std::vector<std::vector<ufcity::resource *>>& _data) {

        std::vector<ufcity::resource *> _result;

        for(auto each_resource_list : _data){
            auto * _resource_model = each_resource_list.front();
            auto * _new_resource = new ufcity::resource(_resource_model->get_uuid_resource());
            _new_resource->set_location(_resource_model->get_location());

            for(auto _service_model : _resource_model->get_services()){
                auto * _new_service = new ufcity::service(_service_model->get_uuid_service());

                for(auto _service_data_model : _service_model->get_data()){
                    if(can_convert_to_double(_service_data_model->get_value())) {
                        std::vector<double> _value;
                        for (auto _resource: each_resource_list) {
                            auto _v = _resource->get_service_by_uuid(
                                    _service_model->get_uuid_service()).get_data_by_tag(
                                    _service_data_model->get_tag())->get_value();
                            double _v_double = convert_to_double(_v);
                            _value.push_back(_v_double);
                        }
                        //missing data
                        //TODO
                        //remove outliers
                        //TODO
                    }else{

                    }



//                    ufcity::service_data * _new_service_data;
//                    auto _service_data = _service_model->get_data_by_tag(_service_data_model->get_tag());
//                    if(can_convert_to_double(_service_data->get_value())){
//                        double _double = convert_to_double(_service_data->get_value());
//                        _value.push_back(_double);
//                    }else{
//
//                    }
                }
            }


            //Missing data


            //Remove outliers

//            _result.push_back(_resource);
        }

        return _result;

    }



}// proc