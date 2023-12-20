#pragma once

#include <SFML/Graphics.hpp>
#include "IDelegate.h"

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Specific interface of IDelegate that takes an event as parameter of his ExecuteEvent method.
/// </summary>
class IEventDelegate : public IDelegate<void>
{
public:

    virtual ~IEventDelegate() = default;

    inline virtual void ExecuteEvent(sf::Event _event) = 0;

    inline virtual void Invoke() const = 0;
};

/// <summary>
/// Inherits from IEventDelegate
/// Simple event delegate that takes no parameters and return value.
/// It executes a member's method from TClass.
/// </summary>
/// <typeparam name="TClass">Class of the member method</typeparam>
template<class TClass>
class SimpleEventDelegate : public IEventDelegate
{
    typedef void (TClass::* Callback)();

    TClass* reference = nullptr;

    Callback callback = nullptr;

public:

#pragma region Methods
    inline SimpleEventDelegate(TClass* _ref, Callback _function)
    {
        reference = _ref;
        callback = _function;
    }

    inline virtual void ExecuteEvent(sf::Event _event)
    {
        Invoke();
    }

    inline virtual void Invoke() const override
    {
        if (!reference || !callback)
            return;

        (reference->*callback)();
    }
#pragma endregion
};

/// <summary>
/// Inherits from IEventDelegate.
/// DSpecial delegate that handles event triggered by a key action (key pressed or released).
/// It executes a member's method from TClass with no parameters and no return type.
/// </summary>
/// <typeparam name="TClass">Class of the member method</typeparam>
template<class TClass>
class KeyDelegate : public IEventDelegate
{
    typedef void (TClass::* Callback)();

    TClass* reference = nullptr;

    Callback callback = nullptr;

    Scancode key;

public:

    inline KeyDelegate(TClass* _ref, Callback _function, Scancode _key)
    {
        reference = _ref;
        callback = _function;
        key = _key;
    }

    inline virtual void ExecuteEvent(sf::Event _event) override
    {
        if (_event.key.scancode == key)
            Invoke();
    }

    inline virtual void Invoke() const override
    {
        if (!reference || !callback)
            return;

        (reference->*callback)();
    }
};