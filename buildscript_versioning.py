import datetime

FILENAME_VERSION_NO = 'versioning_version'
FILENAME_BUILD_NO   = 'versioning_build'
FILENAME_VERSION_H  = 'include/build.h'

def createVersionFile(filen_name, content):
    with open(filen_name, 'w+') as f:
        f.write(content)
        print(f'Wrote {content} to {filen_name}.')

def inc_build_no():
    build_no = 0
    try:
        with open(FILENAME_BUILD_NO) as f:
            build_no = int(f.readline()) + 1
    except:
        print('Starting build number from 1')
        build_no = 1
    return build_no

def constructVersionHeader(version_no, build_no):
    tm = datetime.datetime.today()
    long_timestamp = tm.strftime('%Y-%m-%d %H:%M:%S')
    short_timestamp = tm.strftime('%y%m%d')
    build_version = f'{version_no}.{short_timestamp}.{build_no}'
    version_json = f'{{\\"version\\": \\"{version_no}\\", \\"buildVersion\\": \\"{build_version}\\", \\"timestamp\\": \\"{long_timestamp}\\"}}'

    hf = """
    #ifndef BUILD_NUMBER
    #define BUILD_NUMBER "{}"
    #endif

    #ifndef VERSION
    #define VERSION "{}"
    #endif

    #ifndef BUILD_VERSION
    #define BUILD_VERSION "{}"
    #endif

    #ifndef BUILD_TIMESTAMP
    #define BUILD_TIMESTAMP "{}"
    #endif

    #ifndef VERSION_JSON
    #define VERSION_JSON "{}"
    #endif
    """.format(build_no, version_no, build_version, long_timestamp, version_json)
    return hf

def get_version_number():
    # read version number from file
    version_no = '0.0.0'
    try:
        with open(FILENAME_VERSION_NO) as f:
            line = f.readline()
            # validate the version?
            version_no = line
    except FileNotFoundError:
        print(f"\033[31m Couldn't find version file ({FILENAME_VERSION_NO}. Creating a new one.")
        createVersionFile(FILENAME_VERSION_NO, version_no)
    except:
        print(f'Error! Cannot read version number from {FILENAME_VERSION_NO}')
        import sys
        sys.exit('Build process halted.')
    return version_no

# get version number
version_no = get_version_number()

# increment build number
build_no = inc_build_no()

# store build number
createVersionFile(FILENAME_BUILD_NO, str(build_no))

# construct version header
hf = constructVersionHeader(version_no, build_no)

# store version in header file
createVersionFile(FILENAME_VERSION_H, hf)
