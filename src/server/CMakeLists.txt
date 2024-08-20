# 定义了一个SRC_LIST变量，包含了该目录下所有的源文件
aux_source_directory(. SRC_LIST)
# 定义了一个db_LIST变量，包含了./db下所有的源文件
aux_source_directory(./db db_LIST)
# 定义了一个model_LIST变量，包含了./model下所有的源文件
aux_source_directory(./model model_LIST)
# 定义了一个redis_LIST变量，包含了./redis下所有的源文件
aux_source_directory(./redis redis_LIST)

# 指定生成可执行文件ChatServer，由SRC_LIST、db_LIST变量所定义的源文件编译而来
add_executable(ChatServer ${SRC_LIST} ${db_LIST} ${model_LIST} ${redis_LIST})

#指定可执行文件ChatServer连接时需要依赖的库文件
#muduo_net muduo_base ： muduo的库文件 
#pthread ： 第三方库文件存放位置
target_link_libraries(ChatServer muduo_net muduo_base  mysqlclient hiredis pthread)