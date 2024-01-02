#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include "IEventDelegate.h"

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Handles all window events in the game, including key events.
/// </summary>
class InputManager
{
public:

#pragma region Constructor/Destructor
    InputManager() = default;
    ~InputManager() = default;
#pragma endregion
    
#pragma region PublicMethods
    /// <summary>
    /// Add a delegate for a specific event. 
    /// </summary>
    /// <typeparam name="TClass">Class of the method to invoke.</typeparam>
    /// <param name="_type">Type of the event.</param>
    /// <param name="_class">Instance of TClass</param>
    /// <param name="_function">Method of TClass to invoke when event is triggered.</param>
    template<class TClass>
    inline void AddEvent(const sf::Event::EventType& _type, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<SimpleEventDelegate<TClass>>(_class, _function));
    }

    /// <summary>
    /// Remove a delegate for the corresponding event if it exists.
    /// </summary>
    /// <typeparam name="TClass">Class of the method to invoke.</typeparam>
    /// <param name="_type">Type of the event.</param>
    /// <param name="_class">Instance of TClass</param>
    /// <param name="_function">Method of TClass to invoke when event is triggered.</param>
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

    /// <summary>
    /// Specific version of AddEvent method for key events such as pressing or releasing a key.
    /// </summary>
    /// <typeparam name="TClass">Class of the method to invoke.</typeparam>
    /// <param name="_type">Type of the event.</param>
    /// <param name="_key">Key to press or release.</param>
    /// <param name="_class">Instance of TClass</param>
    /// <param name="_function">Method of TClass to invoke when event is triggered.</param>
    template<class TClass>
    inline void AddKeyEvent(const sf::Event::EventType& _type, Scancode _key, TClass* _class, void(TClass::* _function)())
    {
        delegates[_type].push_back(std::make_unique<KeyDelegate<TClass>>(_class, _function, _key));
    }

    /// <summary>
    /// Specific version of RemoveEvent method for key events such as pressing or releasing a key.
    /// </summary>
    /// <typeparam name="TClass">Class of the method to invoke.</typeparam>
    /// <param name="_type">Type of the event.</param>
    /// <param name="_key">Key to press or release.</param>
    /// <param name="_class">Instance of TClass</param>
    /// <param name="_function">Method of TClass to invoke when event is triggered.</param>
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

    /// <summary>
    /// Check if any event was triggered, if true then invokes all delegates binded to this window event.
    /// </summary>
    /// <param name="window">Game window.</param>
    void ListenEvents(sf::RenderWindow& window);
#pragma endregion

private:

    /// <summary>
    /// Map of events and the delegates it needs to invoke when the corresponding event is triggered.
    /// </summary>
    std::unordered_map<sf::Event::EventType, std::vector<uptr<EventDelegate>>> delegates;
};