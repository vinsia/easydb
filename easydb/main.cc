#include <glog/logging.h>
#include <iostream>

#include "easydb/easydb.h"

void InitGoogleLogging(char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
}

int main(int argc, char* argv[]) {
  // Initialize Google’s logging library.
  InitGoogleLogging(argv);

  easydb::EasyDB easydb("/tmp/easydb");
  easydb.Put("hello", "world");
  easydb.Put("bonnie", "female");
  easydb.Put("vinsia", "male");

  LOG(INFO) << "get bonnie " << easydb.Get("bonnie");
  LOG(INFO) << "get vinsia " << easydb.Get("vinsia");
  // LOG(DEBUG) << "Found " << num_cookies << " cookies";
  return 0;
}
