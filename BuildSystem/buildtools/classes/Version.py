"""
This class is responsible for creating the Version.h file in the source directory
and returning the version parameters used by the documentation generator
"""
import os
import sys
import subprocess
import os.path
import shutil
import fileinput
import re
import time
import pytz
from datetime import datetime, date

import Globals

EX_OK = getattr(os, "EX_OK", 0)

class Version:
	def __init__(self):
		print("--> Starting Version Class")

	def create_version_header(self):
		print("--> Creating Version.h from Git Information")

		if Globals.git_path_ == '':
			print("[WARNING] - No Git was found. Cannot create Version.h file")
			return True

		p = subprocess.Popen(['git', '--no-pager', 'log', '-n', '1', '--pretty=format:%H%n%h%n%ci' ], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		out, err = p.communicate()
		lines = out.decode('utf-8').split('\n')
		if len(lines) != 3:
			return Globals.PrintError('Format printed by GIT did not meet expectations. Expected 3 lines but got ' + str(len(lines)))

		time_pieces = lines[2].split(' ')
		temp = ' '.join(time_pieces)
		local_time = datetime.strptime(temp, '%Y-%m-%d %H:%M:%S %z')
		utc_time   = local_time.astimezone(pytz.utc)
		
		# Build the Version.h file
		print('-- Build SPM/Source/Version.h with Git log information')
		version = '// This file is automatically built by the build system. Do not modify this file\n'
		version += '#ifndef VERSION_H_\n'
		version += '#define VERSION_H_\n'
		version += '#define SOURCE_CONTROL_DATE "' + utc_time.strftime('%Y-%m-%d') + '"\n'
		version += '#define SOURCE_CONTROL_YEAR "' + utc_time.strftime('%Y') + '"\n'
		version += '#define SOURCE_CONTROL_MONTH "' + utc_time.strftime('%B') + '"\n'
		version += '#define SOURCE_CONTROL_TIME "' + utc_time.strftime('%H:%M:%S') + '"\n'
		version += '#define SOURCE_CONTROL_VERSION "' + utc_time.strftime('%Y-%m-%d %H:%M:%S %Z') + '"\n'
		version += '#endif\n'
		file_output = open(Globals.root_directory_ + '/Source/Version.h', 'w')
		file_output.write(version)
		file_output.close()
		
		# Build the Version.tex file
		print('-- Build SPM/Documention/Manual/version.tex with Git log information')
		version = '% WARNING: THIS FILE IS AUTOMATICALLY GENERATED BY doBuild documentation. DO NOT EDIT THIS FILE\n'
		version += '\\newcommand{\\SourceControlDateDoc}{' + utc_time.strftime('%Y-%m-%d') + '}\n'
		version += '\\newcommand{\\SourceControlYearDoc}{' + utc_time.strftime('%Y') + '}\n'
		version += '\\newcommand{\\SourceControlMonthDoc}{' + utc_time.strftime('%B') + '}\n'
		version += '\\newcommand{\\SourceControlTimeDoc}{' + utc_time.strftime('%H:%M:%S') + '}\n'
		version += '\\newcommand{\\SourceControlShortVersionDoc}{' + utc_time.strftime('%Y-%m-%d') + '}\n'
		version += '\\newcommand{\\SourceControlVersionDoc}{' + utc_time.strftime('%Y-%m-%d %H:%M:%S %Z') + '}\n'
		file_output = open(Globals.root_directory_ + '/Documentation/Manual/Version.tex', 'w')
		file_output.write(version)
		file_output.close()
		
		print('-- Build SPM/Documention/Manual/SPMversion.tex with Git log information')
		version = Globals.SPM_version_number + '-' + utc_time.strftime('%Y-%m-%d') + '\n'
		file_output = open(Globals.root_directory_ + '/Documentation/Manual/SPMVersion.tex', 'w')
		file_output.write(version)
		file_output.close()
		
		# Build the Version.tex file
		print('-- Build SPM/RLibrary/version.R with Git log information')
		version = '# WARNING: THIS FILE IS AUTOMATICALLY GENERATED BY doBuild documentation. DO NOT EDIT THIS FILE\n'
		version += 'version.number<-"' + Globals.SPM_version_number + '"\n'
		version += 'version.date<-"' + utc_time.strftime('%Y-%m-%d') + '"\n'
		file_output = open(Globals.root_directory_ + '/R-libraries/Version.R', 'w')
		file_output.write(version)
		file_output.close()

		print('-- Version updated')
		
	