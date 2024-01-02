#pragma once

#include <iostream>
#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;

/// <summary>
/// Interface that executes something which can returns any type and takes any parameters.
/// </summary>
/// <typeparam name="Res">Return type of Invoke method.</typeparam>
/// <typeparam name="...Params">Parameters to use inside of the Invoke method.</typeparam>
template<typename Res, typename... Params>
class IDelegate
{
public:
    virtual ~IDelegate() = default;
    virtual Res Invoke(Params... _params) const = 0;

    bool operator==(IDelegate<Res, Params...>& _other)
    {
        return Compare(_other);
    }

    bool operator!=(IDelegate<Res, Params...>& _other)
    {
        return !(this == _other);
    }

protected:

    /// <summary>
    /// Compare two delegates. Override it in order to edit comparison conditions.
    /// </summary>
    /// <param name="_other">Other delegate to compare the current one with.</param>
    /// <returns>True if the two delegates are the same, else false.</returns>
    virtual bool Compare(const IDelegate<Res, Params...>& _other) = 0;

};

/// <summary>
/// Inherits from IDelegate interface.
/// Takes an instance of the templated class and method's pointer in constructor.
/// Then, call this member method through Invoke method.
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

    Function function;
    Class* owner;
#pragma endregion
public:
#pragma region Constructors
    MemberDelegate(nullptr_t) :
        owner(nullptr),
        function(nullptr)
    {}

    MemberDelegate(Class* _instance, Function _function) :
        owner(_instance),
        function(_function)
    {}
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

    bool operator==(const MemberDelegate<Res, Class>& _other)
    {
        return _other.owner == owner && _other.function == function;
    }

    bool operator!=(const MemberDelegate<Res, Class>& _other)
    {
        return !(this == _other);
    }
#pragma endregion

protected:

    /// <summary>
    /// Compare the owner and the function's pointer of the two delegates.
    /// </summary>
    /// <typeparam name="Res">Return type of the delegates</typeparam>
    /// <typeparam name="Class">Function's class of the delegates</typeparam>
    /// <typeparam name="...Params">Parameters of the function of each delegates.</typeparam>
    virtual bool Compare(const IDelegate<Res, Params...>& _other)
    {
        const MemberDelegate<Res, Class, Params...>* _delegate = static_cast<const MemberDelegate<Res, Class, Params...>*>(&_other);
        if (!_delegate)
            return false;

        return _delegate->owner == owner && _delegate->function == function;
    }
};

/// <summary>
/// Template struct that invokes each delegate of a vector passed in parameters.
/// This full template version takes into account the result type of the delegates.
/// </summary>
/// <param name="_delegates">Vector of delegates to invoke</param>
/// <param name="..._params">Parameters to give to each delegates</param>
/// <returns>Sum result of each delegates.</returns>
template<typename Res, typename... Params>
struct DelegateInvoker
{
    static Res Invoke(const std::vector<uptr<IDelegate<Res, Params...>>>& _delegates, Params... _params)
    {
        Res _result = Res();
        const size_t _size = _delegates.size();
        for (size_t i = 0; i < _size; ++i)
            _result += _delegates[i]->Invoke(_params...);

        return _result;
    }
};

/// <summary>
/// Partialized template version of the DelegateInvoker struct.
/// This does not take into account the result value and type.
/// </summary>
/// <param name="..._params">Parameters to give to each delegates</param>
template<typename... Params>
struct DelegateInvoker<void, Params...>
{
    static void Invoke(const std::vector<uptr<IDelegate<void, Params...>>>& _delegates, Params... _params)
    {
        const size_t _size = _delegates.size();
        for (size_t i = 0; i < _size; ++i)
            _delegates[i]->Invoke(_params...);
    }
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

    template<typename Class>
    void RemoveDynamic(Class* _instance, Res(Class::* _ptr)(Params... _params))
    {       
        uptr<MemberDelegate<Res, Class, Params...>> _temp = 
            std::make_unique<MemberDelegate<Res, Class, Params...>>(_instance, _ptr);

        // Use erase-remove idiom.
        delegates.erase(std::remove_if(delegates.begin(), delegates.end(), 
            [&_temp](uptr<IDelegate<Res, Params...>>& _delegate)
            {  
                return *_delegate == *_temp;
            }
        ), delegates.end());
    }

    Res Invoke(Params... _params) const override
    {
        return DelegateInvoker<Res, Params...>::Invoke(delegates, _params...);
    }
#pragma endregion

protected:

    virtual bool Compare(const IDelegate<Res, Params...>& _other)
    {
        return true;
    }
};

template<typename... Params>
using Action = ActionInternal<void, Params...>;