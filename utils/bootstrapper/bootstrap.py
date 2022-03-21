import os
import shutil
import sys


def copy_project_files(project_name, templates_dir, project_dir):
    templates_main = os.path.join(templates_dir, 'project_main.cpp')
    project_main = os.path.join(project_dir, 'main.cpp')
    templates_cmake = os.path.join(templates_dir, 'project_cmake.txt')
    project_cmake = os.path.join(project_dir, 'CMakeLists.txt')

    shutil.copy(templates_main, project_main)
    with open(templates_cmake, 'r') as source:
        text = source.read()
        with open(project_cmake, 'w', newline='\n') as destination:
            destination.write(text.replace('%project_name%', project_name))


def copy_test_files(project_name, templates_dir, tests_dir):
    templates_main = os.path.join(templates_dir, 'tests_main.cpp')
    tests_main = os.path.join(tests_dir, project_name + '.test.cpp')
    templates_cmake = os.path.join(templates_dir, 'tests_cmake.txt')
    tests_cmake = os.path.join(tests_dir, 'CMakeLists.txt')

    shutil.copy(templates_main, tests_main)
    with open(templates_cmake , 'r') as source:
        text = source.read()
        with open(tests_cmake, 'w', newline='\n') as destination:
            destination.write(text.replace('%project_name%', project_name))


def main(args):
    if len(args) != 2:
        print('Usage: python bootstrap.py <project name>')
        sys.exit(1)

    project_name = args[1]

    templates_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'templates')
    project_dir = os.path.join(os.getcwd(), project_name)
    tests_dir = os.path.join(project_dir, 'tests')

    os.mkdir(project_dir)
    os.mkdir(tests_dir)

    copy_project_files(project_name, templates_dir, project_dir)
    copy_test_files(project_name, templates_dir, tests_dir)

    print('Finished bootstrapping ' + project_name)


if __name__ == '__main__':
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        print('\nUser interrupt', file=sys.stderr)
        sys.exit(1)
