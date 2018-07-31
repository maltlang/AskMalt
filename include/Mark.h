#pragma once

namespace amalt {
	template<typename T>
	class Mark {
	public:
		enum Color {
			WRITE,
			GREEN,
			BLACK,
		};
		Color *color;
		T *obj;

		Mark(T *o) : color(new Color(WRITE)), obj(o) {}
		Mark(const Mark& m) {
			color = m.color;
			obj = m.obj;
		}
		Mark(const Mark&& m) {
			color = m.color;
			obj = m.obj;
		}
		void marking(Color c = WRITE) {
			*color = c;
		}
		void clear() {
			delete color;
			delete obj;
		}
		Color getColor() const {
			return *color;
		}
		T *get() const {
			return obj;
		}
	};
}