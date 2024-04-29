#include <iostream>
#include <map>
#include <vector>

void recordSegments(
    std::map<int, std::pair<int, int>>& segments,
    int index
) {
    if (segments.empty()) {
        segments[index] = {index, index};
    } else {
        if (segments.rbegin()->second.second == index - 1) {
            segments.rbegin()->second.second = index;
        } else {
		std::cout << " index: " << index << " ---- " << std::endl;
            segments[index] = {index, index};
        }
    }
}

int main() {
    std::map<int, std::pair<int, int>> segments;
    std::map<int, std::vector<std::pair<int, int>>> typeSegments;
    std::map<int, std::vector<int>> typeOrder;
    
    for (int i = 0; i < 10000; i++) {
        recordSegments(segments, i);
        int type = i % 2; // Assume type is 0 or 1
        typeSegments[type].push_back(segments[i]);
        typeOrder[type].push_back(i);
    }
    
    // Find the 10th segment
    int index1 = segments.begin()->first + 9; // Get the 10th index
    std::pair<int, int> segment1;
    for (const auto& seg : segments) {
        if (seg.second.first <= index1 && index1 <= seg.second.second) {
            segment1 = seg.second;
            break;
        }
    }
    std::cout << "The 10th segment is [" << segment1.first << ", " << segment1.second << "]" << std::endl;
    
    // Find the 12th segment of type 1
    int index2 = typeOrder[1][11]; // Get the 12th index of type 1
    std::pair<int, int> segment2;
    for (const auto& seg : typeSegments[1]) {
        if (seg.first <= index2 && index2 <= seg.second) {
            segment2 = seg;
            break;
        }
    }
    std::cout << "The 12th segment of type 1 is [" << segment2.first << ", " << segment2.second << "]" << std::endl;
    
    // Find the 13th segment of type 0
    int index3 = typeOrder[0][12]; // Get the 13th index of type 0
    std::pair<int, int> segment3;
    for (const auto& seg : typeSegments[0]) {
        if (seg.first <= index3 && index3 <= seg.second) {
            segment3 = seg;
            break;
        }
    }
    std::cout << "The 13th segment of type 0 is [" << segment3.first << ", " << segment3.second << "]" << std::endl;
    
    return 0;
}

