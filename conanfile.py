from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration
import os



class CppTemplateConan(ConanFile):
    name = "CppTemplate"
    version = "0.0.1"
    license = "MIT"
    author = "Bertouz blopiblop100@gmail.com"
    url = "https://github.com/Bertouz/CppTemplate"
    description = ""
    topics = ("c++", "template")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "build_doc":[True, False], "build_test":[True, False], "use_conan":[True, False], "enable_code_coverage":[True, False], "enable_clang_tidy":[True, False], "enable_clang_format":[True, False] }
    default_options = {"shared": False, "build_doc":False, "build_test":False, "use_conan":True, "enable_code_coverage":False, "enable_clang_tidy":False, "enable_clang_format":False}
    generators = "cmake_find_package"
    requires= []

    def source(self):
        self.run("".join(["git clone ", self.url]))

    def configure(self):
        if self.settings.compiler.cppstd not in ["11", "14","17"]:
            raise ConanInvalidConfiguration("C++ standard less than 11 not handled ")

    def configure_cmake(self):
        cmake = CMake(self)
        kv = {True:"On", False:"Off"}
        cmake.definitions["BUILD_DOC"]            = kv[self.options.build_doc == True]
        cmake.definitions["BUILD_TESTS"]          = kv[self.options.build_test == True]
        cmake.definitions["USE_CONAN"]            = kv[True] 
        cmake.definitions["ENABLE_CODE_COVERAGE"] = kv[self.options.enable_code_coverage == True]
        cmake.definitions["ENABLE_CLANG_TIDY"]    = kv[self.options.enable_clang_tidy == True]
        cmake.definitions["ENABLE_CLANG_FORMAT"]  = kv[self.options.enable_clang_format == True]
        cmake.configure(source_folder="CppTemplate")
        return cmake

    def requirements(self):
        if self.options.build_test == True:
            self.requires("catch2/3.0.0@catchorg/stable")

    def build(self):
        cmake = self.configure_cmake()
        cmake.build()
        if self.options.build_test is True:
            cmake.test()

    def package(self):
        cmake = self.configure_cmake()
        cmake.install()

    def package_info(self):
        # default behavior, doesn't need to be explicitly defined in recipes
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libdirs = ["lib/MyCppProject"]
        self.cpp_info.bindirs = ["bin"]
        self.cpp_info.resdirs = ["res"] 
        self.cpp_info.libs    = ["libMyCppProject"]
$
