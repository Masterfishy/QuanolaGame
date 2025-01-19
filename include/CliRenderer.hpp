#pragma once

#include "IRenderer.hpp"

#include <fstream>
#include <memory>

/**
 * Renders the game in a CLI
 */
class CliRenderer : public IRenderer
{
  public:
    /**
     * Create a new CLI Renderer.
     */
    CliRenderer();

    /**
     * Destructor.
     */
    ~CliRenderer();

    /**
     * Render the given \c GameState in the CLI.
     * @param state The \c GameState to render.
     */
    void Render(const GameState& state) override;

  private:
    /**
     * Check if the given string is a positive integer.
     *
     * @param numberStr The string to check.
     * @return true     If the whole string represents a valid positive
     * integer.
     * @return false    If the whole string is not a valid positive integer.
     */
    bool IsPositiveInt(const std::string& numberStr);
};
