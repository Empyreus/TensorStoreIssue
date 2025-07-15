#include <stddef.h>
#include "tensorstore/context.h"
#include "tensorstore/index_space/dim_expression.h"
#include "tensorstore/open.h"
#include "tensorstore/open_mode.h"
#include "tensorstore/tensorstore.h"

int main(int argc, char** argv) {

  auto context = tensorstore::Context::Default();

  auto file = tensorstore::Open({{"driver", "zarr3"},
                                 {"kvstore", "file:///tmp/example/"},
                                 {"metadata",
                                  {
                                      {"data_type", "float64"},
                                      {"shape", {100, 100, 100}},
                                      {"codecs",
                                       {{{"name", "blosc"},
                                         {"configuration",
                                          {{"cname", "blosclz"},
                                           {"clevel", 3},
                                           {"shuffle", "noshuffle"}}}}}},
                                  }}},
                                context, tensorstore::OpenMode::open_or_create);
  auto read_future =
      tensorstore::Read(file.result() | tensorstore::Dims(0).IndexSlice(0));

  ABSL_LOG(INFO) << read_future.status();
}