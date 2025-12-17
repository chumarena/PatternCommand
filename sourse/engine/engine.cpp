#include "engine.h"
#include <stdexcept>

void engine::register_command(Interface_command* interface, const std::string& command_name) {
	if (interface) {
		commands[command_name] = interface;
	}
}

int engine::execute(const std::string& command_name, const std::map<std::string, int>& args) {
	auto it = commands.find(command_name);
	if (it != commands.end()) {
		return it->second->execute(args);
	}
	throw std::runtime_error("команда не найдена: " + command_name);
}