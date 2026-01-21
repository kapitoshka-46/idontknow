cmake_minimum_required(VERSION 4.2.1)

project(IDK CXX)


add_executable(idk)

target_sources(idk 
    PRIVATE 
        src/main.cxx
        src/game.cxx
)

target_include_directories(idk 
    PUBLIC
        src/include

)



target_link_libraries(idk 
    PRIVATE 
    raylib    
)  



