#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Users.hpp"
#include "Debts.hpp"

using std::string, std::ofstream, std::ifstream, std::map, std::vector;

class Database {
private:
    map
    
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