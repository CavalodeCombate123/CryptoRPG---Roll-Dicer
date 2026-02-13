# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CryptoRPG_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CryptoRPG_autogen.dir\\ParseCache.txt"
  "CryptoRPG_autogen"
  )
endif()
