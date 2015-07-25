/*
 * Credit: thesaint (http://codereview.stackexchange.com/users/9978/thesaint)
 * http://codereview.stackexchange.com/questions/7786/c-like-class-properties
 */

# pragma once

#include <boost/function.hpp>

template<class T, class TGetter = boost::function<T& ()>, class TSetter = boost::function<void (const T&)>>
struct obj_attr
{
    template<class X, class Y, class Z> friend struct obj_attr; // makes this a friend to all instantiations
private:
    TGetter m_Getter;
    TSetter m_Setter;
    T m_ValueIfNoAccessors;

    T& get()
    {
        if(!m_Getter.empty())
            return m_Getter();
        else
            return m_ValueIfNoAccessors;
    }

    const T& get() const
    {
        if(!m_Getter.empty())
            return m_Getter();
        else
            return m_ValueIfNoAccessors;
    }

    void set(const T& newValue)
    {
        if(!m_Setter.empty())
            m_Setter(newValue);
        else
            m_ValueIfNoAccessors = newValue;
    }

    typename typedef obj_attr<T, TGetter, TSetter> prop_type;

public:
    obj_attr() : m_Getter(), m_Setter(), m_ValueIfNoAccessors() { set(T()); }
    obj_attr(T initValue) : m_Getter(), m_Setter(), m_ValueIfNoAccessors() { set(initValue); }
    obj_attr(TGetter getter) : m_Getter(getter), m_Setter(), m_ValueIfNoAccessors() { set(T()); }
    obj_attr(TGetter getter, TSetter setter) : m_Getter(getter), m_Setter(setter), m_ValueIfNoAccessors() { set(T()); }

    operator T() { return get(); }

    template<class X, class Y, class Z>
    prop_type& operator=(obj_attr<X,Y,Z>& other)
    {
        set(other.get());

        return *this;
    }

    template<class TI>
    prop_type& operator=(const TI& other)
    {
        set(other);

        return *this;
    }

    /*
        This operator was introduced for simplifying access to call operators:

        PROPERTY<boost::function<int (int)>> myFunc;

        myFunc(345); // ERROR!
        myFunc()(345); // now is valid...
    */
    T& operator()() { return get(); }
    const T& operator()() const { return get(); }

    /*
        Beaware of the fact, that anyone really wanting to change the backing value
        of a property sure can, by simply doing:

        PROPERTY<T> myProp;
        T* myRef = myProp.operator->();

        So do not rely on Getter/Setter safety in case of any security critical scenario.
    */
    T* operator->() { return &get(); }
    const T* operator->() const { return &get(); }

    template<class TI> prop_type& operator/=(TI newValue) { set(get() / newValue); return *this; }
    template<class TI> prop_type& operator+=(TI newValue) { set(get() + newValue); return *this; }
    template<class TI> prop_type& operator-=(TI newValue) { set(get() - newValue); return *this; }
    template<class TI> prop_type& operator*=(TI newValue) { set(get() * newValue); return *this; }

    template<class TI> auto operator/(TI newValue) const -> decltype(T() / TI()) { return get() / newValue; }
    template<class TI> auto operator+(TI newValue) const -> decltype(T() + TI()) { return get() + newValue; }
    template<class TI> auto operator-(TI newValue) const -> decltype(T() - TI()) { return get() - newValue; }
    template<class TI> auto operator*(TI newValue) const -> decltype(T() * TI()) { return get() * newValue; }
};
