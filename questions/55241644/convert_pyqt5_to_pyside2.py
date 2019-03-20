import os
import fileinput
import argparse
import shutil

def modify_source_code(directory, text_to_search, replacement_text):
    for path, subdirs, files in os.walk(directory):
        for name in files:
            filename = os.path.join(path, name)
            with fileinput.FileInput(filename, inplace=True) as file:
                for line in file:
                    if line.startswith('#'):
                        # not change on comments
                        print(line, end='')
                    else:
                        print(line.replace(text_to_search, replacement_text), end='')

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", help="Input directory")
    parser.add_argument("-o", "--output", help="Output directory")
    args = parser.parse_args()
    if args.input and args.output:
        input_dir = os.path.join(os.path.abspath(args.input), "pyuic", "uic")
        output_dir = os.path.abspath(args.output)
        shutil.copytree(input_dir, output_dir)
        modify_source_code(output_dir, 'PyQt5', 'PySide2')

if __name__ == '__main__':
    main()