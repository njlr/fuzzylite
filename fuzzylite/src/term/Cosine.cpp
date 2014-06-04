// #BEGIN_LICENSE
// fuzzylite: a fuzzy logic control library in C++
// Copyright (C) 2014  Juan Rada-Vilela
// 
// This file is part of fuzzylite.
//
// fuzzylite is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// fuzzylite is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with fuzzylite.  If not, see <http://www.gnu.org/licenses/>.
// #END_LICENSE

#include "fl/term/Cosine.h"

#include <cmath>

namespace fl {

    Cosine::Cosine(const std::string& name, scalar center, scalar width)
    : Term(name), _center(center), _width(width) {

    }

    Cosine::~Cosine() {

    }

    std::string Cosine::className() const {
        return "Cosine";
    }

    std::string Cosine::parameters() const {
        return Op::join(2, " ", _center, _width);
    }

    void Cosine::configure(const std::string& parameters) {
        if (parameters.empty()) return;
        std::vector<std::string> values = Op::split(parameters, " ");
        std::size_t required = 2;
        if (values.size() < required) {
            std::ostringstream ex;
            ex << "[configuration error] term <" << className() << ">"
                    << " requires <" << required << "> parameters";
            throw fl::Exception(ex.str(), FL_AT);
        }
        setCenter(Op::toScalar(values.at(0)));
        setWidth(Op::toScalar(values.at(1)));
    }

    scalar Cosine::membership(scalar x) const {
        if (fl::Op::isNaN(x)) return fl::nan;
        if (fl::Op::isLt(x, _center - _width / 2.0)
                or fl::Op::isGt(x, _center + _width / 2.0))
            return 0.0;
        return 0.5 * (1.0 + std::cos(2.0 / _width * fl::pi * (x - _center)));
    }

    void Cosine::setCenter(scalar center) {
        this->_center = center;
    }

    scalar Cosine::getCenter() const {
        return this->_center;
    }

    void Cosine::setWidth(scalar width) {
        this->_width = width;
    }

    scalar Cosine::getWidth() const {
        return this->_width;
    }

    Cosine* Cosine::clone() const {
        return new Cosine(*this);
    }

    Term* Cosine::constructor() {
        return new Cosine;
    }
}
