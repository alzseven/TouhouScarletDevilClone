#pragma once
#include "config.h"

FPOINT Lerp(const FPOINT& a, const FPOINT& b, float t) {
    return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
}

struct Segment {
    float startTime;
    float endTime; 
    std::vector<FPOINT> points; 
    FPOINT offset = { 0.0f, 0.0f };
    FPOINT GetCurrentPos(float currentTime);
};


class PathMaker {
public:
    std::vector<Segment> segments;

    FPOINT GetCurrentPos(float currentTime);
};

