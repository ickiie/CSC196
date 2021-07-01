#pragma once
#include "core.h"

namespace nc {

	struct Color {
		float r, g, b;

		Color() : r{0}, g{0}, b{0} {}
		Color(float r, float g, float b) : r{r}, g{g}, b{b} {}
		Color(DWORD rgb) { // DWORD(X | b | g | r )

			r = (rgb & 0xff) / 255.0f;	          // 0 - 255 -> 0 - 1
			g = ((rgb >> 8) & 0xff) / 255.0f;     // 0 - 255 -> 0 - 1
			b = ((rgb >> 16) & 0xff) / 255.0f;    // 0 - 255 -> 0 - 1
		}

		Color operator * (float s) const { return { r * s, g * s, b * s }; }
		operator DWORD() const { return ToRGB(); }

		DWORD ToRGB() const {

			BYTE red = static_cast<BYTE>(r * 255);
			BYTE green = static_cast<BYTE>(g * 255);
			BYTE blue = static_cast<BYTE>(b * 255);

			return (red | green << 8 | blue << 16);
		}

	};
}