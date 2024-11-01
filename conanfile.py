from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain


class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.variables["CMAKE_CXX_STANDARD"] = "20"
        tc.generate()

    def configure(self):
        self.options["glad"].gl_version = "4.6"

    def requirements(self):
        requirements = self.conan_data.get('requirements', [])
        for requirement in requirements:
            self.requires(requirement)
