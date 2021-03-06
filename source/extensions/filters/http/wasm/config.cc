#include "extensions/filters/http/wasm/config.h"

#include "envoy/config/filter/http/wasm/v2/wasm.pb.validate.h"
#include "envoy/registry/registry.h"

#include "common/common/empty_string.h"
#include "common/config/datasource.h"

#include "extensions/common/wasm/wasm.h"
#include "extensions/filters/http/wasm/wasm_filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Wasm {

Http::FilterFactoryCb WasmFilterConfig::createFilterFactoryFromProtoTyped(
    const envoy::config::filter::http::wasm::v2::Wasm& proto_config, const std::string&,
    Server::Configuration::FactoryContext& context) {
  auto filter_config = std::make_shared<FilterConfig>(proto_config, context);
  return [filter_config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    auto filter = filter_config->createFilter();
    callbacks.addStreamFilter(filter);
    callbacks.addAccessLogHandler(filter);
  };
}

/**
 * Static registration for the Wasm filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<WasmFilterConfig,
                                 Server::Configuration::NamedHttpFilterConfigFactory>
    register_;

} // namespace Wasm
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
