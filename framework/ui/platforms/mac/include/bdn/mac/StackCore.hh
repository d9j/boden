#pragma once

#import <bdn/mac/ViewCore.hh>

#include <bdn/Stack.h>
#include <bdn/StackCore.h>

#include <deque>

@class BdnBackButtonClickHandler;

namespace bdn::mac
{
    class StackCore : public ViewCore, public bdn::StackCore
    {
      public:
        StackCore();
        virtual ~StackCore();

        virtual void init() override;

      public:
        virtual void pushView(std::shared_ptr<View> view, String title) override;
        virtual void popView() override;
        virtual std::list<std::shared_ptr<View>> childViews() override;

      public:
        virtual void setLayout(std::shared_ptr<Layout> layout) override;

      private:
        void updateCurrentView();
        void reLayout();

      private:
        NSView *_navigationBar;
        NSButton *_backButton;
        NSTextField *_title;

        std::shared_ptr<View> _currentView;
        std::shared_ptr<FixedView> _container;

        struct StackEntry
        {
            std::shared_ptr<View> view;
            String title;
        };

        std::deque<StackEntry> _stack;

        BdnBackButtonClickHandler *_backButtonClickHandler;
    };
}
