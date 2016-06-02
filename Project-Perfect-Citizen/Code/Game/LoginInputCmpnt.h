#pragma once

#include "../Engine/inputComponent.h"

namespace ppc {

    class WindowInterface;
    class TextBoxInputComponent;
    class Event;

class LoginInputCmpnt : public InputComponent {
public:

    LoginInputCmpnt(WindowInterface& ownerWin, TextBoxInputComponent* textBox = nullptr);

    void setTextBox(TextBoxInputComponent& tBox);

    bool registerInput(Event ev) override;

    void loadSave();

    bool findSave();

    void createSave();

    friend bool create_save(LoginInputCmpnt*, ppc::Event);

private:

    WindowInterface* currWindow_;

    TextBoxInputComponent* textBox_;

};


bool registerLogIn(LoginInputCmpnt*, ppc::Event);


};
