project('antware', 'cpp',
    license: 'GPL-3.0-or-later',
    version: '2.1.3',
    default_options: ['warning_level=3','default_library=static'])

glew_dep = dependency('glew')

if host_machine.system() == 'linux'
    sfml_dep = dependency('sfml-all')
    assimp_dep = dependency('assimp')
elif host_machine.system() == 'windows'
    rapidjson_dep = dependency('rapidjson')
    glm_dep = dependency('glm')
    cmake = import('cmake')
    compiler = meson.get_compiler('cpp')
    
    if target_machine.cpu_family() == 'x86'
        sfml_dep = dependency('sfml_win32')
    elif target_machine.cpu_family() == 'x86_64'
        sfml_dep = dependency('sfml_win64')
    endif

    assimp_opt = cmake.subproject_options()
    assimp_opt.add_cmake_defines({
        'BUILD_SHARED_LIBS': false,
        'CMAKE_BUILD_TYPE': get_option('buildtype') == 'debug' ? 'Debug' : 'Release',
        'ASSIMP_BUILD_ASSIMP_TOOLS': false,
        'ASSIMP_BUILD_TESTS': false,
        'ASSIMP_BUILD_ZLIB': false,

        'ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT': false,
        'ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT': false,

        'ASSIMP_BUILD_GLB_IMPORTER': true,
        'ASSIMP_BUILD_OBJ_IMPORTER': true,
        'ASSIMP_BUILD_GLTF_IMPORTER': true,
    })
    assimp_dep = cmake.subproject('assimp', options: assimp_opt).dependency('assimp')
endif

src_assembler = run_command('src_assembler.py')
sources = src_assembler.stdout().strip().split('\n')


if host_machine.system() == 'windows'
executable('antware', sources,
    win_subsystem: 'windows',
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, glm_dep, rapidjson_dep, assimp_dep])
elif host_machine.system() == 'linux'
executable('antware', sources,
    override_options: ['cpp_std=c++17'],
    include_directories: ['include'],
    dependencies: [sfml_dep, glew_dep, assimp_dep],
    install: true)

install_subdir('Assets',install_dir:'share/antware')
install_data('default_settings.json')
install_subdir('scenes',install_dir:'share/antware')
install_subdir('Shaders',install_dir:'share/antware')
install_data('metadata/run_antware.sh',install_dir:'bin')
install_data('metadata/io.github.yamanqd.antware.desktop',install_dir:'share/applications')
    
install_data('metadata/antware_1_16x16x32.png',install_dir:'share/icons/hicolor/16x16/apps',rename:'io.github.yamanqd.antware.png')
install_data('metadata/antware_2_32x32x32.png',install_dir:'share/icons/hicolor/32x32/apps',rename:'io.github.yamanqd.antware.png')
install_data('metadata/antware_3_64x64x32.png',install_dir:'share/icons/hicolor/64x64/apps',rename:'io.github.yamanqd.antware.png')
install_data('metadata/antware_4_128x128x32.png',install_dir:'share/icons/hicolor/128x128/apps',rename:'io.github.yamanqd.antware.png')
install_data('metadata/antware_5_256x256x32.png',install_dir:'share/icons/hicolor/256x256/apps',rename:'io.github.yamanqd.antware.png')

install_data('io.github.yamanqd.antware.metainfo.xml',install_dir:'share/metainfo')

endif