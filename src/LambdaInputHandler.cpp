#include <cstdlib>
#include <iostream>
#include <string>

#include "al5poly/LambdaInputHandler.hpp"

namespace al5poly
{
    LambdaInputHandler::LambdaInputHandler(
            LambdaInputHandler::Handler lambda):
        lambda_(lambda)
    {
    }

    LambdaInputHandler::~LambdaInputHandler(void)
    {
    }

    void LambdaInputHandler::operator()(
            const std::string & name,
            const IGameTime & time) const
    {
        this->lambda_(name, time);
    }

    const LambdaInputHandler::Handler & LambdaInputHandler::getLambda() const
    {
        return this->lambda_;
    }
}
