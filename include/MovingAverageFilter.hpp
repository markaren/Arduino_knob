
#ifndef ARDUINO_KNOB_MOVINGAVERAGEFILTER_HPP
#define ARDUINO_KNOB_MOVINGAVERAGEFILTER_HPP

#include <vector>

class MovingAverageFilter {

public:
    explicit MovingAverageFilter(int size) : windowSize(size) {}

    void update(float newValue) {
        values.push_back(newValue);
        if (values.size() > windowSize) {
            values.erase(values.begin());
        }
    }

    [[nodiscard]] float value() const {

        if (values.empty()) {
            return 0;
        }

        float sum{0};
        for (float value: values) {
            sum += value;
        }
        return sum / static_cast<float>(values.size());
    }

private:
    std::vector<float> values;
    int windowSize;
};

#endif//ARDUINO_KNOB_MOVINGAVERAGEFILTER_HPP
