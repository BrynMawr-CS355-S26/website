#! /bin/bash


/usr/local/bin/asciidoctor assts/*.adoc *.adoc labs/*.adoc
if [ $# -ge 1 ]; then
  git add .
  git commit -m "$1"
fi
if [ $# -ne 1 ]; then
  echo "specify message to commit changes"
fi
