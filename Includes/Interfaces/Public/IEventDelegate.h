#pragma once

#include <SFML/Graphics.hpp>
#include "IDelegate.h"

using Scancode = sf::Keyboard::Scan::Scancode;

/// <summary>
/// Contains an IDelegate which is invoked when a specific window event is triggered.
/// </summary>
class EventDelegate
{
public:
#pragma region Constructor/Destructor
    EventDelegate(uptr<IDelegate<void>> _delegate) : eventDelegate(std::move(_delegate)) {}
    virtual ~EventDelegate() = default;
#pragma endregion

    inline virtual void ExecuteEvent(sf::Event _event) = 0;

    bool operator==(const EventDelegate& _other)
    {
        return Compare(_other);
    }

    bool operator!=(const EventDelegate& _other)
    {
        return !Compare(_other);
    }

protected:

    uptr<IDelegate<void>> eventDelegate;

    inline virtual bool Compare(const EventDelegate& _other) = 0;
};

/// <summary>
/// Inherits from EventDelegate
/// Simple event delegate that takes no parameters and return value.
/// It executes a member's method from TClass.
/// </summary>
/// <typeparam name="TClass">Class of the member method</typeparam>
template<class TClass>
class SimpleEventDelegate : public EventDelegate
{
public:
#pragma region Constructor/Destructor
    inline SimpleEventDelegate(TClass* _ref, void(TClass::* _function)()) :
        EventDelegate(std::make_unique<MemberDelegate<void, TClass>>(_ref, _function))
    {}

    ~SimpleEventDelegate() = default;
#pragma endregion

#pragma region Methods
    inline virtual void ExecuteEvent(sf::Event _event) override
    {
        if (!eventDelegate)
            return;

        eventDelegate->Invoke();
    }

protected:

    inline virtual bool Compare(const EventDelegate& _other) override
    {
        const SimpleEventDelegate<TClass>* _eventDelegate = static_cast<const SimpleEventDelegate<TClass>*>(&_other);
        if (!_eventDelegate)
            return false;

        return *_eventDelegate->eventDelegate == *eventDelegate;
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
class KeyDelegate : public SimpleEventDelegate<TClass>
{
public:
#pragma region Constructor/Destructor
    inline KeyDelegate(TClass* _ref, void (TClass::* _function)(), Scancode _key) :
        SimpleEventDelegate<TClass>(_ref, _function),
        key(_key)
    {}

    ~KeyDelegate() = default;
#pragma endregion

    inline virtual void ExecuteEvent(sf::Event _event) override final
    {
        if (_event.key.scancode == key)
            SimpleEventDelegate<TClass>::ExecuteEvent(_event);
    }

protected:

    Scancode key;

    inline virtual bool Compare(const EventDelegate& _other) override
    {
        const KeyDelegate<TClass>* _eventDelegate = static_cast<const KeyDelegate<TClass>*>(&_other);
        if (!_eventDelegate)
            return false;

        return SimpleEventDelegate<TClass>::Compare(_other) && _eventDelegate->key == key;
    }
};