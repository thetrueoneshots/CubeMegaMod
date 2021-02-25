import os

path = os.path.dirname(os.path.realpath(__file__))
_, folderName = os.path.split(path)

lines = [
'cmake_minimum_required (VERSION 3.8)',
'project(project_%s)' % folderName,

'add_subdirectory(cwmods)',

'add_library (%s SHARED "main.cpp")' % folderName,

'target_link_libraries (%s LINK_PUBLIC CWSDK)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/common)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/cube)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/gfx)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/IDA)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/msvc)' % folderName,
'target_include_directories (%s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cwmods/plasma)' % folderName
    ]

with open(os.path.join(path, 'CMakeLists.txt'), 'w') as f:
    f.write('\n'.join(lines))
