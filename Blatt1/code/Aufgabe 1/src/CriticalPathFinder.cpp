#include "CriticalPathFinder.h"
#include "Package.h"
#include <algorithm>

CriticalPathFinder::CriticalPathFinder(const std::unordered_map<int, std::shared_ptr<Package>>& package_map) : package_map(package_map) {}

void CriticalPathFinder::complete() {
    complete_earliest();
    complete_latest();
    for (const auto& pair : package_map) {
        pair.second->calculate_slack();
    }
}

void CriticalPathFinder::complete_earliest() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& pair : package_map) {
            if (update_earliest_start(*pair.second)) {
                changed = true;
            }
        }
    }
}

bool CriticalPathFinder::update_earliest_start(Package& package) {
    int max_dependency_finish_time = 0;
    for (int dependency_id : package.get_dependencies()) {
        auto dependency = package_map.at(dependency_id).get();
        if (dependency->get_earliest_finish() == Package::UNSET_TIME) {
            return false;
        }
        max_dependency_finish_time = std::max(max_dependency_finish_time, dependency->get_earliest_finish());
    }

    if (package.get_earliest_start() < max_dependency_finish_time) {
        package.set_earliest_start(max_dependency_finish_time);
        return true;
    }

    return false;
}

void CriticalPathFinder::complete_latest() {
    int project_finish_time = 0;
    for (const auto& pair : package_map) {
        project_finish_time = std::max(project_finish_time, pair.second->get_earliest_finish());
    }

    for (const auto& pair : package_map) {
        pair.second->set_latest_finish(project_finish_time);
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& pair : package_map) {
            if (update_dependencies_latest_finish(*pair.second)) {
                changed = true;
            }
        }
    }
}

bool CriticalPathFinder::update_dependencies_latest_finish(Package& package) {
    bool was_updated = false;
    int package_latest_start = package.get_latest_start();

    for (int dependency_id : package.get_dependencies()) {
        auto dependency = package_map.at(dependency_id).get();
        int dependency_latest_finish = dependency->get_latest_finish();

        if (dependency_latest_finish > package_latest_start) {
            dependency->set_latest_finish(package_latest_start);
            was_updated = true;
        }
    }
    return was_updated;
}