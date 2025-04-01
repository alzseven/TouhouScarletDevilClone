#include "PathMaker.h"

FPOINT Lerp(const FPOINT& a, const FPOINT& b, float t) {
    return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
}

//FPOINT Segment::GetCurrentPos(float currentTime, FPOINT offset)
//{
//    if (currentTime <= startTime)
//        return { points.front().x + offset.x, points.front().y + offset.y };
//    if (currentTime >= endTime)
//        return { points.back().x + offset.x, points.back().y + offset.y };
//
//    float totalTime = endTime - startTime;
//    int numSeg = points.size() - 1;
//    float timerPerSeg = totalTime / numSeg;
//
//    int segIdx = (int)((currentTime - startTime) / timerPerSeg);
//    if (segIdx >= numSeg)
//        segIdx = numSeg - 1;
//
//    //ÁøÇà·ü
//    float t = (currentTime - (startTime + segIdx * timerPerSeg)) / timerPerSeg;
//    FPOINT localPos = Lerp(points[segIdx], points[segIdx + 1], t);
//    return { localPos.x + offset.x, localPos.y + offset.y };
//}
//
//FPOINT PathMaker::GetCurrentPos(float currentTime, FPOINT pos)
//{
//    for (auto& seg : segments) {
//        if (currentTime >= seg.endTime)
//        {
//            offset = pos;
//        }
//        if (currentTime >= seg.startTime && currentTime <= seg.endTime) {
//            return seg.GetCurrentPos(currentTime,offset);
//        }
//    }
//    if (!segments.empty() && (currentTime < segments.front().startTime))
//        return segments.front().points.front();
//    if (!segments.empty())
//        return segments.back().points.back();
//    return offset;
//}

FPOINT Segment::GetCurrentPos(float currentTime, FPOINT offset)
{
    if (currentTime <= startTime)
        return { points.front().x + offset.x, points.front().y + offset.y };
    if (currentTime >= endTime)
        return { points.back().x + offset.x, points.back().y + offset.y };

    float totalTime = endTime - startTime;
    int numSeg = points.size() - 1;
    float timerPerSeg = totalTime / numSeg;

    int segIdx = static_cast<int>((currentTime - startTime) / timerPerSeg);
    if (segIdx >= numSeg)
        segIdx = numSeg - 1;

    // ÁøÇà·ü t (0~1) °è»ê
    float t = (currentTime - (startTime + segIdx * timerPerSeg)) / timerPerSeg;
    FPOINT localPos = Lerp(points[segIdx], points[segIdx + 1], t);
    return { localPos.x + offset.x, localPos.y + offset.y };
}

FPOINT PathMaker::GetCurrentPos(float currentTime)
{
    if (currentIdx >= segments.size())
    {
        return SumOffset;
    }
    if (segments.empty())
        return offset;

    if (currentTime < segments.front().startTime) {
        return offset;
    }

    Segment& seg = segments[currentIdx];
    if (currentTime >= seg.startTime && currentTime <= seg.endTime) {
        return seg.GetCurrentPos(currentTime, SumOffset);
    }
    if (currentTime > seg.endTime) {
        SumOffset.x += seg.points.back().x;
        SumOffset.y += seg.points.back().y;
        currentIdx++;
    }
    

    return SumOffset;
}
