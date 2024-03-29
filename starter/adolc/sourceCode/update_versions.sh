WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#!/bin/bash

autoreconf -fi

./configure

pushd ADOL-C/doc

pdflatex adolc-manual.tex
pdflatex adolc-manual.tex
pdflatex adolc-manual.tex

latex adolc-manual.tex
latex adolc-manual.tex
latex adolc-manual.tex
dvips adolc-manual.dvi

popd
