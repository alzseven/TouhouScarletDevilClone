#pragma once
#include "config.h"



struct Segment {
    float startTime;
    float endTime; 
    std::vector<FPOINT> points; 
    FPOINT GetCurrentPos(float currentTime,FPOINT offset);
};


class PathMaker {
public:
    std::vector<Segment> segments;
    FPOINT offset = { 0,0 };
    int currentIdx = 0;
    FPOINT SumOffset = { 0,0 };
    FPOINT GetCurrentPos(float currentTime);
    inline void SetOffset(FPOINT pos) 
    { 
        offset = pos; 
        currentIdx = 0;
        SumOffset = pos;
    }
};

