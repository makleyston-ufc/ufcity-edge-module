//
// Created by makleyston on 25/08/22.
//

#include "semantic_annotation.h"

namespace ufcity {

    std::string get_semantic_from_resource(resource * r) {
        //TODO
        return "##"+ r->get_resource_uuid() +"##";
    }

} // ufcity