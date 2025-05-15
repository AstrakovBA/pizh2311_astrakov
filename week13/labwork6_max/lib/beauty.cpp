#include <iostream>
#include "lib/parser.h"

using namespace omfl;

void PrintSection(const Section& section, const std::string& name) {
    std::cout << "\n== Section [" << name << "] ==" << std::endl;
    for (const auto& [key, val] : section.values_) {
        std::cout << key << ": ";
        if (val.IsArray()) {
            std::cout << "[";
            const auto& arr = val.AsArray();
            for (size_t i = 0; i < arr.size(); ++i) {
                if (arr[i].IsString()) std::cout << "\"" << arr[i].AsString() << "\"";
                else if (arr[i].IsInt()) std::cout << arr[i].AsInt();
                else if (arr[i].IsFloat()) std::cout << arr[i].AsFloat();
                if (i != arr.size() - 1) std::cout << ", ";
            }
            std::cout << "]";
        } else if (val.IsString()) {
            std::cout << "\"" << val.AsString() << "\"";
        } else if (val.IsBool()) {
            std::cout << (val.AsBool() ? "true" : "false");
        } else if (val.IsInt()) {
            std::cout << val.AsInt();
        } else if (val.IsFloat()) {
            std::cout << val.AsFloat();
        } else if (val.IsSection()) {
            std::cout << "<section>";
        }
        std::cout << std::endl;
    }
}