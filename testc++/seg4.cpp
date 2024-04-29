#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

struct Segment {
    int type;
    int startIndex;
    int endIndex;
    int length;
};

class SegmentManager {
public:
    void fun_first(int index, int type) {
        if (segments.empty()) {
            segments.push_back({type, index, index, 1});
        } else {
            if (segments.back().type == type) {
                segments.back().endIndex = index;
                segments.back().length = segments.back().endIndex - segments.back().startIndex + 1;
            } else {
                segments.push_back({type, index, index, 1});
                typeToSegments[type].push_back(segments.size() - 1);
            }
        }
    }

    void fun_second(int index, int type) {
        segments.push_back({type, index, index, 1});
        typeToSegments[type].push_back(segments.size() - 1);
    }

    std::vector<Segment> findSegmentsByType(int type) {
        std::vector<Segment> segmentsOfType;
        for (const auto& segmentIndex : typeToSegments[type]) {
            segmentsOfType.push_back(segments[segmentIndex]);
        }
        return segmentsOfType;
    }

private:
    std::vector<Segment> segments;
    std::unordered_map<int, std::vector<int>> typeToSegments;
};

int main() {
    SegmentManager segmentManager;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> typeDistribution(0, 1);

    int index = 0;
    int type = typeDistribution(gen);
    int typeCount = 0;
    while (index < 10000) {
        segmentManager.fun_first(index, type);
        typeCount++;

        if (typeCount % 5 == 0) {
            type = typeDistribution(gen);
        }

        if (typeCount % 10 == 0) {
            segmentManager.fun_second(index, type);
        }

        index++;
    }

    // Find all segments of type 1
    std::vector<Segment> segmentsOfType1 = segmentManager.findSegmentsByType(1);
    std::cout << "Segments of type 1:" << std::endl;
    for (const auto& segment : segmentsOfType1) {
        std::cout << "Type: " << segment.type << ", Start: " << segment.startIndex << ", End: " << segment.endIndex << ", Length: " << segment.length << std::endl;
    }

    return 0;
}

