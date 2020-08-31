target_sources(swan PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SwanFunctions.cc)
target_link_libraries(swan PUBLIC netcdf)
