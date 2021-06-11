"""
Helper script for parsingt the header file of MEADE

USAGE:
 - Ensure you have a Python interperter working for VSCode
 - Execute this file by pressing the little green "Play" button in the top-right corner
 - Output will be written to "./scripts/MeadeToWikiOutput.txt" directory
 - Copy entire content of the file and paste it on the wiki page
"""

import os
import re

MEADE_HPP = "..\\src\\MeadeCommandProcessor.cpp"
MODULE_PATH = os.path.dirname(os.path.realpath(__file__))
START_LINE = 0
END_LINE = 0


class Family:
    def __init__(self):
        self.name = None
        self.commands = []


class Command:
    def __init__(self):
        self.__command = None
        self.__description = str()
        self.__information = list()
        self.__returns = list()
        self.__parameters = list()
        self.__remarks = list()
        self.__x = list()

    def set_data(self, attribute, data):
        setattr(self, attribute, data)
    
    @property
    def command(self):
        return self.__command

    @command.setter
    def command(self, val):
        self.__command = val
    
    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, val):
        self.__description = val

    @property
    def information(self):
        return self.__information

    @information.setter
    def information(self, val):
        if val not in self.__information:
            self.__information.append(val)

    @property
    def returns(self):
        return self.__returns

    @returns.setter
    def returns(self, val):
        if val not in self.__returns:
            self.__returns.append(val)

    @property
    def parameters(self):
        return self.__parameters

    @parameters.setter
    def parameters(self, val):
        if val not in self.__parameters:
            self.__parameters.append(val)
    
    @property
    def remarks(self):
        return self.__remarks

    @remarks.setter
    def remarks(self, val):
        if val not in self.__remarks:
            self.__remarks.append(val)


command_sepparators = ["//      Description::",
                       "//      Information:",
                       "//      Returns:",
                       "//      Parameters:",
                       "//      Remarks:",
                       "//"]


def remove_line_prefix(line):
    fixed_line = line.replace("//", "").lstrip()
    fixed_line = fixed_line.replace("\"", "`")
    return fixed_line

def check_command_sepparator(line):
    if line in command_sepparators:
        return True
    else:
        return False

# Meade hpp File
with open(os.path.join(MODULE_PATH, MEADE_HPP)) as f:
    content = f.readlines()
content = [x.strip() for x in content]

# Find start/end block
div = "/////////////////////////////////////////////////////////////////////////////////////////"
startStop = []
for count, line in enumerate(content):
    if div in line:
        startStop.append(count)

if len(startStop) != 2:
    raise Exception("Could not locate start and stop of comment block.")

START_LINE = startStop[0]
END_LINE = startStop[1]

print(("Start and end of block: {0}, {1} ".format(START_LINE, END_LINE)))

familyDividers = []
for i in range(START_LINE, END_LINE):
    for div in ["//------------------------------------------------------------------", "// --"]:
        if div in content[i]:
            familyDividers.append(i)

print(("Found {0} family groups ".format(len(familyDividers))))

all_commands = []
# for i in range(len(familyDividers) - 1):
for i in range(0, 6):
    start = familyDividers[i] + 1
    end = familyDividers[i + 1]

    new_family = Family()
    new_family.name = remove_line_prefix(content[start])

    # Find command groups
    sub_offsets = list()
    sub_offsets.append(start+2)
    for j in range(start+2, end):
        if content[j] == "//":
            sub_offsets.append(j)
    
    for k in range(0, len(sub_offsets)-1):
        command = Command()
        sub_start = sub_offsets[k]
        sub_end = sub_offsets[k+1]
        
        for l in range(sub_start, sub_end):
            if content[l] == "//":
                continue
            
            # Command
            if content[l].startswith("// :"):
                command.command = remove_line_prefix(content[l])

            # Description
            if content[l].startswith("//      Description:"):
                command.description = remove_line_prefix(content[l+1])

            # Information
            if content[l].startswith("//      Information:"):
                m = l+1
                while not check_command_sepparator(content[m]):
                    command.information = remove_line_prefix(content[m])
                    m += 1
                l = m
            
            # Returns
            if content[l].startswith("//      Returns:"):
                m = l+1
                while not check_command_sepparator(content[m]):
                    command.returns = remove_line_prefix(content[m])
                    m += 1
                l = m

            # Remarks
            if content[l].startswith("//      Remarks:"):
                m = l+1
                while not check_command_sepparator(content[m]):
                    command.remarks = remove_line_prefix(content[m])
                    m += 1
                l = m

            # Parameters
            if content[l].startswith("//      Parameters:"):
                m = l+1
                while not check_command_sepparator(content[m]):
                    command.parameters = remove_line_prefix(content[m])
                    m += 1
                l = m
        
        

        new_family.commands.append(command)
        
    all_commands.append(new_family)

def output_wiki():
    f = open("./scripts/MeadeToWikiOutput.txt", "w")
    
    f.write("# MEADE Command Index\n\n")
    f.write("<br>\n\n")
    for fam in all_commands:
        f.write(f"## {fam.name}\n")

        for cmd in fam.commands:
            f.write(f"### {cmd.description}\n")
            
            f.write(f"**Command:**\n")
            f.write(f"`{cmd.command}`\n")
            f.write("\n")
            
            if cmd.information:
                f.write("**Information:**\n")
                for line in cmd.information:
                    f.write(f"{line}\n")
                f.write("\n")    

            f.write("**Returns:**\n")
            for line in cmd.returns:
                f.write(f"- {line}\n")
            f.write("\n")

            if cmd.parameters:
                f.write("**Parameters:**\n")
                for param in cmd.parameters:
                    f.write(f"- {param}\n")
                f.write("\n")

            if cmd.remarks:
                f.write("**Remarks:**\n")
                for param in cmd.remarks:
                    f.write(f"{param}\n")
                f.write("\n")
            
            f.write("<br>")
            f.write("\n")
            f.write("\n")

    f.write("\n\n")

    f.close()
    print("FilOutpute written to: ./scripts/MeadeToWikiOutput.txt")

if __name__ == "__main__":
    output_wiki()
"""
for fam in all_commands:
    print("-----")
    print(fam.name)
    for cmd in fam.commands:
        print("############################")
        print(f"Command: {cmd.command}")
        print(f"Description: {cmd.description}")
        print(f"Information: {cmd.information}")
        print(f"Returns: {cmd.returns}")
        print(f"Parameters: {cmd.parameters}")
        print(f"Remarks: {cmd.remarks}")
        
"""