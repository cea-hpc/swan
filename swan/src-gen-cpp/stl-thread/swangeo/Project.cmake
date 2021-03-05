target_sources(swangeo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../bathylib/BathyLib.cc)
target_link_libraries(swangeo PUBLIC netcdf)
