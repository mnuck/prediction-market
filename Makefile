.PHONY: clean All

All:
	@echo "----------Building project:[ Book-Test - Debug ]----------"
	@cd "Book-Test" && "$(MAKE)" -f  "Book-Test.mk"
clean:
	@echo "----------Cleaning project:[ Book-Test - Debug ]----------"
	@cd "Book-Test" && "$(MAKE)" -f  "Book-Test.mk" clean
