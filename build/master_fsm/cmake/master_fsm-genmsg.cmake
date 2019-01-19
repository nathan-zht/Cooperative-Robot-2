# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "master_fsm: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(master_fsm_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_custom_target(_master_fsm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "master_fsm" "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(master_fsm
  "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/master_fsm
)

### Generating Module File
_generate_module_cpp(master_fsm
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/master_fsm
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(master_fsm_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(master_fsm_generate_messages master_fsm_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_dependencies(master_fsm_generate_messages_cpp _master_fsm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(master_fsm_gencpp)
add_dependencies(master_fsm_gencpp master_fsm_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS master_fsm_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(master_fsm
  "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/master_fsm
)

### Generating Module File
_generate_module_eus(master_fsm
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/master_fsm
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(master_fsm_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(master_fsm_generate_messages master_fsm_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_dependencies(master_fsm_generate_messages_eus _master_fsm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(master_fsm_geneus)
add_dependencies(master_fsm_geneus master_fsm_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS master_fsm_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(master_fsm
  "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/master_fsm
)

### Generating Module File
_generate_module_lisp(master_fsm
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/master_fsm
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(master_fsm_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(master_fsm_generate_messages master_fsm_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_dependencies(master_fsm_generate_messages_lisp _master_fsm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(master_fsm_genlisp)
add_dependencies(master_fsm_genlisp master_fsm_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS master_fsm_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(master_fsm
  "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/master_fsm
)

### Generating Module File
_generate_module_nodejs(master_fsm
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/master_fsm
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(master_fsm_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(master_fsm_generate_messages master_fsm_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_dependencies(master_fsm_generate_messages_nodejs _master_fsm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(master_fsm_gennodejs)
add_dependencies(master_fsm_gennodejs master_fsm_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS master_fsm_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(master_fsm
  "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/master_fsm
)

### Generating Module File
_generate_module_py(master_fsm
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/master_fsm
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(master_fsm_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(master_fsm_generate_messages master_fsm_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/xillinux/cobot/catkin_ws/src/master_fsm/srv/ServerListener.srv" NAME_WE)
add_dependencies(master_fsm_generate_messages_py _master_fsm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(master_fsm_genpy)
add_dependencies(master_fsm_genpy master_fsm_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS master_fsm_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/master_fsm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/master_fsm
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(master_fsm_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/master_fsm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/master_fsm
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(master_fsm_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/master_fsm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/master_fsm
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(master_fsm_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/master_fsm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/master_fsm
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(master_fsm_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/master_fsm)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/master_fsm\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/master_fsm
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(master_fsm_generate_messages_py std_msgs_generate_messages_py)
endif()
