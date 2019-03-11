#pragma once

#include <bdn/WebView.h>
#include <bdn/WebViewCore.h>

#include <bdn/android/ViewCore.h>
#include <bdn/android/wrapper/WebView.h>

namespace bdn::android
{
    class WebViewCore : public ViewCore, virtual public bdn::WebViewCore
    {
      public:
        WebViewCore(const ContextWrapper &ctxt);
        virtual ~WebViewCore() = default;

        void loadURL(const String &url) override;

      private:
        wrapper::WebView _jWebView;
    };
}
