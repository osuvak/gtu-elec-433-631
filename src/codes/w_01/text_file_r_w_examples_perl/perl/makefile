# Onder Suvak (C) 2020

dname:=content
scriptname:=text_r_w.pl

default : clean operate force_look

operate : force_look
	@./$(scriptname)
	
exe_make : force_look
	@chmod +x ./$(scriptname)

exe_remove : force_look
	@chmod -x ./$(scriptname)

clean : force_look
	@mkdir -p $(dname) && cd ./$(dname) && rm -rf ./*
	
realclean : force_look
	@rm -rf ./$(dname)

help : force_look
	@echo ""
	@echo "***RECIPES***"
	@echo "  default  - cleans + operates"
	@echo "  operate  - runs the script"
	@echo "  exe_make - changes permissions to render script executable"
	@echo "  exe_make - changes permissions to remove script executability"
	@echo "  clean    - makes sure folder exists + clears its contents"
	@echo "  realclean- deletes folder together with its contents"
	
force_look :
	@true
