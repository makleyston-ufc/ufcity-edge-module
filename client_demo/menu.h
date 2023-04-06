//
// Created by makleyston on 22/03/23.
//
static std::string HOST = "172.18.0.2", PORT = "1883";

int menu(int argc, char *argv[]){

    if(argc == 1) {
        std::cout << "Invalid arguments. Type -h for help." << std::endl;
        return 1;
    }

    if(argc == 2){
        if(strcmp(argv[1], "-h") == 0){
            std::cout << "Option    \tVerbose       \tDescription" << std::endl;
            std::cout << "-a        \t--address        \tIP address of fog computing node." << std::endl;
            std::cout << "-p        \t--port        \tMQTT broker port of fog computing node." << std::endl;
            return 1;
        }else{
            std::cout << "Invalid arguments. Type -h for help." << std::endl;
            return 1;
        }
    }

    if(argc % 2 == 0) {
        std::cout << "Invalid arguments. Type -h for help." << std::endl;
        return 1;
    }

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0) {
            HOST = argv[i + 1];
        }else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0){
            PORT = argv[i + 1];
        }
        i = i + 2;
    }

    return 0;
}