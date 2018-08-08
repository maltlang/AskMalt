#include "Objects.h"
#include "Value.h"

namespace amalt {
	List::List(Mark<Value> a, Mark<Value> d) :
		car(a), cdr(d),
		len(d.get()->tp == LISTT ?
			//(std::get<Mark<List>>(d.get()->val).get()->len)+1
		(std::get<std::shared_ptr<List>>(d.get()->val).get()->len) + 1
			:0) {}
}