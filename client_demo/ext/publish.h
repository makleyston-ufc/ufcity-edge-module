////
//// Created by makleyston on 21/09/22.
////
//
//#ifndef UFCITY_PUBLISH_H
//#define UFCITY_PUBLISH_H
//
//
//
//class encoded_file_persistence : virtual public mqtt::iclient_persistence
//{
//    // The name of the store
//    // Used as the directory name
//    std::string name_;
//
//    // A key for encoding the data
//    std::string encodeKey_;
//
//    // Simple, in-place XOR encoding and decoding
//    void encode(std::string& s) const {
//        size_t n = encodeKey_.size();
//        if (n == 0 || s.empty()) return;
//
//        for (size_t i=0; i<s.size(); ++i)
//            s[i] ^= encodeKey_[i%n];
//    }
//
//    // Gets the persistence file name for the supplied key.
//    std::string path_name(const std::string& key) const { return name_ + "/" + key; }
//
//public:
//    // Create the persistence object with the specified encoding key
//    encoded_file_persistence(const std::string& encodeKey)
//            : encodeKey_(encodeKey) {}
//
//    // "Open" the persistence store.
//    // Create a directory for persistence files, using the client ID and
//    // serverURI to make a unique directory name. Note that neither can be
//    // empty. In particular, the app can't use an empty `clientID` if it
//    // wants to use persistence. (This isn't an absolute rule for your own
//    // persistence, but you do need a way to keep data from different apps
//    // separate).
//    void open(const std::string& clientId, const std::string& serverURI) override {
//        if (clientId.empty() || serverURI.empty())
//            throw mqtt::persistence_exception();
//
//        name_ = serverURI + "-" + clientId;
//        std::replace(name_.begin(), name_.end(), ':', '-');
//
//        mkdir(name_.c_str(), S_IRWXU | S_IRWXG);
//    }
//
//    // Close the persistent store that was previously opened.
//    // Remove the persistence directory, if it's empty.
//    void close() override {
//        rmdir(name_.c_str());
//    }
//
//    // Clears persistence, so that it no longer contains any persisted data.
//    // Just remove all the files from the persistence directory.
//    void clear() override {
//        DIR* dir = opendir(name_.c_str());
//        if (!dir) return;
//
//        dirent *next;
//        while ((next = readdir(dir)) != nullptr) {
//            auto fname = string(next->d_name);
//            if (fname == "." || fname == "..") continue;
//            string path = name_ + "/" + fname;
//            remove(path.c_str());
//        }
//        closedir(dir);
//    }
//
//    // Returns whether or not data is persisted using the specified key.
//    // We just look for a file in the store directory with the same name as
//    // the key.
//    bool contains_key(const string& key) override {
//        DIR* dir = opendir(name_.c_str());
//        if (!dir) return false;
//
//        dirent *next;
//        while ((next = readdir(dir)) != nullptr) {
//            if (string(next->d_name) == key) {
//                closedir(dir);
//                return true;
//            }
//        }
//        closedir(dir);
//        return false;
//    }
//
//    // Returns the keys in this persistent data store.
//    // We just make a collection of the file names in the store directory.
//    mqtt::string_collection keys() const override {
//        mqtt::string_collection ks;
//        DIR* dir = opendir(name_.c_str());
//        if (!dir) return ks;
//
//        dirent *next;
//        while ((next = readdir(dir)) != nullptr) {
//            auto fname = string(next->d_name);
//            if (fname == "." || fname == "..") continue;
//            ks.push_back(fname);
//        }
//
//        closedir(dir);
//        return ks;
//    }
//
//    // Puts the specified data into the persistent store.
//    // We just encode the data and write it to a file using the key as the
//    // name of the file. The multiple buffers given here need to be written
//    // in order - and a scatter/gather like writev() would be fine. But...
//    // the data will be read back as a single buffer, so here we first
//    // concat a string so that the encoding key lines up with the data the
//    // same way it will on the read-back.
//    void put(const string& key, const std::vector<mqtt::string_view>& bufs) override {
//        auto path = path_name(key);
//
//        ofstream os(path, ios_base::binary);
//        if (!os)
//            throw mqtt::persistence_exception();
//
//        string s;
//        for (const auto& b : bufs)
//            s.append(b.data(), b.size());
//
//        encode(s);
//        os.write(s.data(), s.size());
//    }
//
//    // Gets the specified data out of the persistent store.
//    // We look for a file with the name of the key, read the contents,
//    // decode, and return it.
//    string get(const string& key) const override {
//        auto path = path_name(key);
//
//        ifstream is(path, ios_base::ate|ios_base::binary);
//        if (!is)
//            throw mqtt::persistence_exception();
//
//        // Read the whole file into a string
//        streamsize sz = is.tellg();
//        if (sz == 0) return string();
//
//        is.seekg(0);
//        string s(sz, '\0');
//        is.read(&s[0], sz);
//        if (is.gcount() < sz)
//            s.resize(is.gcount());
//
//        encode(s);
//        return s;
//    }
//
//    // Remove the data for the specified key.
//    // Just remove the file with the same name as the key, if found.
//    void remove(const string &key) override {
//        auto path = path_name(key);
//        ::remove(path.c_str());
//    }
//};
//
//
//#endif //UFCITY_PUBLISH_H
