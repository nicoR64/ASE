#include "gtest/gtest.h"
#include "CriticalPathFinder.h"
#include "Package.h"
#include <memory>
#include <vector>

TEST(CriticalPath, PackageFromAssignment) {
    auto a01 = std::make_shared<Package>(1, 3, std::vector<int>{});
    auto a02 = std::make_shared<Package>(2, 4, std::vector<int>{});
    auto a03 = std::make_shared<Package>(3, 5, std::vector<int>{});
    auto a04 = std::make_shared<Package>(4, 4, std::vector<int>{ a01.get()->get_id() });
    auto a05 = std::make_shared<Package>(5, 9, std::vector<int>{ a01.get()->get_id() });
    auto a06 = std::make_shared<Package>(6, 4, std::vector<int>{ a02.get()->get_id() });
    auto a07 = std::make_shared<Package>(7, 2, std::vector<int>{ a03.get()->get_id() });
    auto a08 = std::make_shared<Package>(8, 4, std::vector<int>{ a04.get()->get_id() });
    auto a09 = std::make_shared<Package>(9, 2, std::vector<int>{ a06.get()->get_id() });
    auto a10 = std::make_shared<Package>(10, 3, std::vector<int>{ a06.get()->get_id() });
    auto a11 = std::make_shared<Package>(11, 3, std::vector<int>{ a07.get()->get_id() });
    auto a12 = std::make_shared<Package>(12, 2, std::vector<int>{ a05.get()->get_id(), a08.get()->get_id() });
    auto a13 = std::make_shared<Package>(13, 4, std::vector<int>{ a10.get()->get_id(), a11.get()->get_id() });
    auto a14 = std::make_shared<Package>(14, 7, std::vector<int>{ a09.get()->get_id(), a12.get()->get_id() });
    auto a15 = std::make_shared<Package>(15, 2, std::vector<int>{ a09.get()->get_id(), a12.get()->get_id() });
    auto a16 = std::make_shared<Package>(16, 4, std::vector<int>{ a13.get()->get_id(), a15.get()->get_id() });

    std::unordered_map<int, std::shared_ptr<Package>> package_map = {
        { a01.get()->get_id(), a01 }, { a02.get()->get_id(), a02 }, { a03.get()->get_id(), a03 }, { a04.get()->get_id(), a04 },
        { a05.get()->get_id(), a05 }, { a06.get()->get_id(), a06 }, { a07.get()->get_id(), a07 }, { a08.get()->get_id(), a08 },
        { a09.get()->get_id(), a09 }, { a10.get()->get_id(), a10 }, { a11.get()->get_id(), a11 }, { a12.get()->get_id(), a12 },
        { a13.get()->get_id(), a13 }, { a14.get()->get_id(), a14 }, { a15.get()->get_id(), a15 }, { a16.get()->get_id(), a16 }
    };

    CriticalPathFinder completer{ package_map };
    completer.complete();

    // A01
    EXPECT_EQ(0, a01.get()->get_earliest_start());
    EXPECT_EQ(3, a01.get()->get_earliest_finish());
    EXPECT_EQ(0, a01.get()->get_latest_start());
    EXPECT_EQ(3, a01.get()->get_latest_finish());
    EXPECT_EQ(0, a01.get()->get_slack());

    // A02
    EXPECT_EQ(0, a02.get()->get_earliest_start());
    EXPECT_EQ(4, a02.get()->get_earliest_finish());
    EXPECT_EQ(2, a02.get()->get_latest_start());
    EXPECT_EQ(6, a02.get()->get_latest_finish());
    EXPECT_EQ(2, a02.get()->get_slack());

    // A03
    EXPECT_EQ(0, a03.get()->get_earliest_start());
    EXPECT_EQ(5, a03.get()->get_earliest_finish());
    EXPECT_EQ(3, a03.get()->get_latest_start());
    EXPECT_EQ(8, a03.get()->get_latest_finish());
    EXPECT_EQ(3, a03.get()->get_slack());

    // A04
    EXPECT_EQ(3, a04.get()->get_earliest_start());
    EXPECT_EQ(7, a04.get()->get_earliest_finish());
    EXPECT_EQ(4, a04.get()->get_latest_start());
    EXPECT_EQ(8, a04.get()->get_latest_finish());
    EXPECT_EQ(1, a04.get()->get_slack());

    // A05
    EXPECT_EQ(3, a05.get()->get_earliest_start());
    EXPECT_EQ(12, a05.get()->get_earliest_finish());
    EXPECT_EQ(3, a05.get()->get_latest_start());
    EXPECT_EQ(12, a05.get()->get_latest_finish());
    EXPECT_EQ(0, a05.get()->get_slack());

    // A06
    EXPECT_EQ(4, a06.get()->get_earliest_start());
    EXPECT_EQ(8, a06.get()->get_earliest_finish());
    EXPECT_EQ(6, a06.get()->get_latest_start());
    EXPECT_EQ(10, a06.get()->get_latest_finish());
    EXPECT_EQ(2, a06.get()->get_slack());

    // A07
    EXPECT_EQ(5, a07.get()->get_earliest_start());
    EXPECT_EQ(7, a07.get()->get_earliest_finish());
    EXPECT_EQ(8, a07.get()->get_latest_start());
    EXPECT_EQ(10, a07.get()->get_latest_finish());
    EXPECT_EQ(3, a07.get()->get_slack());

    // A08
    EXPECT_EQ(7, a08.get()->get_earliest_start());
    EXPECT_EQ(11, a08.get()->get_earliest_finish());
    EXPECT_EQ(8, a08.get()->get_latest_start());
    EXPECT_EQ(12, a08.get()->get_latest_finish());
    EXPECT_EQ(1, a08.get()->get_slack());

    // A09
    EXPECT_EQ(8, a09.get()->get_earliest_start());
    EXPECT_EQ(10, a09.get()->get_earliest_finish());
    EXPECT_EQ(12, a09.get()->get_latest_start());
    EXPECT_EQ(14, a09.get()->get_latest_finish());
    EXPECT_EQ(4, a09.get()->get_slack());

    // A10
    EXPECT_EQ(8, a10.get()->get_earliest_start());
    EXPECT_EQ(11, a10.get()->get_earliest_finish());
    EXPECT_EQ(10, a10.get()->get_latest_start());
    EXPECT_EQ(13, a10.get()->get_latest_finish());
    EXPECT_EQ(2, a10.get()->get_slack());

    // A11
    EXPECT_EQ(7, a11.get()->get_earliest_start());
    EXPECT_EQ(10, a11.get()->get_earliest_finish());
    EXPECT_EQ(10, a11.get()->get_latest_start());
    EXPECT_EQ(13, a11.get()->get_latest_finish());
    EXPECT_EQ(3, a11.get()->get_slack());

    // A12
    EXPECT_EQ(12, a12.get()->get_earliest_start());
    EXPECT_EQ(14, a12.get()->get_earliest_finish());
    EXPECT_EQ(12, a12.get()->get_latest_start());
    EXPECT_EQ(14, a12.get()->get_latest_finish());
    EXPECT_EQ(0, a12.get()->get_slack());

    // A13
    EXPECT_EQ(11, a13.get()->get_earliest_start());
    EXPECT_EQ(15, a13.get()->get_earliest_finish());
    EXPECT_EQ(13, a13.get()->get_latest_start());
    EXPECT_EQ(17, a13.get()->get_latest_finish());
    EXPECT_EQ(2, a13.get()->get_slack());

    // A14
    EXPECT_EQ(14, a14.get()->get_earliest_start());
    EXPECT_EQ(21, a14.get()->get_earliest_finish());
    EXPECT_EQ(14, a14.get()->get_latest_start());
    EXPECT_EQ(21, a14.get()->get_latest_finish());
    EXPECT_EQ(0, a14.get()->get_slack());

    // A15
    EXPECT_EQ(14, a15.get()->get_earliest_start());
    EXPECT_EQ(16, a15.get()->get_earliest_finish());
    EXPECT_EQ(15, a15.get()->get_latest_start());
    EXPECT_EQ(17, a15.get()->get_latest_finish());
    EXPECT_EQ(1, a15.get()->get_slack());

    // A16
    EXPECT_EQ(16, a16.get()->get_earliest_start());
    EXPECT_EQ(20, a16.get()->get_earliest_finish());
    EXPECT_EQ(17, a16.get()->get_latest_start());
    EXPECT_EQ(21, a16.get()->get_latest_finish());
    EXPECT_EQ(1, a16.get()->get_slack());
}

