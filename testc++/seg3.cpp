 #include <iostream>
#include <map>
#include <vector>

struct Segment {
    int type;
    int startIndex;
    int endIndex;
};

class SegmentManager {
public:
    void recordSegments(int index, int type) {
        std::cout << " in-- index : "<< index << std::endl;
        if (segments.empty()) {
            segments[index] = {type, index, index};
        } else {
            if (segments.rbegin()->second.endIndex == index - 1 && segments.rbegin()->second.type == type) {
                segments.rbegin()->second.endIndex = index;
            } else {
		    std::cout << "new -- index : "<< index << std::endl;
                segments[index] = {type, index, index};
            }
        }
    }

    Segment findSegment(int index) {
        Segment segment;
        for (const auto& seg : segments) {
            if (seg.second.startIndex <= index && index <= seg.second.endIndex) {
                segment = seg.second;
                break;
            }
        }
        return segment;
    }

private:
    std::map<int, Segment> segments;
};

int main() {
    SegmentManager segmentManager;

    for (int i = 0; i < 100; i++) {
        int type = i % 3; // Assume type is 0 or 1
        segmentManager.recordSegments(i, type);
    }

    // Find the 10th segment
    Segment segment1 = segmentManager.findSegment(9);
    std::cout << "The 10th segment is [" << segment1.startIndex << ", " << segment1.endIndex << "] of type " << segment1.type << std::endl;

    return 0;
}

