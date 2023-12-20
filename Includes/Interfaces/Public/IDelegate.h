#pragma once

#include <iostream>
#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Interface thats executes something which can returns any type and takes any parameters.
/// </summary>
/// <typeparam name="Res">Return type of Invoke method.</typeparam>
/// <typeparam name="...Params">Parameters to use inside of the Invoke method.</typeparam>
template<typename Res, typename... Params>
class IDelegate
{
public:
    virtual ~IDelegate() = default;
    virtual Res Invoke(Params... _params) const = 0;
};

/// <summary>
/// Inherits from IDelegate interface.
/// Takes an instance of the templated class and method's pointer in constructor.
///  Then, call this member method through Invoke method.
/// </summary>
/// <typeparam name="Res">Return type of member method.</typeparam>
/// <typeparam name="Class">Member method's class</typeparam>
/// <typeparam name="...Params">All params of the member method</typeparam>
template<typename Res, typename Class, typename... Params>
struct MemberDelegate : public IDelegate<Res, Params...>
{
private:
#pragma region Properties
    typedef Res(Class::* Function)(Params... _params);

    Function function = nullptr;
    Class* owner = nullptr;
#pragma endregion
public:
#pragma region Constructors
    MemberDelegate(nullptr_t)
    {
        owner = nullptr;
        function = nullptr;
    }

    MemberDelegate(Class* _instance, Function _function)
    {
        owner = _instance;
        function = _function;
    }
#pragma endregion

#pragma region Methods
    Res Invoke(Params... _params) const override
    {
        if (!IsValid())
            throw std::exception("[MemberDelegate] => function or owner is null !");
        return (owner->*function)(_params...);
    }

    bool IsValid() const
    {
        return function != nullptr && owner != nullptr;
    }
#pragma endregion

#pragma region OperatorOverloads
    void operator=(Function _function)
    {
        function = _function;
    }

    void operator=(nullptr_t)
    {
        function = nullptr;
        owner = nullptr;
    }

    bool operator==(MemberDelegate<Res, Class>& _other)
    {
        return _other.owner == owner && _other.function == function;
    }

    bool operator!=(MemberDelegate<Res, Class>& _other)
    {
        return !(this != _other);
    }
#pragma endregion
};

/// <summary>
/// Inherits from IDelegate interface.
/// Similarly to C# Action, it follows a template version of a member method of any classes.
/// Also, it can register each listeners that needs to be called when firing this Action.
/// </summary>
/// <typeparam name="Res">Return type of each member's method, 
/// return type is always the same between each listeners.</typeparam>
/// <typeparam name="...Params">All parameters of each member's method, 
/// parameters are always the same between each listeners.</typeparam>
template<typename Res, typename... Params>
class ActionInternal : public IDelegate<Res, Params...>
{
private:
    typedef std::vector<uptr<IDelegate<Res, Params...>>> Delegates;
    Delegates delegates = Delegates();

public:

    ActionInternal(nullptr_t)
    {
        delegates = Delegates();
    }

    ~ActionInternal() = default;

#pragma region Methods
    template<typename Class>
    void AddDynamic(Class* _instance, Res(Class::* _ptr)(Params... _params))
    {
        uptr<MemberDelegate<Res, Class, Params...>> _delegate = 
            std::make_unique<MemberDelegate<Res, Class, Params...>>(_instance, _ptr);
        delegates.push_back(std::move(_delegate));
    }

    Res Invoke(Params... _params) const override
    {
        const size_t _size = delegates.size();
        if constexpr (std::is_same_v<Res, void>)
        {
            for (size_t i = 0; i < _size; ++i)
                delegates[i]->Invoke(_params...);

            return Res();
        }
        else
        {
            Res _result = Res();
            for (size_t i = 0; i < _size; ++i)
                _result = delegates[i]->Invoke(_params...);

            return _result;
        }
    }
#pragma endregion
};

template<typename... Params>
using Action = ActionInternal<void, Params...>;