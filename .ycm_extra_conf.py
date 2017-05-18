def FlagsForFile(filename, **kwargs):
    flags = {
        'flags': [
            '--std=c++11',
            '-x', 'c++',
            '-Wall',
            '-Wextra',
            '-Werror',
        ]
    }

    if 'main.cc' in filename:
        flags['flags'].append('-Wno-unused-parameter')
    return flags


