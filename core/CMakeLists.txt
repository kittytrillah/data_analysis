# Add the core library
add_library(FinanceCore
    src/Core.cpp
    src/DataPreprocessing.cpp
    src/FeatureEngineering.cpp
    src/MLModels.cpp
)

# Include public headers
target_include_directories(FinanceCore PUBLIC include)

# Enable OpenMP for parallelization if available
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(FinanceCore PRIVATE OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found, parallelization will not be enabled.")
endif()
