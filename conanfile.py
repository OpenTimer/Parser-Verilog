from conans import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.layout import cmake_layout


class ParserVerilogConan(ConanFile):
    name = "parser-verilog"
    version = "0.1"

    # Optional metadata
    license = "MIT"
    author = "Tsung-Wei Huang <twh760812@gmail.com>, Chun-Xun Lin <artiferlly@gmail.com>, Martin Wong"
    url = "https://github.com/OpenTimer/Parser-Verilog"
    description = "A Standalone Structural Verilog Parser"
    topics = ("lex, eda, verilog, cpp17, circuit, computer-aided-design, vlsi-physical-design, electronic-design-automation, vlsi-circuits, bison-yacc")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "parser-verilog/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["parser-verilog"]
