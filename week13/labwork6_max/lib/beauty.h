#pragma once
#include <iostream>
#include <sstream>
#include "lib/parser.h"

namespace beauty {

using namespace omfl;

inline std::string ValueToString(const Value& val) {
    std::ostringstream out;
    if (val.IsArray()) {
        out << "[";
        const auto& arr = val.AsArray();
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i].IsString()) out << "\"" << arr[i].AsString() << "\"";
            else if (arr[i].IsInt()) out << arr[i].AsInt();
            else if (arr[i].IsFloat()) out << val.AsArray()[i].AsFloat();
            else if (arr[i].IsBool()) out << (arr[i].AsBool() ? "true" : "false");
            if (i != arr.size() - 1) out << ", ";
        }
        out << "]";
    } else if (val.IsString()) {
        out << "\"" << val.AsString() << "\"";
    } else if (val.IsBool()) {
        out << (val.AsBool() ? "true" : "false");
    } else if (val.IsInt()) {
        out << val.AsInt();
    } else if (val.IsFloat()) {
        out << val.AsFloat();
    } else if (val.IsSection()) {
        out << "<section>";
    } else {
        out << "<unknown>";
    }
    return out.str();
}

inline void PrintSection(const Section& section, const std::string& name) {
    std::cout << "------------------------------" << std::endl;
    std::cout << " Section [" << name << "]" << std::endl;
    std::cout << "------------------------------" << std::endl;

    for (const auto& [key, val] : section.values_) {
        std::cout << key << " = " << ValueToString(val) << std::endl;
    }

    std::cout << "------------------------------" << "\n\n";
}

} // namespace beauty
