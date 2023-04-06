//
// Created by makleyston on 29/08/22.
//

#ifndef UFCITY_MESSAGE_RECEIVER_H
#define UFCITY_MESSAGE_RECEIVER_H

#include <vector>
#include <algorithm>
#include <mutex>
#include "../../error/error_list.h"

namespace ufcity {
    class message_receiver{
    private:

    public:
        void running_thread_subscribe();
    };
} // ufcity

#endif //UFCITY_MESSAGE_RECEIVER_H
