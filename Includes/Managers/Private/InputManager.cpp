#include "InputManager.h"

void InputManager::ListenEvents(sf::RenderWindow& _window)
{
    sf::Event _event;

    while (_window.pollEvent(_event))
    {
        auto _it = delegates.find(_event.type);
        if (_it == delegates.end())
            return;

        std::vector<uptr<IEventDelegate>>& _delegates = delegates[_event.type];
        for (uptr<IEventDelegate>& _delegate : _delegates)
            _delegate->ExecuteEvent(_event);
    }
}
