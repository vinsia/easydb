package(default_visibility = ["//visibility:public"])

cc_library(
    name = "random",
    hdrs = ["random.h"],
)

cc_library(
    name = "arena",
    srcs = ["arena.cc"],
    hdrs = ["arena.h"],
    deps = [
        "@glog",
    ],
)

cc_test(
    name = "random_test",
    srcs = ["random_test.cc"],
    deps = [
        ":random",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "arena_test",
    srcs = ["arena_test.cc"],
    deps = [
        ":arena",
        "@googletest//:gtest_main",
    ],
)
