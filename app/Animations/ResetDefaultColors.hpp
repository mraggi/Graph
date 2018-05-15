#pragma once

#include "GraphApp.hpp"

inline void ResetDefaultColors()
{
    APP.ClearToDefaults();
    APP.default_edge_color = sf::Color(130, 0, 255, 220);
    APP.default_vertex_color = sf::Color(0, 200, 0, 220);
}
