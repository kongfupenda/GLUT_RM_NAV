cmake_minimum_required(VERSION 3.8)
project(test_code)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

add_executable(move_test 	#生成可执行文件，名字是node_01
	src/move_test.cpp		#main文件 主函数入口
)   

ament_target_dependencies(move_test     #ROS2独有的命令:为目标添加依赖关系，将可执行文件 node_01 与 rclcpp 库关联起来
  rclcpp
  std_msgs
)   

install(TARGETS 	# 将编译好的可执行文件 cpp_node 安装到指定目录，确保 ROS 2 系统能找到并启动该节点。
  move_test		
  DESTINATION lib/${PROJECT_NAME}
)
