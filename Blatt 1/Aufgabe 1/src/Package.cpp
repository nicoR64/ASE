#include "Package.h"
#include <iostream>

Package::Package(int id, int duration, const std::vector<int>& dependencies)
    : id(id), duration(duration), dependencies(dependencies) {
    if (this->dependencies.empty()) {
        handle_start_package();
    }
}

Package::Package(int id, int duration, const std::vector<int>& dependencies, int latest_finish)
    : id(id), duration(duration), dependencies(dependencies) {
    set_latest_finish(latest_finish);
    if (this->dependencies.empty()) {
        handle_start_package();
    }
}

void Package::handle_start_package() {
    set_earliest_start(0);
}

void Package::set_earliest_start(int start) {
    earliest_start = start;
    if (earliest_start != UNSET_TIME) {
        earliest_finish = earliest_start + duration;
    }
}

void Package::set_latest_finish(int finish) {
    latest_finish = finish;
    if (latest_finish != UNSET_TIME) {
        latest_start = latest_finish - duration;
    }
}

void Package::calculate_slack() {
    if (latest_start != UNSET_TIME && earliest_start != UNSET_TIME) {
        slack = latest_start - earliest_start;
    }
}

void Package::display_info() {
    std::cout
        << "Package("
        << "ID: " << id
        << ", ES: " << earliest_start
        << ", EF: " << earliest_finish
        << ", LS: " << latest_start
        << ", LF: " << latest_finish
        << ", Duration: " << duration
        << ", Slack: " << slack
        << ", Dependencies: ";

    if (dependencies.empty()) {
        std::cout << "[]";
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < dependencies.size(); ++i) {
            std::cout << dependencies[i] << (i == dependencies.size() - 1 ? "" : ", ");
        }
        std::cout << "]";
    }
    std::cout << ")" << std::endl;
}