#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include "IEventDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

class InputManager
{
    std::unordered_map<sf::Event::EventType, std::vector<uptr<EventDelegate>>> delegates;

public:

    InputManager() = default;
    ~InputManager() = default;
    

    template<class TClass>
    inline void AddEvent(const sf::Event::EventType& _type, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<SimpleEventDelegate<TClass>>(_class, _function));
    }

    template<class TClass>
    inline void RemoveEvent(const sf::Event::EventType& _type, TClass* _class, void(TClass::* _function)())
    {
        uptr<SimpleEventDelegate<TClass>> _temp = std::make_unique<SimpleEventDelegate<TClass>>(_class, _function);

        // Use erase-remove idiom.
        delegates[_type].erase(std::remove_if(delegates[_type].begin(), delegates[_type].end(),
            [&_temp](uptr<EventDelegate>& _delegate)
            {
                return *_delegate == *_temp;
            }
        ), delegates[_type].end());
    }

    template<class TClass>
    inline void AddKeyEvent(const sf::Event::EventType& _type, Scancode _key, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<KeyDelegate<TClass>>(_class, _function, _key));
    }

    template<class TClass>
    inline void RemoveKeyEvent(const sf::Event::EventType& _type, Scancode _key, TClass* _class, void(TClass::* _function)())
    {
        uptr<KeyDelegate<TClass>> _temp = std::make_unique<KeyDelegate<TClass>>(_class, _function, _key);

        // Use erase-remove idiom.
        delegates[_type].erase(std::remove_if(delegates[_type].begin(), delegates[_type].end(),
            [&_temp](uptr<EventDelegate>& _delegate)
            {
                return *_delegate == *_temp;
            }
        ), delegates[_type].end());
    }

    void ListenEvents(sf::RenderWindow& window);
};