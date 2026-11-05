#include "../src/ClipboardPlacement.h"
#include <cassert>
#include <cstdio>
using namespace ClipboardPlacement;
int main() {
    const Rect primary{0,0,1920,1040};
    auto below = NearCaret(400,200,380,480,primary,8,20,false);
    assert(below.left == 400 && below.top == 208);
    auto above = NearCaret(400,950,380,480,primary,8,20,false);
    assert(above.bottom == 922);
    auto edge = NearCaret(1900,950,380,480,primary,8,20,false);
    assert(edge.right == 1912 && edge.bottom < 950);
    auto scaled = NearCaret(1800,1000,570,720,primary,12,30,false);
    assert(scaled.right <= 1908 && scaled.top >= 12);
    const Rect secondary{-1920,-200,0,840};
    auto negative = NearCaret(-1900,700,380,480,secondary,8,20,false);
    assert(negative.left == -1900 && negative.bottom == 672);
    auto large = NearCaret(0,0,3000,3000,secondary,8,20,false);
    assert(large.left >= -1912 && large.top >= -192 && large.right <= -8 && large.bottom <= 832);
    auto centered = NearCaret(500,200,380,480,primary,8,20,true);
    assert(centered.left == 310);
    puts("PASS: 7 caret placement cases (below, above, edges, DPI, negative monitor, oversized, centered)");
}
