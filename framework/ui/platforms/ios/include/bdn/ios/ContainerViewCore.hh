#pragma once

#include <bdn/ContainerView.h>
#include <bdn/ContainerViewCore.h>

#import <bdn/ios/ViewCore.hh>

@interface BodenUIView : UIView <UIViewWithFrameNotification>
@property(nonatomic, assign) std::weak_ptr<bdn::ios::ViewCore> viewCore;

- (void)layoutSubviews;
@end

namespace bdn::ios
{
    class ContainerViewCore : public ViewCore, virtual public bdn::ContainerViewCore
    {
      public:
        ContainerViewCore();
        ContainerViewCore(id<UIViewWithFrameNotification> view);

      protected:
        bool canAdjustToAvailableWidth() const override;

        bool canAdjustToAvailableHeight() const override;

        // ContainerViewCore interface
      public:
        virtual void addChildView(std::shared_ptr<View> child) override;
        virtual void removeChildView(std::shared_ptr<View> child) override;
        virtual std::list<std::shared_ptr<View>> childViews() override;

      private:
        std::list<std::shared_ptr<View>> _children;
    };
}
