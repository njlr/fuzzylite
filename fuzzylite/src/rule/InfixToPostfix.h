/*
 * InfixToPostfix.h
 *
 *  Created on: 4/12/2012
 *      Author: jcrada
 */

#ifndef FL_INFIXTOPOSTFIX_H_
#define FL_INFIXTOPOSTFIX_H_

#include "../scalar.h"

#include <map>
#include <string>
#include <sstream>
namespace fl {

    class InfixToPostfix {
    public:

        class GenericOperator {
        public:
            std::string name;
            short precedence;
            short arity;
            short associativity;
            std::string mask;
            GenericOperator(const std::string& name, short  precedence, short  arity = 2,
                    short  associativity = -1, const std::string& mask = "")
                    : name(name), precedence(precedence), arity(arity), associativity(associativity),
                            mask(mask) {
                if (mask == "") this->mask = name;
            }

            std::string toString() const {
                std::stringstream ss;
                ss << "name='" << name << "' "
                        << "precedence='" << precedence << "' "
                        << "arity='" << arity << "' "
                        << "associativity='" << associativity << "' "
                        << "mask='" << mask << "' "
                        ;
                return ss.str();
            }

        };

        typedef scalar (*OneArgFunction)(scalar);
        typedef scalar (*TwoArgFunction)(scalar, scalar);

        class GenericFunction {
        public:
            std::string name;
            short  arity;
            short  associativity;
            OneArgFunction oneArgFunction;
            TwoArgFunction twoArgFunction;

            GenericFunction(const std::string& name, short  arity = 1)
                    : name(name), arity(arity), associativity(-1),
                            oneArgFunction(NULL), twoArgFunction(NULL) {
            }
            GenericFunction(const std::string&name, OneArgFunction oneArgFunction)
                    : name(name), arity(1), associativity(-1), oneArgFunction(oneArgFunction),
                            twoArgFunction(NULL) {
            }
            GenericFunction(const std::string&name, TwoArgFunction twoArgFunction)
                    : name(name), arity(2), associativity(-1), oneArgFunction(NULL),
                            twoArgFunction(twoArgFunction) {
            }

            std::string toString() const {
                std::stringstream ss;
                ss << "name='" << name << "' "
                        << "arity='" << arity << "' "
                        << "associativity='" << associativity << "' "
                        ;
                return ss.str();
            }
        };

    protected:
        std::map<std::string, GenericOperator*> _genericOperators;
        std::map<std::string, GenericFunction*> _genericFunctions;

        void loadGenericOperators();
        void loadGenericFunctions();

    public:
        InfixToPostfix();
        ~InfixToPostfix();

        /**
         * Operations for std::map _genericOperators
         */
        void addGenericOperator(GenericOperator* genericOperator);
        GenericOperator* removeGenericOperator(const std::string& key);
        GenericOperator* getGenericOperator(const std::string& key) const;
        const std::map<std::string, GenericOperator*>& genericOperators() const;

        /**
         * Operations for std::map _genericFunctions
         */
        void addGenericFunction(GenericFunction* genericFunction);
        GenericFunction* removeGenericFunction(const std::string& key);
        GenericFunction* getGenericFunction(const std::string& key) const;
        const std::map<std::string, GenericFunction*>& genericFunctions() const;

        std::string convert(const std::string& infix);

    };

} /* namespace fl */
#endif /* FL_INFIXTOPOSTFIX_H_ */
