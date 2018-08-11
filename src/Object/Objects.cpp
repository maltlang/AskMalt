#include "Objects.h"
#include "Value.h"

namespace amalt {
	List::List(Value a, Value d) :
		car(a), cdr(d),
		len(d.tp == LISTT ?
			std::get<RList>(d.val).get()->len
			:0) {}
}