#pragma once
#include "Models/Task.h"

namespace YAML {
    template<>
    struct convert<DoLah::FloatingTask> {
        static Node encode(const DoLah::FloatingTask& rhs) {
            Node node;
            node.push_back(rhs);
            return node;
        }

        static bool decode(const Node& node, DoLah::FloatingTask& rhs) {
            if (!node.IsSequence() || node.size() != 3) {
                return false;
            }

            rhs.setDescription(node[0].as<std::string>());
            return true;
        }
    };
}

//namespace DoLah {
//    template<FloatingTask> struct convert<FloatingTask> {
//        static Node encode(const FloatingTask& task) {
//            Node node;
//            
//            return node;
//        }
//
//        static bool decode(const Node& node, FloatingTask& task) {
//            task
//            return true;
//        }
//    };
//}