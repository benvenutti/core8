from conans import ConanFile, CMake

class Core8(ConanFile):
    name = "core8"
    version = "0.1"
    url = "https://github.com/benvenutti/core8.git"
    settings = "os", "compiler", "build_type", "arch"
    license = "MIT"
    exports_sources = "*"

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.hpp", dst="include/core8", src="include/core8")
        self.copy("*", dst="lib", src="lib")

    def package_info(self):
        self.cpp_info.libs = ["core8"]