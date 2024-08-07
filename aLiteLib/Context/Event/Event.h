//
// Created by Bryan on 07/08/2024.
//

#ifndef ALITE_EVENT_H
#define ALITE_EVENT_H

#include <stdexcept>
#include <functional>
#include <unordered_map>

namespace Context::Event {

    using ListenerID_t = uint64_t;

    template<class ... ArgTypes>
    class Event {

    public:

        using f_callback_t = std::function<void (ArgTypes ...)>;

        Event() = default;
        virtual ~Event() = default;

        ListenerID_t AddListener(f_callback_t func);
        void RemoveListener(ListenerID_t ID);
        uint64_t ListenerCount();
        void Invoke(ArgTypes ... p_args);

    private:

        std::unordered_map <ListenerID_t, f_callback_t> m_callback_map;

        ListenerID_t m_nextID = 1;

    };

    template<class... ArgTypes>
    void Event<ArgTypes...>::Invoke(ArgTypes... p_args) {

        for (const auto &[_, func] : m_callback_map) {

            func(p_args...);

        }

    }

    template<class... ArgTypes>
    ListenerID_t Event<ArgTypes...>::AddListener(Event::f_callback_t func) {

        ListenerID_t ID = m_nextID ++;

        m_callback_map.insert({
            ID,
            func
        });

        return ID;

    }

    template<class... ArgTypes>
    uint64_t Event<ArgTypes...>::ListenerCount() {
        return m_callback_map.size();
    }

    template<class... ArgTypes>
    void Event<ArgTypes...>::RemoveListener(ListenerID_t ID) {
        auto Pos = m_callback_map.find(ID);
        if (Pos == m_callback_map.end()) {
            throw std::runtime_error("Do Not Find Listener");
        }
        m_callback_map.erase(Pos);
    }



}


#endif //ALITE_EVENT_H
