#pragma once

#include <functional>
#include <mutex>
#include <vector>

/**
 * An event that objects can listen to and distribute info.
 *
 * @tparam SIGNATURE The signature of the callbacks of the event.
 */
template <typename SIGNATURE> class Event
{
  public:
    /**
     * @brief Construct a new Event object
     */
    Event() : mListeners(), mListenerMutex() {}

    /**
     * @brief Destroy the Event object
     */
    ~Event() {}

    /**
     * Add a listener to be invoked when the Event is tigerred.
     *
     * @param listener  The function callback to add to the Event.
     * @return Returns true if the function is added as a listener; false
     * otherwise.
     */
    bool AddListener(std::function<SIGNATURE> listener)
    {
        if (listener == nullptr)
        {
            return false;
        }

        std::lock_guard<std::mutex> lock(mListenerMutex);

        mListeners.emplace_back(std::move(listener));

        return true;
    }

    /**
     * Add a listener to be invoked when the Event is tigerred.
     *
     * @param listener  The function callback to add to the Event.
     * @return Returns true if the function is added as a listener; false
     * otherwise.
     */
    template <typename OBJ, typename... ARGS>
    bool AddListener(OBJ* obj, void (OBJ::*method)(ARGS... args))
    {
        return AddListener([=](ARGS... args) { (obj->*method)(args...); });
    }

    /**
     * Invoke the event with the given arguments.
     *
     * @tparam ARGS The type of the arguments to invoke listeners with.
     * @param ARGS  The arguments to invoke listeners with.
     */
    template <typename... ARGS> void Invoke(ARGS&&... args)
    {
        std::lock_guard<std::mutex> lock(mListenerMutex);

        for (auto& listener : mListeners)
        {
            listener(std::forward<ARGS>(args)...);
        }
    }

  private:
    /**
     * The collection of listeners to this event.
     */
    std::vector<std::function<SIGNATURE>> mListeners;

    /**
     * Mutex to protect read and write operations of the listener collection
     */
    std::mutex mListenerMutex;
};
