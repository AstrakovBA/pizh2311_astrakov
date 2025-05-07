#include "ArgParser.h"

namespace ArgumentParser {

    /**
     * @brief ����������� ������� ����������
     * @param name �������� ��������� (����� �������������� � �������)
     */
    ArgParser::ArgParser(const std::string& name) : name_(name) {}

    // ������ ������� ��� ���������� ��������� ����������

    /**
     * @brief ��������� ��������� �������� � ������� ������
     * @param long_name ������� ��� ��������� (��������, "--input")
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddStringArgument(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ��������� �������� � �������� � ������� ������
     * @param short_name �������� ��� ��������� (��������, "-i")
     * @param long_name ������� ��� ���������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddStringArgument(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief ��������� ��������� �������� � ���������
     * @param long_name ������� ��� ���������
     * @param description �������� ��������� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddStringArgument(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ��������� �������� � �������� ������ � ���������
     * @param short_name �������� ��� ���������
     * @param long_name ������� ��� ���������
     * @param description �������� ��������� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddStringArgument(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // ������ ������� ��� ���������� ������������� ����������

    /**
     * @brief ��������� ������������� ��������
     * @param long_name ������� ��� ���������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddIntArgument(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_int = true;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ������������� �������� � �������� ������
     * @param short_name �������� ��� ���������
     * @param long_name ������� ��� ���������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddIntArgument(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_int = true;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief ��������� ������������� �������� � ���������
     * @param long_name ������� ��� ���������
     * @param description �������� ��������� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddIntArgument(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_int = true;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ������������� �������� � �������� ������ � ���������
     * @param short_name �������� ��� ���������
     * @param long_name ������� ��� ���������
     * @param description �������� ��������� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddIntArgument(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_int = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // ������ ������� ��� ���������� ������

    /**
     * @brief ��������� ���� (������� ��������)
     * @param long_name ������� ��� �����
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddFlag(const std::string& long_name) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_flag = true;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ���� � �������� ������
     * @param short_name �������� ��� �����
     * @param long_name ������� ��� �����
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddFlag(char short_name, const std::string& long_name) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief ��������� ���� � ���������
     * @param long_name ������� ��� �����
     * @param description �������� ����� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddFlag(const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        return *this;
    }

    /**
     * @brief ��������� ���� � �������� ������ � ���������
     * @param short_name �������� ��� �����
     * @param long_name ������� ��� �����
     * @param description �������� ����� ��� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddFlag(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    // ������ ������� ��� ��������� ����������

    /**
     * @brief ������������� �������� ��������� ��� �������
     * @param description ����� ��������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::Help(const std::string& description) {
        help_description_ = description;
        return *this;
    }

    /**
     * @brief ��������� �������� ������ �������
     * @param short_name �������� ��� ��������� �������
     * @param long_name ������� ��� ��������� �������
     * @param description �������� �������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& description) {
        Argument arg;
        arg.short_name = short_name;
        arg.long_name = long_name;
        arg.is_flag = true;
        arg.description = description;
        arguments_[long_name] = arg;
        short_to_long_[short_name] = long_name;
        return *this;
    }

    /**
     * @brief ������������� ��������� �������� �� ���������
     * @param value �������� �� ���������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::Default(const char* value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.default_value = value;
        }
        return *this;
    }

    /**
     * @brief ������������� ������ �������� �� ���������
     * @param value �������� �� ���������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::Default(bool value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.default_bool_value = value;
        }
        return *this;
    }

    /**
     * @brief �������� �������� ��� �����������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::Positional() {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.is_positional = true;
            positional_args_names_.push_back(arguments_.rbegin()->second.long_name);
        }
        return *this;
    }

    /**
     * @brief ��������� ��������� ��������� ��������� ��������
     * @param min_args_count ����������� ���������� �������� (�� ��������� 0)
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::MultiValue(size_t min_args_count) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.is_multi_value = true;
            arguments_.rbegin()->second.min_args_count = min_args_count;
        }
        return *this;
    }

    // ������ ������� ��� ���������� ��������

    /**
     * @brief ��������� �������� ��������� � ��������� ����������
     * @param value ������ �� ���������� ��� ����������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::StoreValue(std::string& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.string_store = &value;
        }
        return *this;
    }

    /**
     * @brief ��������� �������� ��������� � ������������� ����������
     * @param value ������ �� ���������� ��� ����������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::StoreValue(int& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.int_store = &value;
        }
        return *this;
    }

    /**
     * @brief ��������� �������� ����� � ������ ����������
     * @param value ������ �� ���������� ��� ����������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::StoreValue(bool& value) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.bool_store = &value;
        }
        return *this;
    }

    /**
     * @brief ��������� ��������� �������� ��������� � ������
     * @param values ������ �� ������ ��� ����������
     * @return ������ �� ���� ��� ������� �������
     */
    ArgParser& ArgParser::StoreValues(std::vector<int>& values) {
        if (!arguments_.empty()) {
            arguments_.rbegin()->second.int_vector_store = &values;
        }
        return *this;
    }

