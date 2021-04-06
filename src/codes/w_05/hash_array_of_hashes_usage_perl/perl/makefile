# /*
#  * This file is part of the "dev-in-place" repository located at:
#  * https://github.com/osuvak/dev-in-place
#  * 
#  * Copyright (C) 2020  Onder Suvak
#  * 
#  * For licensing information check the above url.
#  * Please do not remove this header.
#  * */

# This source code file was
#   Commented through (with interspersed questions) on
#     Fri Apr 24 17:27:31 AST 2020
#   Removed tab separated comment from inside recipes on
#     Thu May  7 21:34:36 AST 2020

# variable definition
# Questions:
#   What is the difference between "=" and ":="?
#   Why would I prefer ":=" in here?
scriptname:=hash_aoh_example.pl

# Recipes

# Questions:
#   What are targets and dependencies?
#   Can we have multiple targets/dependencies?
#   Order of execution, does it matter?
#   Is "default" as a target a reserved name?
#   What is the recipe that is called with "make" without
#     a target specified?
default : operate force_look
	@true;

# Questions: 
#   Why do I have "@" below? 
#   What if I had not used it?
#   Note the "./" in front? Why do I have it?
#   What if I did not have a tab in front of "@..."?
operate : force_look
	@./$(scriptname)

# Q: Are the following two recipes always necessary?
#    Or are they just coded here for demonstration?
#    There is a catch! Mind what I say.
exe_make : force_look
	@chmod +x ./$(scriptname)

exe_remove : force_look
	@chmod -x ./$(scriptname)

# Tells you which recipes you may call when you ask for help.
help : force_look
	@echo ""
	@echo "***RECIPES***"
	@echo "  default   - operates"
	@echo "  operate   - runs the script"
	@echo "  exe_make  - changes permissions to render script executable"
	@echo "  exe_remove- changes permissions to remove script executability"

# Q: Do I need this recipe? Do I have it here just for safety?
# Questions:
#   If there is a command called "true", 
#     we must have "false" as well.
#     What are they about?
#   How can you code the command "true" in C
#     for example?
force_look :
	@true