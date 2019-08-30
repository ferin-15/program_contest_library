import argparse
import subprocess

def is_local(filename):
    with open(filename, mode='r') as f:
        str = f.readline()
        return str == '// Local\n'

# filenameを実行
def run(filename):
    subprocess.run(['g++', filename])
    if is_local(filename):
        print('local')
        subprocess.run(['./a.out'])
    else:
        print('submit')

parser = argparse.ArgumentParser(description='verify library')
parser.add_argument('files', nargs='*', help='list of file to verify')
args = parser.parse_args()

if len(args.files) == 0:
    print('引数の数が0')
else:
    for file in args.files:
        run(file)
