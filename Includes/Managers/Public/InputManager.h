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
    std::unordered_map<sf::Event::EventType, std::vector<uptr<IEventDelegate>>> delegates;

public:

    InputManager() = default;
    ~InputManager() = default;
    

    template<class TClass>
    inline void BindEvent(sf::Event::EventType _type, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<SimpleEventDelegate<TClass>>(_class, _function));
    }

    template<class TClass>
    inline void BindKeyEvent(sf::Event::EventType _type, Scancode _key, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<KeyDelegate<TClass>>(_class, _function, _key));
    }

    void ListenEvents(sf::RenderWindow& window);
};