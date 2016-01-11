

MAIN = bib.pdf
main: $(MAIN)

all: $(MAIN) h2r.pdf template.pdf mapred.pdf sdn.pdf bd.pdf bm.pdf site.pdf bib.pdf


%.pdf: %.tex
	latexmk -pdf -pdflatex="pdflatex -interactive=nonstopmode" -use-make $<

.PHONY: clean deepclean show

show:
	open $(MAIN)

clean:
	latexmk -CA

deepclean:
	-rm -f *.log *.aux *.dvi *.bbl *.blg *.ilg *.toc *.lof *.lot *.idx *.ind *.ps  *~


