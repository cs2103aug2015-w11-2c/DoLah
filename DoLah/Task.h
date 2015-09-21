#pragma once
#include <string>


namespace DoLah {
    class AbstractTask {
    public:
        AbstractTask();
        virtual ~AbstractTask();
        void setId(int id);
        int getId();
        void setName(std::string);
        std::string getName();
        void setDescription(std::string);
        std::string getDescription();
        void setDone(bool);
        bool isDone();
    private:
        std::string description;
        std::string name;
        int id;
        bool done;
    };
}