TEST(CriticalPath, PackageNetFromLecture) {
    auto a = std::make_shared<Package>(1, 6, std::vector<int>{});
    auto b = std::make_shared<Package>(2, 8, std::vector<int>{});
    auto c = std::make_shared<Package>(3, 5, std::vector<int>{});
    auto d = std::make_shared<Package>(4, 15, std::vector<int>{a.get()->get_id()});
    auto e = std::make_shared<Package>(5, 17, std::vector<int>{a.get()->get_id()});
    auto f = std::make_shared<Package>(6, 13, std::vector<int>{b.get()->get_id()});
    auto g = std::make_shared<Package>(7, 9, std::vector<int>{c.get()->get_id()});
    auto h = std::make_shared<Package>(8, 9, std::vector<int>{d.get()->get_id()});
    auto i = std::make_shared<Package>(9, 6, std::vector<int>{e.get()->get_id()});
    auto j = std::make_shared<Package>(10, 12, std::vector<int>{f.get()->get_id(), g.get()->get_id()});

    std::unordered_map<int, std::shared_ptr<Package>> package_map_from_lecture = {
        { a.get()->get_id(), a }, { b.get()->get_id(), b }, { c.get()->get_id(), c }, { d.get()->get_id(), d },
        { e.get()->get_id(), e }, { f.get()->get_id(), f }, { g.get()->get_id(), g }, { h.get()->get_id(), h },
        { i.get()->get_id(), i }, { j.get()->get_id(), j }
    };

    CriticalPathFinder completer{ package_map_from_lecture };
    completer.complete();

    // A
    EXPECT_EQ(0, a.get()->get_earliest_start());
    EXPECT_EQ(6, a.get()->get_earliest_finish());
    EXPECT_EQ(3, a.get()->get_latest_start());
    EXPECT_EQ(9, a.get()->get_latest_finish());
    EXPECT_EQ(3, a.get()->get_slack());

    // B
    EXPECT_EQ(0, b.get()->get_earliest_start());
    EXPECT_EQ(8, b.get()->get_earliest_finish());
    EXPECT_EQ(0, b.get()->get_latest_start());
    EXPECT_EQ(8, b.get()->get_latest_finish());
    EXPECT_EQ(0, b.get()->get_slack());

    // C
    EXPECT_EQ(0, c.get()->get_earliest_start());
    EXPECT_EQ(5, c.get()->get_earliest_finish());
    EXPECT_EQ(7, c.get()->get_latest_start());
    EXPECT_EQ(12, c.get()->get_latest_finish());
    EXPECT_EQ(7, c.get()->get_slack());

    // D
    EXPECT_EQ(6, d.get()->get_earliest_start());
    EXPECT_EQ(21, d.get()->get_earliest_finish());
    EXPECT_EQ(9, d.get()->get_latest_start());
    EXPECT_EQ(24, d.get()->get_latest_finish());
    EXPECT_EQ(3, d.get()->get_slack());

    // E
    EXPECT_EQ(6, e.get()->get_earliest_start());
    EXPECT_EQ(23, e.get()->get_earliest_finish());
    EXPECT_EQ(10, e.get()->get_latest_start());
    EXPECT_EQ(27, e.get()->get_latest_finish());
    EXPECT_EQ(4, e.get()->get_slack());

    // F
    EXPECT_EQ(8, f.get()->get_earliest_start());
    EXPECT_EQ(21, f.get()->get_earliest_finish());
    EXPECT_EQ(8, f.get()->get_latest_start());
    EXPECT_EQ(21, f.get()->get_latest_finish());
    EXPECT_EQ(0, f.get()->get_slack());

    // G
    EXPECT_EQ(5, g.get()->get_earliest_start());
    EXPECT_EQ(14, g.get()->get_earliest_finish());
    EXPECT_EQ(12, g.get()->get_latest_start());
    EXPECT_EQ(21, g.get()->get_latest_finish());
    EXPECT_EQ(7, g.get()->get_slack());

    // H
    EXPECT_EQ(21, h.get()->get_earliest_start());
    EXPECT_EQ(30, h.get()->get_earliest_finish());
    EXPECT_EQ(24, h.get()->get_latest_start());
    EXPECT_EQ(33, h.get()->get_latest_finish());
    EXPECT_EQ(3, h.get()->get_slack());

    // I
    EXPECT_EQ(23, i.get()->get_earliest_start());
    EXPECT_EQ(29, i.get()->get_earliest_finish());
    EXPECT_EQ(27, i.get()->get_latest_start());
    EXPECT_EQ(33, i.get()->get_latest_finish());
    EXPECT_EQ(4, i.get()->get_slack());

    // J
    EXPECT_EQ(21, j.get()->get_earliest_start());
    EXPECT_EQ(33, j.get()->get_earliest_finish());
    EXPECT_EQ(21, j.get()->get_latest_start());
    EXPECT_EQ(33, j.get()->get_latest_finish());
    EXPECT_EQ(0, j.get()->get_slack());
}