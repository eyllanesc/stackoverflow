import os
import sys
import json
import subprocess
import utils


# https://stackoverflow.com/a/50216611/6622587
def user_prompt(question):
    from distutils.util import strtobool
    while True:
        user_input = input(question + " [y/n]: ").lower()
        try:
            result = strtobool(user_input)
            return result
        except ValueError:
            print("Please use y/n or yes/no.\n")
    return

def main():
	locations = []
	search_item = input("Input The Search Item: ")
	if search_item:
		result = True
		while result:
			location = input("Location:")
			if location: 
				locations.append(location)
			result = user_prompt("Do you want to add a new location?:")
	if locations and search_item:
		directory, program, args = utils.create_arguments(search_item, locations)
		subprocess.call([program] + args, cwd=directory)

if __name__ == '__main__':
	main()