    // ������ ������� ��������

    /**
     * @brief ������ ��������� ��������� ������
     * @param argc ���������� ����������
     * @param argv ������ ����������
     * @return true, ���� ������� �������, false � ��������� ������
     */
    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> args;
        for (int i = 1; i < argc; ++i) {
            args.push_back(argv[i]);
        }
        return Parse(args);
    }

    /**
     * @brief ������ ��������� �� ������� �����
     * @param args ������ ����� � �����������
     * @return true, ���� ������� �������, false � ��������� ������
     */
    bool ArgParser::Parse(const std::vector<std::string>& args) {
        size_t current_arg = 0;

        // ��������� ����������� ���������� � ������
        while (current_arg < args.size()) {
            const std::string& arg = args[current_arg];

            // �������� �� ������ �������
            if (arg == "--help" || arg == "-h") {
                help_requested_ = true;
                return true;
            }

            // ���������� ����������� ��������� - ��� �������������� ��������
            if (arg[0] != '-') {
                current_arg++;
                continue;
            }

            ParseArgument(arg, current_arg, args);
            current_arg++;
        }

        // ��������� ����������� ����������
        ParsePositionalArguments(args);

        // �������� ���������� ����������
        if (!ValidateArguments()) {
            return false;
        }

        // ���������� �������� � ���������� ������
        StoreValuesToReferences();

        return true;
    }

    // ������ ������� ��������� ��������

    /**
     * @brief �������� ��������� �������� ���������
     * @param name ��� ���������
     * @return �������� ���������
     */
    std::string ArgParser::GetStringValue(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        if (!arg.string_values.empty()) {
            return arg.string_values[0];
        }
        if (arg.default_value.has_value()) {
            return arg.default_value.value();
        }
        return "";
    }

    /**
     * @brief �������� ������������� �������� ���������
     * @param name ��� ���������
     * @return �������� ���������
     */
    int ArgParser::GetIntValue(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        if (!arg.int_values.empty()) {
            return arg.int_values[0];
        }
        return 0;
    }

    /**
     * @brief �������� ������������� �������� �� �������
     * @param name ��� ���������
     * @param index ������ ��������
     * @return �������� ���������
     */
    int ArgParser::GetIntValue(const std::string& name, size_t index) const {
        const Argument& arg = GetArgument(name);
        if (index < arg.int_values.size()) {
            return arg.int_values[index];
        }
        return 0;
    }

    /**
     * @brief ���������, ��� �� ���������� ����
     * @param name ��� �����
     * @return true, ���� ���� ����������, false � ��������� ������
     */
    bool ArgParser::GetFlag(const std::string& name) const {
        const Argument& arg = GetArgument(name);
        return !arg.string_values.empty() || arg.default_bool_value.value_or(false);
    }

    /**
     * @brief ���������, ��� �� �������� ����� �������
     * @return true, ���� ��������� �������, false � ��������� ������
     */
    bool ArgParser::Help() const {
        return help_requested_;
    }

    /**
     * @brief ���������� ������ � ��������� �������
     * @return ��������������� ������ �������
     */
    std::string ArgParser::HelpDescription() const {
        std::string result = name_ + "\n";
        if (!help_description_.empty()) {
            result += help_description_ + "\n";
        }
        result += "\n";

        // ��������� ������ ����������
        for (const auto& [name, arg] : arguments_) {
            if (arg.is_positional) continue; // ����������� ��������� �������������� ��������

            // ����������� ������ � ������� ���������
            std::string names;
            if (arg.short_name.has_value()) {
                names += "-" + std::string(1, arg.short_name.value()) + ",  ";
            }
            else {
                names += "     ";
            }
            names += "--" + arg.long_name;

            // ��������� ��� �������� ��� ��-������
            if (!arg.is_flag) {
                names += arg.is_int ? "=<int>" : "=<string>";
            }

            // �������� ������ ������ ��������
            std::string line = names + ",  " + arg.description;

            // ��������� �������������� ��������
            if (arg.is_multi_value) {
                line += " [repeated, min args = " + std::to_string(arg.min_args_count) + "]";
            }
            if (arg.default_value.has_value()) {
                line += " [default = " + arg.default_value.value() + "]";
            }
            else if (arg.default_bool_value.has_value()) {
                line += " [default = " + std::string(arg.default_bool_value.value() ? "true" : "false") + "]";
            }

            result += line + "\n";
        }

        // ��������� ���������� � ����������� ����������
        for (const auto& name : positional_args_names_) {
            const Argument& arg = arguments_.at(name);
            std::string line = "[" + arg.long_name + "]";
            if (arg.is_multi_value) {
                line += "...";
            }
            line += ",  " + arg.description;
            result += line + "\n";
        }

        result += "\n";
        result += "-h, --help Display this help and exit\n";

        return result;
    }

    // ���������� ������

    /**
     * @brief ������������ ��������� �������� ��������� ������
     * @param arg ������� �������� ��� ���������
     * @param current_arg ������ �������� ���������
     * @param args ��� ��������� ��������� ������
     */
    void ArgParser::ParseArgument(const std::string& arg, size_t& current_arg, const std::vector<std::string>& args) {
        size_t equal_pos = arg.find('=');
        std::string name_part = arg.substr(0, equal_pos);
        std::string value_part = equal_pos != std::string::npos ? arg.substr(equal_pos + 1) : "";

        // ���������� ������� ��� ���������
        std::string long_name;
        if (name_part[1] == '-') {
            // ������� ��� (--name)
            long_name = name_part.substr(2);
        }
        else {
            // �������� ��� (-n)
            char short_name = name_part[1];
            long_name = short_to_long_.at(short_name);
        }

        Argument& argument = GetArgument(long_name);

        if (argument.is_flag) {
            // ��������� �����
            argument.string_values.push_back("true");
        }
        else {
            // ��������� ��������� �� ���������
            if (equal_pos != std::string::npos) {
                // �������� ������� ����� =
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(value_part));
                }
                else {
                    argument.string_values.push_back(value_part);
                }
            }
            else if (current_arg + 1 < args.size() && args[current_arg + 1][0] != '-') {
                // �������� ������� ��������� ����������
                current_arg++;
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(args[current_arg]));
                }
                else {
                    argument.string_values.push_back(args[current_arg]);
                }
            }
            else if (argument.default_value.has_value()) {
                // ���������� �������� �� ���������
                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(argument.default_value.value()));
                }
                else {
                    argument.string_values.push_back(argument.default_value.value());
                }
            }
            else if (argument.default_bool_value.has_value()) {
                // ��� ������ � ��������� ���������
                argument.string_values.push_back(argument.default_bool_value.value() ? "true" : "false");
            }
        }
    }

    /**
     * @brief ������������ ����������� ���������
     * @param args ��� ��������� ��������� ������
     */
    void ArgParser::ParsePositionalArguments(const std::vector<std::string>& args) {
        size_t positional_index = 0;

        for (const auto& arg : args) {
            if (arg[0] == '-') continue; // ���������� ����������� ���������

            if (positional_index < positional_args_names_.size()) {
                std::string long_name = positional_args_names_[positional_index];
                Argument& argument = arguments_[long_name];

                if (argument.is_int) {
                    argument.int_values.push_back(std::stoi(arg));
                }
                else {
                    argument.string_values.push_back(arg);
                }

                // ��� �� multi-value ���������� ��������� � ���������� ������������
                if (!argument.is_multi_value) {
                    positional_index++;
                }
            }
        }
    }

    /**
     * @brief ��������� �������� � ��������� ����������
     */
    void ArgParser::StoreValuesToReferences() {
        for (auto& [name, arg] : arguments_) {
            if (arg.bool_store != nullptr) {
                *arg.bool_store = !arg.string_values.empty();
            }
            if (arg.string_store != nullptr && !arg.string_values.empty()) {
                *arg.string_store = arg.string_values[0];
            }
            if (arg.int_store != nullptr && !arg.int_values.empty()) {
                *arg.int_store = arg.int_values[0];
            }
            if (arg.int_vector_store != nullptr) {
                *arg.int_vector_store = arg.int_values;
            }
        }
    }

    /**
     * @brief ��������� ���������� ����������
     * @return true, ���� ��� ��������� �������, false � ��������� ������
     */
    bool ArgParser::ValidateArguments() const {
        for (const auto& [name, arg] : arguments_) {
            // �������� ������������ ����������
            if (!arg.default_value.has_value() && !arg.default_bool_value.has_value() &&
                arg.string_values.empty() && arg.int_values.empty() && !arg.is_flag) {
                return false;
            }

            // �������� ������������ ���������� �������� ��� multi-value
            if (arg.is_multi_value && arg.int_values.size() < arg.min_args_count) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief �������� �������� �� ����� (������������� ������)
     * @param name ��� ���������
     * @return ������ �� ��������
     */
    ArgParser::Argument& ArgParser::GetArgument(const std::string& name) {
        return arguments_.at(name);
    }

    /**
     * @brief �������� �������� �� ����� (����������� ������)
     * @param name ��� ���������
     * @return ����������� ������ �� ��������
     */
    const ArgParser::Argument& ArgParser::GetArgument(const std::string& name) const {
        return arguments_.at(name);
    }

    /**
     * @brief �������� �������� �� ��������� �����
     * @param short_name �������� ��� ���������
     * @return ������ �� ��������
     */
    ArgParser::Argument& ArgParser::GetArgumentByShortName(char short_name) {
        return arguments_.at(short_to_long_.at(short_name));
    }

} // namespace ArgumentParser
