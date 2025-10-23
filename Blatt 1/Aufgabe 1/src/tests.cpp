#include "gtest/gtest.h"
#include "CriticalPathFinder.h"
#include "Package.h"
#include <vector>

TEST(CriticalPath, PackageFromAssignment) {
    Package a01{ 1, 3, {} };
    Package a02{ 2, 4, {} };
    Package a03{ 3, 5, {} };
    Package a04{ 4, 4, { a01.get_id() } };
    Package a05{ 5, 9, { a01.get_id() } };
    Package a06{ 6, 4, { a02.get_id() } };
    Package a07{ 7, 2, { a03.get_id() } };
    Package a08{ 8, 4, { a04.get_id() } };
    Package a09{ 9, 2, { a06.get_id() } };
    Package a10{ 10, 3, { a06.get_id() } };
    Package a11{ 11, 3, { a07.get_id() } };
    Package a12{ 12, 2, { a05.get_id(), a08.get_id() } };
    Package a13{ 13, 4, { a10.get_id(), a11.get_id() } };
    Package a14{ 14, 7, { a09.get_id(), a12.get_id() } };
    Package a15{ 15, 2, { a09.get_id(), a12.get_id() } };
    Package a16{ 16, 4, { a13.get_id(), a15.get_id() } };

    std::unordered_map<int, Package*> package_map = {
        { a01.get_id(), &a01 }, { a02.get_id(), &a02 }, { a03.get_id(), &a03 }, { a04.get_id(), &a04 },
        { a05.get_id(), &a05 }, { a06.get_id(), &a06 }, { a07.get_id(), &a07 }, { a08.get_id(), &a08 },
        { a09.get_id(), &a09 }, { a10.get_id(), &a10 }, { a11.get_id(), &a11 }, { a12.get_id(), &a12 },
        { a13.get_id(), &a13 }, { a14.get_id(), &a14 }, { a15.get_id(), &a15 }, { a16.get_id(), &a16 }
    };

    CriticalPathFinder completer{ package_map };
    completer.complete();

    // A01
    EXPECT_EQ(0, a01.get_earliest_start());
    EXPECT_EQ(3, a01.get_earliest_finish());
    EXPECT_EQ(0, a01.get_latest_start());
    EXPECT_EQ(3, a01.get_latest_finish());
    EXPECT_EQ(0, a01.get_slack());

    // A02
    EXPECT_EQ(0, a02.get_earliest_start());
    EXPECT_EQ(4, a02.get_earliest_finish());
    EXPECT_EQ(2, a02.get_latest_start());
    EXPECT_EQ(6, a02.get_latest_finish());
    EXPECT_EQ(2, a02.get_slack());

    // A03
    EXPECT_EQ(0, a03.get_earliest_start());
    EXPECT_EQ(5, a03.get_earliest_finish());
    EXPECT_EQ(3, a03.get_latest_start());
    EXPECT_EQ(8, a03.get_latest_finish());
    EXPECT_EQ(3, a03.get_slack());

    // A04
    EXPECT_EQ(3, a04.get_earliest_start());
    EXPECT_EQ(7, a04.get_earliest_finish());
    EXPECT_EQ(4, a04.get_latest_start());
    EXPECT_EQ(8, a04.get_latest_finish());
    EXPECT_EQ(1, a04.get_slack());

    // A05
    EXPECT_EQ(3, a05.get_earliest_start());
    EXPECT_EQ(12, a05.get_earliest_finish());
    EXPECT_EQ(3, a05.get_latest_start());
    EXPECT_EQ(12, a05.get_latest_finish());
    EXPECT_EQ(0, a05.get_slack());

    // A06
    EXPECT_EQ(4, a06.get_earliest_start());
    EXPECT_EQ(8, a06.get_earliest_finish());
    EXPECT_EQ(6, a06.get_latest_start());
    EXPECT_EQ(10, a06.get_latest_finish());
    EXPECT_EQ(2, a06.get_slack());

    // A07
    EXPECT_EQ(5, a07.get_earliest_start());
    EXPECT_EQ(7, a07.get_earliest_finish());
    EXPECT_EQ(8, a07.get_latest_start());
    EXPECT_EQ(10, a07.get_latest_finish());
    EXPECT_EQ(3, a07.get_slack());

    // A08
    EXPECT_EQ(7, a08.get_earliest_start());
    EXPECT_EQ(11, a08.get_earliest_finish());
    EXPECT_EQ(8, a08.get_latest_start());
    EXPECT_EQ(12, a08.get_latest_finish());
    EXPECT_EQ(1, a08.get_slack());

    // A09
    EXPECT_EQ(8, a09.get_earliest_start());
    EXPECT_EQ(10, a09.get_earliest_finish());
    EXPECT_EQ(12, a09.get_latest_start());
    EXPECT_EQ(14, a09.get_latest_finish());
    EXPECT_EQ(4, a09.get_slack());

    // A10
    EXPECT_EQ(8, a10.get_earliest_start());
    EXPECT_EQ(11, a10.get_earliest_finish());
    EXPECT_EQ(10, a10.get_latest_start());
    EXPECT_EQ(13, a10.get_latest_finish());
    EXPECT_EQ(2, a10.get_slack());

    // A11
    EXPECT_EQ(7, a11.get_earliest_start());
    EXPECT_EQ(10, a11.get_earliest_finish());
    EXPECT_EQ(10, a11.get_latest_start());
    EXPECT_EQ(13, a11.get_latest_finish());
    EXPECT_EQ(3, a11.get_slack());

    // A12
    EXPECT_EQ(12, a12.get_earliest_start());
    EXPECT_EQ(14, a12.get_earliest_finish());
    EXPECT_EQ(12, a12.get_latest_start());
    EXPECT_EQ(14, a12.get_latest_finish());
    EXPECT_EQ(0, a12.get_slack());

    // A13
    EXPECT_EQ(11, a13.get_earliest_start());
    EXPECT_EQ(15, a13.get_earliest_finish());
    EXPECT_EQ(13, a13.get_latest_start());
    EXPECT_EQ(17, a13.get_latest_finish());
    EXPECT_EQ(2, a13.get_slack());

    // A14
    EXPECT_EQ(14, a14.get_earliest_start());
    EXPECT_EQ(21, a14.get_earliest_finish());
    EXPECT_EQ(14, a14.get_latest_start());
    EXPECT_EQ(21, a14.get_latest_finish());
    EXPECT_EQ(0, a14.get_slack());

    // A15
    EXPECT_EQ(14, a15.get_earliest_start());
    EXPECT_EQ(16, a15.get_earliest_finish());
    EXPECT_EQ(15, a15.get_latest_start());
    EXPECT_EQ(17, a15.get_latest_finish());
    EXPECT_EQ(1, a15.get_slack());

    // A16
    EXPECT_EQ(16, a16.get_earliest_start());
    EXPECT_EQ(20, a16.get_earliest_finish());
    EXPECT_EQ(17, a16.get_latest_start());
    EXPECT_EQ(21, a16.get_latest_finish());
    EXPECT_EQ(1, a16.get_slack());
}

