file(GLOB testSrc
	"*.h"
	"*.cpp"
)

add_executable(triangle "../../QPUassembler/qpu_assembler.c" ${testSrc} )
target_compile_options(triangle PRIVATE -Wall -std=c++11 -std=c11)

target_link_libraries(triangle vulkan-1-rpi)
