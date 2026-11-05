#pragma once
#include <algorithm>

namespace ClipboardPlacement {
struct Rect { int left, top, right, bottom; };
// Coordinates and size are physical pixels, including per-monitor DPI scaling.
inline Rect NearCaret(int x, int bottom, int width, int height, Rect work,
                      int gap, int caretHeight, bool centered)
{
    width = (std::max)(1, (std::min)(width, work.right - work.left - 2 * gap));
    height = (std::max)(1, (std::min)(height, work.bottom - work.top - 2 * gap));
    if (centered) x -= width / 2;
    int y = bottom + gap;
    if (y + height > work.bottom - gap) y = bottom - caretHeight - gap - height;
    x = (std::max)(work.left + gap, (std::min)(x, work.right - gap - width));
    y = (std::max)(work.top + gap, (std::min)(y, work.bottom - gap - height));
    return { x, y, x + width, y + height };
}
}
