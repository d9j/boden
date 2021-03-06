#include <bdn/ui/TextField.h>
#include <bdn/ui/ViewUtilities.h>

namespace bdn::ui
{
    namespace detail
    {
        VIEW_CORE_REGISTRY_IMPLEMENTATION(TextField)
    }

    TextField::TextField(std::shared_ptr<ViewCoreFactory> viewCoreFactory) : View(std::move(viewCoreFactory))
    {
        detail::VIEW_CORE_REGISTER(TextField, View::viewCoreFactory());
    }

    void TextField::submit()
    {
        SubmitEvent event(shared_from_this());
        onSubmit().notify(event);
    }

    Notifier<const SubmitEvent &> &TextField::onSubmit() { return _onSubmit; }

    void TextField::focus() { core<TextField::Core>()->focus(); }

    void TextField::bindViewCore()
    {
        View::bindViewCore();
        if (auto core = View::core<TextField::Core>()) {
            core->text.bind(text);
            core->autocorrectionType.bind(autocorrectionType);
            core->returnKeyType.bind(returnKeyType);
            core->placeholder.bind(placeholder);
            core->textInputType.bind(textInputType);
            core->obscureInput.bind(obscureInput);

            _submitCallbackReceiver = core->submitCallback.set([=]() {
                SubmitEvent evt(shared_from_this());
                onSubmit().notify(evt);
            });
        }
    }

    void TextField::updateFromStylesheet()
    {
        if (auto core = View::core<TextField::Core>()) {
            if (stylesheet->count("font")) {
                core->font = (Font)stylesheet->at("font");
            } else {
                core->font = Font();
            }
        }

        View::updateFromStylesheet();
    }
}
