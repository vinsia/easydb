cc_library(
    name = "easydb",
    srcs = ["easydb.cc"],
    hdrs = ["easydb.h"],
    deps = [
        ":skiplist",
        "//easydb/utils:arena",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":easydb",
        "@glog",
    ],
)

cc_library(
    name = "skiplist",
    hdrs = ["skiplist.h"],
    deps = [
        "//easydb/utils:arena",
        "//easydb/utils:random",
    ],
)

cc_test(
    name = "skiplist_test",
    srcs = ["skiplist_test.cc"],
    deps = [
        ":skiplist",
        "//easydb/utils:random",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "construct_order_test",
    srcs = ["construct_order_test.cc"],
    deps = [
        ":skiplist",
        "//easydb/utils:random",
        "@googletest//:gtest_main",
    ],
)
