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

cc_library(
    name = "slice",
    hdrs = ["slice.h"],
)

cc_library(
    name = "struct",
    hdrs = ["struct.h"],
)

cc_library(
    name = "status",
    hdrs = ["status.h"],
    deps = [
        ":slice",
    ],
)

cc_library(
    name = "memtable",
    srcs = ["memtable.cc"],
    hdrs = ["memtable.h"],
    deps = [
        ":slice",
        ":status",
        ":struct",
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
