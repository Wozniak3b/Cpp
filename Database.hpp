#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json, std::string, std::ofstream, std::ifstream;

class Database {
public:
    virtual ~Database(){};

    virtual json toJson() const = 0;
    virtual void fromJson(const json& j) = 0;

    void saveToFile(const string& fileName){
        ofstream file(fileName);
        file<<toJson().dump(4);
        file.close();
    }

    void loadFromFile(const string& fileName){
        ifstream file(fileName);
        if(file.is_open()){
            json j;
            file>>j;
            fromJson(j);
            file.close();
        }
    }
};