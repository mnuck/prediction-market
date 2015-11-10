.PHONY: clean All

All:
	@echo "----------Building project:[ Book - Debug ]----------"
	@cd "Book" && "$(MAKE)" -f  "Book.mk"
clean:
	@echo "----------Cleaning project:[ Book - Debug ]----------"
	@cd "Book" && "$(MAKE)" -f  "Book.mk" clean
