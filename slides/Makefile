default: all

all: main1 bibli main2

main1:
	pdflatex slides.tex

bibli:
	bibtex slides.aux

main2:
	pdflatex slides.tex ; pdflatex slides.tex
