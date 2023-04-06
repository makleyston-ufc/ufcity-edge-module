//
// Created by makleyston on 12/08/22.
//

#ifndef UFCITY_OBSERVER_H
#define UFCITY_OBSERVER_H

#include <string>

namespace ufcity {

    class observer {
    private:
        int id;

    public:

        void set_id_client(int id_client){
            this->id = id_client;
        }

        int get_id_client(){
            return this->id;
        }

        /**
         * Update the state of this observer
         */
        virtual void update(std::string topic, std::string message) = 0;


    };

} // ufcity

#endif //UFCITY_OBSERVER_H
