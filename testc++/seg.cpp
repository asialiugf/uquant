#include <iostream>
#include <unordered_map>
#include <vector>

void recordSegments(std::unordered_map<int, std::vector<int>>& segments, int index, int type) {
    if (segments.find(type) == segments.end()) {
        segments[type] = {index};
    } else {
        if (segments[type].back() == index - 1) {
            segments[type].back() = index;
        } else {
            segments[type].push_back(index);
        }
    }
}

int main() {
    std::unordered_map<int, std::vector<int>> segments;
    
    for (int i = 0; i < 10000; i++) {
        // Execute the function with different types at different indices
        // For example:
        int type = i % 3; // Example: alternate between types 0, 1, and 2
        recordSegments(segments, i, type);
    }
    
    // Print the recorded segments
    for (const auto& segment : segments) {
        std::cout << "Type " << segment.first << " segments: ";
        for (int i = 0; i < segment.second.size(); i += 2) {
            std::cout << "[" << segment.second[i] << ", " << segment.second[i + 1] << "] ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}

