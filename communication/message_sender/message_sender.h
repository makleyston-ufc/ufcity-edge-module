//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_MESSAGE_SENDER_H
#define UFCITY_MESSAGE_SENDER_H

#include <string>
#include "../../model/resource.h"
#include "../../model/device.h"

namespace ufcity {

    class message_sender{
    private:

    public:
        void running_thread_publish();
    };

} // ufcity

#endif //UFCITY_MESSAGE_SENDER_H
