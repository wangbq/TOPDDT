# TOPDDT

Skeleton code for TOP DQM development.

## Usage

1. Running it from command line:

'''
root -l Main.cpp\(\"inputfile.root\"\)
'''

where inputfile.root is the file you want to analyze. If there are more than one file you want to analyze, wildcards can be used as

'''
root -l Main.cpp\(\"\*.root\"\)
'''

2. Another way to run it is from the root command line:

'''
.L Main.cpp
Main("inputfile.root")
'''

Wildcards could also be used without escaping.

After running the script, the output histograms are saved in a root file called "outfile.root". You can write a script to read this file and make fancy plots by your self. Or you can open it with root and inspect it by using TBrowser.

