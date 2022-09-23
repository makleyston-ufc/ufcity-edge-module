//
// Created by makleyston on 23/09/22.
//



//    nlohmann::json object;
//    object["attr1"] = "on";
//    object["attr2"] = 99;
//    object["attr3"] = {10, 11, 12, 13};
//
//    std::cout << object.dump() << object.dump().size() << std::endl;
//
//    /*BJData*/
//    std::vector<std::uint8_t> v_bjdata = nlohmann::json::to_bjdata(object);
//    std::cout << v_bjdata.data() << " => " << v_bjdata.size() << std::endl;
//
//    /*BJData-Size*/
//    std::vector<std::uint8_t> v_bjdata_size = nlohmann::json::to_bjdata(object, true);
//    std::cout << v_bjdata_size.data() << " => " << v_bjdata_size.size() << std::endl;
//
//    /*BJData-Size-SizeType*/
//    std::vector<std::uint8_t> v_bjdata_size_type = nlohmann::json::to_bjdata(object, true, true);
//    std::cout << v_bjdata_size_type.data() << " => " << v_bjdata_size_type.size() << std::endl;
//
//    /*BSON*/
//    std::vector<std::uint8_t> v_bson = nlohmann::json::to_bson(object);
//    std::cout << v_bson.data() << " => " << v_bson.size() << std::endl;
//
//    /*CBOR*/
//    std::vector<std::uint8_t> v_cbor = nlohmann::json::to_cbor(object);
//    std::cout << v_cbor.data() << " => " << v_cbor.size() << std::endl;
//
//    /*MessegePack*/
//    std::vector<std::uint8_t> v_msgpack = nlohmann::json::to_msgpack(object);
//    std::cout << v_msgpack.data() << " => " << v_msgpack.size() << std::endl;
//
//    /*UBJSON*/
//    std::vector<std::uint8_t> v_ubjson = nlohmann::json::to_ubjson(object);
//    std::cout << v_ubjson.data() << " => " << v_ubjson.size() << std::endl;
//
//    /*UBJSON-Size*/
//    std::vector<std::uint8_t> v_ubjson_size = nlohmann::json::to_ubjson(object, true);
//    std::cout << v_ubjson_size.data() << " => " << v_ubjson_size.size() << std::endl;
//
//    /*UBJSON-Size-SizeType*/
//    std::vector<std::uint8_t> v_ubjson_size_type = nlohmann::json::to_ubjson(object, true, true);
//    std::cout << v_ubjson_size_type.data() << " => " << v_ubjson_size_type.size() << std::endl;
