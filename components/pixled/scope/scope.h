#ifndef SCOPE_H
#define SCOPE_H

#include <memory>
#include <string>
#include <map>

template<class T> class Scope {
	public:
		void define(std::string name, T variable);
		T get(std::string name);

	protected:
		std::map<std::string, T> variables;
};

template<class T>
void Scope<T>::define(std::string name, T variable) {
	this->variables[name] = variable;
}

template<class T>
T Scope<T>::get(std::string name) {
	return this->variables[name];
}
#endif //SCOPE_H
