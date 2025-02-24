from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class QuanolaRecipe(ConanFile):
    name = "quanola"
    version = "0.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("jsoncpp/1.9.6")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    