#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

template <typename T>
class Function {
public:
    virtual ~Function() = default;

    virtual T f(T x) const = 0;
    virtual T df(T x) const = 0;
    virtual std::string name() const = 0;
};

#endif