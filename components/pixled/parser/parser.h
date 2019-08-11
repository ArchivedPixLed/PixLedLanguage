#ifndef PARSER_H
#define PARSER_H

#include <regex>
#include <string>

std::shared_ptr<Animation> parseScript(std::string script);
void parseAnimation(std::shared_ptr<Animation> animation, std::string body);

#endif
