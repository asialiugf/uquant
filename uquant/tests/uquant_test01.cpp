#include <gtest/gtest.h>

#include "future_BoolAll_test.h"
#include "future_BoolSerial_test.h"
#include "future_BoolsegsList_test.h"
#include "future_PointsList_test.h"
#include "future_SectionsBase_test.h"
#include "future_StopsegsList_test.h"
#include "trader_macdkd.h"

using namespace uBEE;

TEST(PointsList_test, PointsList类测试) {
    EXPECT_EQ(PointsList_test(), 0); // 通过
}

TEST(StopsegsList_test, StopsegsList类测试) {
    EXPECT_EQ(StopsegsList_test1(), 0); // 通过
    EXPECT_EQ(StopsegsList_test2(), 0); // 通过
}

TEST(BoolsegsList_test, BoolsegsList类测试) {
    EXPECT_EQ(BoolsegsList_test1(), 0); // 通过
    EXPECT_EQ(BoolsegsList_test2(), 0); // 通过
}

TEST(SectionsBase_test, SectionsBase类测试) {
    EXPECT_EQ(SectionsBase_test1(), 0); // 通过
    // EXPECT_EQ(SectionsBase_test2(), 0); // 通过
    EXPECT_EQ(SectionsBase_test3(), 0); // 通过
}

TEST(BoolSerial_test, BoolSerial类测试) {
    EXPECT_EQ(BoolSerial_test(), 0); // 通过
}

TEST(BoolAll_test, BoolAll测试) {
    EXPECT_EQ(BoolAll_test(), 0); // 通过
}

// TEST(trading_test, 策略整体RSVEMASMA测试) {
//     // arrange
//     // act
//     // assert
//     EXPECT_EQ(trading_test1(), 0); // 通过
// }
