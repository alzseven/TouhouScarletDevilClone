#include "PathMaker.h"

FPOINT Segment::GetCurrentPos(float currentTime)
{
    if (currentTime <= startTime)
        return { points.front().x + offset.x, points.front().y + offset.y };
    if (currentTime >= endTime)
        return { points.back().x + offset.x, points.back().y + offset.y };

    float totalTime = endTime - startTime;
    int numSeg = points.size() - 1;
    float timerPerSeg = totalTime / numSeg;

    int segIdx = (int)((currentTime - startTime) / timerPerSeg);
    if (segIdx >= numSeg)
        segIdx = numSeg - 1;

    //ÁøÇà·ü
    float t = (currentTime - (startTime + segIdx * timerPerSeg)) / timerPerSeg;
    FPOINT localPos = Lerp(points[segIdx], points[segIdx + 1], t);
    return { localPos.x + offset.x, localPos.y + offset.y };
}

FPOINT PathMaker::GetCurrentPos(float currentTime)
{
    for (auto& seg : segments) {
        if (currentTime >= seg.startTime && currentTime <= seg.endTime) {
            return seg.GetCurrentPos(currentTime);
        }
    }
    if (!segments.empty() && (currentTime < segments.front().startTime))
        return segments.front().points.front();
    if (!segments.empty())
        return segments.back().points.back();
    return { 0.0f, 0.0f };
}