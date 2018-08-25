#include "Function.h"
#include "Value.h"

namespace amalt {
	Function::Function(std::string n) : name(std::move(n)) {};
	RTFunction::
		RTFunction(std::weak_ptr<Module> m,
			std::string n, AST a, std::shared_ptr<Dict> e, std::vector<String> at) :
		mod(std::move(m)),
		Function(std::move(n)), expr(a), env(std::move(e)), argstable(std::move(at)) {}

	NativeFunction::
		NativeFunction(std::string n = "<Unknown>", NativeInterface fp = nullptr):
		Function(std::move(n)), f(std::move(fp)) {}

	Value NativeFunction::fcall(RTuple args) {
		return f(args);
	}
	
	Module::Module(String p, AST e) :
		path(std::move(p)), vartable(std::make_shared<Dict>()), expr(e) {}

}

