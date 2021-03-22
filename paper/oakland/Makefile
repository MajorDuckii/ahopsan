#!/usr/bin/make

paper	:= ahopsan

all:
	pdflatex -synctex=1 -interaction=nonstopmode -shell-escape ${paper}.tex
	bibtex references
	pdflatex -synctex=1 -interaction=nonstopmode -shell-escape ${paper}.tex
	pdflatex -synctex=1 -interaction=nonstopmode -shell-escape ${paper}.tex


clean:
	@rm -rf _minted-${paper}
	@rm -rf *.cut
	@rm -rf ${paper}.aux  ${paper}.blog ${paper}.blg ${paper}.bbl ${paper}.log  ${paper}.out ${paper}.fls



