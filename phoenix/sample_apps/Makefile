include makefile.env

.PHONY: all clean

all:
	$(MAKE) -C histogram
	$(MAKE) -C kmeans
	$(MAKE) -C linear_regression
	$(MAKE) -C matrix_multiply
	$(MAKE) -C pca
# $(MAKE) -C reverse_index
	$(MAKE) -C string_match
	$(MAKE) -C word_count

clean:
	$(MAKE) -C histogram clean
	$(MAKE) -C kmeans	clean
	$(MAKE) -C linear_regression clean
	$(MAKE) -C matrix_multiply clean
	$(MAKE) -C pca clean
# $(MAKE) -C reverse_index clean
	$(MAKE) -C string_match clean
	$(MAKE) -C word_count clean