TEST(Completions, PackageNetFromLecture) {
    Package a{ 1, 6, {} };
    Package b{ 2, 8, {} };
    Package c{ 3, 5, {} };
    Package d{ 4, 15, {a.get_id()} };
    Package e{ 5, 17, {a.get_id()} };
    Package f{ 6, 13, {b.get_id()} };
    Package g{ 7, 9, {c.get_id()} };
    Package h{ 8, 9, {d.get_id()} };
    Package i{ 9, 6, {e.get_id()} };
    Package j{ 10, 12, {f.get_id(), g.get_id()} };

    std::unordered_map<int, Package*> package_map_from_lecture = {
        { a.get_id(), &a }, { b.get_id(), &b }, { c.get_id(), &c }, { d.get_id(), &d },
        { e.get_id(), &e }, { f.get_id(), &f }, { g.get_id(), &g }, { h.get_id(), &h },
        { i.get_id(), &i }, { j.get_id(), &j }
    };

    CriticalPathFinder completer{ package_map_from_lecture };
    completer.complete();
    // A
    EXPECT_EQ(0, a.get_earliest_start());
    EXPECT_EQ(6, a.get_earliest_finish());
    EXPECT_EQ(3, a.get_latest_start());
    EXPECT_EQ(9, a.get_latest_finish());
    EXPECT_EQ(3, a.get_slack());

    // B
    EXPECT_EQ(0, b.get_earliest_start());
    EXPECT_EQ(8, b.get_earliest_finish());
    EXPECT_EQ(0, b.get_latest_start());
    EXPECT_EQ(8, b.get_latest_finish());
    EXPECT_EQ(0, b.get_slack());

    // C
    EXPECT_EQ(0, c.get_earliest_start());
    EXPECT_EQ(5, c.get_earliest_finish());
    EXPECT_EQ(7, c.get_latest_start());
    EXPECT_EQ(12, c.get_latest_finish());
    EXPECT_EQ(7, c.get_slack());

    // D
    EXPECT_EQ(6, d.get_earliest_start());
    EXPECT_EQ(21, d.get_earliest_finish());
    EXPECT_EQ(9, d.get_latest_start());
    EXPECT_EQ(24, d.get_latest_finish());
    EXPECT_EQ(3, d.get_slack());

    // E
    EXPECT_EQ(6, e.get_earliest_start());
    EXPECT_EQ(23, e.get_earliest_finish());
    EXPECT_EQ(10, e.get_latest_start());
    EXPECT_EQ(27, e.get_latest_finish());
    EXPECT_EQ(4, e.get_slack());

    // F
    EXPECT_EQ(8, f.get_earliest_start());
    EXPECT_EQ(21, f.get_earliest_finish());
    EXPECT_EQ(8, f.get_latest_start());
    EXPECT_EQ(21, f.get_latest_finish());
    EXPECT_EQ(0, f.get_slack());

    // G
    EXPECT_EQ(5, g.get_earliest_start());
    EXPECT_EQ(14, g.get_earliest_finish());
    EXPECT_EQ(12, g.get_latest_start());
    EXPECT_EQ(21, g.get_latest_finish());
    EXPECT_EQ(7, g.get_slack());

    // H
    EXPECT_EQ(21, h.get_earliest_start());
    EXPECT_EQ(30, h.get_earliest_finish());
    EXPECT_EQ(24, h.get_latest_start());
    EXPECT_EQ(33, h.get_latest_finish());
    EXPECT_EQ(3, h.get_slack());

    // I
    EXPECT_EQ(23, i.get_earliest_start());
    EXPECT_EQ(29, i.get_earliest_finish());
    EXPECT_EQ(27, i.get_latest_start());
    EXPECT_EQ(33, i.get_latest_finish());
    EXPECT_EQ(4, i.get_slack());

    // J
    EXPECT_EQ(21, j.get_earliest_start());
    EXPECT_EQ(33, j.get_earliest_finish());
    EXPECT_EQ(21, j.get_latest_start());
    EXPECT_EQ(33, j.get_latest_finish());
    EXPECT_EQ(0, j.get_slack());
}