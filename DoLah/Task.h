#pragma once
#include <string>


namespace DoLah {
    class Task {
    public:
        Task();
        virtual ~Task();
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
