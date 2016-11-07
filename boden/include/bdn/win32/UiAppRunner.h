#ifndef BDN_WIN32_UiAppRunner_H_
#define BDN_WIN32_UiAppRunner_H_

#include <bdn/AppRunnerBase.h>
#include <bdn/GenericDispatcher.h>
#include <bdn/ThreadRunnableBase.h>
#include <bdn/Thread.h>

#include <bdn/win32/util.h>
#include <bdn/win32/MessageWindowBase.h>

namespace bdn
{
namespace win32
{
    
    
class UiAppRunner : public AppRunnerBase, BDN_IMPLEMENTS IDispatcher
{
public:
	UiAppRunner( std::function< P<AppControllerBase>() > appControllerCreator, int showCommand);
    
	int entry();

	void initiateExitIfPossible(int exitCode) override;

    P<IDispatcher> getMainDispatcher() override
    {
        return this;
    }


    // IDispatcher methods
    
	void enqueue(
		std::function< void() > func,
		Priority priority = Priority::normal ) override;
    	
	void enqueueInSeconds(
		double seconds,
		std::function< void() > func,
		Priority priority = Priority::normal ) override;


	void createTimer(
		double intervalSeconds,
		std::function< bool() > func ) override;
    	
	
protected:
	void platformSpecificInit() override;

	void mainLoop() override;

    void disposeMainDispatcher() override;

private:

    enum class Message
    {
        /** Handle the next normal priority item*/
        executeNormalItem = WM_USER+100,

        /** An idle item was added to the queue.*/
        idleItemAdded,
    };

    class AppMessageWindow : public MessageWindowBase
    {
    public:
        AppMessageWindow(UiAppRunner* pAppRunnerWeak)
            : MessageWindowBase( "win32.UiAppRunner" )
        {
            _pAppRunnerWeak = pAppRunnerWeak;
        }
                
	    enum class Message
	    {
		    messageProcess = WM_USER+100
	    };

	    virtual void handleMessage(MessageContext& context, HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            // we know that the app runner object still exists because
            // it implements the message loop
            _pAppRunnerWeak->handleAppMessage(context, windowHandle, message, wParam, lParam);
        }

    private:
        UiAppRunner* _pAppRunnerWeak;
    };
    friend class AppMessageWindow;


    
    void handleAppMessage(MessageWindowBase::MessageContext& context, HWND windowHandle,  UINT message, WPARAM wParam, LPARAM lParam);
    
    bool executeAndRemoveItem( std::list< std::function<void()> >& queue, bool* pHaveMoreWaiting=nullptr );


    AppMessageWindow _messageWindow;


	int     _exitCode = 0;

    bool    _haveIdleItemsWaiting_MainThread = false;
    
    Mutex                                _queueMutex;
    std::list< std::function< void() > > _idleQueue;
    std::list< std::function< void() > > _normalQueue;


    P<Thread>                            _pTimedEventThread;
    P<GenericDispatcher>                 _pTimedEventThreadDispatcher;
};
  		

    
}    
}

#endif

