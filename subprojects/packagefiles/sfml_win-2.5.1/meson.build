project('sfml_win32', 'cpp',
    license: 'zlib',
    version: '2.5.1')

compiler = meson.get_compiler('cpp')

inc_dirs = include_directories('SFML-2.5.1/include')
lib_dirs = [join_paths(meson.current_source_dir(), 'SFML-2.5.1/lib')]

if get_option('debug')
    main_lib = compiler.find_library('sfml-main-d', dirs: lib_dirs)

    system_lib = compiler.find_library('sfml-system-s-d', dirs: lib_dirs)
    window_lib = compiler.find_library('sfml-window-s-d', dirs: lib_dirs)
    graphics_lib = compiler.find_library('sfml-graphics-s-d', dirs: lib_dirs)
    audio_lib = compiler.find_library('sfml-audio-s-d', dirs: lib_dirs)
    network_lib = compiler.find_library('sfml-network-s-d', dirs: lib_dirs)
else
    main_lib = compiler.find_library('sfml-main', dirs: lib_dirs)

    system_lib = compiler.find_library('sfml-system-s', dirs: lib_dirs)
    window_lib = compiler.find_library('sfml-window-s', dirs: lib_dirs)
    graphics_lib = compiler.find_library('sfml-graphics-s', dirs: lib_dirs)
    audio_lib = compiler.find_library('sfml-audio-s', dirs: lib_dirs)
    network_lib = compiler.find_library('sfml-network-s', dirs: lib_dirs)
endif

flac_lib = compiler.find_library('flac', dirs: lib_dirs)
freetype_lib = compiler.find_library('freetype', dirs: lib_dirs)
ogg_lib = compiler.find_library('ogg', dirs: lib_dirs)
openal32_lib = compiler.find_library('openal32', dirs: lib_dirs)
vorbis_lib = compiler.find_library('vorbis', dirs: lib_dirs)
vorbisenc_lib = compiler.find_library('vorbisenc', dirs: lib_dirs)
vorbisfile_lib = compiler.find_library('vorbisfile', dirs: lib_dirs)

winmm_lib = compiler.find_library('winmm')
w32_lib = compiler.find_library('ws2_32')

sfml_dep = declare_dependency(
    compile_args: ['-DSFML_STATIC'],
    dependencies: [
        main_lib,
        
        system_lib,
        window_lib,
        graphics_lib,
        audio_lib,
        network_lib,

        flac_lib,
        freetype_lib,
        ogg_lib,
        openal32_lib,
        vorbis_lib,
        vorbisenc_lib,
        vorbisfile_lib,

        winmm_lib,
        w32_lib,
    ],
    include_directories: inc_dirs,
)