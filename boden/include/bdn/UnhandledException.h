#ifndef BDN_UnhandledException_H_
#define BDN_UnhandledException_H_


#include <bdn/IUnhandledProblem.h>

namespace bdn
{


/** IUnhandledProblem implementation for unhandled C++ exceptions.*/
class UnhandledException : public Base, BDN_IMPLEMENTS IUnhandledProblem
{
public:
    UnhandledException( const std::exception_ptr& p, bool ignorable );


    /** Returns the problem type.*/
    Type getType() const override
    {
        return Type::exception;
    }


    bool canKeepRunning() const override
    {
        return _canKeepRunning;
    }


    bool keepRunning() override
    {
        if(_canKeepRunning)
        {
            _keepRunning = true;
            return true;
        }
        else
            return false;
    }


    /** Returns true if the app has decided to continue running, despite this exception.*/
    bool shouldKeepRunning() const
    {
        return _keepRunning;
    }
        

        
    void throwAsException() const override;

    String getErrorMessage() const override;

    String toString() const override;

private:
    void ensureStringsInitialized();

    std::exception_ptr  _exceptionPtr;

    bool                _stringsInitialized = false;

    String              _errorMessage;
    String              _detailedString;

    bool                _canKeepRunning;
    bool                _keepRunning = false;
};


}



#endif