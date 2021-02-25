from pathlib import Path
import os

path = os.path.dirname(os.path.realpath(__file__))

files = list(Path(path).glob('**/*.cpp'))
   
for filename in files:
    print(filename)


lines = [

'cmake_minimum_required (VERSION 3.8)',

'if(NOT CMAKE_CL_64)',
'   message(FATAL_ERROR "CWSDK REQUIRES clang-cl x64 to build. " )',
'endif()',

'if(CMAKE_BUILD_TYPE MATCHES "Debug")',
'    message(FATAL_ERROR "CWSDK cannot be built debug mode due to MSVC binary compatibility issues." )',
'endif()',

'project("CWSDK" VERSION "1.0.0")',

'add_library (CWSDK \n    %s)' % '\n    '.join([str(x)[len(path)+1:].replace('\\', '/') for x in files]),
'target_link_libraries(CWSDK winmm.lib)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/common)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/cube)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/gfx)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/IDA)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/msvc)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/plasma)',
'target_include_directories (CWSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CWSDK/steam)'
    ]

with open(os.path.join(path, 'CMakeLists.txt'), 'w') as f:
    f.write('\n'.join(lines))
