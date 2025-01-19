#pragma once

#include "Event.hpp"

// Forward declarations
class Node;
class Option;
struct GameState;
// end

class IRenderer
{
  public:
    /**
     * Destructor.
     */
    virtual ~IRenderer() = default;

    /**
     * Delete the copy operations to prevent copying of the interface.
     * This prevents object slicing.
     * Object slicing is when fields/methods of a derived class not in the
     * interface do not get copied.
     */
    IRenderer(const IRenderer&) = delete;
    IRenderer& operator=(const IRenderer&) = delete;

    //! @brief Render the given \c GameState.
    //! @param state The \c GameState to Render.
    virtual void Render(const GameState& state) = 0;

    /**
     * The OnNext event.
     */
    Event<void()> OnNextEvent;

    /**
     * The OnOption event.
     */
    Event<void(const Option&)> OnOptionEvent;

  protected:
    //! Define protected constructor to prevent instantiation of this class,
    //! but enable implementing classes to call this constructor.
    IRenderer() = default;
};
