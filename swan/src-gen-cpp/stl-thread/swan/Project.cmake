target_sources(swan PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../bathylib/BathyLib.cc)
target_link_libraries(swan PUBLIC netcdf)
