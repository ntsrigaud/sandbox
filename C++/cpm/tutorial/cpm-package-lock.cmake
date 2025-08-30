
# Example of locked package versions populated by CPM
CPMAddPackage(
    NAME fmt
    VERSION 8.1.1
    OPTIONS "CPM_FMT_USE_SYSTEM=OFF"
    URL "https://github.com/fmtlib/fmt/archive/8.1.1.zip"
    SHA256 "b8e1e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8e8"
)

CPMAddPackage(
    NAME spdlog
    VERSION 1.9.2
    OPTIONS "CPM_SPDLOG_USE_SYSTEM=OFF"
    URL "https://github.com/gabime/spdlog/archive/v1.9.2.zip"
    SHA256 "c9e1e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9e9"
)
