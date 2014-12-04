default: all

all: main1 bibli main2

main1:
	pdflatex main.tex

bibli:
	bibtex main.aux

main2:
	pdflatex main.tex ; pdflatex main.tex
