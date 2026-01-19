#! /bin/bash

asciidoctor assts/*.adoc notes/*.adoc labs/*.adoc *.adoc
git add .
git status
git commit -m "update website"
git push
