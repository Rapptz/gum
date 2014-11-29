# helps create the .rst file skeleton for a file

import os, sys, re
import argparse

# command line
parser = argparse.ArgumentParser()
parser.add_argument('--input', '-i', help='the file to process', metavar='<file>', action='store', required=True)
parser.add_argument('--output', '-o', help='the file to write to', metavar='<file>', action='store')
args = parser.parse_args()

# regular expressions and building blocks
identifier =  r"([a-zA-Z_]\w*)"
modifiers = r"\s*(?:(?:inline|static|constexpr|friend|virtual|explicit|const|\[\[.+\]\])\s+)*"
return_type = r'[a-zA-Z_][\w&<>:]*'
function_name = r'(?:operator\s*.{1,2}|[A-Za-z_:]\w*)'
namespace_regex = re.compile(r"\s*namespace " + identifier + r"\s*.*?")
class_regex = re.compile(r"\s*(?:class|struct)\s*" + identifier + r"\s*.*?")
function_regex = re.compile(r"^(?!\s*return)" + modifiers + return_type + r"\s+" + function_name + r"\(.*?\)")
enum_regex = re.compile(r'\s*enum\s+(class|struct)?\s*([a-zA-Z_]\w*)?\s*(?:\:\s*[a-zA-Z_]\w*)?.*?')


def process_file(filename):
    in_class = False
    in_enum = False
    result = []
    f = open(filename, 'r')
    anchor = os.path.splitext(filename)[0].replace(os.sep, '-').replace('_', '-')
    result.append('.. default-domain:: cpp')
    result.append('.. highlight:: cpp')
    result.append('.. _{}:\n'.format(anchor))
    result.append('Insert Title Here')
    result.append('====================\n')
    result.append('Insert text here\n')
    result.append('This file is included through: ::\n')
    result.append('    #include <{}>\n'.format(filename.replace('\\', '/')))

    for line in f:
        indentation = (4 * in_class) + (4 * in_enum)

        if line.strip().startswith('};'):
            if in_enum:
                in_enum = False
                result.append('')
            elif in_class:
                in_class = False
                result.append('\n')

        if in_enum:
            value = line.strip()
            index = value.find('=')
            if index != -1:
                value = value[0:index].strip()
            else:
                value = value[:-1] # remove the comma
            result.append(' ' * indentation + '.. enumerator:: ' + value + '\n')
            result.append(' ' * (indentation + 4) + 'Insert text here')

        enum = enum_regex.match(line)
        if enum:
            in_enum = True
            enum_class = 'class ' if enum.group(1) else ''
            enum_name = enum.group(2) if enum.group(2) != None else 'anonymous'
            result.append(' ' * indentation + '.. enum:: ' + enum_class + enum_name + '\n')
            result.append(' ' * (indentation + 4) + 'Insert text here')


        namespace = namespace_regex.match(line)
        if namespace:
            result.append('.. namespace:: ' + namespace.group(1) + '\n')

        struct = class_regex.match(line)
        if struct:
            result.append('.. class:: ' + struct.group(1) + '\n')
            result.append(' ' * 4 + 'Insert text here')
            in_class = True

        function = function_regex.match(line)
        if function:
            string = function.group(0).strip()
            string = string[0:string.rfind(')') + 1]
            result.append(' ' * indentation + '.. function:: ' + string + '\n')
            result.append(' ' * (indentation + 4) + 'Insert text here')

    f.close()
    return '\n'.join(result)



result = process_file(args.input)

if not args.output:
    args.output = 'testing.rst'

with open(args.output, 'wb') as f:
    f.write(result + '\n')
