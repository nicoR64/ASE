#pragma once

#include <vector>

/**
 * @class Package
 * @brief Represents a single package or task in a dependency graph.
 *
 * This class stores all timing information related to a package, such as its duration,
 * dependencies, and calculated start/finish times according to the Critical Path Method (CPM).
 */
class Package {
public:
    /**
     * @brief A constant representing an unset time value.
     */
    static constexpr int UNSET_TIME = -1;

    /**
     * @brief Constructs a Package.
     * @param id The unique identifier for the package.
     * @param duration The time required to complete the package.
     * @param dependencies A vector of IDs of packages that must be completed before this one can start.
     */
    Package(int id, int duration, const std::vector<int>& dependencies);

    int get_id() const { return id; }
    int get_earliest_start() const { return earliest_start; }
    int get_earliest_finish() const { return earliest_finish; }
    int get_latest_start() const { return latest_start; }
    int get_latest_finish() const { return latest_finish; }
    int get_duration() const { return duration; }
    int get_slack() const { return slack; }
    const std::vector<int>& get_dependencies() const { return dependencies; }

    /**
     * @brief Sets the earliest start time and calculates the earliest finish time.
     * @param start The earliest possible start time for this package.
     */
    void set_earliest_start(int start);

    /**
     * @brief Sets the latest finish time and calculates the latest start time.
     * @param finish The latest possible finish time for this package.
     */
    void set_latest_finish(int finish);

    /**
     * @brief Calculates the slack time for this package.
     * Slack is the duration a package can be delayed without affecting the project's finish time.
     * This should be called after both earliest and latest times have been computed.
     */
    void calculate_slack();

    /**
     * @brief Displays all information about the package to the console.
     */
    void display_info();

private:
    /**
     * @brief Initializes the earliest start time for packages with no dependencies.
     * These are considered starting points in the project graph.
     */
    void handle_start_package();

    int id{ UNSET_TIME };
    int duration{ 0 };
    std::vector<int> dependencies;

    int earliest_start{ UNSET_TIME };
    int earliest_finish{ UNSET_TIME };
    int latest_start{ UNSET_TIME };
    int latest_finish{ UNSET_TIME };
    int slack{ UNSET_TIME };
};