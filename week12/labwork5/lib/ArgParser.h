#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <functional>

namespace ArgumentParser {

    class ArgParser {
    public:
        explicit ArgParser(const std::string& name);

        ArgParser& AddStringArgument(const std::string& long_name);
        ArgParser& AddStringArgument(char short_name, const std::string& long_name);
        ArgParser& AddStringArgument(const std::string& long_name, const std::string& description);
        ArgParser& AddStringArgument(char short_name, const std::string& long_name, const std::string& description);

        ArgParser& AddIntArgument(const std::string& long_name);
        ArgParser& AddIntArgument(char short_name, const std::string& long_name);
        ArgParser& AddIntArgument(const std::string& long_name, const std::string& description);
        ArgParser& AddIntArgument(char short_name, const std::string& long_name, const std::string& description);

        ArgParser& AddFlag(const std::string& long_name);
        ArgParser& AddFlag(char short_name, const std::string& long_name);
        ArgParser& AddFlag(const std::string& long_name, const std::string& description);
        ArgParser& AddFlag(char short_name, const std::string& long_name, const std::string& description);

        ArgParser& Help(const std::string& description);
        ArgParser& AddHelp(char short_name, const std::string& long_name, const std::string& description);

        ArgParser& Default(const char* value);
        ArgParser& Default(bool value);
        ArgParser& Positional();
        ArgParser& MultiValue(size_t min_args_count = 0);

        ArgParser& StoreValue(std::string& value);
        ArgParser& StoreValue(int& value);
        ArgParser& StoreValue(bool& value);
        ArgParser& StoreValues(std::vector<int>& values);

        bool Parse(int argc, char** argv);
        bool Parse(const std::vector<std::string>& args);

        std::string GetStringValue(const std::string& name) const;
        int GetIntValue(const std::string& name) const;
        int GetIntValue(const std::string& name, size_t index) const;
        bool GetFlag(const std::string& name) const;
        bool Help() const;
        std::string HelpDescription() const;

    private:
        struct Argument {
            std::optional<char> short_name;
            std::string long_name;
            std::string description;
            bool is_flag = false;
            bool is_int = false;
            bool is_multi_value = false;
            bool is_positional = false;
            size_t min_args_count = 0;
            std::optional<std::string> default_value;
            std::optional<bool> default_bool_value;
            std::vector<std::string> string_values;
            std::vector<int> int_values;
            bool* bool_store = nullptr;
            std::string* string_store = nullptr;
            int* int_store = nullptr;
            std::vector<int>* int_vector_store = nullptr;
        };

        std::string name_;
        std::string help_description_;
        std::map<std::string, Argument> arguments_;
        std::map<char, std::string> short_to_long_;
        std::vector<std::string> positional_args_names_;
        bool help_requested_ = false;

        void ParseArgument(const std::string& arg, size_t& current_arg, const std::vector<std::string>& args);
        void ParsePositionalArguments(const std::vector<std::string>& args);
        void StoreValuesToReferences();
        bool ValidateArguments() const;
        Argument& GetArgument(const std::string& name);
        const Argument& GetArgument(const std::string& name) const;
        Argument& GetArgumentByShortName(char short_name);
    };
}
