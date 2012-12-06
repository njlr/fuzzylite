/*
 * Seldom.cpp
 *
 *  Created on: 4/12/2012
 *      Author: jcrada
 */

#include "Seldom.h"

#include "../engine/Operator.h"

#include <cmath>

namespace fl {

    std::string Seldom::name() const {
        return "seldom";
    }
    scalar Seldom::hedge(scalar x) const {
        return Op::IsLE(x, 0.5)
                ? std::sqrt(x / 2)
                : 1 - std::sqrt((1 - x) / 2);
    }

} /* namespace fl */