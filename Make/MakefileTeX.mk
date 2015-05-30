
MAIN = main.pdf
main: $(MAIN)

all: $(MAIN)

%.pdf: %.tex
	latexmk -f -pdf -pdflatex="pdflatex -interactive=nonstopmode -shell-escape" -use-make $<

.PHONY: show linkbib unlinkbib linkcode unlinkcode clean deepclean

bibhome = /Users/LIYING/Bibliography
biblist = $(notdir $(wildcard $(bibhome)/*.bib))

linkbib:
	for bibfile in $(biblist); do ln -s $(bibhome)/$$bibfile $$bibfile; done
unlinkbib:
	for bibfile in $(biblist); do unlink $$bibfile; done

codehome = /Users/LIYING/Programming/algo/algo
codelist = $(notdir $(wildcard $(codehome)/*.c)) $(notdir $(wildcard $(codehome)/*.h))

linkcode:
	for codefile in $(codelist); do ln -s $(codehome)/$$codefile $$codefile; done
unlinkcode:
	for codefile in $(codelist); do unlink $$codefile; done

clean:
	latexmk -CA
deepclean: unlinkbib unlinkcode clean
	rm -f *.log *.aux *.dvi *.bbl *.blg *.ilg *.toc *.lof *.lot *.idx *.ind *.ps *.gnuplot *~ *gnuplotlatex* *gnuplottex*
show:
	open $(MAIN)
auto: clean main show


