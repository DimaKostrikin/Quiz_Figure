//
// Created by moroz on 12.11.2020.
//

#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

TEST(widget, ok) {
    ASSERT_EQ(1, 1);
}