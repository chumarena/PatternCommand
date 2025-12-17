#pragma once
#include "Interface_Command.h"
#include <map>
#include <string>

class engine {
public:
	void register_command(Interface_command* interface, const std::string& command_name);
	int execute(const std::string& command_name, const std::map<std::string, int>& args);

private:
	std::map<std::string, Interface_command*> commands;
};