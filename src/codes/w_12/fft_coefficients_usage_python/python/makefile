# /*
#  * This file is part of the "dev-in-place" repository located at:
#  * https://github.com/osuvak/dev-in-place
#  * 
#  * Copyright (C) 2020  Onder Suvak
#  * 
#  * For licensing information check the above url.
#  * Please do not remove this header.
#  * */

# Updates
#   Commented through with interspersed questions on
#     Thu May 14 16:17:07 AST 2020

script_name := tttest_fft_class.py

default: help  force_look

# Q:
#   Observe the script calls in the test recipes below.
#     Is there an alternative way of expressing any one of
#     the script calls?
#   Does each of the test recipes as a whole (i.e., target, 
#     dependencies, recipe) follow a pattern? Indicate the
#     the specifics.
test_dummy : force_look
	@./$(script_name) -e dummy

test_sine_cosine : force_look
	@./$(script_name) -e sine_cosine

test_step_function : force_look
	@./$(script_name) -e step_function

test_triangular : force_look
	@./$(script_name) -e triangular

clean : force_look
	@find . -name "*.pyc" -type f -delete
	
help : force_look
	@echo ""
	@echo "*** RECIPES ***"
	@echo "  default             - helps"
	@echo "  test_dummy          - calls indicated test"
	@echo "  test_sine_cosine    - calls indicated test"
	@echo "  test_step_function  - calls indicated test"
	@echo "  test_triangular     - calls indicated test"
	@echo "  clean"
	@echo "  help"

force_look :
	@true;