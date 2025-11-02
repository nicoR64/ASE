#pragma once

#include <unordered_map>

class Package;
/**
Maximilian Peresunchak (st152466@stud.uni-stuttgart.de)
Nico Reng (st188620@stud.uni-stuttgart.de)
Viorel Tsigos (st188085@stud.uni-stuttgart.de)
Philip Reimann (st182312@stud.uni-stuttgart.de)
Christian Keller (st166512@stud.uni-stuttgart.de)
Florian Frank  (st@stud.uni-stuttgart.de)
Johannes Heugel (st@stud.uni-stuttgart.de)
Maysaa Abualqumboz (st@stud.uni-stuttgart.de)
Benedikt Wachmer (st177118@stud.uni-stuttgart.de)
Miles Holl (st@stud.uni-stuttgart.de)
*/

/**
 * @class CriticalPathFinder
 * @brief Calculates timing information for a network of dependent packages.
 *
 * This class implements the Critical Path Method (CPM) to determine the earliest
 * and latest start/finish times for all packages in a project, as well as their slack time.
 * It operates on a map of packages provided during construction.
 *
 * @note This class does not take ownership of the Package pointers it manages.
 * The caller is responsible for the lifecycle of the Package objects.
 */
class CriticalPathFinder {
public:
    /**
     * @brief Constructs a CriticalPathFinder.
     * @param package_map A map of package IDs to Package pointers representing the project.
     */
    explicit CriticalPathFinder(const std::unordered_map<int, Package*>& package_map);

    /**
     * @brief Runs the complete CPM calculation process.
     * This involves a forward pass to calculate earliest times, a backward pass
     * for latest times, and finally the slack calculation for each package.
     */
    void complete();

private:
    /**
     * @brief Performs the forward pass of the CPM algorithm.
     * Iteratively calculates the earliest start and finish times for all packages
     * until all values have been stabilized.
     */
    void complete_earliest();

    /**
     * @brief Performs the backward pass of the CPM algorithm.
     * Iteratively calculates the latest start and finish times for all packages
     * until all values have been stabilized.
     */
    void complete_latest();

    /**
     * @brief Updates a package's earliest start time based on its dependencies.
     * A package can only start after all its dependencies have finished. This method
     * ensures its earliest start time reflects the latest of its dependencies' earliest finish times.
     * @param package The package to update.
     * @return True if the package's earliest start time was changed, false otherwise.
     */
    bool update_earliest_start(Package& package);

    /**
     * @brief Updates a dependency's latest finish time based on the package that depends on it.
     * A dependency must be finished before the dependent package's latest start time. This
     * method propagates this constraint backward through the graph.
     * @param package The package whose dependencies will be updated.
     * @return True if any dependency's latest finish time was changed, false otherwise.
     */
    bool update_dependencies_latest_finish(Package& package);

    /// A map of package IDs to non-owning pointers of the packages.
    const std::unordered_map<int, Package*>& package_map;
};